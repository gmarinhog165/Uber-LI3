#ifndef QUERIES_TESTS_H
#define QUERIES_TESTS_H


/**
 * @brief Função responsável por executar a query pedida, onde compara e imprime o tempo de execução
 * 
 * @param stats 
 * @param drivers 
 * @param users 
 * @param id 
 * @param nquery 
 * @param path 
 * @param n_command 
 * @param tests 
 * @param p 
 */
void query_testes(CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users, char *id, int nquery, char *path,int n_command, char *tests, Paginacao *p);



#endif 
