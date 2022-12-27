#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    e_new->count = 1;
    e_new->next = NULL;

    return e_new;
}

void entry_free(entry **e){
    if(!e || !*e) return;

    if((*e)->next != NULL) {
        entry_free(&(*e)->next);
        free((*e)->next);
    }

    free((*e)->key);
    free((*e)->value);
    free(*e);
    *e = NULL;
}

void entry_print(const entry *e){
    entry *e_next;

    if(!e) return;

    printf("%s  ->  ", e->value);

    e_next = e->next;
    while(e_next){
        printf("%s  ->  ", e_next->value);
        e_next = e_next->next;
    }
    printf("NULL\n");
}

void entry_add(entry *e, const char *key, char *value){
    entry *e_next, *e_last;

    if(!e || !key || !value){
        return;
    }

    if(!strncmp(e->key, key, STRING_LENGHT)) {
        strncpy(e->value, value, STRING_LENGHT);
        e->count++;
        return;
    }

    e_last = e;
    e_next = e->next;
    while(e_next){
        if(!strncmp(e_last->key, key, STRING_LENGHT)) {
            strncpy(e->value, value, STRING_LENGHT);
            e_last->count++;
            return;
        }
        e_last = e_next;
        e_next = e_next->next;
    }

    e_last->next = entry_create(key, value);
}
