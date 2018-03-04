@echo off
:begin
python maker.py
echo std
std.exe < data.in > std.out
echo bf
BF.exe < data.in > BF.out
fc std.out BF.out
if ERRORLEVEL 1 goto wa
goto begin
:wa
echo wa
pause
