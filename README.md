# facebooklet
======
cmps 1600 facebook "clone"

compilation instruction
------
* option 1: compile source directory files

``` bash
$ cd src
# compile (with dialect set to C++ 2011)
$ c++ -std=c++11 *.cc -o fb
$ ./fb
```

* option 2: use cmake (allows running unit tests)
``` bash
$ mkdir build
$ cd build
$ cmake ..
$ make

# run tests
$ ./facebooklet_tests

# run main program
$ ./facebooklet_exec
```

* option 3: run project from my [github page](http://dangerbird2.github.io/facebooklet)
    * precompiled from c++ to javascript with [emscripten](http://kripken.github.io/emscripten-site/index.html)
