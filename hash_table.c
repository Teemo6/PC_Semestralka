#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "hash_table.h"

size_t table_hash(char *word){
    size_t i, hash, word_len;

    word_len = strnlen(word, STRING_LENGHT);
    hash = 0;

    for(i = 0; i < word_len; i++){
        hash = ((hash * HASH_PRIME) + word[i]) % TABLE_SIZE;
    }

    return hash;
}

hash_table *table_create(void){
    printf("asdasd");
}
