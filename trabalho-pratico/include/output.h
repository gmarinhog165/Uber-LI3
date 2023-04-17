#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * @brief Struct definida para desenvolver a paginação do modo interativo
 * 
 */
typedef struct paginacao Paginacao;

/**
 * @brief Função que trata do output duma query
 * 
 * @param string 
 * @param path 
 * @param p 
 */
void gere_output(char *string, char *path, Paginacao *p);

/**
 * @brief Função que recolhe os paths para os files
 * 
 * @param user 
 * @param driver 
 * @param rides 
 */
void path_interativo(char **user, char **driver, char **rides);

/**
 * @brief Função que recolhe valores para a query
 * 
 * @param numero 
 * @param valores 
 */
void get_query_info(int *numero, char **valores);

/**
 * @brief Função que trata do modo interativo das queries
 * 
 * @param t 
 */
void interativo(Paginacao *t);

/**
 * @brief Função para dar free à estrutura
 * 
 * @param dados 
 */
void free_paginacao_wrapper(void *dados);

/**
 * @brief Função que inicia a estrutura
 * 
 * @return Paginacao* 
 */
Paginacao *paginacao_create();

/**
 * @brief Função que trata do modo interativo para o loop de queries ou encerramento do programa
 * 
 * @param k 
 */
void printf_mini_menu(int *k);


#endif
