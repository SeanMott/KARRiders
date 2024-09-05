# KARRiders
A resurection of Ploaj's work on alt KAR Riders

# Requried

- Python 3 or higher

## How To Build

1. Run `ExtractDisk.py` passing the `-rom <pathToYourROM>` ie `ExtractDisk.py -rom "C:/Users/Jas/Desktop/HackPack.iso`, this will generate a fresh ISO filesystem to edit.

2. Run `ASMCompile.py`, this will compile the assembly needed and inject it into the FileSystem

2. pick your Rider, go into their folder and run `Build.py` to compile all the content and inject it into your filesystem

## How To Make A Rider