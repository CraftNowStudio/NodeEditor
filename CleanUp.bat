@echo off
setlocal enabledelayedexpansion

set ROOT_DIR=%~dp0

set FILE_LIST=(
	*.vcxproj
	*.vcxproj.*
	*.sln
)

for /r "%ROOT_DIR%" %%d in (.) do (
	for %%f in %FILE_LIST% do (
		echo Delete "%%d\%%f"
		del /q "%%d\%%f" 2>nul
	)
)

echo Clean up completed.
endlocal
pause