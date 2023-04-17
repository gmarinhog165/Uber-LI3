#ifndef PARSING_DRIVERS_H
#define PARSING_DRIVERS_H

/**
 * @brief Struct que define pelo que é constituído um driver, eventualmente armazenando os dados correspondentes
 * 
 */
typedef struct drivers Driver;

/**
 * @brief Função wrapper da free_driver
 * 
 * @param user 
 */
void free_driver_void (gpointer user);

/**
 * @brief Função que retorna o id do driver
 * 
 * @param dados 
 * @return int 
 */
int get_driver_id(Driver* dados);

/**
 * @brief Função que retorna o nome do driver
 * 
 * @param dados 
 * @return char* 
 */
char* get_driver_name(Driver* dados);

/**
 * @brief Funcção que retorna o género do driver
 * 
 * @param dados 
 * @return char 
 */
char get_driver_gender(Driver* dados);

/**
 * @brief Função que retorna a data de nascimento do driver
 * 
 * @param dados 
 * @return Date* 
 */
Date* get_driver_birth_date(Driver* dados);

/**
 * @brief Função que retorna a car class do driver
 * 
 * @param dados 
 * @return int 
 */
int get_driver_car_class(Driver* dados);

/**
 * @brief Função que retorna a data de criação de conta do driver
 * 
 * @param dados 
 * @return Date* 
 */
Date* get_driver_acc_creation(Driver* dados);

/**
 * @brief Função que retorna o status da conta do driver
 * 
 * @param dados 
 * @return int 
 */
int get_driver_acc_status(Driver* dados);

/**
 * @brief Função que cria um clone de estrutura Driver
 * 
 * @param dados 
 * @return Driver* 
 */
Driver *clone_driver(Driver *dados);

/**
 * @brief Função que dá free do clone de driver
 * 
 * @param data 
 */
void free_clone_driver(Driver* data);

/**
 * @brief Função que verifica se há erros nos tokens
 * 
 * @param tokens 
 * @return int 
 */
int validate_drivers_tokens(char **tokens);

/**
 * @brief Função que preenche a estrutura Driver
 * 
 * @param tokens 
 * @return Driver* 
 */
Driver* preenche_drivers_tokens(char** tokens);

#endif 
