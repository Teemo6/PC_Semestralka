#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "hash_table_entry.h"

entry *entry_create(const char *key, const char *value){
    entry *e_new;

    e_new = (entry *)malloc(sizeof(entry));
    if(!e_new){
        return NULL;
    }
    e_new->key = (char *)malloc(STRING_LENGHT);
    e_new->value = (char *)malloc(STRING_LENGHT);

    if(!e_new->key || !e_new->value){
        free(e_new);
        return NULL;
    }

    strncpy(e_new->key, key, STRING_LENGHT);
    strncpy(e_new->value, value, STRING_LENGHT);

    return e_new;
}

void entry_free(entry **e){
    if(!e || !*e){
        return;
    }

    free((**e).key);
    free((**e).value);
    free(*e);
    *e = NULL;
}
