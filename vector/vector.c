#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Vector *vector_create(size_t elem_size) {
    if (elem_size == 0) {
        return NULL; // Element size cannot be 0
    }
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (v != NULL) {
        if (DEFAULT_CAPACITY > SIZE_MAX / elem_size) {
            free(v);
            return NULL;
        }
        v->data = malloc(DEFAULT_CAPACITY * elem_size);
        if (v->data == NULL) {
            free(v);
            return NULL;
        }
        v->capacity = DEFAULT_CAPACITY;
        v->size = 0;
        v->element_size = elem_size;
    }
    return v;
}

void vector_destroy(Vector *vec) {
    if (vec != NULL) {
        free(vec->data);
        free(vec);
    }
}

size_t vector_size(const Vector *vec) {
    if (vec == NULL) {
        return 0;
    }
    return vec->size;
}

size_t vector_capacity(const Vector *vec) {
    if (vec == NULL) {
        return 0;
    }
    return vec->capacity;
}

size_t vector_element_size(const Vector *vec) {
    if (vec == NULL) {
        return 0;
    }
    return vec->element_size;
}

int vector_empty(const Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (vec->size == 0) {
        return 1;
    }
    return 0;
}

int vector_full(const Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (vec->size == vec->capacity) {
        return 1;
    }
    return 0;
}

void *vector_front(const Vector *vec) {
    if (vec == NULL) {
        return NULL;
    }
    if (vec->size == 0) {
        return NULL;
    }
    return vec->data;
}

void *vector_back(const Vector *vec) {
    if (vec == NULL) {
        return NULL;
    }
    if (vec->size == 0) {
        return NULL;
    }
    return (void *)((char *)vec->data + (vec->size - 1) * vec->element_size);
}

void *vector_at(const Vector *vec, size_t pos) {
    if (vec == NULL) {
        return NULL;
    }
    if (pos >= vec->size) {
        return NULL;
    }
    return (void *)((char *)vec->data + pos * vec->element_size);
}

int vector_push_back(Vector *vec, const void *data) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (data == NULL) {
        return VECTOR_ERROR_INVALID_DATA;
    }
    if (vec->size == vec->capacity) {
        if (vec->capacity > SIZE_MAX / 2) {
            return VECTOR_ERROR_OVERFLOW;
        }
        if (vector_reserve(vec, vec->capacity * 2)) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
    }
    memcpy((char *)vec->data + vec->size * vec->element_size, data,
           vec->element_size);
    vec->size++;
    return VECTOR_SUCCESS;
}

int vector_pop_back(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (vec->size == 0) {
        return VECTOR_ERROR_EMPTY;
    }
    vec->size--;
    return VECTOR_SUCCESS;
}

int vector_insert(Vector *vec, void *data, size_t pos) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (data == NULL) {
        return VECTOR_ERROR_INVALID_DATA;
    }
    if (pos > vec->size) {
        return VECTOR_ERROR_INVALID_INDEX;
    }
    if (pos == vec->size) {
        return vector_push_back(vec, data);
    }
    if (vec->size == vec->capacity) {
        if (vec->capacity > SIZE_MAX / 2 ||
            vec->capacity * 2 > SIZE_MAX / vec->element_size) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
        if (vector_reserve(vec, vec->capacity * 2)) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
    }
    memmove((char *)vec->data + (pos + 1) * vec->element_size,
            (char *)vec->data + pos * (vec->element_size),
            (vec->size - pos) * vec->element_size);
    memcpy((char *)vec->data + pos * (vec->element_size), data,
           vec->element_size);
    vec->size++;
    return VECTOR_SUCCESS;
}

int vector_erase(Vector *vec, size_t pos) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (pos >= vec->size) {
        return VECTOR_ERROR_INVALID_INDEX;
    }
    memmove((char *)vec->data + pos * vec->element_size,
            (char *)vec->data + (pos + 1) * vec->element_size,
            (vec->size - pos - 1) * vec->element_size);
    vec->size--;
    return VECTOR_SUCCESS;
}

int vector_clear(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    vec->size = 0;
    return VECTOR_SUCCESS;
}

int vector_reserve(Vector *vec, size_t new_capacity) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (new_capacity <= vec->capacity) {
        return VECTOR_SUCCESS;
    }
    if (new_capacity > SIZE_MAX / vec->element_size) {
        return VECTOR_ERROR_OUT_OF_MEMORY;
    }
    void *arr = realloc(vec->data, new_capacity * vec->element_size);
    if (arr == NULL) {
        return VECTOR_ERROR_OUT_OF_MEMORY;
    }
    vec->data = arr;
    vec->capacity = new_capacity;
    return VECTOR_SUCCESS;
}

int vector_resize(Vector *vec, size_t new_size) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (new_size > vec->capacity) {
        if (vector_reserve(vec, new_size)) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
    }
    vec->size = new_size;
    return VECTOR_SUCCESS;
}

int vector_shrink_to_fit(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (vec->size == vec->capacity) {
        return VECTOR_SUCCESS;
    }
    if (vec->size == 0 && vec->capacity > DEFAULT_CAPACITY) {
        void *arr = realloc(vec->data, DEFAULT_CAPACITY * vec->element_size);
        if (arr == NULL) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
        vec->data = arr;
        vec->capacity = DEFAULT_CAPACITY;
        return VECTOR_SUCCESS;
    }
    if (vec->size < vec->capacity && vec->size > 0) {
        void *arr = realloc(vec->data, vec->size * vec->element_size);
        if (arr == NULL) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
        vec->data = arr;
        vec->capacity = vec->size;
        return VECTOR_SUCCESS;
    }
    return VECTOR_SUCCESS;
}
