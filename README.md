# BMP PROCCESING

A simple project that work with BMP images in C.


## `Table of Contents`

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [App](#app)

## `Introduction`

The project helps you to modify a BMP image in console,
it's a simple project than can draw lines,squars and triangles of 
different colors on a new  BMP image.


## `Installation`

```bash
    $> git clone https://github.com/IntoParadox/bmp-processor.git
    $> cd bmp-processor
    $> cd build
    $> make

    # ...
    $> ls
    $> Makefile sbmp3
```

If you want to install the executable in your path:

```bash
    $> export PATH=$PATH:$PWD
```

## `Usage`

Trigger the usage menu by:

```bash
    $> sbmp3
    Usage: sbmp3 [file input.bmp] [file output.bmp]
```

The application waits for a **valid** bmp3 file and writes the output to another file

>**NOTE:** The input file can be the same as the output file.

## `App`

In order to see the *available* options, a pop-up menu will be triggered when the app is opened.

>**NOTE:** Every option has a pop-up instructions for its execution.








