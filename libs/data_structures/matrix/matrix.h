//
// Created by Admin on 14.02.2022.
//

#ifndef INC_1_MATRIX_H
#define INC_1_MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

#endif //INC_1_MATRIX_H
