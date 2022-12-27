#ifndef PC_SEMESTRALKA_LOADER_H
#define PC_SEMESTRALKA_LOADER_H

#include "config.h"
#include "hash_table.h"

/* Cesta k souborům */
#define FILE_PATH "../data/train/"

/* Přípona souboru */
#define FILE_EXTENSION ".txt"

int load_file(hash_table *table, const char *spam_pattern, const size_t *spam_count, int flag);

int output_file(hash_table *table, const char *out_file);

#endif
