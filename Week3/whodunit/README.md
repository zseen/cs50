# Questions

## What's `stdint.h`?
It is a header that contains the definition of new integer types, like it guarantees that an integer type int32_t has 32 bits anywhere.
Use it if you would like your program to work universally in any system environments, because otherwise you cannot be sure that the actual size of int will always be 32 bits, and long long will always be 64 bits.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
It is a cross-platform implementation of a standard data type, uint8_t is an unsigned int of 8 bits wide.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
BYTE: 1 x 8 bit -> 1 byte
DWORD: 4 bytes
WORD: 2 bytes
LONG: 4 bytes


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
ASCII: the first 2 bytes of the BMP file format are the characters "B" and "M" that identify the file type.


## What's the difference between `bfSize` and `biSize`?
- bfSize = biSizeImage + sizeof(BITMAPFILEHEADER(14)) + sizeof(BITMAPINFOHEADER(40)) ->  it is the full file size of the bitmap image
- biSize = sizeof(BITMAPINFOHEADER) = 40 bytes


## What does it mean if `biHeight` is negative?
The bitmap is a top-down DIB (device-independent bitmap) and its origin is the upper-left corner.


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
The BiBitCount.


## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
Because it cannot find or create the requested files.


## Why is the third argument to `fread` always `1` in our code?
Because it reads 1 RGBTRIPLE struct at a time.


## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
--> padding = (4 - (3 * 3) % 4) %4)
--> padding = (4 - 1) % 4;
--> padding = 3


## What does `fseek` do?
It sets the file position of the stream pointer to a new position (by the given offset).


## What is `SEEK_CUR`?
It moves a file pointer position to a given location and the new file position will be the current position plus offset (in bytes).


## Whodunit?
It was Professor Plum with the candlestick in the library.
