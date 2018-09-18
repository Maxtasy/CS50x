# Questions

## What's `stdint.h`?

With stdint.h we can set specific widths for integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

We can declare how many bits make up a specific data type.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 and 0x4d

## What's the difference between `bfSize` and `biSize`?

bfSize gives information about the size (in bytes) of the bitmap file.
biSize gives information about the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

A negative biHeight indicates that the bitmap is in top-down order, meaning the triples information starts at the top left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file might not exist.

## Why is the third argument to `fread` always `1` in our code?

We are reading/processing 1 element at a time. First 1 BITMAPFILEHEADER, then 1 BITMAPINFOHEADER and then 1 TRIPLE in each iteration of the for loop.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

With fseek() we can place the "cursor" (position indicator) at a specific place in the file.

## What is `SEEK_CUR`?

The current position of the "cursor" (position indicator) in the file.

## Whodunit?

It was Professor Plum with the candlestick in the library
