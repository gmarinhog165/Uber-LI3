#ifndef RIDES_H
#define RIDES_H

/**
 * @brief Struct que representa os detalhes de uma viagem
 * 
 */
typedef struct rides Ride;

/**
 * @brief Função que dá free da estrutura Ride
 * 
 * @param data 
 */
void free_rides(Ride* data);

/**
 * @brief Função wrapper da free_rides
 * 
 * @param user 
 */
void free_rides_void (gpointer user);

/**
 * @brief Função que devolve o id da ride
 * 
 * @param dados 
 * @return int 
 */
int get_rides_id(Ride* dados);

/**
 * @brief Função que devolve a data da viagem da ride
 * 
 * @param dados 
 * @return Date* 
 */
Date* get_rides_data(Ride* dados);

/**
 * @brief Função que devolve o id do driver da viagem
 * 
 * @param dados 
 * @return int 
 */
int get_rides_driver(Ride* dados);

/**
 * @brief Função que devolve o username do user da viagem
 * 
 * @param dados 
 * @return char* 
 */
char* get_rides_user(Ride* dados);

/**
 * @brief Função que devolve a cidade da viagem
 * 
 * @param dados 
 * @return char* 
 */
char* get_rides_city(Ride* dados);

/**
 * @brief Função que devolve a distancia da viagem
 * 
 * @param dados 
 * @return int 
 */
int get_rides_distance(Ride* dados);

/**
 * @brief Função que devolve o score_user da viagem
 * 
 * @param dados 
 * @return int 
 */
int get_rides_score_user(Ride* dados);

/**
 * @brief Função que devolve o score_driver da viagem
 * 
 * @param dados 
 * @return int 
 */
int get_rides_score_driver(Ride* dados);

/**
 * @brief Função que devolve a tip da viagem
 * 
 * @param dados 
 * @return double 
 */
double get_rides_tip(Ride* dados);

/**
 * @brief Função que cria um clone da estrutura Ride
 * 
 * @param dados 
 * @return Ride* 
 */
Ride *clone_rides(Ride *dados);

/**
 * @brief Função que dá free do clone da estrutura Ride
 * 
 * @param data 
 */
void free_clone_rides(Ride* data);

/**
 * @brief Função que verifica se há erros nos tokens
 * 
 * @param command 
 * @return int 
 */
int validate_tokens(char **command);

/**
 * @brief Função que preenche a estrutura Ride
 * 
 * @param tokens 
 * @return Ride* 
 */
Ride* preenche_rides_tokens(char** tokens);


#endif