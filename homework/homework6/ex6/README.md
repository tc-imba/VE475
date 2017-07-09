# Ex.6 Readme File

## Compilation

This program is written in c, built and tested under Linux (Ubuntu 17.04), with cmake > 3.5

You can generate the Makefile by
```
$ sudo apt-get install cmake
$ cmake ./
```
You need to generate it yourself due to some cross-platform issues. (You can also use the Makefile in this directory, but perhaps it won't work)

## Description

Input a number n, the algorithm will find nontrivial factors of n.

Note that the algorithm may fail to find a nontrivial factor even when n is composite.