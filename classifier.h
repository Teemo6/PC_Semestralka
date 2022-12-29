#ifndef PC_SEMESTRALKA_CLASSIFIER_H
#define PC_SEMESTRALKA_CLASSIFIER_H

#include "hash_table.h"

/**
 * @brief Načte trénovací soubory do hash tabulky.\n
 *        Sestavuje název souboru podle vzoru.\n
 *        Načítá soubory z adresáře FILE_PATH.\n
 * @param table hash tabulka
 * @param train_pattern vzor trénovacího souboru
 * @param train_count počet trénovacích souborů
 * @param flag FLAG_SPAM spamový soubor\n
 *             FLAG_HAM hamový soubor
 */
void classifier_train(hash_table *table, const char *train_pattern, const size_t *train_count, int flag);

/**
 * @brief Vypočítá pravděpodobnost spamu/hamu všech slov uložených v tabulce.
 * @param table hash tabulka
 */
void compute_probability(hash_table *table);

/**
 * @brief Klasifikuje testovací soubory.\n
 *        Sestavuje název testovacího souboru podle vzoru.\n
 *        Načítá soubory z adresáře FILE_PATH.\n
 *        Vytvoří výstupní soubor.
 * @param table hash tabulka
 * @param test_pattern vzor testovacího souboru
 * @param test_count počet testovacích souborů
 * @param out_file název výstupního souboru
 */
void classifier_test(hash_table *table, const char *test_pattern, const size_t *test_count, const char *out_file);

#endif
