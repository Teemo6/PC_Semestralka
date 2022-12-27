#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "hash_table.h"

LOCAL int hash_function(const char *word){
    size_t i, word_len;
    int hash;

    if(!word){
        return -1;
    }

    word_len = strlen(word);
    hash = 0;

    for(i = 0; i < word_len; i++){
        hash = ((hash * HASH_PRIME) + word[i]) % TABLE_SIZE;
    }
    return hash;
}

hash_table *table_create(void){
    size_t i;
    hash_table *table;

    /* Alokace pameti hash table */
    table = (hash_table *)malloc(sizeof(hash_table));
    if (!table) return NULL;

    table->size = TABLE_SIZE;
    table->entry_count = 0;
    table->spam_count = 0;
    table->ham_count = 0;

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
    printf("Pocet vsech slov:\t%lu\n", (unsigned long)table->entry_count);
    printf("Pocet slov spamu:\t%lu\n", (unsigned long)table->spam_count);
    printf("Pocet slov hamu:\t%lu\n", (unsigned long)table->ham_count);
    printf("------------------------------\n");
}

int table_insert(hash_table *table, const char *key, int flag){
    entry *e_new, *e_table;
    int index;

    if(!table || !key){
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

    /* Pocitadla */
    if(flag == FLAG_SPAM){
        e_new->spam_count++;
        table->spam_count++;
    }

    if(flag == FLAG_HAM){
        e_new->ham_count++;
        table->ham_count++;
    }
    table->entry_count++;

    /* Prvek v tabulce neni */
    if(e_table == NULL){
        table->entries[index] = e_new;
        return 1;
    }

    /* V tabulce uz je nejaky prvek, kolize */
    return entry_insert(e_table, e_new);
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
