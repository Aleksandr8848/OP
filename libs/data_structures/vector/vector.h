//
// Created by Admin on 08.02.2022.
//

#ifndef INC_1_VECTOR_H
#define INC_1_VECTOR_H
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

// возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n);

// изменяет количество памяти,
// выделенное под хранение элементов вектора.
void reserve(vector *v, size_t newCapacity);

// удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

// освобождает память, выделенную под
// неиспользуемые элементы.
void shrinkToFit(vector *v);

#endif //INC_1_VECTOR_H
