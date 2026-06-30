# Vector API Reference

## Overview

A **Vector** is a dynamically resizable contiguous array capable of storing elements of any type.

The library stores elements of any data type using `void *` and keeps track of the element size internally. Memory management is automatic, with dynamic growth when the vector becomes full.

---
## Features

- Generic storage (`void *`)
- Automatic resizing
- O(1) amortized push_back
- Random access
- Insert and erase at arbitrary positions
- Reserve and shrink capacity
- STL-inspired API
- Error codes instead of terminating the program

---
## Complexity

| Operation | Complexity |
|-----------|------------|
| vector_push_back | O(1) amortized |
| vector_pop_back | O(1) |
| vector_at | O(1) |
| vector_front | O(1) |
| vector_back | O(1) |
| vector_insert | O(n) |
| vector_erase | O(n) |
| vector_reserve | O(n) |
| vector_resize | O(n) (if reallocation occurs) |
| vector_clear | O(1) |
| vector_shrink_to_fit | O(n) |

---
## Error Codes

| Code | Meaning |
|------|---------|
| VECTOR_SUCCESS | Operation completed successfully |
| VECTOR_ERROR_NULL_POINTER | NULL pointer supplied |
| VECTOR_ERROR_OUT_OF_MEMORY | Memory allocation failed |
| VECTOR_ERROR_INVALID_INDEX | Index out of bounds |
| VECTOR_ERROR_EMPTY | Vector contains no elements |
| VECTOR_ERROR_INVALID_CAPACITY | Invalid capacity |
| VECTOR_ERROR_INVALID_DATA | NULL data pointer supplied |
| VECTOR_ERROR_OVERFLOW | Integer overflow detected |

---
# Detailed Functionalities

## vector_create

```c
Vector *vector_create(size_t element_size);
```

Creates a new vector capable of storing objects of size `element_size`.

### Parameters

| Name | Description |
|------|-------------|
| element_size | Size of one element in bytes. |

### Returns

Pointer to the new vector, or `NULL` on failure.

### Example

```c
Vector *ints = vector_create(sizeof(int));
Vector *floats = vector_create(sizeof(float));
Vector *points = vector_create(sizeof(Point));
```

---
## vector_destroy

```c
void vector_destroy(Vector *vec);
```

Releases all memory owned by the vector.

### Parameters

| Name | Description |
|------|-------------|
| vec | Pointer to the vector. |

> **NOTE:** Passing a `NULL` pointer is safe and has no effect.

### Returns

Doesn't return anything.

### Example

```c
vector_destroy(vec);
```

---
## vector_size

```c
size_t vector_size(const Vector *vec);
```

Returns the number of elements currently stored in the vector.

### Parameters

| Name | Description |
|------|-------------|
| vec | Pointer to the vector. |

### Returns

- The number of elements in the vector.
- Returns `0` if `vec` is `NULL`.

### Example

```C
size_t size = vector_size(vec);
```

---
## vector_capacity

```c
size_t vector_capacity(const Vector *vec);
```

Returns the current allocated capacity of the vector.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

- The current capacity of the vector.
- Returns `0` if `vec` is `NULL`.

### Example

```c
size_t capacity = vector_capacity(vec);
```
---
## vector_element_size

```c
size_t vector_element_size(const Vector *vec);
```

Returns the size, in bytes, of each element stored in the vector.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

- The size of each element, in bytes.
- Returns `0` if `vec` is `NULL`.

### Example

```c
size_t element_size = vector_element_size(vec);
```

---
## vector_empty

```c
int vector_empty(const Vector *vec);
```

Checks whether the vector contains any elements.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

| Value | Description |
|------|-------------|
| `1` | The vector is empty. |
| `0` | The vector contains one or more elements. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |

### Example

```c
if (vector_empty(vec) == 1) {
    printf("Vector is empty.\n");
}
```

---
## vector_full

```c
int vector_full(const Vector *vec);
```

Checks whether the vector has reached its allocated capacity.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

| Value | Description |
|------|-------------|
| `1` | The vector is full. |
| `0` | The vector has available capacity. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |

### Example

```c
if (vector_full(vec) == 1) {
    printf("Vector is full.\n");
}
```

---
## vector_front

```c
void *vector_front(const Vector *vec);
```

Returns a pointer to the first element in the vector.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

- A pointer to the first element in the vector.
- Returns `NULL` if `vec` is `NULL` or the vector is empty.

### Example

```c
int first = *(int *)vector_front(vec);
```

---
## vector_back

```c
void *vector_back(const Vector *vec);
```

Returns a pointer to the last element in the vector.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

- A pointer to the last element in the vector.
- Returns `NULL` if `vec` is `NULL` or the vector is empty.

### Example

```c
int last = *(int *)vector_back(vec);
```

---
## vector_at

```c
void *vector_at(const Vector *vec, size_t pos);
```

Returns a pointer to the element at the specified position in the vector.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `pos` | Zero-based index of the element to access. |

### Returns

- A pointer to the element at the specified position.
- Returns `NULL` if `vec` is `NULL` or `pos` is out of bounds.

### Example

```c
int value = *(int *)vector_at(vec, 4);
```

---
## vector_push_back

```c
int vector_push_back(Vector *vec, const void *data);
```

Appends an element to the end of the vector.

If the vector has reached its allocated capacity, the capacity is automatically increased before the element is inserted.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `data` | Pointer to the element to be copied into the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The element was appended successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_INVALID_DATA` | `data` is `NULL`. |
| `VECTOR_ERROR_OUT_OF_MEMORY` | Memory allocation failed while expanding the vector. |
| `VECTOR_ERROR_OVERFLOW` | Increasing the vector's capacity would cause an integer overflow. |

### Example

```c
int value = 42;
vector_push_back(vec, &value);
```

---
## vector_pop_back

```c
int vector_pop_back(Vector *vec);
```

Removes the last element from the vector.

This operation decreases the size of the vector by one but does not reduce its allocated capacity.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The last element was removed successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_EMPTY` | The vector is empty. |

### Example

```c
if (vector_pop_back(vec) == VECTOR_SUCCESS) {
    printf("Last element removed.\n");
}
```

---
## vector_insert

```c
int vector_insert(Vector *vec, void *data, size_t pos);
```

Inserts an element at the specified position in the vector.

Elements at and after the specified position are shifted one position to the right. If the vector has reached its allocated capacity, the capacity is automatically increased before the element is inserted.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `data` | Pointer to the element to be copied into the vector. |
| `pos` | Zero-based index at which the element is to be inserted. Valid values are in the range `[0, size]`. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The element was inserted successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_INVALID_DATA` | `data` is `NULL`. |
| `VECTOR_ERROR_INVALID_INDEX` | `pos` is outside the valid range. |
| `VECTOR_ERROR_OUT_OF_MEMORY` | Memory allocation failed while expanding the vector. |
| `VECTOR_ERROR_OVERFLOW` | Increasing the vector's capacity would cause an integer overflow. |

### Example

```c
int value = 42;
vector_insert(vec, &value, 2);
```

---
## vector_erase

```c
int vector_erase(Vector *vec, size_t pos);
```

Removes the element at the specified position from the vector.

Elements after the specified position are shifted one position to the left. This operation decreases the size of the vector by one but does not reduce its allocated capacity.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `pos` | Zero-based index of the element to remove. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The element was removed successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_INVALID_INDEX` | `pos` is out of bounds. |

### Example

```c
vector_erase(vec, 2);
```

---
## vector_clear

```c
int vector_clear(Vector *vec);
```

Removes all elements from the vector.

This operation sets the size of the vector to zero but preserves its allocated capacity.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The vector was cleared successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |

### Example

```c
vector_clear(vec);
```

---
## vector_reserve

```c
int vector_reserve(Vector *vec, size_t new_capacity);
```

Increases the allocated capacity of the vector to at least `new_capacity`.

If `new_capacity` is less than or equal to the current capacity, the vector is left unchanged.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `new_capacity` | Minimum capacity to reserve for the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The capacity was increased successfully, or no reallocation was necessary. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_OUT_OF_MEMORY` | Memory allocation failed or the requested capacity is too large. |

### Example

```c
vector_reserve(vec, 100);
```

---
## vector_resize

```c
int vector_resize(Vector *vec, size_t new_size);
```

Changes the size of the vector to `new_size`.

If `new_size` is greater than the current capacity, the vector is automatically expanded to accommodate the requested size.

> **NOTE:** If the vector is expanded, the newly added elements are **uninitialized**.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |
| `new_size` | The new size of the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The vector was resized successfully. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_OUT_OF_MEMORY` | Memory allocation failed while expanding the vector. |

### Example

```c
vector_resize(vec, 50);
```

---
## vector_shrink_to_fit

```c
int vector_shrink_to_fit(Vector *vec);
```

Reduces the allocated capacity of the vector to match its current size.

If the vector is empty, its capacity is reduced to `DEFAULT_CAPACITY`.

### Parameters

| Name | Description |
|------|-------------|
| `vec` | Pointer to the vector. |

### Returns

| Value | Description |
|------|-------------|
| `VECTOR_SUCCESS` | The vector was shrunk successfully, or no reallocation was necessary. |
| `VECTOR_ERROR_NULL_POINTER` | `vec` is `NULL`. |
| `VECTOR_ERROR_OUT_OF_MEMORY` | Memory reallocation failed. |

### Example

```c
vector_shrink_to_fit(vec);
```

---
# Notes

- The vector stores copies of objects, not pointers to caller-owned memory (unless the stored type itself is a pointer).
- Elements are copied using `memcpy`.
- Stored types should be trivially copyable.
- The library performs no automatic destruction of stored objects.
- Pointer stability is **not guaranteed**. Any operation that reallocates the vector may invalidate pointers previously obtained from `vector_at`, `vector_front`, or `vector_back`.
