#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"



unsigned int hashmap_hash(const char* key) {
    unsigned int hash_value = 0;
    for (size_t i = 0; i < strlen(key); i++) {
        hash_value = 31 * hash_value + key[i];
    }
    return hash_value % HASHMAP_SIZE;
}

void hashmap_add(hashmap* hashmap, const char* key, const char* value) {
    unsigned int index = hashmap_hash(key);
    KeyValuePair* kvp = malloc(sizeof(KeyValuePair));
    kvp->key = _strdup(key);
    kvp->value = _strdup(value);
    hashmap->data[index] = kvp;
}

void hashmap_remove_key(hashmap* hashmap, const char* key) {
    unsigned int index = hashmap_hash(key);
    KeyValuePair* kvp = hashmap->data[index];
    if (kvp != NULL && strcmp(kvp->key, key) == 0) {
        free(kvp->key);
        free(kvp->value);
        free(kvp);
        hashmap->data[index] = NULL;
    }
}

char* hashmap_find(hashmap* hashmap, const char* key) {
    unsigned int index = hashmap_hash(key);
    KeyValuePair* kvp = hashmap->data[index];
    if (kvp != NULL) {
        if(strcmp(kvp->key, key) == 0)
            return kvp->value;
    }
    return NULL;
}

hashmap* hashmap_create(void){
    hashmap* map = malloc(sizeof(hashmap));
    if (map != NULL) {
    memset(map, 0, sizeof(hashmap));
    }
    return map;
}
