#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/matrix/matrix.h"

void swapRowsWithMaxAndMinElements(matrix m) {
    position maxPos = getMaxValuePos(m);
    position minPos = getMinValuePos(m);

    swapRows(m, maxPos.rowIndex, minPos.rowIndex);
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

void test_sortRowsByMinElement(){
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

void test() {
    test_swapRowsWithMaxAndMinElements;
    test_sortRowsByMinElement;
}

int main() {
    test();
    return 0;
}
