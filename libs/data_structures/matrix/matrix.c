//
// Created by Admin on 14.02.2022.
//

#include "matrix.h"

static void universalSwap(void *a, void *b, size_t size) {
    char *pa = a;
    char *pb = b;
    for (int i = 0; i < size; ++i) {
        char t = *pa;
        *pa = *pb;
        *pb = t;
        pa++;
        pb++;
    }
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *m = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        m[i] = getMemMatrix(nRows, nCols);
    return m;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);

        }
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf(" %d", m.values[i][j]);

        }
        printf("\n");
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert(i1 < m.nRows && i2 < m.nRows);

    universalSwap(&m.values[i1], &m.values[i2], sizeof(int *));
}

void swapColumns(matrix m, int j1, int j2) {
    assert(j1 < m.nCols && j2 < m.nCols);

    for (int i = 0; i < m.nRows; ++i) {
        universalSwap(&m.values[i][j1], &m.values[i][j2], sizeof(int));

    }
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m1.nCols; ++j) {
            if (m1.values[i][j] != m2.values[i][j])
                return false;
        }
    }
    return true;
}

bool isEMatrix(matrix m) {
    if (!isSquareMatrix(m))
        return false;

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (i == j && m.values[i][j] != 1 || i != j && m.values[i][j] != 0)
                return false;
        }
    }
    return true;
}


bool isSymmetricMatrix(matrix m) {
    if (!isSquareMatrix(m))
        return false;


    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < i; ++j) {
            if (m.values[i][j] != m.values[j][i])
                return false;

        }
    }
    return true;
}

void transposeSquareMatrix(matrix m){
    assert(!isSquareMatrix(m));

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < i; ++j)
            universalSwap(&m.values[i][j],&m.values[j][i],sizeof (int));
    }
}

position getMinValuePos(matrix m){
    position minValuePos = {0,0};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            position curPos = {i, j};
            if (m.values[curPos.rowIndex][curPos.colIndex] < m.values[minValuePos.rowIndex][minValuePos.colIndex])
                minValuePos = curPos;
        }
    }
    return minValuePos;
}

position getMaxValuePos(matrix m){
    position maxValuePos = {0,0};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            position curPos = {i, j};
            if (m.values[curPos.rowIndex][curPos.colIndex] > m.values[maxValuePos.rowIndex][maxValuePos.colIndex])
                maxValuePos = curPos;
        }
    }
    return maxValuePos;
}

void outputPosition(position p) {
    printf("{%d, ", p.rowIndex);
    printf("%d}", p.colIndex);
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}