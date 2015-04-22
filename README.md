# facebooklet
======
cmps 1600 facebook "clone"

[documentation](

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

For this project, I have chosen to roughly emulate a model-view-controller
architecture as a way of separating concerns of the various classes. The IFacebookletNode,
Profile, Database, and NodeData classes make up the model by manipulating and storing data.

The Prompter class handles user input. It is given instructions from the Facebooklet instance,
and provides promts and parses input. Rather than using std::cin dirrectly, it takes a std::istream
object reference. This allows for easier testing, as you can pass in a stringstream object
to emulate user input (this can be seen in the test cases of test/engine_tests.c).

Finally, The
Facebooklet class acts as the controller. It provides an interface between the model and the
user interactions handled by Prompter, such as adding users or posts. It also provides
the program's main loop method.

