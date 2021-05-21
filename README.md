## Table of contents
* [General info](#general-info)
* [Setup](#setup)
* [Example runs](#example)
* [Status](#status)

## General info
#### Archiwizator - archiver
- This program compresses files
- Creates one file with all informations
- From this archive file you can restore saved files

## Setup
To run this project:
- You need download Archiwizator.exe from repo
- With command line you need run Archiwizator.exe
#### Program can be run with 3 ways
- First - run .exe without any switches, but then you get an error and instruction what to do
- Second - run .exe with -o switch, then you have acces to operate on archive without options making new files 
- Third - run .exe after two or more arguments, the first specifies the directory location, second and next files

## Example runs
#### You can run program with:
- First way
```
Archiwizator.exe
```
- Second way
```
Archiwizator.exe -o
```
- Third way
```
Archiwizator.exe Catalog1/Catalog2/CatalogNEW TxtFile.txt BinFile.bin ...
```

## Status
- Finished
