# Questions

## What's `stdint.h`?
Use it if you would like your program to work universally in any system environments, because otherwise you cannot be sure that the actual size of int will always be 32 bits, and long long will always be 64 bits. If you inclue this header, it contains the definition of new integer types, like it guarantees that an integer type int32_t has 32 bits anywhere.

TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
It is a cross-platform implementation of a standard data type, uint8_t is an unsigned int of 8 bits wide.

TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
BYTE: 1 x 8 bit -> 1 byte
DWORD: 4 bytes
WORD: 2 bytes
LONG: 4 bytes
 
TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
ASCII: the first 2 bytes of the BMP file format are the character "B" then the character "M" that identify the file type.

TODO

## What's the difference between `bfSize` and `biSize`?
- bfSize = biSizeImage + sizeof(BITMAPFILEHEADER(14)) + sizeof(BITMAPINFOHEADER(40)) ->  is the full file size of the bitmap image
- biSize = sizeof(BITMAPINFOHEADER) = 40 bytes



TODO

## What does it mean if `biHeight` is negative?
The image is top-down.

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

TODO

## Why is the third argument to `fread` always `1` in our code?

TODO

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

TODO

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO

## Whodunit?

TODO
