#ifndef PC_SEMESTRALKA_HASH_TABLE_ENTRY_H
#define PC_SEMESTRALKA_HASH_TABLE_ENTRY_H

/* Zretezeny prvek v hash tabulce */
typedef struct ENTRY{
    char *key;
    char *value;
    size_t count;
    struct ENTRY *next;
} entry;

entry *entry_create(const char *key, const char *value);
void entry_free(entry **e);
void entry_print(const entry *e);
void entry_add(entry *e, const char *key, char *value);

#endif
