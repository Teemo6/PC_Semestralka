#ifndef PC_SEMESTRALKA_HASH_TABLE_H
#define PC_SEMESTRALKA_HASH_TABLE_H

#include "hash_table_entry.h"

/* Velikost Hash tabulky */
#define TABLE_SIZE 26489

/* Prvocislo podle ktereho se dela hash funkce */
#define HASH_PRIME 13

/* Hash tabulka */
typedef struct HASH_TABLE {
    entry **entries;
    size_t count;
    size_t count_spam;
    size_t count_ham;
    size_t unique;
    size_t unique_spam;
    size_t unique_ham;
    size_t size;
} hash_table;

hash_table *table_create(void);

void table_free(hash_table **table);

void table_print(const hash_table *table);

int table_insert(hash_table *table, const char *key, int flag);

entry *table_find(hash_table *table, const char *key);

#endif
