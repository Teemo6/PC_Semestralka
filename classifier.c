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
                /* P(<word>|c) */
                e_last->spam_prob = ((double)e_last->spam_count + 1) / ((double)table->count + (double)table->unique_spam);
                e_last->ham_prob = ((double)e_last->ham_count + 1) / ((double)table->count + (double)table->unique_ham);
                e_last = e_next;
                e_next = e_next->next;
            }
            e_last->spam_prob = ((double)e_last->spam_count + 1) / ((double)table->count + (double)table->unique_spam);
            e_last->ham_prob = ((double)e_last->ham_count + 1) / ((double)table->count + (double)table->unique_ham);
        }
    }
}
