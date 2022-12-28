#include <stdio.h>

#include "classifier.h"
#include "error.h"

void compute_probability(hash_table *table){
    size_t i;
    entry *e_last, *e_next;

    if(!table){
        error_probabilty();
    }

    for(i = 0; i < table->size; i++){
        if(table->entries[i]){
            e_last = table->entries[i];
            e_next = e_last->next;
            while(e_next){
                e_last->spam_prob = (double)e_last->spam_count / (double)table->entry_count;
                e_last->ham_prob = (double)e_last->ham_count / (double)table->entry_count;
                e_last = e_next;
                e_next = e_next->next;
            }
            e_last->spam_prob = (double)e_last->spam_count / (double)table->entry_count;
            e_last->ham_prob = (double)e_last->ham_count / (double)table->entry_count;
        }
    }
}