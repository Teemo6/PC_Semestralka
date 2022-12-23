#ifndef PC_SEMESTRALKA_HASH_TABLE_H
#define PC_SEMESTRALKA_HASH_TABLE_H

/* Velikost hash tabulky */
#define TABLE_SIZE 1531

/* Prvocislo podle ktereho se dela hash funkce */
#define HASH_PRIME 33

/* Prvek hash tabulky */
typedef struct ENTRY {
    char word[STRING_LENGHT];
    double probability;
} entry;

/* Hash tabulka */
typedef struct HASH_TABLE {
    entry *entries;
    size_t size;
} hash_table;

/* Iterator */
typedef struct ITERATOR {
    const char* key;
    void* value;

    hash_table* _table;
    size_t _index;
} iterator;


hash_table *table_create(void);

void table_destroy(hash_table *table);

void *table_get(hash_table *table, const char *key);

const char *table_set(hash_table *table, const char *key, void *value);

iterator table_iterator(hash_table *table);

int table_has_next(iterator *it);

#endif
