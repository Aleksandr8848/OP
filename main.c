#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/data_structures/matrix/matrix.h"
#include <math.h>

// task 1
void swapRowsWithMaxAndMinElements(matrix m) {
    position maxPos = getMaxValuePos(m);
    position minPos = getMinValuePos(m);

    swapRows(m, maxPos.rowIndex, minPos.rowIndex);
}

// task 2
int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[max])
            max = a[i];
    }
    return max;
}

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

// task 3
int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 0; i < n; ++i) {
        if (a[i] < a[min])
            min = a[i];
    }
    return min;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

// task 4
void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (!isSymmetricMatrix(*m))
        return;

    matrix res = mulMatrices(*m, *m);
    *m = res;
}

// task 5
int long_long_cmp(const void *a, const void *b) {
    long long arg1 = *(const long long *) a;
    long long arg2 = *(const long long *) b;


    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool isUnique(long long *a, const int n) {
    long long *aCopy = (long long *) malloc(n * sizeof(long long));
    memcpy(aCopy, a, n * sizeof(long long));
    qsort(aCopy, n, sizeof(long long), long_long_cmp);

    for (int i = 0; i < n - 1; ++i) {
        if (aCopy[i] == aCopy[i + 1]) {
            free(aCopy);
            return false;
        }
    }
    free(aCopy);
    return true;
}

long long getSum(const int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long sumArray[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        sumArray[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(sumArray, m.nRows))
        transposeSquareMatrix(m);

}

// task 6
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    return (isEMatrix(mulMatrices(m1, m2)));
}

// task 7

// возвращает максимальное значение из двух целочисленных переменных типа int.
int max2(const int a, const int b) {
    return a > b ? a : b;
}

int getMaxValueOnDiagonal(matrix m, int rowsIndex, int colsIndex) {
    int maxValue = m.values[rowsIndex][colsIndex];
    while (rowsIndex < m.nRows && colsIndex < m.nCols) {
        maxValue = max2(maxValue, m.values[rowsIndex++][colsIndex++]);
    }
    return maxValue;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long sumMaxElementsOfPseudoDiagonal = 0;
    for (int i = 1; i < m.nRows; ++i)
        sumMaxElementsOfPseudoDiagonal += getMaxValueOnDiagonal(m, i, 0);
    for (int j = 1; j < m.nCols; ++j)
        sumMaxElementsOfPseudoDiagonal += getMaxValueOnDiagonal(m, 0, j);
    return sumMaxElementsOfPseudoDiagonal;
}

// task 8

// возвращает минимальное значение из двух целочисленных переменных типа int.
int min2(const int a, const int b) {
    return a > b ? b : a;
}

int getMinInArea(matrix m) {
    position minPos = getMaxValuePos(m);
    int minElement = m.values[minPos.rowIndex][minPos.colIndex];
    int right = minPos.colIndex;
    int left = minPos.colIndex;

    for (int i = minPos.rowIndex - 1; i >= 0; ++i) {
        right = right > m.nCols ? right : right + 1;
        left = left > 0 ? left - 1 : left;

        minElement = min2(getMin(&m.values[i][left], right - left), minElement);
    }
    return minElement;
}

// task 9

float getDistance(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i)
        sum += pow(a[i], 2);
    return sqrt(sum);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float *criteriaArray = (float *) malloc(sizeof(int) * m.nRows);
    for (size_t i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            universalSwap(&criteriaArray[j - 1], &criteriaArray[j], sizeof(float));
            swapRows(m, j - 1, j);

            j--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

// task 10
int countNUnique(long long *a, const int n) {
    if (n == 0)
        return 0;

    long long *aCopy = (long long *) malloc(n * sizeof(long long));
    memcpy(aCopy, a, n * sizeof(long long));
    qsort(aCopy, n, sizeof(long long), long_long_cmp);

    int countNUnique = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (aCopy[i] != aCopy[i + 1]) {
            countNUnique++;
        }
    }
    free(aCopy);
    return countNUnique;
}

int countEqClassesByRowsSum(matrix m) {
    long long *arrayOfSums = (long long *) malloc(sizeof(long long) * m.nRows);

    for (int i = 0; i < m.nRows; ++i)
        arrayOfSums[i] = getSum(m.values[i], m.nCols);
    int classes = countNUnique(arrayOfSums, m.nRows);

    free(arrayOfSums);

    return classes;
}

// task 11
int getSpecialElements(matrix m) {
    int countSpecialElements = 0;

    for (int i = 0; i < m.nCols; ++i) {
        long long sumCols = 0;
        for (int j = 0; j < m.nRows; ++j)
            sumCols += m.values[i][j];

        for (int j = 0; j < m.nRows; ++j) {
            if (sumCols - m.values[i][j] < m.values[i][j])
                countSpecialElements++;
        }
    }
    return countSpecialElements;
}

// task 12
position getLeftMin(matrix m) {
    position minValuePos = {0, 0};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            position curPos = {i, j};
            if (m.values[i][j] < m.values[minValuePos.rowIndex][minValuePos.colIndex] ||
                m.values[i][j] == m.values[minValuePos.rowIndex][minValuePos.colIndex] && j < minValuePos.colIndex)
                minValuePos = curPos;
        }
    }
    return minValuePos;
}

void swapPenultimateRow(matrix m) {
    position minPos = getLeftMin(m);

    int *col = (int *) malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; ++i)
        col[i] = m.values[i][minPos.colIndex];

    memcpy(m.values[m.nRows - 2], col, sizeof(int) * m.nCols);

    free(col);
}

// task 13
bool isNonDescendingSorted(const int *a, int n) {
    for (int i = 0; i < n - 1; ++i)
        if (a[i] > a[i + 1]) {
            return false;
        }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; ++i) {
        if (hasAllNonDescendingRows(ms[i]))
            count++;
    }
    return count;
}

// task 14
int countValues(const int *a, int n, int value) {
    int countValues = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == value)
            countValues++;
    }
    return countValues;
}

int countZeroRows(matrix m) {
    int countZeroRows = 0;
    for (int i = 0; i < m.nRows; ++i) {
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            countZeroRows++;
    }
    return countZeroRows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int *msZeroRows = (int *) malloc(sizeof(int) * nMatrix);
    int zeroRowsMaxCount = 0;

    for (int i = 0; i < nMatrix; ++i) {
        msZeroRows[i] = countZeroRows(ms[i]);
        zeroRowsMaxCount = max2(zeroRowsMaxCount, msZeroRows[i]);
    }
    for (int i = 0; i < nMatrix; ++i) {
        if (msZeroRows[i] == zeroRowsMaxCount)
            outputMatrix(ms[i]);
    }
    free(msZeroRows);
}

// task 15
int getMatrixNorm(matrix m) {
    int norm = abs(m.values[0][0]);
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (abs(m.values[i][j]) > norm)
                norm = abs(m.values[i][j]);
        }
    }
    return norm;
}

void printMatrixWithMimNorm(matrix *ms, int nMatrix) {
    int *normMatrix = (int *) malloc(sizeof(int) * nMatrix);

    for (int i = 0; i < nMatrix; ++i)
        normMatrix[i] = getMatrixNorm(ms[i]);

    int minNorm = getMin(normMatrix, nMatrix);

    for (int i = 0; i < nMatrix; ++i) {
        if (normMatrix[i] == minNorm)
            outputMatrix(ms[i]);
    }
    free(normMatrix);
}

// tests
void test_swapRows() {
    matrix m1 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);


    swapRows(m1, 1, 2);

    matrix m2 = createMatrixFromArray((int[]) {1, 4, 5,
                                               4, 7, 2,
                                               3, 6, 7}, 3, 3);

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapColumns() {
    matrix m1 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);

    swapColumns(m1, 0, 2);

    matrix m2 = createMatrixFromArray((int[]) {5, 4, 1,
                                               7, 6, 3,
                                               2, 7, 4}, 3, 3);

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    assert(isSquareMatrix(m));

    freeMemMatrix(m);
}

void test_twoMatricesEqual() {
    matrix m1 = createMatrixFromArray((int[]) {1, 7, 5,
                                               3, 6, 9,
                                               4, 8, 2}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]) {1, 7, 5,
                                               3, 6, 9,
                                               4, 8, 2}, 3, 3);
    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isEMatrix_matrixIsE() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    assert(isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_matrixIsNotE() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 2, 0,
                                              0, 0, 3}, 3, 3);
    assert(!isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_matrixIsNotSquare() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0}, 2, 3);

    assert(!isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix() {
    test_isEMatrix_matrixIsE();
    test_isEMatrix_matrixIsNotE();
    test_isEMatrix_matrixIsNotSquare();
}

void test_isSymmetricMatrix_matrixIsSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 5, 6,
                                              3, 6, 7}, 3, 3);

    assert(isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_matrixIsNotSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_matrixIsNotSquare() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6}, 2, 3);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix() {
    test_isSymmetricMatrix_matrixIsSymmetric();
    test_isSymmetricMatrix_matrixIsNotSymmetric();
    test_isSymmetricMatrix_matrixIsNotSquare();
}

void test_transposeSquareMatrix_matrixIsSquare() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2, 3,
                                               4, 5, 6,
                                               7, 8, 9}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]) {1, 4, 7,
                                               2, 5, 8,
                                               3, 6, 9}, 3, 3);
    transposeSquareMatrix(m1);

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeSquareMatrix() {
    test_transposeSquareMatrix_matrixIsSquare();
}


void test_part1() {
    test_swapRows();
    test_swapColumns();
    test_isSquareMatrix();
    test_twoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();

}

void test_swapRowsWithMaxAndMinElements() {
    matrix m = createMatrixFromArray((int[]) {
            1, 2, 3,
            4, 5, 9,
            6, 7, 8
    }, 3, 3);
    swapRowsWithMaxAndMinElements(m);
    matrix x = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 7, 8,
            1, 2, 3
    }, 3, 3);

    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_sortRowsByMinElement() {
    matrix m = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 7, 8,
            1, 2, 3
    }, 3, 3);

    sortRowsByMinElement(m);
    matrix x = createMatrixFromArray((int[]) {
            1, 2, 3,
            4, 5, 9,
            6, 7, 8
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_sortColsByMinElement() {
    matrix m = createMatrixFromArray((int[]) {
            4, 5, 9,
            6, 1, 8,
            7, 2, 3
    }, 3, 3);

    sortColsByMinElement(m);
    matrix x = createMatrixFromArray((int[]) {
            5, 9, 4,
            1, 8, 6,
            2, 3, 7
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_sortRowsByMinElement_oneCol() {
    matrix m = createMatrixFromArray((int[]) {8,
                                              2,
                                              4,
                                              6}, 4, 1);

    sortRowsByMinElement(m);

    matrix x = createMatrixFromArray((int[]) {2,
                                              4,
                                              6,
                                              8}, 4, 1);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_sortColsByMinElement_oneRow() {
    matrix m = createMatrixFromArray((int[]) {8, 2, 4, 6}, 1, 4);

    sortColsByMinElement(m);

    matrix x = createMatrixFromArray((int[]) {2, 4, 6, 8}, 1, 4);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_getSquareOfMatrixIfSymmetric_symmetricSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {
            4, 3, 1,
            3, 1, 2,
            1, 2, 3
    }, 3, 3);

    getSquareOfMatrixIfSymmetric(&m);
    matrix x = createMatrixFromArray((int[]) {
            26, 17, 13,
            17, 14, 11,
            13, 11, 14
    }, 3, 3);
    assert(twoMatricesEqual(m, x));
    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_getSquareOfMatrixIfSymmetric_oneElem() {
    matrix m = createMatrixFromArray((int[]) {4}, 1, 1);

    getSquareOfMatrixIfSymmetric(&m);

    matrix x = createMatrixFromArray((int[]) {16}, 1, 1);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_getSquareOfMatrixIfSymmetric_NotSymmetricSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 1, 2,
                                              1, 1, 1,
                                              3, 1, 1}, 3, 3);

    getSquareOfMatrixIfSymmetric(&m);

    matrix x = createMatrixFromArray((int[]) {1, 1, 2,
                                              1, 1, 1,
                                              3, 1, 1}, 3, 3);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_transposeIfMatrixHasNotEqualSumOfRows_hasEqualSum() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              1, 4, 1,
                                              3, 1, 3}, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m);

    matrix x = createMatrixFromArray((int[]) {1, 2, 3,
                                              1, 4, 1,
                                              3, 1, 3}, 3, 3);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_transposeIfMatrixHasNotEqualSumOfRows_hasNotEqualSum() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 1,
                                              1, 8, 1,
                                              3, 1, 3}, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m);

    matrix x = createMatrixFromArray((int[]) {7, 1, 3,
                                              1, 8, 1,
                                              1, 1, 3}, 3, 3);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_isMutuallyInverseMatrices_matrixProduceIsEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {2, 5, 7,
                                               6, 3, 4,
                                               5, -2, -3}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, -1, 1,
                                               -38, 41, -34,
                                               27, -29, 24}, 3, 3);

    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices_matrixProduceIsNotEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {3, 5, 7,
                                               6, 3, 4,
                                               5, -2, -3}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, -1, 1,
                                               -38, 41, -34,
                                               27, -29, 24}, 3, 3);

    assert(!isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);

    assert(findSumOfMaxesOfPseudoDiagonal(m) == 20);

    freeMemMatrix(m);
}

void test_getMinInArea1() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);
    assert(getMinInArea(m) == 2);
    freeMemMatrix(m);
}

void test_getMinInArea2() {
    matrix m = createMatrixFromArray((int[]) {10, 7, 5, 6,
                                              3, 11, 8, 9,
                                              3, 2, 12, 2}, 3, 4);
    assert(getMinInArea(m) == 5);
    freeMemMatrix(m);
}

void test_getMinInArea3() {
    matrix m = createMatrixFromArray((int[]) {10, 17, 5, 6,
                                              3, 11, 8, 9,
                                              3, 2, 12, 2}, 3, 4);
    assert(getMinInArea(m) == 17);
    freeMemMatrix(m);
}

void test_sortByDistances_somePoints() {
    matrix m = createMatrixFromArray((int[]) {6, 8, 9, 2,
                                              10, 11, 5, 1,
                                              7, 12, 3, 4}, 3, 4);

    sortByDistances(m);

    matrix expectation = createMatrixFromArray((int[]) {6, 8, 9, 2,
                                                        7, 12, 3, 4,
                                                        10, 11, 5, 1}, 3, 4);

    assert(twoMatricesEqual(m, expectation));

    freeMemMatrix(m);
    freeMemMatrix(expectation);
}

void test_sortByDistances_somePoints2() {
    matrix m = createMatrixFromArray((int[]) {8, 9, 10, 11,
                                              0, 1, 2, 3,
                                              4, 5, 6, 7}, 3, 4);

    sortByDistances(m);

    matrix expectation = createMatrixFromArray((int[]) {0, 1, 2, 3,
                                                        4, 5, 6, 7,
                                                        8, 9, 10, 11,}, 3, 4);

    assert(twoMatricesEqual(m, expectation));

    freeMemMatrix(m);
    freeMemMatrix(expectation);
}


void test_sortByDistances_oneCols() {
    matrix m = createMatrixFromArray((int[]) {11,
                                              9,
                                              10,
                                              2}, 4, 1);

    sortByDistances(m);

    matrix expectation = createMatrixFromArray((int[]) {2,
                                                        9,
                                                        10,
                                                        11}, 4, 1);

    assert(twoMatricesEqual(m, expectation));

    freeMemMatrix(m);
    freeMemMatrix(expectation);
}

void test_countEqClassesByRowsSum1() {
    matrix m = createMatrixFromArray((int[]) {7, 1,
                                              2, 7,
                                              5, 4,
                                              4, 3,
                                              1, 6,
                                              8, 0}, 6, 2);
    assert(countEqClassesByRowsSum(m) == 3);
    freeMemMatrix(m);
}

void test_countEqClassesByRowsSum_oneCols() {
    matrix m = createMatrixFromArray((int[]) {7,
                                              2,
                                              5,
                                              4,
                                              1,
                                              1}, 6, 1);
    assert(countEqClassesByRowsSum(m) == 5);
    freeMemMatrix(m);
}

void test_countEqClassesByRowsSum_void() {
    matrix m = createMatrixFromArray((int[]) {}, 0, 0);
    assert(countEqClassesByRowsSum(m) == 0);

    freeMemMatrix(m);
}

void test_countEqClassesByRowsSum() {
    test_countEqClassesByRowsSum_oneCols;
    test_countEqClassesByRowsSum_void;
    test_countEqClassesByRowsSum1;
}

void test_getSquareOfMatrixIfSymmetric() {
    test_getSquareOfMatrixIfSymmetric_symmetricSquareMatrix;
    test_getSquareOfMatrixIfSymmetric_oneElem;
    test_getSquareOfMatrixIfSymmetric_NotSymmetricSquareMatrix;
}

void test_swapRowsOrCols() {
    test_swapRowsWithMaxAndMinElements;
    test_sortRowsByMinElement;
    test_sortColsByMinElement;
    test_sortRowsByMinElement_oneCol;
    test_sortColsByMinElement_oneRow;
}

void test_getMinInArea() {
    test_getMinInArea1;
    test_getMinInArea2;
    test_getMinInArea3;
}

void test_sortByDistances() {
    test_sortByDistances_somePoints;
    test_sortByDistances_somePoints2;
    test_sortByDistances_oneCols;
}

void test_getSpecialElements() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 5, 4,
                                              2, 3, 6, 7,
                                              12, 2, 1, 2}, 3, 4);
    assert(getSpecialElements(m) == 2);
    freeMemMatrix(m);
}

void test_swapPenultimateRow() {
    matrix m = createMatrixFromArray((int[]) {
            4, 7, 1,
            3, 1, 2,
            5, 2, 3
    }, 3, 3);

    swapPenultimateRow(m);

    matrix x = createMatrixFromArray((int[]) {
            4, 3, 1,
            7, 1, 2,
            5, 2, 3
    }, 3, 3);

    assert(twoMatricesEqual(m, x));

    freeMemMatrix(m);
    freeMemMatrix(x);
}

void test_countNonDescendingRowsMatrices_squareMatrixHasSuitableMatrix() {
    matrix *ms = createArrayOfMatrixFromArray((int[]) {7, 1,
                                                       1, 1,

                                                       1, 6,
                                                       2, 2,

                                                       5, 4,
                                                       2, 3,

                                                       1, 3,
                                                       7, 9}, 4, 2, 2);

    assert(countNonDescendingRowsMatrices(ms, 4) == 2);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices_notSquareMatrixHasSuitableMatrix() {
    matrix *ms = createArrayOfMatrixFromArray((int[]) {1, 2, 3,
                                                       4, 5, 6,

                                                       1, 6, 7,
                                                       2, 2, 2,

                                                       1, 0, 1,
                                                       2, 1, 2,

                                                       1, 2, 3,
                                                       1, 2, 3}, 4, 2, 3);

    assert(countNonDescendingRowsMatrices(ms, 4) == 3);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices_oneRow() {
    matrix *ms = createArrayOfMatrixFromArray((int[]) {0, 0, 1,

                                                       8, 6, 7,

                                                       -1, 0, 1,

                                                       1, 2, 3,}, 4, 1, 3);

    assert(countNonDescendingRowsMatrices(ms, 4) == 3);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices_oneCol() {
    matrix *ms = createArrayOfMatrixFromArray((int[]) {0,
                                                       0,
                                                       1,

                                                       1,
                                                       6,
                                                       7,

                                                       -1,
                                                       0,
                                                       1,

                                                       1,
                                                       2,
                                                       3,}, 4, 3, 1);

    assert(countNonDescendingRowsMatrices(ms, 4) == 4);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices_oneElem() {
    matrix *ms = createArrayOfMatrixFromArray((int[]) {0,

                                                       1,

                                                       -1,

                                                       1}, 4, 1, 1);

    assert(countNonDescendingRowsMatrices(ms, 4) == 4);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices() {
    test_countNonDescendingRowsMatrices_squareMatrixHasSuitableMatrix();
    test_countNonDescendingRowsMatrices_notSquareMatrixHasSuitableMatrix();
    test_countNonDescendingRowsMatrices_oneRow();
    test_countNonDescendingRowsMatrices_oneCol();
    test_countNonDescendingRowsMatrices_oneElem();
}

void test_countZeroRows() {
    matrix m = createMatrixFromArray((int[]) {
            4, 7, 0,
            0, 1, 2,
            0, 0, 0
    }, 3, 3);

    assert(countZeroRows(m) == 1);

    freeMemMatrix(m);
}
void test_getMatrixNorm1(){
    matrix m = createMatrixFromArray((int[]) {
            4, -7, 1,
            3, -1, 2,
            5, -2, 3
    }, 3, 3);
    assert(getMatrixNorm(m) == 7);

    freeMemMatrix(m);
}
void test_getMatrixNorm_oneRow() {
    matrix m = createMatrixFromArray((int[]) {-2,
                                              0,
                                              1},3, 1);

    assert(getMatrixNorm(m) == 2);

    freeMemMatrix(m);
}

void test_getMatrixNorm_oneCol() {
    matrix m = createMatrixFromArray((int[]) {1, 0, -2},1, 3);

    assert(getMatrixNorm(m) == 2);

    freeMemMatrix(m);
}
void test_getMatrixNorm(){
    test_getMatrixNorm1;
    test_getMatrixNorm_oneRow;
    test_getMatrixNorm_oneCol;
}
void test() {
    test_part1;
    test_swapRowsOrCols;
    test_getSquareOfMatrixIfSymmetric;
    test_transposeIfMatrixHasNotEqualSumOfRows_hasEqualSum;
    test_transposeIfMatrixHasNotEqualSumOfRows_hasNotEqualSum;
    test_isMutuallyInverseMatrices_matrixProduceIsEMatrix;
    test_isMutuallyInverseMatrices_matrixProduceIsNotEMatrix;
    test_findSumOfMaxesOfPseudoDiagonal;
    test_getMinInArea;
    test_sortByDistances;
    test_countEqClassesByRowsSum;
    test_getSpecialElements;
    test_swapPenultimateRow;
    test_countNonDescendingRowsMatrices;
    test_countZeroRows;
    test_getMatrixNorm;
}

int main() {
    test();
    matrix *ms = createArrayOfMatrixFromArray((int[]) {7, 1,
                                                       1, 1,
                                                       0, 0,

                                                       0, 0,
                                                       2, 2,
                                                       1, 1,

                                                       5, 4,
                                                       2, 3,
                                                       1, 1,

                                                       1, 3,
                                                       7, 9,
                                                       0, 0}, 4, 3, 2);

    printMatrixWithMaxZeroRows(ms, 4);
    printMatrixWithMimNorm(ms,4);

    freeMemMatrices(ms, 4);
    return 0;
}
