#include <stddef.h>

#ifndef VECTOR_H
#define VECTOR_H

// ERROR CODES
#define VECTOR_SUCCESS 0
#define VECTOR_ERROR_NULL_POINTER -99
#define VECTOR_ERROR_OUT_OF_MEMORY -98
#define VECTOR_ERROR_INVALID_INDEX -97
#define VECTOR_ERROR_EMPTY -96
#define VECTOR_ERROR_INVALID_CAPACITY -95
#define VECTOR_ERROR_INVALID_DATA -94
#define VECTOR_ERROR_OVERFLOW -93

#define DEFAULT_CAPACITY 4

// DATA STRUCTURE
typedef struct Vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

// CONSTRUCTORS/DESTRUCTORS
Vector *vector_create(size_t ele_size);
void vector_destroy(Vector *vec);

// METAINFO
size_t vector_size(const Vector *vec);
size_t vector_capacity(const Vector *vec);
size_t vector_element_size(const Vector *vec);
int vector_empty(const Vector *vec);
int vector_full(const Vector *vec);

// ELEMENT ACCESS
void *vector_front(const Vector *vec);
void *vector_back(const Vector *vec);
void *vector_at(const Vector *vec, size_t pos);

// MODIFIERS
int vector_push_back(Vector *vec, const void *data);
int vector_pop_back(Vector *vec);
int vector_insert(Vector *vec, void *data, size_t pos);
int vector_erase(Vector *vec, size_t pos);
int vector_clear(Vector *vec);
int vector_reserve(Vector *vec, size_t new_capacity);
int vector_resize(Vector *vec, size_t new_size);
int vector_shrink_to_fit(Vector *vec);

#endif
