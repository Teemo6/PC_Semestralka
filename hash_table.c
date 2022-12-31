#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "hash_table.h"

/**
 * @brief Hashovací funkce tabulky.
 * @param key klíč k hashování
 * @return Hash klíče.\n
 *         -1 Chyba\n
 *         int Hash klíče
 */
LOCAL int hash_function(const char *key){
    size_t i, word_len;
    int hash;

    if(!key){
        return -1;
    }

    word_len = strlen(key);
    hash = 0;

    for(i = 0; i < word_len; i++){
        hash = ((hash * HASH_PRIME) + key[i]) % TABLE_SIZE;
    }
    return hash;
}

hash_table *table_create(void){
    size_t i;
    hash_table *table;

    /* Alokace pameti hash table */
    table = (hash_table *)malloc(sizeof(hash_table));
    if (!table){
        return NULL;
    }

    /* Inicializace atributu */
    table->size = TABLE_SIZE;
    table->count = 0;
    table->count_spam = 0;
    table->count_ham = 0;
    table->unique = 0;
    table->unique_spam = 0;
    table->unique_ham = 0;
    table->file_count = 0;
    table->file_spam = 0;
    table->file_ham = 0;
    table->aprior_spam = 0;
    table->aprior_ham = 0;

    /* Alokace pameti prvku */
    table->entries = (entry **)calloc(table->size, sizeof(entry *));
    if(!table->entries){
        free(table);
        return NULL;
    }

    /* Nastaveni vsech prvku na NULL */
    for(i = 0; i < table->size; i++){
        table->entries[i] = NULL;
    }
    return table;
}

void table_free(hash_table **table){
    size_t i;

    if(!table || !*table){
        return;
    }

    for(i = 0; i < (*table)->size; i++){
        entry *e_table = (*table)->entries[i];
        if(e_table != NULL){
            entry_free(&e_table);
        }
    }

    free((*table)->entries);
    free(*table);
    *table = NULL;
}

void table_print(const hash_table *table){
    size_t i;

    if(table == NULL){
        return;
    }

    for(i = 0; i < table->size; i++){
        if(table->entries[i]){
            printf("%lu\t\t", (unsigned long)i);
            entry_print(table->entries[i]);
        }
    }
    printf("------------------------------\n");
    printf("Common entry count:\t%lu\n",    (unsigned long)table->count);
    printf("Common spam count:\t%lu\n",     (unsigned long)table->count_spam);
    printf("Common ham count:\t%lu\n\n",    (unsigned long)table->count_ham);
    printf("Unique entry count:\t%lu\n",    (unsigned long)table->unique);
    printf("Unique spam count:\t%lu\n",     (unsigned long)table->unique_spam);
    printf("Unique ham count:\t%lu\n",      (unsigned long)table->unique_ham);
    printf("------------------------------\n");
}

int table_insert(hash_table *table, const char *key, int flag){
    entry *e_new, *e_table;
    int index, result;

    if(!table || !key || !flag){
        return 0;
    }

    /* Prazdne slovo */
    index = hash_function(key);
    if(index == -1){
        return 0;
    }

    e_table = table->entries[index];
    e_new = entry_create(key);

    if(e_new == NULL){
        return 0;
    }

    /* Pocitadlo vlozeni */
    if(flag == FLAG_SPAM){
        e_new->count_entry_spam++;
        table->count_spam++;
    }

    if(flag == FLAG_HAM){
        e_new->count_entry_ham++;
        table->count_ham++;
    }
    table->count++;

    /* Prvek v tabulce neni */
    if(e_table == NULL){
        table->entries[index] = e_new;
        /* Pocitadlo unikatnich polozek */
        if(flag == FLAG_SPAM){
            table->unique_spam++;
        }
        if(flag == FLAG_HAM){
            table->unique_ham++;
        }
        table->unique++;
        return 1;
    }

    /* V tabulce uz je nejaky prvek, kolize */
    result = entry_insert(e_table, e_new);
    if(result == 1){
        /* Pocitadlo unikatnich polozek */
        if(flag == FLAG_SPAM){
            table->unique_spam++;
        }
        if(flag == FLAG_HAM){
            table->unique_ham++;
        }
        table->unique++;
    }

    /* Byl vlozen novy ham */
    if(result == 3){
        table->unique_ham++;
    }
    return result;
}

entry *table_find(hash_table *table, const char *key){
    entry *e_table;
    int index;

    if(!table || !key){
        return NULL;
    }

    /* Prazdne slovo */
    index = hash_function(key);
    if(index == -1){
        return NULL;
    }

    e_table = table->entries[index];

    /* Prvek se v tabulce nenachazi */
    if(e_table == NULL){
        return NULL;
    }

    return entry_find(e_table, key);
}
