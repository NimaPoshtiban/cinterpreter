#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE 100

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* data[HASHMAP_SIZE];
} hashmap;

unsigned int hashmap_hash(const char* key);
void hashmap_add(hashmap*hashmap, const char* key, const char* value);
void hashmap_remove_key(hashmap*hashmap, const char* key);
char* hashmap_find(hashmap*hashmap, const char* key);
hashmap* hashmap_create(void);
#endif /* HASHMAP_H */
