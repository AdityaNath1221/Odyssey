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
| push_back | O(1) amortized |
| pop_back | O(1) |
| at | O(1) |
| front | O(1) |
| back | O(1) |
| insert | O(n) |
| erase | O(n) |
| reserve | O(n) |
| resize | O(n) (if reallocation occurs) |
| clear | O(1) |
| shrink_to_fit | O(n) |

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
# Detailed Functionalites

## vector_create

```c
Vector *vector_create(size_t element_size);
```

Creates a new vector capable of storing objects of size `element_size`.

### Parameters

| Name | Description |
|------|-------------|
| element_size | Size of one element in bytes |

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
| vec | Pointer to the vector |

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
| vec | Pointer to the vector |

### Returns

- The number of elements in the vector.
- Returns `0` if `vec` is `NULL`.

### Example

```C
size_t size = vector_size(vec);
```

---
## vector_capacity

Returns the current allocated capacity.

```c
size_t cap = vector_capacity(vec);
```

---
## vector_element_size

Returns the size of one stored element.

```c
size_t bytes = vector_element_size(vec);
```

---
## vector_empty

Returns

- `1` if empty
- `0` otherwise
- error code on invalid vector

---
## vector_full

Returns

- `1` if size equals capacity
- `0` otherwise

---
## vector_front

Returns a pointer to the first element.

Returns `NULL` if the vector is empty.

```c
int first = *(int *)vector_front(vec);
```

---
## vector_back

Returns a pointer to the last element.

Returns `NULL` if the vector is empty.

---
## vector_at

Returns a pointer to the element at the specified position.

Returns `NULL` if the index is invalid.

```c
int value = *(int *)vector_at(vec, 4);
```

---
## vector_push_back

Appends an element to the end of the vector.

Automatically doubles the capacity if necessary.

### Returns

`VECTOR_SUCCESS` on success.

### Example

```c
int x = 42;
vector_push_back(vec, &x);
```

---
## vector_pop_back

Removes the last element.

Does not reduce capacity.

Returns an error if the vector is empty.

---
## vector_insert

Inserts an element before the specified position.

Elements after the insertion point are shifted one position to the right.

```c
vector_insert(vec, &value, 2);
```

---
## vector_erase

Removes the element at the specified position.

Remaining elements are shifted left.

```c
vector_erase(vec, 3);
```

---
## vector_clear

Removes all elements.

Allocated memory is preserved.

Capacity remains unchanged.

---
## vector_reserve

Ensures the vector has at least the requested capacity.

If the requested capacity is smaller than the current capacity, nothing happens.

```c
vector_reserve(vec, 1000);
```

---
## vector_resize

Changes the logical size of the vector.

If the new size exceeds the current capacity, the vector is reallocated.

**Note:** Newly added elements are **uninitialized**.

```c
vector_resize(vec, 50);
```

---
## vector_shrink_to_fit

Reduces the allocated capacity to match the current size.

If the vector is empty, capacity is reduced to `DEFAULT_CAPACITY`.

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
