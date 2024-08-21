#define PY_SSIZE_T_CLEAN


#include "Python.h"
#include <iostream>



static PyObject *SpamError;

static PyObject *spam_system_new(PyObject *self, PyObject *args) {
  const char *command;
  int sts;
  std::cout << "Tada";
  /*if (!PyArg_ParseTuple(args, "s", &command)) return NULL;
  
  sts = system(command);
  if (sts < 0) {
    PyErr_SetString(SpamError, "System command failed");
    return NULL;
  }*/
  std::string tempVal = "Tada - Try, things look okay";
  
  return PyUnicode_FromStringAndSize(tempVal.c_str(), tempVal.size());
}

static PyMethodDef SpamMethods[] = {
    {"system", spam_system_new, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT, "spam", /* name of module */
    NULL,                      /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
    SpamMethods};

PyMODINIT_FUNC PyInit_spam(void) {
  PyObject *m;

  m = PyModule_Create(&spammodule);
  if (m == NULL) return NULL;

  SpamError = PyErr_NewException("spam.error", NULL, NULL);
  Py_XINCREF(SpamError);
  if (PyModule_AddObject(m, "error", SpamError) < 0) {
    Py_XDECREF(SpamError);
    Py_CLEAR(SpamError);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}



