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
    size_t file_count;      /* Počet všech trénovacích souborů */
    size_t file_spam;       /* Počet trénovacích souborů obsahující spam */
    size_t file_ham;        /* Počet trénovacích souborů obsahující spam */
    double aprior_spam;     /* Apriorní pravděpodobnost výskytu spamu */
    double aprior_ham;      /* Apriorní pravděpodobnost výskytu hamu */
} hash_table;

/**
 * @brief Vytvoří hash tabulku.
 * @return Prázdná hash tabulka.\n
 *         NULL Tabulka se nepodařila vytvořit.
 */
hash_table *table_create(void);

/**
 * @brief Uvolní paměť hash tabulky.
 * @param table hash tabulka
 */
void table_free(hash_table **table);

/**
 * @brief Vypíše obsah hash tabulky na neprázdných kolonkách.
 * @param head hash tabulka
 */
void table_print(const hash_table *table);

/**
 * @brief Vloží prvek do tabulky.\n
 * @param table hash tabulka
 * @param key klíč vkládaného prvku
 * @param flag FLAG_SPAM spamový prvek\n
 *             FLAG_HAM hamový prvek
 * @return 0 Chyba.\n
 *         1 Úspěšné vložení.\n
 *         2 Úspěšné přepšání.\n
 *         3 Úspěšné přepšání, byl vložen nový ham.
 */
int table_insert(hash_table *table, const char *key, int flag);

/**
 * @brief Vrátí prvek z tabulky podle klíče.
 * @param table hash tabulka
 * @param key klíč podle kterého se hledá
 * @return Prvek v hash tabulce.\n
 *         NULL Tabulka neobsahuje prvek se stejným klíčem.
 */
entry *table_find(hash_table *table, const char *key);

#endif
