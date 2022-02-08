//
// Created by Admin on 08.02.2022.
//

#include "vector.h"
void isBadAlloc(vector *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    };
}

void isEmptyVectorError(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "empty vector");
        exit(1);
    };
}
vector createVector(size_t n) {
    vector v = {
            malloc(sizeof(int) * n),
            0,
            n
    };
    isBadAlloc(&v);
    return v;

}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else if (newCapacity < v->size)
        v->size = newCapacity;
    else {
        realloc(v->data, sizeof(int) * newCapacity);
        isBadAlloc(v);
    }
    v->capacity = newCapacity;
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector(vector *v) {
    free(v->data);
}