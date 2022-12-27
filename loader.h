#ifndef PC_SEMESTRALKA_LOADER_H
#define PC_SEMESTRALKA_LOADER_H

#include "config.h"
#include "hash_table.h"

/* Cesta k souborum */
#define FILE_PATH "../data/train/"

/* Pripona souboru */
#define FILE_EXTENSION ".txt"

void load_files(hash_table *table, const char *spam_pattern, const size_t *spam_count, int flag);

void output_file(hash_table *table, const char *out_file);

#endif
