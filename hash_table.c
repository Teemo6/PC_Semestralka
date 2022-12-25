#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "hash_table.h"

LOCAL size_t hash_function(const char *word){
    size_t i, hash, word_len;

    word_len = strnlen(word, STRING_LENGHT);
    hash = 0;

    for(i = 0; i < word_len; i++){
        hash = ((hash * HASH_PRIME) + word[i]) % INIT_TABLE_SIZE;
    }
    return hash;
}

LOCAL void handle_collision(const hash_table *table, const size_t index, const entry *e_new){

}

hash_table *table_create(void){
    size_t i;
    hash_table *table;

    /* Alokace pameti hash_function table */
    table = (hash_table *)malloc(sizeof(hash_table));
    if (!table){
        return NULL;
    }
    table->size = INIT_TABLE_SIZE;
    table->entry_count = 0;

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

    free((**table).entries);
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
            printf("%lu\t\t%s\n", (unsigned long)i, table->entries[i]->value);
        }
    }
    printf("Pocet prvku:\t%lu\n", (unsigned long)table->entry_count);
}


void table_insert(hash_table *table, const char *key, const char *value){
    entry *e_new, *e_table;
    size_t index;

    if(!table || !key){
        return;
    }
    index = hash_function(key);
    e_table = table->entries[index];
    e_new = entry_create(key, value);

    if(e_new == NULL){
        return;
    }

    if(e_table == NULL){
        /* V tabulce doslo misto */
        if(table->entry_count >= table->size){
            printf("Insert error\n");
            entry_free(&e_new);
            return;
        }

        /* Vlozeni polozky */
        table->entries[index] = e_new;
        table->entry_count++;
    } else {
        /* Hodnoty klice jsou stejne */
        if(!strncmp(e_table->key, key, STRING_LENGHT)){
            /* Uprava hodnoty */
            strncpy(table->entries[index]->value, value, STRING_LENGHT);
        } else {
            /* Vyreseni kolize */
            handle_collision(table, index, e_new);
        }
    }
}
