# ImageManip: A Command-Line Image Processing Tool

ImageManip is a lightweight, command-line utility designed for basic image processing tasks with support for PPM (Portable PixMap) and PGM (Portable GrayMap) formats. It allows users to copy images, convert PPM images to grayscale PGM images, and shrink PGM images with ease.

## Features

- **Copy Image**: Duplicate PPM or PGM images.
- **Convert to Grayscale**: Convert color PPM images to grayscale PGM images.
- **Shrink Image**: Reduce the size of PGM images by half.

## Getting Started

### Prerequisites

- GCC compiler
- Make (optional for compilation automation)

### Compiling

To compile ImageManip, navigate to the project directory and run:

```bash
gcc -o ImageManip interface.c image.c -I.
