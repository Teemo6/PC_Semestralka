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

void entry_print(const entry *e){
    if(!e) return;

    printf("%s\t->\t%s\n", e->key, e->value);
}

entry_list *entry_list_create(const entry *e){
    entry_list *e_new;

    e_new = (entry_list *)malloc(sizeof(entry_list));
    if(!e_new){
        return NULL;
    }
    e_new->entry = (entry *)malloc(sizeof(entry));

    if(!e_new->entry){
        free(e_new);
        return NULL;
    }

    e_new->entry = e;
    e_new->next = NULL;

    return e_new;
}

void entry_list_free(entry_list **e_list){
    entry_list *e_next, *e_last;

    if(!e_list || !*e_list){
        return;
    }

    e_last = (*e_list);
    e_next = (*e_list)->next;
    while(e_next){
        entry_free(&e_last->entry);
        free(e_last);

        e_last = e_next;
        e_next = e_next->next;
    }
    entry_free(&e_last->entry);
    free(e_last);

    *e_list = NULL;
}

void entry_list_print(const entry_list *e_list){
    entry_list *e_next;

    if(!e_list){
        return;
    }

    printf("%s  ->  ", e_list->entry->value);

    e_next = e_list->next;
    while(e_next){
        printf("%s  ->  ", e_next->entry->value);
        e_next = e_next->next;
    }
    printf("NULL\n");
}

void entry_list_insert(const entry_list *e_list, const entry *e){
    entry_list *e_next, *e_last;

    if(!e_list || !e){
        return;
    }

    e_last = e_list;
    e_next = e_list->next;
    while(e_next){
        e_last = e_next;
        e_next = e_next->next;
    }

    e_last->next = (entry_list *)malloc(sizeof(entry_list));

    if(!e_last->next){
        return;
    }

    e_last->next = entry_list_create(e);
}
