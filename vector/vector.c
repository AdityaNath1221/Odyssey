#include "vector.h"
#include <stdlib.h>

Vector *vector_create() {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (v != NULL) {
        v->capacity = DEFAULT_CAPACITY;
        v->size = 0;
        v->data = (int *)malloc(v->capacity * sizeof(int));
        if (v->data == NULL) {
            free(v);
            return NULL;
        }
    }
    return v;
}

void vector_destroy(Vector *vec) {
    if (vec != NULL) {
        free(vec->data);
        free(vec);
    }
}

int vector_size(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        return vec->size;
    }
}

int vector_capacity(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        return vec->capacity;
    }
}

int vector_empty(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else if (vec->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

int vector_full(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else if (vec->size == vec->capacity) {
        return 1;
    } else {
        return 0;
    }
}

int *vector_front(Vector *vec) {
    if (vec != NULL && !vector_empty(vec)) {
        return vec->data;
    }
    return NULL;
}

int *vector_back(Vector *vec) {
    if (vec != NULL && !vector_empty(vec)) {
        return vec->data + (vec->size - 1);
    }
    return NULL;
}

int *vector_at(Vector *vec, int pos) {
    if (vec != NULL && !vector_empty(vec)) {
        if (pos >= vec->size || pos < 0) {
            return NULL;
        } else {
            return vec->data + pos;
        }
    }
    return NULL;
}

int vector_push_back(Vector *vec, int data) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (vec->size == vec->capacity) {
        int new_capacity = vec->capacity * 2;
        if (vector_reserve(vec, new_capacity)) {
            return VECTOR_ERROR_OUT_OF_MEMORY;
        }
    }
    vec->data[vec->size] = data;
    vec->size++;
    return 0;
}

int vector_pop_back(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else if (vector_empty(vec)) {
        return VECTOR_ERROR_EMPTY;
    }
    vec->size--;
    return 0;
}

int vector_insert(Vector *vec, int data, int pos) {
    if (vec != NULL) {
        if ((vector_empty(vec) && pos == 0) || pos == vec->size) {
            if (vector_push_back(vec, data) == VECTOR_ERROR_OUT_OF_MEMORY) {
                return VECTOR_ERROR_OUT_OF_MEMORY;
            }
        } else if (pos > vec->size || pos < 0) {
            return VECTOR_ERROR_INVALID_INDEX;
        } else {
            if (vec->size == vec->capacity) {
                int new_capacity = vec->capacity * 2;
                if (vector_reserve(vec, new_capacity)) {
                    return VECTOR_ERROR_OUT_OF_MEMORY;
                }
            }
            int ele = data;
            for (int i = pos; i < vec->size; i++) {
                int temp = vec->data[i];
                vec->data[i] = ele;
                ele = temp;
            }
            vec->data[vec->size] = ele;
            vec->size++;
        }
        return 0;
    }
    return VECTOR_ERROR_NULL_POINTER;
}

int vector_erase(Vector *vec, int pos) {
    if (vec != NULL) {
        if (vector_empty(vec)) {
            return VECTOR_ERROR_EMPTY;
        } else if (pos >= vec->size || pos < 0) {
            return VECTOR_ERROR_INVALID_INDEX;
        } else {
            for (int i = pos; i < vec->size - 1; i++) {
                vec->data[i] = vec->data[i + 1];
            }
            vec->size--;
            return 0;
        }
    }
    return VECTOR_ERROR_NULL_POINTER;
}

int vector_clear(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        vec->size = 0;
        return 0;
    }
}

int vector_reserve(Vector *vec, int new_capacity) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        if (new_capacity > vec->capacity) {
            int *arr = realloc(vec->data, new_capacity * sizeof(int));
            if (arr == NULL) {
                return VECTOR_ERROR_OUT_OF_MEMORY;
            }
            vec->data = arr;
            vec->capacity = new_capacity;
            return 0;
        }
        return VECTOR_ERROR_INVALID_CAPACITY;
    }
}

int vector_resize(Vector *vec, int new_size) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        if (new_size > vec->capacity) {
            if (vector_reserve(vec, new_size)) {
                return VECTOR_ERROR_OUT_OF_MEMORY;
            }
        }
        vec->size = new_size;
        return 0;
    }
}

int vector_shrink_to_fit(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    } else {
        if (vec->size == vec->capacity) {
            return 0;
        } else if (vec->size == 0 && vec->capacity > DEFAULT_CAPACITY) {
            int *arr = realloc(vec->data, DEFAULT_CAPACITY * sizeof(int));
            if (arr == NULL) {
                return VECTOR_ERROR_OUT_OF_MEMORY;
            }
            vec->data = arr;
            vec->capacity = DEFAULT_CAPACITY;
            return 0;
        } else if (vec->size < vec->capacity && vec->size > 0) {
            int *arr = realloc(vec->data, vec->size * sizeof(int));
            if (arr == NULL) {
                return VECTOR_ERROR_OUT_OF_MEMORY;
            }
            vec->data = arr;
            vec->capacity = vec->size;
            return 0;
        }
    }
}
