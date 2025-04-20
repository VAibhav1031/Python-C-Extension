#include <Python.h>

// Function that will be called from Python
static PyObject* hello_world(PyObject* self, PyObject* args) {
    const char* name;
    
    // Parse arguments - expect a single string
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
    "Example C extension module",  // Module docstring
    -1,           // Size of per-interpreter state (or -1)
    ExampleMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_example1(void) {
    return PyModule_Create(&examplemodule);
}
