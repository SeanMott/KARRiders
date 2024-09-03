SET "TKPATH=../../../MexTK/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "marx.c" -s rdFunction -dat "../../../FileSystem/files/RdExtMarx.dat"

pause