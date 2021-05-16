# libhare

A very thin and inexpensive layer above common C headers.

## Usage

    cd $HOME
    git clone https://github.com/hareat/libhare.git
    gcc -I$HOME/libhare/include

And in your code use `#include <hare/wrap/stdio.h>` instead of `#include <stdio.h>`
if you want to use a wrapped FILE*.

### Example

For many example usages see subdirectory test/.

    #include <hare/algorithm>
    #include <hare/numeric>
    const std::vector<int> vi = {1, 2, 3};
    // use of STL without the need of <algorithm>(vi.begin(), vi.end()...
    std::cout << hare::any_of(vi, 2));      // prints "1" meaning "true"
    std::cout << hare::accumulate(vi, 0));  // prints "6"

    #include <hare/throws/stdio.h>
    #include <hare/wrap/stdio.h>
    // hare::FILE autmatically closes an open file pointer
    const hare::FILE fp(hare::throws::fopen(<your path>, "w"));
    hare::throws::fputs(data, fp);  // throws in case of an error
    fputs(data, fp);  // if you do not care about a successful write

### Usage Arduino IDE

    ... after the steps above ...
    cd <sketchbook location>/libraries
    ln -s $HOME/libhare/include/ libhare

And in your sketch before the first use of `#include <hare/......h>` you have to
`#include <esp_enable_subdir_hare.h>` first (which is an empty file).
Once I have just found out this hack without the reason why.

    #include <esp_enable_subdir_hare.h>
    #include <hare/esp....h>

## Source code formatting

[Wikipedia about indentation style](https://en.wikipedia.org/wiki/Indentation_style)

I have decided using 1TBS because the code is be very simple and therefore
structuring empty lines are not so necessary.
