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
                e_last->prob_entry_spam = ((double)e_last->count_entry_spam + 1) / (double)table->count_spam;
                e_last->prob_entry_ham = ((double)e_last->count_entry_ham + 1) / (double)table->count_ham;
                e_last = e_next;
                e_next = e_next->next;
            }
            e_last->prob_entry_spam = ((double)e_last->count_entry_spam + 1) / (double)table->count_spam;
            e_last->prob_entry_ham = ((double)e_last->count_entry_ham + 1) / (double)table->count_ham;
        }
    }
}
