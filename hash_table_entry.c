#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "hash_table_entry.h"

/**
 * @brief Uvolní jednu položku.
 * @param e položka k uvolnění
 */
LOCAL void entry_free_single(entry **e){
    if(!e || !*e) return;

    free((*e)->key);
    free(*e);
    *e = NULL;
}

entry *entry_create(const char *key){
    entry *e_new;

    e_new = (entry *)malloc(sizeof(entry));
    if(!e_new){
        return NULL;
    }
    e_new->key = (char *)malloc(STRING_LENGHT);

    if(!e_new->key){
        free(e_new);
        return NULL;
    }

    strncpy(e_new->key, key, STRING_LENGHT);
    e_new->spam_count = 0;
    e_new->ham_count = 0;
    e_new->spam_prob = 0;
    e_new->ham_prob = 0;
    e_new->next = NULL;

    return e_new;
}

void entry_free(entry **head){
    if(!head || !*head) return;

    if((*head)->next != NULL) entry_free(&(*head)->next);

    entry_free_single(head);
}

void entry_print_single(const entry *e){
    if(!e) return;

    printf("[Key: %s, SC: %ld, HC: %ld, SP: %.4f, HP: %.4f]", e->key, (unsigned long)e->spam_count, (unsigned long)e->ham_count, e->spam_prob, e->ham_prob);
}

void entry_print(entry *head){
    entry *e_next, *e_last;

    if(!head){
        return;
    }

    e_last = head;
    e_next = head->next;
    while(e_next){
        entry_print_single(e_last);
        printf("  ->  ");
        e_last = e_next;
        e_next = e_next->next;
    }

    entry_print_single(e_last);
    printf("  ->  NULL\n");
}

int entry_insert(entry *head, entry *e_new){
    entry *e_next, *e_last;

    if(!head || !e_new){
        return 0;
    }

    e_last = head;
    e_next = head->next;
    while(e_next){
        /* Stejny klic, prepsani polozky */
        if(!strncmp(e_last->key, e_new->key, STRING_LENGHT)) {
            e_last->spam_count += e_new->spam_count;
            e_last->ham_count += e_new->ham_count;
            entry_free_single(&e_new);
            return 2;
        }
        e_last = e_next;
        e_next = e_next->next;
    }

    /* Stejny klic, prepsani polozky */
    if(!strncmp(e_last->key, e_new->key, STRING_LENGHT)) {
        e_last->spam_count += e_new->spam_count;
        e_last->ham_count += e_new->ham_count;
        entry_free_single(&e_new);
        return 2;
    }

    /* Nastaveni next na novou polozku */
    e_last->next = e_new;
    return 1;
}

entry *entry_find(entry *head, const char *key){
    entry *e_last, *e_next;

    if(!head || !key){
        return NULL;
    }

    e_last = head;
    e_next = head->next;
    while(e_next){
        if(!strncmp(e_last->key, key, STRING_LENGHT)) {
            return e_last;
        }
        e_last = e_next;
        e_next = e_next->next;
    }

    if(!strncmp(e_last->key, key, STRING_LENGHT)) {
        return e_last;
    }

    return NULL;
}
