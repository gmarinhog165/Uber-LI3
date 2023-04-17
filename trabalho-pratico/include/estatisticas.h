#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

/**
 * @brief Struct com a função de guardar a estrutura para cada Query
 * 
 */
typedef struct catestat CatalogoStats;

/**
 * @brief Struct que guarda as estatísticas de um user
 * 
 */
typedef struct um StatsUsers;

/**
 * @brief Struct que guarda as estatísticas de um driver
 * 
 */
typedef struct driv StatsDrivers;

/**
 * @brief Struct que guarda os dados para calcular o preço médio de viagens para cada cidade necessária para a Query 4
 * 
 */
typedef struct pmedcidade CityAvg;

/**
 * @brief Struct que guarda os dados para fins de calculo do preço médio de cada cidade necessária para a Query 5 
 * 
 */
typedef struct pdt DataStats;

/**
 * @brief Struct que guarda a distância média numa determinada cidade necessária para a Query 6
 * 
 */
typedef struct dmed DMed;

/**
 * @brief Struct que guarda os dados necessários para o cálculo dos top condutores numa determinada cidade necessário na Query 7
 * 
 */
typedef struct topcc TopCC;

/**
 * @brief Struct que guarda os dados necessários para o desenrolar da Query 8
 * 
 */
typedef struct topviag TopViagem;

/**
 * @brief Struct que guarda os dados necessários para o cálculo da gorjeta da Query 9
 * 
 */
typedef struct gorj VG;

/**
 * @brief Função que dá load da data para o catálogo estatísticas para executar as queries
 * 
 * @param rides 
 * @param driver 
 * @return CatalogoStats* 
 */
CatalogoStats *loadStats (RidesCatalog *rides, DriverCatalog *driver, UserCatalog*);

/**
 * @brief Função que dá free do catalogo estatísticas
 * 
 * @param stats 
 */
void free_catalogo_stats(CatalogoStats *stats);

/**
 * @brief Função que verifica se o driver é valido, se for traz informação necessária à query1
 * 
 * @param stats 
 * @param id 
 * @param aval 
 * @param nviag 
 * @param total_gasto 
 * @return int 
 */
int getStatsDriverInfos(CatalogoStats *stats, int id, int *aval, int *nviag, double *total_gasto);

/**
 * @brief Função que verifica se o user é valido, se for traz informação necessária à query1
 * 
 * @param stats 
 * @param id 
 * @param aval 
 * @param nviag 
 * @param total_gasto 
 * @return int 
 */
int getStatsUserInfos(CatalogoStats *stats, char *id, int *aval, int *nviag, double *total_gasto);

/**
 * @brief Função que traz informação necessária de um driver para a query2
 * 
 * @param stats 
 * @param id 
 * @param aval 
 * @param nviag 
 * @param i 
 */
void getTopDrivInfos(CatalogoStats *stats, int *id, int *aval, int *nviag, int i);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param stats 
 * @return int 
 */
int getLengthTopDriv(CatalogoStats *stats);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param stats 
 * @return int 
 */
int getLengthTopUser(CatalogoStats *stats);

/**
 * @brief Função que traz informação necessária de um user para a query3
 * 
 * @param stats 
 * @param username 
 * @param distancia 
 * @param i 
 */
void getTopUserInfos(CatalogoStats *stats, char **username, int *distancia, int i);

/**
 * @brief Função que verifica se a cidade é válida, se for traz a informação necessária para a query4
 * 
 * @param stats 
 * @param preco 
 * @param nviag 
 * @param key 
 * @return int 
 */
int getCityAvgInfos(CatalogoStats *stats, double *preco, int *nviag,char *key);

/**
 * @brief Função que traz a informação necessária para a query5
 * 
 * @param stats 
 * @param preco 
 * @param nviag 
 * @param data 
 * @param i 
 */
void getDataStatsInfo(CatalogoStats *stats, double *preco, int *nviag, Date **data, int i);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param stats 
 * @return int 
 */
int getLengthQ5(CatalogoStats *stats);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param stats 
 * @return int 
 */
int getLengthQ6(CatalogoStats *stats);

/**
 * @brief Função que traz a informação necessária para a query6
 * 
 * @param stats 
 * @param dist 
 * @param nviag 
 * @param data 
 * @param city 
 * @param i 
 */
void getDMedInfo(CatalogoStats *stats, int *dist, int *nviag,Date **data, char **city, int i);

/**
 * @brief Função que retorna a length da estrutura
 * 
 * @param stats 
 * @return int 
 */
int getLengthQ7(CatalogoStats *stats);

/**
 * @brief Função que traz a informação necessária para a query7
 * 
 * @param stats 
 * @param id 
 * @param aval 
 * @param nviag 
 * @param i 
 */
void getTopCCInfo(CatalogoStats *stats, int *id, int *aval, int *nviag,char**, int i);

/**
 * @brief Função que retorna a length da estrutura 
 * 
 * @param stats 
 * @return int 
 */
int getLengthQ8(CatalogoStats *stats);

/**
 * @brief Função que traz a informação necessária para verificar condições de execução da query8
 * 
 * @param stats 
 * @param gender 
 * @param idade_condutor 
 * @param idade_user 
 * @param i 
 */
void getTopViagemInfoConditions(CatalogoStats *stats, char *gender, int *idade_condutor, int *idade_user, int i);

/**
 * @brief Função que traz a informação necessária para a query8
 * 
 * @param stats 
 * @param id_driver 
 * @param username 
 * @param nome_user 
 * @param nome_condutor 
 * @param i 
 */
void getTopViagemInfo(CatalogoStats *stats, int *id_driver, char **username, char **nome_user, char **nome_condutor, int i);

/**
 * @brief Função que retorna a length da estrutura 
 * 
 * @param stats 
 * @return int 
 */
int getLengthQ9(CatalogoStats *stats);

/**
 * @brief Função que traz a informação necessária para verificar condições de execução da query9
 * 
 * @param stats 
 * @param data 
 * @param i 
 */
void getVGInfoConditions(CatalogoStats *stats, Date **data, int i);

/**
 * @brief Função que traz a informação necessária para a query9
 * 
 * @param stats 
 * @param id 
 * @param dist 
 * @param city 
 * @param tip 
 * @param i 
 */
void getVGInfo(CatalogoStats *stats, int *id, int *dist, char **city, double *tip, int i);



#endif
