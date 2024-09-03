SET "TKPATH=../../MexTK/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "gooey.c" -s rdFunction -dat "../../FileSystem/files/RdExtGooey.dat" -ow 

pause