#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "hash_table.h"
#include "loader.h"

/* Pocet argumentu */
#define ARG_COUNT 8

/* Vyznam jednotlivych argumentu */
#define ARG_SPAM_NAME   argv[1]
#define ARG_SPAM_COUNT  argv[2]
#define ARG_HAM_NAME    argv[3]
#define ARG_HAM_COUNT   argv[4]
#define ARG_TEST_NAME   argv[5]
#define ARG_TEST_COUNT  argv[6]
#define ARG_OUTPUT      argv[7]


void help(void){
    printf("Usage:\n\tspamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n\n");
    printf("Example:\n\tspamid.exe spam 10 ham 20 test 50 result.txt\n\n");
}

void handle_input(int argc, char *argv[]){
    long spam_cnt, ham_cnt, test_cnt;

    /* Kontrola poctu argumentu */
    if(argc < ARG_COUNT){
        help();
        exit(1);
    }

    /* Kontrola intervalu cisel <1; N> */
    spam_cnt = strtol(ARG_SPAM_COUNT, NULL, 0);
    ham_cnt = strtol(ARG_HAM_COUNT, NULL, 0);
    test_cnt = strtol(ARG_TEST_COUNT, NULL, 0);

    if(!spam_cnt || !ham_cnt || !test_cnt){
        help();
        exit(1);
    }
}

int main(int argc, char *argv[]){
    size_t spam_cnt, ham_cnt;
    hash_table *bayes_hash_table;

    /* Kontrola argumentu */
    handle_input(argc, argv);

    /* Hash table*/
    bayes_hash_table = table_create();

    /* Prevod cisel na int */
    spam_cnt = strtol(ARG_SPAM_COUNT, NULL, 0);
    ham_cnt = strtol(ARG_HAM_COUNT, NULL, 0);

    /* Nacteni souboru */
    load_file(bayes_hash_table, ARG_SPAM_NAME, &spam_cnt, FLAG_SPAM);
    load_file(bayes_hash_table, ARG_HAM_NAME, &ham_cnt, FLAG_HAM);

    table_print(bayes_hash_table);
    table_free(&bayes_hash_table);

    return EXIT_SUCCESS;
}
