#include <Python.h>
#include <stdio.h>

/*

This is the first file which uses the Python.h API call ( by following all rules)
This helps in creation of Module which is written in c 

Mostly things are maintained Manually. 
*/

PyObject *add(PyObject *self, PyObject *args){
  int x;
  int y;

  PyArg_ParseTuple(args,"ii",&x,&y);

  return PyLong_FromLong((long)(x + y));
}

static  PyMethodDef methods[] = {
  {"add", add, METH_VARARGS,"Adds two number together"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef abc123 = {
  PyModuleDef_HEAD_INIT,
  "abc123",
  "This  is a module named abc123",
  -1,
  methods
};

PyMODINIT_FUNC PyInit_abc123(){
  // printf("Hello world\n");
  return PyModule_Create(&abc123);

}
