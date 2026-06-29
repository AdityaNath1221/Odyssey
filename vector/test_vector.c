#include "vector.h"
#include <assert.h>
#include <stdio.h>

static void test_create(void);
static void test_push_back(void);
static void test_pop_back(void);
static void test_front_back(void);
static void test_at(void);
static void test_insert(void);
static void test_erase(void);
static void test_clear(void);
static void test_reserve(void);
static void test_resize(void);
static void test_shrink_to_fit(void);
static void test_null_pointer(void);
static void test_stress(void);

int main(void) {
    test_create();
    test_push_back();
    test_pop_back();
    test_front_back();
    test_at();
    test_insert();
    test_erase();
    test_clear();
    test_reserve();
    test_resize();
    test_shrink_to_fit();
    test_null_pointer();
    test_stress();

    puts("All vector tests passed!");
    return 0;
}

static void test_create(void) {
    Vector *vec = vector_create();

    assert(vec != NULL);

    assert(vector_size(vec) == 0);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);

    assert(vector_empty(vec) == 1);
    assert(vector_full(vec) == 0);

    assert(vector_front(vec) == NULL);
    assert(vector_back(vec) == NULL);
    assert(vector_at(vec, 0) == NULL);

    vector_destroy(vec);
}

static void test_push_back(void) {
    Vector *vec = vector_create();

    /* Push first element */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 1);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);
    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 10);

    /* Fill the initial capacity */
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 40) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 4);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);

    /* Trigger automatic resize */
    assert(vector_push_back(vec, 50) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 5);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY * 2);

    /* Verify all elements survived the resize */
    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);
    assert(*vector_at(vec, 3) == 40);
    assert(*vector_at(vec, 4) == 50);

    /* Front and back should still be correct */
    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 50);

    vector_destroy(vec);
}

static void test_pop_back(void) {
    Vector *vec = vector_create();

    /* Pop from an empty vector */
    assert(vector_pop_back(vec) == VECTOR_ERROR_EMPTY);

    /* Add some elements */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 3);

    /* Pop one element */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 2);
    assert(*vector_back(vec) == 20);

    /* Pop another */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 1);
    assert(*vector_back(vec) == 10);

    /* Pop the last element */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 0);
    assert(vector_empty(vec) == 1);

    /* Accessors should now return NULL */
    assert(vector_front(vec) == NULL);
    assert(vector_back(vec) == NULL);

    /* Popping again should fail */
    assert(vector_pop_back(vec) == VECTOR_ERROR_EMPTY);

    vector_destroy(vec);
}

static void test_front_back(void) {
    Vector *vec = vector_create();

    /* Empty vector */
    assert(vector_front(vec) == NULL);
    assert(vector_back(vec) == NULL);

    /* One element */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);

    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 10);

    /* Multiple elements */
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);

    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 30);

    /* Pop the last element */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);

    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 20);

    /* Pop until one element remains */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);

    assert(*vector_front(vec) == 10);
    assert(*vector_back(vec) == 10);

    /* Pop the last element */
    assert(vector_pop_back(vec) == VECTOR_SUCCESS);

    assert(vector_front(vec) == NULL);
    assert(vector_back(vec) == NULL);

    vector_destroy(vec);
}

static void test_at(void) {
    Vector *vec = vector_create();

    /* Empty vector */
    assert(vector_at(vec, 0) == NULL);
    assert(vector_at(vec, -1) == NULL);

    /* Populate vector */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 40) == VECTOR_SUCCESS);

    /* Valid indices */
    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);
    assert(*vector_at(vec, 3) == 40);

    /* Invalid indices */
    assert(vector_at(vec, -1) == NULL);
    assert(vector_at(vec, 4) == NULL);
    assert(vector_at(vec, 100) == NULL);

    vector_destroy(vec);
}

static void test_insert(void) {
    Vector *vec = vector_create();

    /* Insert into an empty vector */
    assert(vector_insert(vec, 10, 0) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 1);
    assert(*vector_at(vec, 0) == 10);

    /* Insert at the beginning */
    assert(vector_insert(vec, 5, 0) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 2);
    assert(*vector_at(vec, 0) == 5);
    assert(*vector_at(vec, 1) == 10);

    /* Insert at the end */
    assert(vector_insert(vec, 20, vector_size(vec)) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 3);
    assert(*vector_at(vec, 2) == 20);

    /* Insert in the middle */
    assert(vector_insert(vec, 15, 2) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 4);
    assert(*vector_at(vec, 0) == 5);
    assert(*vector_at(vec, 1) == 10);
    assert(*vector_at(vec, 2) == 15);
    assert(*vector_at(vec, 3) == 20);

    /* Force a resize */
    assert(vector_insert(vec, 25, 4) == VECTOR_SUCCESS);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY * 2);

    assert(*vector_at(vec, 4) == 25);

    /* Invalid indices */
    assert(vector_insert(vec, 100, -1) == VECTOR_ERROR_INVALID_INDEX);
    assert(vector_insert(vec, 100, vector_size(vec) + 1) ==
           VECTOR_ERROR_INVALID_INDEX);

    vector_destroy(vec);
}

static void test_erase(void) {
    Vector *vec = vector_create();

    /* Erasing from an empty vector */
    assert(vector_erase(vec, 0) == VECTOR_ERROR_EMPTY);

    /* Populate vector */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 40) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 50) == VECTOR_SUCCESS);

    /*
     * Current vector:
     * [10, 20, 30, 40, 50]
     */

    /* Erase the first element */
    assert(vector_erase(vec, 0) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 4);
    assert(*vector_at(vec, 0) == 20);
    assert(*vector_at(vec, 1) == 30);
    assert(*vector_at(vec, 2) == 40);
    assert(*vector_at(vec, 3) == 50);

    /* Erase a middle element */
    assert(vector_erase(vec, 1) == VECTOR_SUCCESS);

    /*
     * [20, 40, 50]
     */

    assert(vector_size(vec) == 3);
    assert(*vector_at(vec, 0) == 20);
    assert(*vector_at(vec, 1) == 40);
    assert(*vector_at(vec, 2) == 50);

    /* Erase the last element */
    assert(vector_erase(vec, 2) == VECTOR_SUCCESS);

    /*
     * [20, 40]
     */

    assert(vector_size(vec) == 2);
    assert(*vector_back(vec) == 40);

    /* Invalid indices */
    assert(vector_erase(vec, -1) == VECTOR_ERROR_INVALID_INDEX);
    assert(vector_erase(vec, vector_size(vec)) == VECTOR_ERROR_INVALID_INDEX);
    assert(vector_erase(vec, 100) == VECTOR_ERROR_INVALID_INDEX);

    vector_destroy(vec);
}

static void test_clear(void) {
    Vector *vec = vector_create();

    /* Clearing an empty vector */
    assert(vector_clear(vec) == VECTOR_SUCCESS);
    assert(vector_size(vec) == 0);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);
    assert(vector_empty(vec) == 1);

    /* Populate the vector */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);

    int capacity = vector_capacity(vec);

    /* Clear the vector */
    assert(vector_clear(vec) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 0);
    assert(vector_capacity(vec) == capacity);
    assert(vector_empty(vec) == 1);

    assert(vector_front(vec) == NULL);
    assert(vector_back(vec) == NULL);
    assert(vector_at(vec, 0) == NULL);

    /* Vector should still be usable after clear */
    assert(vector_push_back(vec, 100) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 1);
    assert(*vector_front(vec) == 100);
    assert(*vector_back(vec) == 100);

    vector_destroy(vec);
}

static void test_reserve(void) {
    Vector *vec = vector_create();

    /* Populate vector */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);

    int old_capacity = vector_capacity(vec);

    /* Reserve a larger capacity */
    assert(vector_reserve(vec, 20) == VECTOR_SUCCESS);

    assert(vector_capacity(vec) == 20);
    assert(vector_size(vec) == 3);

    /* Verify elements are preserved */
    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);

    /* Reserve the same capacity */
    assert(vector_reserve(vec, 20) == VECTOR_ERROR_INVALID_CAPACITY);

    /* Reserve a smaller capacity */
    assert(vector_reserve(vec, old_capacity) == VECTOR_ERROR_INVALID_CAPACITY);
    assert(vector_reserve(vec, 2) == VECTOR_ERROR_INVALID_CAPACITY);

    /* Nothing should have changed */
    assert(vector_capacity(vec) == 20);
    assert(vector_size(vec) == 3);

    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);

    vector_destroy(vec);
}

static void test_resize(void) {
    Vector *vec = vector_create();

    /* Populate vector */
    assert(vector_push_back(vec, 10) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 20) == VECTOR_SUCCESS);
    assert(vector_push_back(vec, 30) == VECTOR_SUCCESS);

    /* Grow within capacity */
    assert(vector_resize(vec, 4) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 4);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);

    /* Existing elements should remain */
    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);

    /* Grow beyond capacity */
    assert(vector_resize(vec, 10) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 10);
    assert(vector_capacity(vec) == 10);

    /* Existing elements should still remain */
    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);
    assert(*vector_at(vec, 2) == 30);

    /* Shrink */
    assert(vector_resize(vec, 2) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 2);
    assert(vector_capacity(vec) == 10);

    assert(*vector_at(vec, 0) == 10);
    assert(*vector_at(vec, 1) == 20);

    /* Resize to zero */
    assert(vector_resize(vec, 0) == VECTOR_SUCCESS);

    assert(vector_size(vec) == 0);
    assert(vector_empty(vec));

    vector_destroy(vec);
}

static void test_shrink_to_fit(void) {
    Vector *vec = vector_create();

    /* Shrink an empty vector */
    assert(vector_shrink_to_fit(vec) == VECTOR_SUCCESS);
    assert(vector_capacity(vec) == DEFAULT_CAPACITY);
    assert(vector_size(vec) == 0);

    /* Fill the vector */
    for (int i = 1; i <= 10; i++) {
        assert(vector_push_back(vec, i) == VECTOR_SUCCESS);
    }

    assert(vector_capacity(vec) >= 10);

    /* Remove some elements */
    for (int i = 0; i < 5; i++) {
        assert(vector_pop_back(vec) == VECTOR_SUCCESS);
    }

    assert(vector_size(vec) == 5);

    /* Shrink */
    assert(vector_shrink_to_fit(vec) == VECTOR_SUCCESS);

    assert(vector_capacity(vec) == vector_size(vec));

    /* Verify data */
    for (int i = 0; i < 5; i++) {
        assert(*vector_at(vec, i) == i + 1);
    }

    vector_destroy(vec);
}

static void test_null_pointer(void) {

    assert(vector_size(NULL) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_capacity(NULL) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_empty(NULL) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_full(NULL) == VECTOR_ERROR_NULL_POINTER);

    assert(vector_front(NULL) == NULL);
    assert(vector_back(NULL) == NULL);
    assert(vector_at(NULL, 0) == NULL);

    assert(vector_push_back(NULL, 10) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_pop_back(NULL) == VECTOR_ERROR_NULL_POINTER);

    assert(vector_insert(NULL, 10, 0) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_erase(NULL, 0) == VECTOR_ERROR_NULL_POINTER);

    assert(vector_clear(NULL) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_reserve(NULL, 100) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_resize(NULL, 100) == VECTOR_ERROR_NULL_POINTER);
    assert(vector_shrink_to_fit(NULL) == VECTOR_ERROR_NULL_POINTER);

    vector_destroy(NULL);
}

static void test_stress(void) {
    Vector *vec = vector_create();

    /* Push lots of elements */
    for (int i = 0; i < 10000; i++) {
        assert(vector_push_back(vec, i) == VECTOR_SUCCESS);
    }

    assert(vector_size(vec) == 10000);

    /* Verify all elements */
    for (int i = 0; i < 10000; i++) {
        assert(*vector_at(vec, i) == i);
    }

    /* Pop everything */
    for (int i = 9999; i >= 0; i--) {
        assert(*vector_back(vec) == i);
        assert(vector_pop_back(vec) == VECTOR_SUCCESS);
    }

    assert(vector_empty(vec));

    vector_destroy(vec);
}
