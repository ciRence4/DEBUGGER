@echo off
gcc -o debugger.exe main.c dialogue.c bosses.c ui.c file.c game.c
if %errorlevel% == 0 (
    echo.
    echo Build successful! Run with: debugger.exe
) else (
    echo Build failed.
)
