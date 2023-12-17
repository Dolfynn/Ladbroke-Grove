@echo off
gcc -o IDE IDE.c parser.c lexer.c interpreter.c -I.
IDE
echo.
pause
