#ifndef USERS_H
#define USERS_H 

/**
 * @brief Struct que representa os detalhes de um user 
 * 
 */
typedef struct users User;

/**
 * @brief Função que dá free da estrutura User
 * 
 * @param data 
 */
void free_user(User* data);

/**
 * @brief Função wrapper da free_user
 * 
 * @param user 
 */
void free_user_void (gpointer user);

/**
 * @brief Função que dá free do clone de user
 * 
 * @param data 
 */
void free_clone_user(User* data);

/**
 * @brief Função que retorna o username do user
 * 
 * @param dados 
 * @return char* 
 */
char* get_user_username(User* dados);

/**
 * @brief Função que retorna o nome do user
 * 
 * @param dados 
 * @return char* 
 */
char* get_user_name(User* dados);

/**
 * @brief Função que retorna o género do user
 * 
 * @param dados 
 * @return char 
 */
char get_user_gender(User* dados);

/**
 * @brief Função que retorna a data de nascimento do user
 * 
 * @param dados 
 * @return Date* 
 */
Date* get_user_birth_date(User* dados);

/**
 * @brief Função que retorna a data de criação da conta do user
 * 
 * @param dados 
 * @return Date* 
 */
Date* get_user_acc_creation(User* dados);

/**
 * @brief Função que retorna o status da conta do user
 * 
 * @param dados 
 * @return int 
 */
int get_user_acc_status(User* dados);

/**
 * @brief Função que cria um clone da estrutura User
 * 
 * @param dados 
 * @return User* 
 */
User *clone_user(User *dados);

/**
 * @brief Função que verifica se há erros nos tokens
 * 
 * @param tokens 
 * @return int 
 */
int validate_users_tokens(char **tokens);

/**
 * @brief Função que preenche a estrutura users
 * 
 * @param tokens 
 * @return User* 
 */
User* preenche_users_tokens(char** tokens);

#endif
