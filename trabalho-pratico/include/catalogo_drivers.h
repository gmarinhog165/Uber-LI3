#ifndef CATALOGO_DRIVERS_H
#define CATALOGO_DRIVERS_H 

/**
 * @brief Struct correspondente a um catálogo de Drivers
 * 
 */
typedef struct cata1 DriverCatalog;

/**
 * @brief Função que retorna uma estrutura Driver
 * 
 * @param info 
 * @param key 
 * @return Driver* 
 */
Driver *getDriverByID(DriverCatalog *info, int key);

/**
 * @brief Função que cria e preenche o catálogo dos Drivers
 * 
 * @param path 
 * @return DriverCatalog* 
 */
DriverCatalog *DriverToStruct(char *path);

/**
 * @brief Função que dá free ao catálogo dos Drivers
 * 
 * @param dados 
 */
void free_driver_catalog(DriverCatalog *dados);

#endif