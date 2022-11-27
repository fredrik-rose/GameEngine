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
build and run test coverage, run the following command.

```
cmake -S <path to GameEngine> -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd build
make
ctest --verbose -E GameTests
make lcov
```

Note that the `GameTests` is excluded as it does not perform a proper functionality test and it is
unfair to include it in the coverage report. The test coverage report can be found in
`lcov/index.html`.

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
call stack. Asserts are enabled in this configuration. Unfortunately valgrind is not compatible with
thes anitizers used in the `RelWithDebInfo` configuration. To get full coverage of the dynamic code
analyzers it is therefore required to run the test under two configurations (`RelWithDebInfo` and
`Debug` with valgrind).

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
* include-what-you-use

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
sudo apt install iwyu -y
```

## Architecture

This chapter describes all modules of the game engine.

### Base

Contains utilizes needed by most other modules. This includes math functions and helper macros to
e.g. specify unused function parameters and get the length of an array.

### Engine

This is the core of the game engine. It is build of of several units.

#### Camera

The camera of the game. Defines the camera intrinsic (focal length, principal point, etc.) and
extrinsic (camera position in relation to the world coordinate system) calibration.

#### Coordinate System Transformations

Provides functionality to convert 3D coordinates from one coordinate frame to another (linear and
affine transformations). It can also convert a 3D world coordinate to a 2D image coordinate.

#### Frame Synchronizer

A faster or slower computer should not make the time go faster or slower in the game. This unit
makes sure the game run in a certain constant frame rate.

#### Illumination

Handles the illumination of objects.

#### Object

The interface of a 3D objects.

#### Renderer

The heart of the engine. This unit takes a model consisting of 3D objects and their positions, a
camera calibration and a light source as input. The input is rendered and output to the screen. To
accomplish this it uses all other units of the Engine module.

<img src="img/Renderer_pipeline.png" width="1200"/>

### Game

A game implemented using the game engine. Well, it is not really a game, it just a sphere orbiting
a rotating torus ("donut").

### Linear Algebra

Defines matrix, vector, and function that operates on these types. Some example functions are
matrix matrix multiplication, matrix vector multiplication, matrix transpose, vector normalization
and vector dot product.

### Test Framework

A simple "home made" test framework. It lacks a lot of features like setup/teardown, fixtures,
mocks, etc., but using it in conjunction with `ctest` it is sufficient for a small project like
this. There exists a lot of test frameworks for C but not really any "standard" one that most
project uses.

#### Example

The following is an example of a test suite that uses the framework.

```
#include "TestFramework/test_framework.h"

int TF_test_case_status; /* All test suites must define this global variable. */

static void test_my_function_a(void)
{
    TF_assert(my_function_a(1) == 4);
}

static void test_my_function_b(void)
{
    TF_assert(my_function_b(1) == 2);
}

int main(void)
{
    TF_test_case test_cases[] = {
        test_my_function_a,
        test_my_function_b,
    };

    return TF_run_suite(test_cases, 2);
}
```

## Dependency Graph

It is possible to generate dependency graphs using `cmake`. To generate this graph run `cmake` as
usual but append `--graphviz=dependendy_graph.dot` to the command. An image of the graph can then
be generated by running the following command.

```
dot -Tpng -o build/dependendy_graph.png dependendy_graph.dot
```

## TODO

* Find a good way to temporarily disable printf output to not clutter output for some test.
* Add unit test for the Renderer unit. This can be done by creating simple objects like planes with
  constant surface normals. Then it is possible to test if the projections get the correct size in
  the image and that they occlude eachother correctly. It is also a good idea to test that objects
  behind the camera or outside the frame are handled correctly.
