#ifndef CATALOGO_RIDES_H
#define CATALOGO_RIDES_H 

/**
 * @brief Struct correspondente a um catálogo de Rides
 * 
 */
typedef struct cata3 RidesCatalog;

/**
 * @brief Função que retorna uma estrutura Ride
 * 
 * @param info 
 * @param index 
 * @return Ride* 
 */
Ride *getRideByIndex(RidesCatalog *info, int index);

/**
 * @brief Função que cria e preenche o catálogo das Rides
 * 
 * @param path 
 * @return RidesCatalog* 
 */
RidesCatalog *RidesToStruct(char *path);

/**
 * @brief Função que dá free ao catálogo das Rides
 * 
 * @param dados 
 */
void free_rides_catalog(RidesCatalog *dados);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param info 
 * @return int 
 */
int getRideLength (RidesCatalog *info);

#endif
