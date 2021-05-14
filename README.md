# libhare

A very thin and inexpensive layer above common C headers.

## Usage

    cd $HOME
    git clone https://github.com/hareat/libhare.git
    gcc -I$HOME/libhare/include

And in your code use `#include <hare/wrap/stdio.h>` instead of `#include <stdio.h>`
if you want to use a wrapped FILE*.

## Source code formatting

[Wikipedia about indentation style](https://en.wikipedia.org/wiki/Indentation_style)

I have decided using 1TBS because the code should be very simple and therefore
structuring empty lines can be avoided.
