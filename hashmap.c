#include "hashmap.h"

static long         hash_primary(char* word)
{
    long            hash = 0;
    size_t          counter;

    for (counter = 0; word[counter]; counter++)
        hash = word[counter] + hash << 6 + hash << 16 - hash;

    return hash;
}

static long         hash_secondary(char* word)
{
    long            hash = 5381;
    size_t          counter;

    for (counter = 0; word[counter]; counter++)
        hash = word[counter] + hash << 5 + hash;

    return hash;
}

t_hashmap*          new_hashmap(size_t size)
{
    t_hashmap*      hashmap;

    hashmap = malloc(sizeof(t_hashmap));
    hashmap->map = malloc(size * sizeof(t_hashmap_node*));
    hashmap->map_size = size;
    hashmap->count = 0;

    return hashmap;
}

void                delete_hashmap(t_hashmap* hashmap)
{
    size_t          index;
    t_hashmap_node* current_node;
    t_hashmap_node* next_node;

    for (index = 0; index < hashmap->map_size; index++)
    {
        current_node = hashmap->map[index];

        while (current_node) {
            next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }

    free(hashmap->map);
    free(hashmap);
}

void                hashmap_set(t_hashmap* hashmap, char* key, void* value)
{
    long            hash_index;
    long            hash_verif;
    t_hashmap_node* current_node;

    hash_index = hash_primary(key) % hashmap->map_size;
    hash_verif = hash_secondary(key);

    if (!hashmap->map[hash_index])
    {
        hashmap->map[hash_index] = malloc(sizeof(t_hashmap_node));
        current_node = hashmap->map[hash_index];
    }
    else
    {
        current_node = hashmap->map[hash_index];

        while (current_node->next
            && current_node->hash_verif != hash_verif)
            current_node = current_node->next;

        if (current_node->hash_verif != hash_verif)
        {
            current_node->next = malloc(sizeof(t_hashmap_node));
            current_node = current_node->next;
        }
    }
    current_node->hash_verif = hash_verif;
    current_node->value = value;
}

// void                hashmap_unset(t_hashmap* hashmap, char* key);

void*               hashmap_get(t_hashmap* hashmap, char* key)
{
    long            hash_a;
    long            hash_b;
    t_hashmap_node* current_node;

    hash_a = hash_primary(key);
    hash_b = hash_secondary(key);

    current_node = hashmap->map[hash_a % hashmap->map_size];

    if (!current_node)
        return NULL;

    while (current_node->next && current_node->hash_verif != hash_b)
        current_node = current_node->next;

    return current_node->value;
}