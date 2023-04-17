#ifndef EXECUTER_TESTS_H
#define EXECUTER_TESTS_H 

/**
 * @brief Função responsável por ler uma instrução e fazê-la executar
 * 
 * @param argv 
 * @param stats 
 * @param drivers 
 * @param users 
 */
void execute_test(char *argv[], CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users);

#endif
