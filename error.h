#ifndef PC_SEMESTRALKA_ERROR_H
#define PC_SEMESTRALKA_ERROR_H

/**
 * @brief Ukončí běh programu.\n
 *        Vypíše chybovou hlášku.
 */
void error_arg(void);

/**
 * @brief Ukončí běh programu.\n
 *        Vypíše chybovou hlášku.
 */
void error_table(void);

/**
 * @brief Ukončí běh programu.\n
 *        Vypíše chybovou hlášku.
 * @param path cesta k souboru, který se nepovedl otevřít
 */
void error_fopen(char *path);

/**
 * @brief Ukončí běh programu.\n
 *        Vypíše chybovou hlášku.
 */
void error_probabilty(void);

#endif
