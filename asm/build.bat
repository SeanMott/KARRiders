gecko.exe assemble -o codes.gct
code_merge.exe codes.gct AdditionalCodes.txt
xcopy /s /y "codes.gct" "../FileSystem/files/codes.gct"
gecko.exe assemble -o codes.ini
pause