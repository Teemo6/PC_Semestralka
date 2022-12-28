#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "error.h"
#include "hash_table.h"
#include "loader.h"
#include "classifier.h"

/* Pocet argumentu */
#define ARG_COUNT 8

/* Vyznam jednotlivych argumentu */
#define ARG_SPAM_PATTERN    argv[1]
#define ARG_SPAM_COUNT      argv[2]
#define ARG_HAM_PATTERN     argv[3]
#define ARG_HAM_COUNT       argv[4]
#define ARG_TEST_PATTERN    argv[5]
#define ARG_TEST_COUNT      argv[6]
#define ARG_OUTPUT          argv[7]

/**
 * @brief Zkontroluje argumenty programu.
 *        Při jakékoliv chybě ukončí program.
 * @param argc počet argumentů
 * @param argv argumenty
 */
void handle_input(int argc, char *argv[]){
    size_t spam_cnt, ham_cnt, test_cnt;

    /* Kontrola poctu argumentu */
    if(argc != ARG_COUNT){
        error_arg();
    }

    /* Kontrola intervalu cisel <1; N> */
    spam_cnt = strtol(ARG_SPAM_COUNT, NULL, 0);
    ham_cnt = strtol(ARG_HAM_COUNT, NULL, 0);
    test_cnt = strtol(ARG_TEST_COUNT, NULL, 0);

    if(!spam_cnt || !ham_cnt || !test_cnt){
        error_arg();
    }
}

int main(int argc, char *argv[]){
    size_t spam_cnt, ham_cnt, test_cnt;
    hash_table *bayes_table;

    /* Kontrola argumentu */
    handle_input(argc, argv);

    /* Hash table */
    bayes_table = table_create();
    if(!bayes_table){
        error_table();
    }

    /* Prevod cisel na int */
    spam_cnt = strtol(ARG_SPAM_COUNT, NULL, 0);
    ham_cnt = strtol(ARG_HAM_COUNT, NULL, 0);
    test_cnt = strtol(ARG_TEST_COUNT, NULL, 0);

    /* Nacteni souboru */
    load_train(bayes_table, ARG_SPAM_PATTERN, &spam_cnt, FLAG_SPAM);
    load_train(bayes_table, ARG_HAM_PATTERN, &ham_cnt, FLAG_HAM);

    /* Vypocet pravdepodobnosti spamu, hamu */
    compute_probability(bayes_table);

    /* Nacteni testu a vystup programu */
    load_test(bayes_table, ARG_OUTPUT, ARG_TEST_PATTERN, &test_cnt);

    table_print(bayes_table);

    /* Uvolneni tabulky */
    table_free(&bayes_table);

    return EXIT_SUCCESS;
}
