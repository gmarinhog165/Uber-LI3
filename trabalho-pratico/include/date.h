#ifndef DATE_H
#define DATE_H


/**
 * @brief Struct correspondente onde são armazenadas datas
 * 
 */
typedef struct dat Date;

/**
 * @brief Função que retorna o dia
 * 
 * @param dados 
 * @return int 
 */
int getDateDia(Date *dados);

/**
 * @brief Função que retorna o mes
 * 
 * @param dados 
 * @return int 
 */
int getDateMes(Date *dados);

/**
 * @brief Função que retorna o ano
 * 
 * @param dados 
 * @return int 
 */
int getDateAno(Date *dados);

/**
 * @brief Função que cria um clone de Date
 * 
 * @param dados 
 * @return Date* 
 */
Date* clone_date(Date *dados);

/**
 * @brief Função que preenche a estrutura Date
 * 
 * @param command 
 * @return Date* 
 */
Date* preenche_data(char *command);

/**
 * @brief Função que dá free da estrutura Date
 * 
 * @param data 
 */
void free_date(Date *data);

/**
 * @brief Função que converte a estrutura Date numa string
 * 
 * @param data 
 * @return char* 
 */
char *DateToString(Date *data);

/**
 * @brief Função que converte uma string na estrutura Date
 * 
 * @param command 
 * @return Date* 
 */
Date* StringToDate(char *command);

/**
 * @brief Função que verifica se uma data é válida
 * 
 * @param date 
 * @return int 
 */
int validate_date(char *date);

/**
 * @brief Função que atribui um valor consoante o status da conta
 * 
 * @param account_status 
 * @return int 
 */
int check_acc_status(char *account_status);

/**
 * @brief Função que compara duas datas para saber se é maior, menor ou igual
 * 
 * @param data 
 * @param data2 
 * @return int 
 */
int comp_datas(Date *data, Date *data2);

/**
 * @brief Função que calcula a idade através de uma data
 * 
 * @param birthdate 
 * @return int 
 */
int idade(Date* birthdate);

#endif