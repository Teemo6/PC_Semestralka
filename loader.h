#ifndef PC_SEMESTRALKA_LOADER_H
#define PC_SEMESTRALKA_LOADER_H

#include "config.h"
#include "hash_table.h"

/* Cesta k train souborum */
#define FILE_PATH "../data/train/"

/* Pripona souboru */
#define FILE_EXTENSION ".txt"

void load_train(hash_table *table, const char *train_pattern, const size_t *train_count, int flag);

void load_test(hash_table *table, const char *out_file, const char *test_pattern, const size_t *test_count);

#endif
