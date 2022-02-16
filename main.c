#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libs/data_structures/matrix/matrix.h"

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
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;


    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool isUnique(long long *a, int n) {
    bool isUnique = true;

    qsort(a, n, sizeof(int), compare_ints);

    int i = 0;
    while (i < n - 1 && isUnique) {
        if (a[i] == a[i + 1])
            isUnique = 0;
        i++;
    }

    return isUnique;
}

long long getSum(const int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m)  {
    long long sumArray[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        sumArray[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(sumArray, m.nRows))
        transposeSquareMatrix(m);

}

// tests
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

void test_getSquareOfMatrixIfSymmetric() {
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

void test_isUnique() {
    long long a[5] = {1, 4, 3, 3, 5};
    assert(isUnique(a, 5));
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
void test() {
    test_isUnique;
    test_swapRowsWithMaxAndMinElements;
    test_sortRowsByMinElement;
    test_sortColsByMinElement;
    test_sortRowsByMinElement_oneCol;
    test_sortColsByMinElement_oneRow;
    test_getSquareOfMatrixIfSymmetric;
    test_getSquareOfMatrixIfSymmetric_oneElem;
    test_getSquareOfMatrixIfSymmetric_NotSymmetricSquareMatrix;
    test_transposeIfMatrixHasNotEqualSumOfRows_hasEqualSum;
    test_transposeIfMatrixHasNotEqualSumOfRows_hasNotEqualSum;
}

int main() {
    test();
    return 0;
}
