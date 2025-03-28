#ifndef PC_SEMESTRALKA_HASH_TABLE_ENTRY_H
#define PC_SEMESTRALKA_HASH_TABLE_ENTRY_H

/**
 * @brief Prvek hash tabulky.\n
 *        Může se zřetězit (obsahuje ukazatel na další prvek v seznamu).
 */
typedef struct ENTRY{
    char *key;                  /** Klíč, slovo */
    size_t count_entry_spam;    /** Počet výskytu ve spamových souborech */
    size_t count_entry_ham;     /** Počet výskytu v hamových souborech */
    double prob_entry_spam;     /** Bayesova pravděpodobnost spamu */
    double prob_entry_ham;      /** Bayesova pravděpodobnost hamu */
    struct ENTRY *next;         /** Ukazatel na další prvek v seznamu */
} entry;

/**
 * @brief Vytvoří nový prvek.
 * @param key Klíč, slovo
 * @return Nová položka seznamu.\n
 *         NULL pokud se nepodařilo vytvořit položku.
 */
entry *entry_create(const char *key);

/**
 * @brief Uvolní paměť celému seznamu prvků.
 * @param head hlavička seznamu prvků
 */
void entry_free(entry **head);

/**
 * @brief Vypíše celý seznam prvků Hash tabulky.
 * @format [Key: {key}, SC: {count_entry_spam}, HC: {count_entry_spam}, SP: {prob_entry_spam}, HP: {prob_entry_ham}]
 * @param head hlavička prvků
 */
void entry_print(entry *head);

/**
 * @brief Pokusí se o vložení prvku do seznamu.\n
 *        Pokud se v seznamu nachází prvek se stejným klíčem, přepíše se hodnota.
 * @param e_head hlavička prvků
 * @param e_new prvek který se přidá/přepíše
 * @return 0 Chyba.\n
 *         1 Úspěšné vložení.\n
 *         2 Úspěšné přepšání.\n
 *         3 Úspěšné přepšání, byl vložen nový ham.
 */
int entry_insert(entry *head, entry *e_new);

/**
 * @brief Vyhledá prvek v seznamu.
 * @param e_head hlavička prvků
 * @param key klíč podle kterého se hledá prvek
 * @return Položka obsažená v seznamu.
 *         NULL pokud seznam neobsahuje hledanou položku.
 */
entry *entry_find(entry *head, const char *key);

#endif
