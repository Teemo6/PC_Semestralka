#ifndef PC_SEMESTRALKA_HASH_TABLE_H
#define PC_SEMESTRALKA_HASH_TABLE_H

#include "hash_table_entry.h"

/* Velikost Hash tabulky */
#define TABLE_SIZE 26489

/* Prvocislo podle ktereho se dela hash funkce */
#define HASH_PRIME 13

/*
 * @brief Hash tabulka.
 */
typedef struct HASH_TABLE {
    entry **entries;        /* Položka tabulky */
    size_t size;            /* Velikost hash tabulky */
    size_t count;           /* Počet vložených položek */
    size_t count_spam;      /* Počet vložených položek spamu */
    size_t count_ham;       /* Počet vložených položek hamu */
    size_t unique;          /* Počet vložených unikátních položek */
    size_t unique_spam;     /* Počet vložených unikátních položek spamu */
    size_t unique_ham;      /* Počet vložených unikátních položek hamu */
} hash_table;

/*
 * @brief Vytvoří hash tabulku.
 * @return prázdná hash tabulka.\n
 *         NULL pokud se nepodařila vytvořit.
 */
hash_table *table_create(void);

void table_free(hash_table **table);

void table_print(const hash_table *table);

int table_insert(hash_table *table, const char *key, int flag);

entry *table_find(hash_table *table, const char *key);

#endif
