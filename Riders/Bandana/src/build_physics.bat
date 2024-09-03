SET "TKPATH=../../../MexTK/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "bandana.c" -s rdFunction -dat "../../../FileSystem/files/RdExtWaddle.dat" -ow 

pause