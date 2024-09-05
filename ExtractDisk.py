#extracts your chosen ROM, generating a filesystem we can use use to inject custom Riders

import os
import subprocess
import sys
import shutil

#performs a extracttion
def Extract(rom):

    workingDir = os.path.dirname(__file__)
    filesystemOutput = workingDir + "/FileSystem"

    #deletes the old filesystem if it exists
    if os.path.exists(filesystemOutput):
        shutil.rmtree(filesystemOutput)

    #validates the ROM

    #generates a new one
    command = ['Tools/Windows/dtk.exe', 'disc', 'extract', rom, filesystemOutput]
    subprocess.run(command)

#no args
def NoArgs():
    print("A rom path must be given to the program to generate a FileSystem.")
    print("EXAMPLE: \"ExtractDisk.py -rom \"C:/Users/Jas/Desktop/HackPack.iso\"")
    print("Please run this script again with the ROM path given.")

#only rom flag
def OnlyRomFlag():
    print("You passed just the ROM flag, we need a path as well.\n\n")
    NoArgs()

#unknown flag
def UnknownFlag(flag):
    print("We couldn't understand \"", flag, "\", please check your spelling and have spaces between arguments.\n\n")
    NoArgs()

#------main----------#
args = len(sys.argv)
argv = sys.argv

#if nothing was passed in
if(args == 1):
    NoArgs()

#if just rom was passed
if(args == 2 and argv[1] == "-rom"):
    OnlyRomFlag()

#if we can't desern the extra arg
if(args == 2 and argv[1] != "-rom"):
    UnknownFlag(argv[1])

#if rom and path was passed
if(args == 3 and argv[1] == "-rom"):
    Extract(argv[2])