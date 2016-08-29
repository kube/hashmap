#include "hashmap.h"

int main(void)
{
    t_hashmap* hashmap = new_hashmap(1024);

    printf("%zu\n", hashmap->map_size);
    printf("%zu\n", hashmap->count);

    printf("%p\n", hashmap->map[0]);

    hashmap_set(hashmap, "Hello", "World");

    printf("%s\n", hashmap_get(hashmap, "Hi"));
    printf("%s\n", hashmap_get(hashmap, "Hello"));

    hashmap_set(hashmap, "Hello", "Everybody!");
    printf("%s\n", hashmap_get(hashmap, "Hello"));

    delete_hashmap(hashmap);

    return 0;
}