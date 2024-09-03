SET "TKPATH=../../MexTK/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "magolor.c" -s rdFunction -dat "../../FileSystem/files/RdExtMagolor.dat" -ow 

pause