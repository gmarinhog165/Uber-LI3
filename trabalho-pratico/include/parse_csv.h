#ifndef PARSE_CSV_H
#define PARSE_CSV_H

/**
 * @brief Função que trata do parsing de ficheiros csv
 * 
 * @param path 
 * @param buildFunc 
 * @param structure 
 */
void parseCSV(char *path, void(*buildFunc)(char**,void*), void *structure);

#endif
