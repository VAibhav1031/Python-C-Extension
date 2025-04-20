# Python C Extension Modules

This repository demonstrates how to create Python extensions in C for improved performance and system-level integration.

## Table of Contents
- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
  - [Linux](#linux)
  - [Windows](#windows)
- [Basic Example](#basic-example)
- [Building with setup.py](#building-with-setuppy)
- [Future Topics](#future-topics)
- [Troubleshooting](#troubleshooting)

## Introduction
Python C extensions allow you to:
- Speed up critical code sections
- Integrate with existing C libraries
- Access low-level system functionality

## Prerequisites
- Python 3.x development headers
- C compiler (GCC for Linux, MSVC for Windows)
- Basic understanding of C programming

## Installation

### Linux
```bash
# Install required packages
sudo pacman -Syuu 
sudo pacman -S  python3-dev gcc

# Compile a simple extension manually
gcc -shared -o example.so -fPIC example.c $(python3-config --includes --ldflags)
```
- .so is  shared object file , mostly you see them in linux  , for that we have used -shared
- The -fPIC flag tells the C compiler (like GCC) to generate position-independent code, which is essential for shared libraries.Basically help in running anywhere , without any fixed location
- The compiler flags that link to the Python library (which are usually provided by python3-config --includes --ldflags)
  
### Windows
1. Install Visual Studio Build Tools with "Desktop development with C++"
2. Use x64 Native Tools Command Prompt:
```cmd
:: Adjust paths to match your Python installation
cl /LD example.c /IC:\Python310\include /link /LIBPATH:C:\Python310\libs python310.lib
```

## Basic Example

Create a file `example.c`:
```c
#include <Python.h>

// Function that will be called from Python
static PyObject* hello_world(PyObject* self, PyObject* args) {
    const char* name;
    
    // Parse arguments - it  expects  a single string
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    
    printf("Hello, %s from C extension!\n", name);
    
    // Return Python None
    Py_RETURN_NONE;
}

// Method definition table
static PyMethodDef ExampleMethods[] = {
    {"hello_world", hello_world, METH_VARARGS, "Greet someone from C."},
    {NULL, NULL, 0, NULL}  // Sentinel - marks end of array
};

// Module definition
static struct PyModuleDef examplemodule = {
    PyModuleDef_HEAD_INIT,
    "example",    // Module name
    "Example C extension module",  // Module docstring , here you can give your fucntion docstring
    -1,           // Still checking Documentation why -1 
    ExampleMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_example(void) {
    return PyModule_Create(&examplemodule);
}
```

## Building with setup.py

For a more standard Python package, create a `setup.py` file:
- I think  using this  mostly ease of the work of recompilation and managing all other things
- IT can be good if  you are developing big modules, if you are just learning then normal way is good

```python
from setuptools import setup, Extension

example_module = Extension('example',
                          sources=['example.c'])

setup(
    name='example',
    version='0.1',
    description='Example C extension module',
    ext_modules=[example_module],
)
```

Build and install the extension:

```bash
# Build in development mode
pip install -e .

# Or build a wheel
pip install wheel
python setup.py bdist_wheel
```

Test your extension:

```python
import example

# Call the C function
example.hello_world("Python Developer")
```
-- Still Learning , will update 

## Future Topics
The following advanced topics will be added in future updates:
- Working with Python objects (lists, dictionaries, etc.)
- Reference counting and memory management
- Global Interpreter Lock (GIL)
- Error handling
- Performance optimization techniques

## Troubleshooting

Common Errors:
1. **ImportError: dynamic module does not define module export function**
   * Ensure `PyInit_<module>` matches your filename
   * Check if all symbols are exported

2. **Compiler can't find Python.h**
   * Install python-dev package
   * Check include paths: `python3-config --includes`

3. **Windows link errors**
   * Ensure Python architecture (x86/x64) matches your build
   * Verify the correct path to Python libraries
