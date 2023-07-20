$env:GAMENAME="BowlingObstacle"
$env:BUILD_CONFIG="Development"
$env:MAPS="Map1+Map2+Map3+Map4+Map5+Map6+Map7+Map8+Map9+Map10"
$env:CLEAN=$false

$env:WORKSPACE=$env:BG

# Jenkins uses a Game Subfolder
$env:GAME_DIR="${env:WORKSPACE}"
#$env:GAME_DIR="${env:WORKSPACE}\\Game"

$PROJECT="${env:GAME_DIR}\\${env:GAMENAME}.uproject"
$ENGINE="${env:UEng}\\Engine"							
$ENGINE_BIN="$ENGINE\\Binaries\\Win64"

Remove-Item -Path "${env:WORKSPACE}\\Android\\" -recurse -ErrorAction Ignore
Remove-Item -Path "${env:WORKSPACE}\\Android_ASTC\\" -recurse -ErrorAction Ignore
Remove-Item -Path "${env:GAME_DIR}\\Intermediate\\Android\\" -recurse -ErrorAction Ignore

# Used to cleanup symbol uploads to help build times
Remove-Item -Path "${env:GAME_DIR}\\Binaries\\Android\\" -recurse -ErrorAction Ignore

$UBTARGS="-Upgrades -GooglePlay"
$EXTRA=@()

If ($env:CLEAN -eq "true")
{
	$EXTRA += "-clean"

	Remove-Item -Path "${env:GAME_DIR}\\Binaries\\" -recurse -ErrorAction Ignore
	Remove-Item -Path "${env:GAME_DIR}\\Intermediate\\" -recurse -ErrorAction Ignore
	Remove-Item -Path "${env:GAME_DIR}\\Saved\\" -recurse -ErrorAction Ignore
	Remove-Item -Path "${env:GAME_DIR}\\DerivedDataCache\\" -recurse -ErrorAction Ignore
	Remove-Item -Path "${env:ENGINE}\\DerivedDataCache\\" -recurse -ErrorAction Ignore
}

# Ensure Sharing of Material / Native Libs
(gc $env:GAME_DIR\\Config\\DefaultGame.ini) -replace "bShareMaterialShaderCode=False", "bShareMaterialShaderCode=True" | Out-File $env:GAME_DIR\\Config\\DefaultGame.ini -Encoding utf8
(gc $env:GAME_DIR\\Config\\DefaultGame.ini) -replace "bSharedMaterialNativeLibraries=False", "bSharedMaterialNativeLibraries=True" | Out-File $env:GAME_DIR\\Config\\DefaultGame.ini -Encoding utf8

# App Bundle Specific Options Setup
(gc $env:GAME_DIR\\Config\\DefaultEngine.ini) -replace "bPackageDataInsideApk=False", "bPackageDataInsideApk=False" | Out-File $env:GAME_DIR\\Config\\DefaultEngine.ini -Encoding utf8
(gc $env:GAME_DIR\\Config\\DefaultEngine.ini) -replace "bForceSmallOBBFiles=False", "bForceSmallOBBFiles=True" | Out-File $env:GAME_DIR\\Config\\DefaultEngine.ini -Encoding utf8
(gc $env:GAME_DIR\\Config\\DefaultEngine.ini) -replace "bEnableBundle=False", "bEnableBundle=True" | Out-File $env:GAME_DIR\\Config\\DefaultEngine.ini -Encoding utf8
(gc $env:GAME_DIR\\Config\\DefaultEngine.ini) -replace "bAllowPatchOBBFile=True", "bAllowPatchOBBFile=False" | Out-File $env:GAME_DIR\\Config\\DefaultEngine.ini -Encoding utf8

# Clean asset packs from previous builds for a clean state
Remove-Item -Path "${env:GAME_DIR}\\Build\\Android\\gradle\\assetpacks\\" -recurse -ErrorAction Ignore

# Base Build (No Package or Archive)
& "$ENGINE\\Build\\BatchFiles\\RunUAT" "BuildCookRun" "-project=${PROJECT}" "-ubtargs=$UBTARGS" "-noP4" "-iostore" "-distribution" "-targetplatform=Android" "-cookflavor=ASTC" "-utf8output" "-clientconfig=${env:BUILD_CONFIG}" "-SkipCookingEditorContent" "-cook" "-map=${env:MAPS}" "-unversionedcookedcontent" "-createreleaseversion=GameVersion0" "-build" "-stage" "-pak" "-SkipArchive" "-SkipPackage" @EXTRA
If ($LASTEXITCODE -ne 0)
{
	echo "ERROR in BuildCookRun"
	pause
	exit $LASTEXITCODE
}

$DELETE_FILE="${env:GAME_DIR}\\Saved\\Cooked\\Android_ASTC\\Engine\\Content\\EngineMaterials\\DefaultBloomKernel.uexp"

Remove-Item "${DELETE_FILE}" -Force

# Final Package
& "$ENGINE\\Build\\BatchFiles\\RunUAT" "BuildCookRun" "-project=$PROJECT" "-ubtargs=$UBTARGS" "-noP4" "-iostore" "-distribution" "-targetplatform=Android" "-cookflavor=ASTC" "-utf8output" "-clientconfig=${env:BUILD_CONFIG}" "-nocompile" "-skipcook" "-skippak" "-skipstage" "-package" "-createreleaseversion=GameVersion0" "-archive" "-archivedirectory=$env:WORKSPACE" @EXTRA

If ($LASTEXITCODE -ne 0)
{
	echo "ERROR in BuildCookRun"
	pause
	exit $LASTEXITCODE
}

echo "Done"

pause