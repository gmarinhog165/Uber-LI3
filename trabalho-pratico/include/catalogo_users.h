#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H 


/**
 * @brief Struct correspondente a um catálogo de users
 * 
 */
typedef struct cata2 UserCatalog;

/**
 * @brief Função que retorna uma estrutura User
 * 
 * @param info 
 * @param key 
 * @return User* 
 */
User *getUserByUsername(UserCatalog *info, char *key);

/**
 * @brief Função que cria e preenche o catálogo dos Users
 * 
 * @param path 
 * @return UserCatalog* 
 */
UserCatalog *UserToStruct(char *path);

/**
 * @brief Função que dá free ao catálogo dos Users
 * 
 * @param dados 
 */
void free_user_catalog(UserCatalog *dados);

#endif
