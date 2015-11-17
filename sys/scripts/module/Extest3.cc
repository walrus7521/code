#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/python2.7/Python.h"

extern "C" {

int fac(int n)
{
    if (n < 2) return (1);
    return (n)*fac(n-1);
}

static PyObject *
Extest_fac(PyObject *self, PyObject *args) {
    PyObject *retval = NULL;
    int res;
    int num;

    res = PyArg_ParseTuple(args, "i", &num);
    if (!res) {
        return NULL;
    }
    res = fac(num);
    retval = (PyObject*) Py_BuildValue("i", res);

    return retval;
}

char *reverse(char *s)
{
    register char t,
             *p = s,
             *q = (s + (strlen(s)-1));

    while (p < q) {
        t = *p;
        *p++ = *q;
        *q-- = t;
    }
    return s;
}

static PyObject *
Extest_doppel(PyObject *self, PyObject *args) {
    char *orig_str;
    char *dup_str;
    PyObject *retval = NULL;

    if (!PyArg_ParseTuple(args, "s", &orig_str)) return NULL;

    retval = (PyObject*) Py_BuildValue("ss", orig_str, \
             dup_str = reverse(strdup(orig_str)));

    free(dup_str);

    return retval;
}

static PyMethodDef
ExtestMethods[] = {
    { "fac", Extest_fac, METH_VARARGS },
    { "doppel", Extest_doppel, METH_VARARGS },
    { NULL, NULL },
};

void initExtest() {
    Py_InitModule("Extest", ExtestMethods);
}

}
#if 0
int main()
{
    char s[256];
    cout << "4!  == " << fac(4) << endl;
    cout << "8!  == " << fac(8) << endl;
    cout << "12! == " << fac(12) << endl;

    strcpy(s, "abcdef");
    printf("reversing %s we get %s\n", s, reverse(s));

    strcpy(s, "madam");
    printf("reversing %s we get %s\n", s, reverse(s));

    return 0;
}
#endif
