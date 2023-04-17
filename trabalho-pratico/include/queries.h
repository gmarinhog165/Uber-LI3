#ifndef QUERIES_H
#define QUERIES_H

/**
 * @brief Função responsável por executar a query pedida
 * 
 * @param stats 
 * @param drivers 
 * @param users 
 * @param id 
 * @param nquery 
 * @param path 
 * @param p 
 * @return * void 
 */
void query(CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users, char *id, int nquery, char *path, Paginacao *p);

#endif
