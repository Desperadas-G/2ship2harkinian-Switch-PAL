# Generates mm.o2r from your own Majora's Mask ROM, on Windows, with no install.
# Used by "Generate mm.o2r.bat" in the Windows release zip:
#
#   <zip root>\Generate mm.o2r.bat
#   <zip root>\generator\        ZAPD.exe, this script, assets\, portver.txt
#   <zip root>\switch\2s2h\      2ship.nro, 2ship.o2r, and mm.o2r once generated
#
# The ROM can be dropped on the .bat, placed in the zip root, or picked in a dialog.
# .z64, .n64, .v64 and a .zip holding one of them are accepted.
param([string]$RomPath)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$root = Split-Path -Parent $here
$outDir = Join-Path $root 'switch\2s2h'
$romExt = @('.z64', '.n64', '.v64')

function Fail([string]$msg) {
    Write-Host ""
    Write-Host "ERROR: $msg" -ForegroundColor Red
    exit 1
}

Add-Type -AssemblyName System.IO.Compression.FileSystem
Add-Type @'
public static class RomTools {
    // Returns 0 if already big-endian (.z64), 1 if byte-swapped (.v64), 2 if little-endian (.n64), -1 if unknown.
    public static int ToBigEndian(byte[] d) {
        if (d.Length < 0x40) return -1;
        if (d[0] == 0x80 && d[1] == 0x37 && d[2] == 0x12 && d[3] == 0x40) return 0;
        if (d[0] == 0x37 && d[1] == 0x80 && d[2] == 0x40 && d[3] == 0x12) {
            for (int i = 0; i + 1 < d.Length; i += 2) { byte t = d[i]; d[i] = d[i + 1]; d[i + 1] = t; }
            return 1;
        }
        if (d[0] == 0x40 && d[1] == 0x12 && d[2] == 0x37 && d[3] == 0x80) {
            for (int i = 0; i + 3 < d.Length; i += 4) {
                byte a = d[i], b = d[i + 1];
                d[i] = d[i + 3]; d[i + 1] = d[i + 2]; d[i + 2] = b; d[i + 3] = a;
            }
            return 2;
        }
        return -1;
    }
}
'@

# 1. Find the ROM
if (-not $RomPath) {
    $found = @(Get-ChildItem -LiteralPath $root -File | Where-Object { ($romExt + '.zip') -contains $_.Extension.ToLower() })
    if ($found.Count -eq 1) {
        $RomPath = $found[0].FullName
    } else {
        Add-Type -AssemblyName System.Windows.Forms
        $dlg = New-Object System.Windows.Forms.OpenFileDialog
        $dlg.Title = "Select your Majora's Mask ROM"
        $dlg.Filter = "N64 ROM (*.z64;*.n64;*.v64;*.zip)|*.z64;*.n64;*.v64;*.zip"
        $dlg.InitialDirectory = $root
        if ($dlg.ShowDialog() -ne [System.Windows.Forms.DialogResult]::OK) { Fail "No ROM selected." }
        $RomPath = $dlg.FileName
    }
}
if (-not (Test-Path -LiteralPath $RomPath -PathType Leaf)) { Fail "File not found: $RomPath" }
Write-Host "ROM: $RomPath"

# 2. Read it (from inside a .zip if needed)
if ([IO.Path]::GetExtension($RomPath).ToLower() -eq '.zip') {
    $zip = [IO.Compression.ZipFile]::OpenRead($RomPath)
    try {
        $entry = $zip.Entries | Where-Object { $romExt -contains [IO.Path]::GetExtension($_.Name).ToLower() } | Select-Object -First 1
        if (-not $entry) { Fail "No .z64/.n64/.v64 file inside this zip." }
        Write-Host "  using $($entry.Name) from the zip"
        $data = New-Object byte[] $entry.Length
        $s = $entry.Open()
        try {
            $off = 0
            while ($off -lt $data.Length) {
                $n = $s.Read($data, $off, $data.Length - $off)
                if ($n -le 0) { break }
                $off += $n
            }
        } finally { $s.Dispose() }
    } finally { $zip.Dispose() }
} else {
    $data = [IO.File]::ReadAllBytes($RomPath)
}

# 3. Check the format and version
if ([RomTools]::ToBigEndian($data) -lt 0) { Fail "This is not an N64 ROM (unknown header)." }
if ($data.Length -lt 20MB) { Fail "This ROM is too small to be Majora's Mask." }
$crc = ($data[0x10..0x13] | ForEach-Object { $_.ToString('X2') }) -join ''
$versions = @{
    '0A5D8F83' = @('MM_PAL_11', 'PAL 1.1 / Rev A (Europe)')
    '5354631C' = @('N64_US', 'NTSC-U 1.0 (USA)')
    'DA6983E7' = @('N64_US', 'NTSC-U 1.0 (USA, uncompressed)')
    'B443EB08' = @('GC_US', 'NTSC-U GameCube')
}
if ($crc -eq 'E97955C6') { Fail "PAL 1.0 ROM (CRC E97955C6). Only PAL 1.1 / Rev A is supported." }
if (-not $versions.ContainsKey($crc)) { Fail "Unsupported ROM (header CRC $crc). See the README for the supported versions." }
$xmlVer = $versions[$crc][0]
Write-Host "Version: $($versions[$crc][1]), CRC $crc"

# 4. Run ZAPD. It runs from this folder with relative paths only, so that
# accented or unusual characters in the user's paths can't break it.
if (-not (Test-Path -LiteralPath (Join-Path $here 'ZAPD.exe'))) {
    Fail "generator\ZAPD.exe is missing. Extract the whole zip again (your antivirus may have removed it)."
}
$portVer = (Get-Content -LiteralPath (Join-Path $here 'portver.txt') -TotalCount 1).Trim()
$work = Join-Path $here 'baserom.z64'
$tmpOut = Join-Path $here 'mm.o2r'
[IO.File]::WriteAllBytes($work, $data)
$data = $null
Remove-Item -LiteralPath $tmpOut -ErrorAction SilentlyContinue

Write-Host ""
Write-Host "Extracting the game assets, this takes about a minute..."
try {
    # ZAPD prints thousands of harmless warnings: keep them in logs, not on screen
    $zapdArgs = "ed -i assets/xml/$xmlVer -b baserom.z64 -fl assets/extractor/filelists " +
        "-o placeholder -osf placeholder -rconf assets/extractor/Config_$xmlVer.xml " +
        "-gsf 0 -se OTR --otrfile mm.o2r --portVer $portVer"
    $p = Start-Process -FilePath (Join-Path $here 'ZAPD.exe') -ArgumentList $zapdArgs -WorkingDirectory $here `
        -RedirectStandardOutput (Join-Path $here 'zapd.log') -RedirectStandardError (Join-Path $here 'zapd-errors.log') `
        -NoNewWindow -Wait -PassThru
    $code = $p.ExitCode
} finally {
    Remove-Item -LiteralPath $work -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath (Join-Path $here 'placeholder') -Recurse -Force -ErrorAction SilentlyContinue
}
if ($code -ne 0 -or -not (Test-Path -LiteralPath $tmpOut) -or (Get-Item -LiteralPath $tmpOut).Length -lt 1MB) {
    Fail "Extraction failed (exit code $code). Details in generator\zapd.log and generator\zapd-errors.log."
}

New-Item -ItemType Directory -Force -Path $outDir | Out-Null
Move-Item -LiteralPath $tmpOut -Destination (Join-Path $outDir 'mm.o2r') -Force
Remove-Item -LiteralPath (Join-Path $here 'zapd.log'), (Join-Path $here 'zapd-errors.log') -ErrorAction SilentlyContinue

Write-Host ""
Write-Host "Done: switch\2s2h\mm.o2r was created." -ForegroundColor Green
Write-Host "Copy the 'switch' folder to the root of your SD card, then launch 2Ship from the Homebrew Menu"
Write-Host "(hold R while starting a game). Never share your mm.o2r."
