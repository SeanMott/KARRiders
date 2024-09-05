#compiles the Assembly into a gct and .ini files and injects in the file system

gecko.exe assemble -o codes.gct
code_merge.exe codes.gct AdditionalCodes.txt
xcopy /s /y "codes.gct" "../FileSystem/files/codes.gct"
gecko.exe assemble -o codes.ini
pause