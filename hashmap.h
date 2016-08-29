#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>

typedef struct              s_hashmap_node
{
    long                    hash_verif;
    void*                   value;
    struct s_hashmap_node*  next;
}                           t_hashmap_node;

typedef struct              s_hashmap
{
    size_t                  map_size;
    size_t                  count;
    t_hashmap_node**        map;
}                           t_hashmap;


t_hashmap*  new_hashmap(size_t size);
void        delete_hashmap(t_hashmap* hashmap);

void        hashmap_set(t_hashmap* hashmap, char* key, void* value);
void        hashmap_unset(t_hashmap* hashmap, char* key);
void*       hashmap_get(t_hashmap* hashmap, char* key);

#endif
