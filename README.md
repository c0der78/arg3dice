libarg3dice
===========


[![Build Status](http://img.shields.io/travis/deadcoda/arg3dice.svg)](https://travis-ci.org/deadcoda/arg3dice)
[![Coverage Status](https://coveralls.io/repos/deadcoda/arg3dice/badge.svg?branch=master&service=github)](https://coveralls.io/github/deadcoda/arg3dice?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://deadcoda.mit-license.org)

A c++11 library for working with dice.  Implementations for different dice games (Yahtzee, etc.)

Building
--------

After cloning run the following command to initialize submodules:

```bash

git submodule update --init --recursive
```

you can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug; 
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

options supported are:

    -DCODE_COVERAGE=ON   :   enable code coverage using lcov
    -DMEMORY_CHECK=ON    :   enable valgrind memory checking on tests

Examples
--------

*Simple Example*

```c++
arg3::dice d10(10, 10); // 10 dice with 10 sides each

d10.roll(); // random value
```

*Complex Example*

```c++
class logger_die_engine : public arg3::die::engine
{
public:
    die::value_type generate(die::value_type from, die::value_type to)
    {
    	// pseudo code
    	auto value = generate_random_number(from, to);

    	cout << "Generated random number: " << value << endl;

    	return value;
    }
};

logger_die_engine my_engine;

arg3::dice d10(10, 10, &my_engine);

d10.roll(); // logs the random number
```

