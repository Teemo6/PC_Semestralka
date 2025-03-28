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
    if(!e || !*e){
        return;
    }

    free((*e)->key);
    free(*e);
    *e = NULL;
}

/**
 * @brief Vypíše samotnou položku.
 * @param e položka k vypsání
 */
LOCAL void entry_print_single(const entry *e){
    if(!e){
        return;
    }

    printf("[Key: %s, SC: %ld, HC: %ld, SP: %.5f, HP: %.5f]", e->key, (unsigned long)e->count_entry_spam, (unsigned long)e->count_entry_ham, e->prob_entry_spam, e->prob_entry_ham);
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
    e_new->count_entry_spam = 0;
    e_new->count_entry_ham = 0;
    e_new->prob_entry_spam = 0;
    e_new->prob_entry_ham = 0;
    e_new->next = NULL;

    return e_new;
}

void entry_free(entry **head){
    if(!head || !*head){
        return;
    }

    if((*head)->next){
        entry_free(&(*head)->next);
    }

    entry_free_single(head);
}

void entry_print(entry *head){
    entry *e_last;

    if(!head){
        return;
    }

    e_last = head;
    while(e_last->next){
        entry_print_single(e_last);
        printf("  ->  ");
        e_last = e_last->next;
    }

    entry_print_single(e_last);
    printf("  ->  NULL\n");
}

int entry_insert(entry *head, entry *e_new){
    entry *e_last;

    if(!head || !e_new){
        return 0;
    }

    e_last = head;
    while(e_last->next){
        /* Stejny klic, prepsani polozky */
        if(!strncmp(e_last->key, e_new->key, STRING_LENGHT)) {
            e_last->count_entry_spam += e_new->count_entry_spam;
            e_last->count_entry_ham += e_new->count_entry_ham;
            entry_free_single(&e_new);

            /* Novy unikatni ham */
            if(e_last->count_entry_ham == 1){
                return 3;
            }
            return 2;
        }
        e_last = e_last->next;
    }

    /* Stejny klic, prepsani polozky */
    if(!strncmp(e_last->key, e_new->key, STRING_LENGHT)) {
        e_last->count_entry_spam += e_new->count_entry_spam;
        e_last->count_entry_ham += e_new->count_entry_ham;
        entry_free_single(&e_new);

        /* Novy unikatni ham */
        if(e_last->count_entry_ham == 1){
            return 3;
        }
        return 2;
    }

    /* Nastaveni next na novou polozku */
    e_last->next = e_new;
    return 1;
}

entry *entry_find(entry *head, const char *key){
    entry *e_last;

    if(!head || !key){
        return NULL;
    }

    e_last = head;
    while(e_last->next){
        /* Klice se shoduji */
        if(!strncmp(e_last->key, key, STRING_LENGHT)) {
            return e_last;
        }
        e_last = e_last->next;
    }
    /* Klice se shoduji */
    if(!strncmp(e_last->key, key, STRING_LENGHT)) {
        return e_last;
    }

    return NULL;
}
