#define PY_SSIZE_T_CLEAN

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symnmf.h"
#include "assert.h"
#include <sys/types.h>
#include <Python.h>

static PyObject *GetMatrix(PyObject *self, PyObject *args) {
    int k, N, d, i, j, row = 0, col = 0;
    char *goal;
    double **DataPoints, **result = NULL,**H= NULL;
    PyObject * pl, *ReturnMatrix,*H_matrix_py;
    PyObject *DataPoints_0;
    if (!PyArg_ParseTuple(args, "OsiiiO", &DataPoints_0, &goal, &N, &k, &d, &H_matrix_py)) /*we receive the args from python.*/
        return NULL;
    DataPoints = (double**)malloc(N * sizeof(double *));
    if(DataPoints==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    H = (double**) malloc(N * sizeof(double *));
    if(H==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }

    for (i = 0; i < N; i++) {
        DataPoints[i] = (double*) malloc(d * sizeof(double));
        if(DataPoints[i]==NULL){
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    if(H_matrix_py != Py_None) {
        for (i = 0; i < N; i++) {
            H[i] = (double*)malloc(k * sizeof(double));
            if(H[i]==NULL){
                printf("An Error Has Occurred");
                return NULL;
            }
        }
    }
    if(DataPoints_0 != Py_None) {
        for (i = 0; i < N; i++) { /*trans from python object to c matrix*/

            pl = PyList_GetItem(DataPoints_0, i);
            for (j = 0; j < d; j++) {
                DataPoints[i][j] = PyFloat_AsDouble(PyList_GetItem(pl, j));
            }
            if(H_matrix_py!=Py_None){
            pl = PyList_GetItem(H_matrix_py, i);
            for (j = 0; j < k; j++) {
                H[i][j] = PyFloat_AsDouble(PyList_GetItem(pl, j));
            }
            }
        }
    }
    if (strcmp(goal, "sym") == 0) {
        result = sym_case(DataPoints, N, d);
        row = N;
        col = N;

    } else if (strcmp(goal, "ddg") == 0) {
        result = ddg_case(DataPoints, N, d);
        row = N;
        col = N;

    } else if (strcmp(goal, "norm") == 0) {
        result =  norm_case(DataPoints, N, d);
        row = N;
        col = N;
    } else if (strcmp(goal,"symnmf") == 0) {
        result = symnmf(DataPoints,H,N,d,k);
        row = N;
        col = k;
    }
    ReturnMatrix = PyList_New(row); /*trans from c matrix to PyObject*/
    for (i = 0; i < row; i++) {
        PyList_SetItem(ReturnMatrix, i, PyList_New(col));
        for (j = 0; j < col; j++) {
            PyList_SetItem(PyList_GetItem(ReturnMatrix, i), j, PyFloat_FromDouble(result[i][j]));
        }
    }
    for(i=0;i<N;i++){
        free(DataPoints[i]);
        if(H != NULL){
        }
    }
    for(i=0;i<row;i++){
        free(result[i]);
    }
    free(DataPoints);
    free(result);
    return ReturnMatrix;
}




static PyMethodDef capiMethods[] = {
        {"perform_goal", (PyCFunction) GetMatrix, METH_VARARGS, PyDoc_STR("CC")},
        {NULL, NULL,                           0, NULL}
};

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "symNMF",
        NULL,
        -1,
        capiMethods
};

PyMODINIT_FUNC PyInit_symNMF(void) {
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }
    return m;
}