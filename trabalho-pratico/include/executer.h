#ifndef EXECUTER_H
#define EXECUTER_H 

/**
 * @brief Função responsável por ler uma instrução e fazê-la executar
 * 
 * @param path 
 * @param stats 
 * @param drivers 
 * @param users 
 */
void execute(char *path, CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users);

#endif
