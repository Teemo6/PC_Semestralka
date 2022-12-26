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

    return e_new;
}

void entry_free(entry **e){
    if(!e || !*e) return;

    free((**e).key);
    free((**e).value);
    free(*e);
    *e = NULL;
}

entry_list *entry_list_create(const entry *e){
    entry_list *e_list_new;

    e_list_new = (entry_list *)malloc(sizeof(entry_list));
    if(!e_list_new){
        return NULL;
    }
    e_list_new->current = (entry *)malloc(sizeof(entry));
    e_list_new->next = (entry_list *)malloc(sizeof(entry_list));

    if(!e_list_new->current || !e_list_new->next){
        free(e_list_new);
        return NULL;
    }

    e_list_new->current = e;
    e_list_new->next = NULL;

    return e_list_new;
}

void entry_list_free(entry_list **e_list){
    entry_list *e_next;

    if(!e_list || !*e_list){
        return;
    }

    e_next = (**e_list).next;
    while(e_next) {
        e_next = (**e_list).next;

        entry_free(&(**e_list).current);

        free((**e_list).current);
        free((**e_list).next);
    }
    free(*e_list);
    *e_list = NULL;
}

void entry_list_print(const entry_list *e_list){
    entry_list *e_next;

    if(!e_list){
        return;
    }

    printf("%s\t\t", e_list->current->value);

    e_next = e_list->next;
    while(e_next) {
        printf("%s\t\t", e_next->current->value);
        e_next = e_list->next;
    }
    printf("\n");
}

void entry_list_insert(const entry_list *e_list, const entry *e){
    entry_list *e_list_next, *e_list_last;

    if(!e_list || !e){
        return;
    }

    e_list_next = e_list->next;
    while(e_list_next){
        e_list_last = e_list_next;
        e_list_next = e_list->next;
    }

    e_list_last->next = entry_list_create(e);
}
