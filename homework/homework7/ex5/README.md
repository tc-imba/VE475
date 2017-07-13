# Ex.5 Readme File

## Compilation

This program is written in c++, built and tested under Linux (Ubuntu 17.04), with cmake > 3.5, and the GMP Library is used. It can be installed by
```
$ sudo apt-get install libgmp-dev
```
The CMakeLists file will find `libgmp.so` and `libgmpxx.so` under `/usr/lib` if you've installed it correctly.

You can generate the Makefile by
```
$ sudo apt-get install cmake
$ cmake ./
```
You need to generate it yourself due to some cross-platform issues. (You can also use the Makefile in this directory, but perhaps it won't work)

## Description

In the `main` function, five big integers (a,b,x,y,n) are generated randomly and in the `normal` and `faster` functions, two methods of computing `a^xb^y mod n` are implemented. The time used by each function is printed.

We can find that the second function is 30-40% faster than the first one.

