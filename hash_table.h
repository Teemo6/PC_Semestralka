#ifndef PC_SEMESTRALKA_HASH_TABLE_H
#define PC_SEMESTRALKA_HASH_TABLE_H

#include "hash_table_entry.h"

/* Vychozi velikost hash_function tabulky */
#define INIT_TABLE_SIZE 1511

/* Prvocislo podle ktereho se dela hash_function funkce */
#define HASH_PRIME 13

/* Hash tabulka */
typedef struct HASH_TABLE {
    entry **entries;
    size_t entry_count;
    size_t size;
} hash_table;

hash_table *table_create(void);

void table_free(hash_table **table);

void table_print(const hash_table *table);

void table_insert(hash_table *table, const char *key, const char *value);

void table_get(hash_table *table, const char *key);

#endif
