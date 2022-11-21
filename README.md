# Game Engine

A simple game engine.

## Usage

To build and run the application run the following commands.

```
cmake -S <path to GameEngine> -B build -DCMAKE_BUILD_TYPE=Release
cd build
make
./GameEngine
```

### Documentation

To build the documentation run the following commands.

```
cmake -S <path to GameEngine> -B build
cd build
make doc
```

The generated documentation can be found in `html/index.html`.

### Test

To build and run the tests run the following commands.

```
cmake -S <path to GameEngine> -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd build
make
ctest --verbose
```

Note that `ctest` have other flags that can e.g. select which tests to run. Also note that is is
built using the `RelWithDebInfo` configuration. This includes address sanitizer (asan) and
undefined behavior sanitizer (ubsan). These are runtime instrumentations that will detect memory
errors and undefined behavior. The `RelWithDebInfo` configuration also includes debug information
which makes it easier to find where a particular problem occurred as it will contain a detailed
call stack.

#### Test Coverage

Test coverage is a useful tool that measures how much of the source code is covered by tests. To
build and run test coverage, run everything in the previous section and then run the following
command.

```
make lcov
```

The test coverage report can be found in `lcov/index.html`.

#### Test under valgrind

To build and run the tests under valgrind run the following commands.

```
cmake -S <path to GameEngine> -B build -DCMAKE_BUILD_TYPE=Debug
cd build
make
ctest -T memcheck --verbose
```

Note that the `Debug` configurations is used here. This configuration includes debug information
which makes it easier to find where a particular problem occurred as it will contain a detailed
call stack. Unfortunately valgrind is not compatible with the sanitizers used in the
`RelWithDebInfo` configuration. To get full coverage of the dynamic code analyzers it is therefore
required to run the test under two configurations (`RelWithDebInfo` and `Debug` with valgrind).

### Requirements

The following are required

* gcc
* cmake
* doxygen
* graphviz
* cppcheck
* clang-tidy
* valgrind
* lcov

On an Ubuntu system these can be installed with the following commands.

```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt autoremove -y
sudo apt-get install gcc -y
sudo apt-get install cmake -y
sudo apt-get install doxygen -y
sudo apt install graphviz -y
sudo apt-get install cppcheck -y
sudo apt-get install clang-tidy -y
sudo apt install valgrind -y
sudo apt install lcov -y
```
