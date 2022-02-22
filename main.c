
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

        minElement = min2(getMin(&m.values[i][left],right-left),minElement);
    }
    return minElement;
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

void test_getMinInArea(){
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);
    assert(getMinInArea(m) == 2);
    freeMemMatrix(m);
}

void test_getMinInArea2(){
    matrix m = createMatrixFromArray((int[]) {10, 7, 5, 6,
                                              3, 11, 8, 9,
                                              3, 2, 12, 2}, 3, 4);
    assert(getMinInArea(m) == 5);
    freeMemMatrix(m);
}

void test_getMinInArea3(){
    matrix m = createMatrixFromArray((int[]) {10, 17, 5, 6,
                                              3, 11, 8, 9,
                                              3, 2, 12, 2}, 3, 4);
    assert(getMinInArea(m) == 17);
    freeMemMatrix(m);
}
void test() {
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
    test_isMutuallyInverseMatrices_matrixProduceIsEMatrix;
    test_isMutuallyInverseMatrices_matrixProduceIsNotEMatrix;
    test_findSumOfMaxesOfPseudoDiagonal;
    test_getMinInArea;
    test_getMinInArea2;
    test_getMinInArea3;
}

int main() {
    test();
    return 0;
}
