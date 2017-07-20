Dectable
========

Dectable is a small library to implement [decision table](https://en.wikipedia.org/wiki/Decision_table) in C++ 98.

For now, it handles only a set of string as input and a set of string as output. Tables can be hard coded or read from file.

Installation
------------

Clone the repository then run from the top of the tree:
```
mkdir build
cd build
cmake -D:TEST=1 .. # Remove -D:TEST=1 if you only want to build the lib.
make all
make test  # optional
```

Usage
-----

See [test/PermissionsExample.cpp](test/PermissionsExample.cpp) for a usage example.

