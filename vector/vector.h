#ifndef VECTOR_H
#define VECTOR_H

// ERROR CODES
#define VECTOR_SUCCESS 0
#define VECTOR_ERROR_NULL_POINTER -99
#define VECTOR_ERROR_OUT_OF_MEMORY -98
#define VECTOR_ERROR_INVALID_INDEX -97
#define VECTOR_ERROR_EMPTY -96
#define VECTOR_ERROR_INVALID_CAPACITY -95

#define DEFAULT_CAPACITY 4

// DATA STRUCTURE
typedef struct Vector {
    int *data;
    int size;
    int capacity;
} Vector;

// CONSTRUCTORS/DESTRUCTORS
Vector *vector_create();
void vector_destroy(Vector *vec);

// METAINFO
int vector_size(Vector *vec);
int vector_capacity(Vector *vec);
int vector_empty(Vector *vec);
int vector_full(Vector *vec);

// ELEMENT ACCESS
int *vector_front(Vector *vec);
int *vector_back(Vector *vec);
int *vector_at(Vector *vec, int pos);

// MODIFIERS
int vector_push_back(Vector *vec, int data);
int vector_pop_back(Vector *vec);
int vector_insert(Vector *vec, int data, int pos);
int vector_erase(Vector *vec, int pos);
int vector_clear(Vector *vec);
int vector_reserve(Vector *vec, int new_capacity);
int vector_resize(Vector *vec, int new_size);
int vector_shrink_to_fit(Vector *vec);

#endif
