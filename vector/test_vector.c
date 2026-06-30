#include "vector.h"
#include <assert.h>
#include <stdio.h>

int main() {
    Vector *v = vector_create(sizeof(double));

    assert(v != NULL);

    for (double i = 0; i < 100000; i++)
        vector_push_back(v, &i);

    for (double i = 0; i < 50000; i++)
        vector_pop_back(v);

    vector_destroy(v);

    puts("All test cases passed!");

    return 0;
}
