libarg3dice
===========

A c++11 library for working with dice.  Implementations for different dice games (Yahtzee, etc.)

Building
========

Requires [autotools](http://en.wikipedia.org/wiki/GNU_build_system).

```bash
./configure --prefix=/usr/local

make
```

Coding Style
============

- class/struct/method names are all lower case with underscores separating words
- non public members are camel case with and underscore at end of the name
- macros, enums and constants are all upper case with underscores seperating words
- braces on a new line

Examples
========

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

