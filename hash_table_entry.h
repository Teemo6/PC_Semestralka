#ifndef PC_SEMESTRALKA_HASH_TABLE_ENTRY_H
#define PC_SEMESTRALKA_HASH_TABLE_ENTRY_H

/* Prvek hash_function tabulky */
typedef struct ENTRY{
    char *key;
    char *value;
} entry;

typedef struct ENTRY_LIST{
    entry *key;
    entry *current;
    struct ENTRY_LIST *next;
} entry_list;

entry *entry_create(const char *key, const char *value);
void entry_free(entry **e);

entry_list *entry_list_create(const char *key, const char *value);
void entry_list_free(entry **e);

#endif
