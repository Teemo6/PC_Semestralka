#ifndef PC_SEMESTRALKA_HASH_TABLE_ENTRY_H
#define PC_SEMESTRALKA_HASH_TABLE_ENTRY_H

/* Zretezeny prvek v hash tabulce */
typedef struct ENTRY{
    char *key;
    char *value;
} entry;

/* Prvek hash tabulky */
typedef struct ENTRY_LIST{
    entry *current;
    struct ENTRY_LIST *next;
} entry_list;

entry *entry_create(const char *key, const char *value);
void entry_free(entry **e);
void entry_print(const entry *e);

entry_list *entry_list_create(const entry *e);
void entry_list_free(entry_list **e_list);
void entry_list_print(const entry_list *e_list);
void entry_list_insert(const entry_list *e_list, const entry *e);

#endif
