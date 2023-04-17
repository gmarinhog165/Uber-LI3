#include <stdio.h>
#include <glib.h>
#include <math.h>

#include "date.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_users.h"
#include "catalogo_drivers.h"
#include "catalogo_rides.h"
#include "estatisticas.h"

//QUERY 1,2,3
StatsUsers* preenche_StatsUser(Ride *dados, DriverCatalog *drivers);
StatsDrivers* preenche_StatsDriver(Ride *dados, DriverCatalog *drivers);
StatsUsers* altera_StatsUser(Ride *dados, DriverCatalog *drivers, GHashTable *stats);
StatsDrivers* altera_StatsDriver(Ride *dados, DriverCatalog *drivers, GHashTable *stats);
double gasto_por_viagem(Ride* dados, DriverCatalog *driver, int inclui_tip);
gint compare_person_by_avmed_glib_wrapper(gconstpointer a, gconstpointer b);
int compare_person_by_avmed(StatsDrivers * const* p1, StatsDrivers * const* p2);
gint compare_person_by_distancia_glib_wrapper(gconstpointer a, gconstpointer b);
int compare_person_by_distancia(StatsUsers * const* p1, StatsUsers * const* p2);
void free_q1user_void(void *dados);
void free_q1user(StatsUsers *data);
void free_q1driver_void(void *dados);
void free_q1driver(StatsDrivers *data);

// QUERY 4
CityAvg* preenche_pmed(Ride *dados, DriverCatalog *drivers);
CityAvg* altera_pmed(Ride *dados, DriverCatalog *drivers, GHashTable *stats);
void free_pmed_void (void* stats);
void free_pmed(CityAvg* data);

// QUERY 5
DataStats *preenche_datastats(Ride *dados, DriverCatalog *drivers);
DataStats *altera_datastats(Ride *dados, DriverCatalog *drivers, GHashTable *stats);
gint compare_person_by_data_glib_wrapper(gconstpointer a, gconstpointer b);
int compare_person_by_data(DataStats * const* p1, DataStats * const* p2);
void free_pdata(DataStats* data);
void free_pdata_void (void* stats);

//QUERY 6
DMed* preenche_dmed(Ride *dados);
DMed* altera_dmed(Ride *dados, GHashTable *Q6, char *key);
void free_dmed_void (void* driver);
void free_dmed(DMed* data);
int compare_person_by_data2(DMed * const* p1, DMed * const* p2);
gint compare_person_by_data2_glib_wrapper(gconstpointer a, gconstpointer b);

//QUERY 7
TopCC* preencher_topcc(Ride *dados);
TopCC* altera_topcc(Ride *dados, GHashTable *stats, char *key);
void free_topcc(TopCC* data);
void free_topcc_void (void* driver);
int compare_person_by_avmed2(TopCC * const* p1, TopCC * const* p2);
gint compare_person_by_avmed2_glib_wrapper(gconstpointer a, gconstpointer b);

//QUERY 8
TopViagem* preenche_topv(Ride *dados, Driver* driver, User* user);
void free_topv_void (void* driver);
void free_topv(TopViagem* data);
gint compare_person_by_acc_creation_glib_wrapper(gconstpointer a, gconstpointer b);
int compare_person_by_acc_creation(TopViagem * const* p1, TopViagem * const* p2);

//QUERY 9
VG* preenche_vg(Ride *dados);
gint compare_person_by_dist_glib_wrapper(gconstpointer a, gconstpointer b);
int compare_person_by_dist(VG * const* p1, VG * const* p2);
void free_vg_void (void* driver);
void free_vg(VG* data);
GPtrArray* Ordena(GHashTable *stats, GCompareFunc compare_func);



typedef struct catestat{
    GHashTable *topdriv;
    GHashTable *topuser;
    GPtrArray *Q2;
    GPtrArray *Q3;
    GHashTable *pmed;
    GHashTable *pordata;
    GPtrArray *Q5;
    GHashTable *dmed;
    GPtrArray *Q6;
    GHashTable *topcc;
    GPtrArray *Q7;
    GPtrArray *Q8;
    GPtrArray *Q9;
} CatalogoStats;

typedef struct um{
    char *id;
    Date *data;
    int nviag;
    double total_gasto;
    int aval;
    int dist;
} StatsUsers;

typedef struct driv{
    int id;
    Date *data;
    int nviag;
    double total_gasto;
    int aval;
} StatsDrivers;

typedef struct pmedcidade{
    double preco;
    int n_viagens;
} CityAvg;

typedef struct pdt{
    double preco;
    int nviag;
    Date *data;
} DataStats;

typedef struct dmed{
    Date *data;
    char *city;
    int distancia;
    int nviag;
}DMed;

typedef struct topcc{
    char *city;
    int id;
    int aval;
    int nviag;
} TopCC;

typedef struct topviag{
    int id_viag;
    int id_driver;
    char *username;
    char *nome_user;
    char *nome_condutor;
    Date *data_condutor;
    Date *data_user;
    char gender;
    int idade_condutor;
    int idade_user;
} TopViagem;

typedef struct gorj{
    Date *data;
    int dist;
    char *city;
    int id;
    double tip;
} VG;


void free_catalogo_stats(CatalogoStats *stats){
    g_hash_table_destroy(stats->topdriv);
    g_hash_table_destroy(stats->topuser);
    g_hash_table_destroy(stats->pmed);
    g_hash_table_destroy(stats->pordata);
    g_hash_table_destroy(stats->dmed);
    g_hash_table_destroy(stats->topcc);
    g_ptr_array_free(stats->Q5, TRUE);
    g_ptr_array_free(stats->Q2, TRUE);
    g_ptr_array_free(stats->Q3, TRUE);
    g_ptr_array_free(stats->Q6, TRUE);
    g_ptr_array_free(stats->Q7, TRUE);
    g_ptr_array_free(stats->Q8, TRUE);
    g_ptr_array_free(stats->Q9, TRUE);

}


CatalogoStats *loadStats (RidesCatalog *rides, DriverCatalog *drivers, UserCatalog *users){
    CatalogoStats *stats = malloc(sizeof(struct catestat));
    stats->topuser = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_q1user_void);
    stats->topdriv = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,free_q1driver_void);
    stats->pmed = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_pmed_void);
    stats->pordata = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_pdata_void);
    stats->dmed = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_dmed_void);
    stats->topcc = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_topcc_void);
    stats->Q8 = g_ptr_array_new_with_free_func(free_topv_void);
    stats->Q9 = g_ptr_array_new_with_free_func(free_vg_void);
    
    int tamanho = getRideLength(rides), i=0;
    while(i<tamanho){
        Ride *dados = getRideByIndex(rides,i);

        // QUERY 1, 2, 3 :
        int driver = get_rides_driver(dados);
        char *user = get_rides_user(dados);
        Driver *infos_driver = getDriverByID(drivers, driver);
        User *user1 = getUserByUsername(users, user);
        int driv_status = get_driver_acc_status(infos_driver);
        int user_status = get_user_acc_status(user1);

        if(driv_status == 1){
            if(g_hash_table_contains(stats->topdriv,GINT_TO_POINTER(driver)) == FALSE){
                StatsDrivers *statis = preenche_StatsDriver(dados, drivers);
                g_hash_table_insert(stats->topdriv,GINT_TO_POINTER(driver), statis);
            }
            else if(g_hash_table_contains(stats->topdriv,GINT_TO_POINTER(driver)) == TRUE){
                StatsDrivers *stats_atualizado = altera_StatsDriver(dados, drivers, stats->topdriv);
                g_hash_table_replace(stats->topdriv,GINT_TO_POINTER(driver), stats_atualizado);
            }
        }

        if(user_status == 1){
            if(g_hash_table_contains(stats->topuser,user) == FALSE){
                StatsUsers *stats1 = preenche_StatsUser(dados, drivers);
                g_hash_table_insert(stats->topuser,(user), stats1);
            }
            else if(g_hash_table_contains(stats->topuser,user) == TRUE){
                StatsUsers *stats_atualizado1 = altera_StatsUser(dados, drivers, stats->topuser);
                g_hash_table_replace(stats->topuser,(user), stats_atualizado1);
            }
        }
        else free(user);

        // QUERY 4:

        char *city = get_rides_city(dados);
        if(g_hash_table_contains(stats->pmed,city) == TRUE){
            CityAvg *transporta_atualizado = altera_pmed(dados, drivers, stats->pmed);
            g_hash_table_replace(stats->pmed,(city),transporta_atualizado);
        }
        else{
            CityAvg *transporta = preenche_pmed(dados, drivers);
            g_hash_table_insert(stats->pmed,(city),transporta);
        }


        // QUERY 5:
        char* data = DateToString(get_rides_data(dados));
        if(g_hash_table_contains(stats->pordata,data) == FALSE){
            DataStats *preco_data = preenche_datastats(dados, drivers);
            g_hash_table_insert(stats->pordata, data, preco_data);
        }
        else{
            DataStats *preco_data_atualizado = altera_datastats(dados, drivers, stats->pordata);
            g_hash_table_replace(stats->pordata, data, preco_data_atualizado);
        }


        // QUERY 6:
        char *datacity = g_strconcat(data,city,NULL);
        if(g_hash_table_contains(stats->dmed,datacity) == TRUE){
            DMed *dist_atualizada = altera_dmed(dados, stats->dmed, datacity);
            g_hash_table_replace(stats->dmed,(datacity),dist_atualizada);
        }
        else{
            DMed *dist = preenche_dmed(dados);
            g_hash_table_insert(stats->dmed,datacity,dist);
        }

        // QUERY 7:
        if(driv_status == 1){
            char *cityID = g_strdup_printf("%d%s", driver, city);
            if(g_hash_table_contains(stats->topcc,cityID) == TRUE){
                TopCC *dist_atualizada = altera_topcc(dados, stats->topcc, cityID);
             g_hash_table_replace(stats->topcc,cityID,dist_atualizada);
            }
            else{
                TopCC *dist = preencher_topcc(dados);
                g_hash_table_insert(stats->topcc,cityID,dist);
            }
        }

        // QUERY 8:
        if((user_status == 1) && (driv_status == 1)){
            char genero = get_driver_gender(infos_driver);
            char genero2 = get_user_gender(user1);
            if(genero == genero2){
                TopViagem *viag = preenche_topv(dados, infos_driver, user1);
                g_ptr_array_add(stats->Q8,viag);
            }
        }

        // QUERY 9:
        double tip = get_rides_tip(dados);
        if(tip){
            VG *viagem = preenche_vg(dados);
            g_ptr_array_add(stats->Q9,viagem);
        }



        i++;
        free_clone_driver(infos_driver);
        free_clone_user(user1);
        free_clone_rides(dados);
    }
    stats->Q2 = Ordena(stats->topdriv,compare_person_by_avmed_glib_wrapper);
    stats->Q3 = Ordena(stats->topuser,compare_person_by_distancia_glib_wrapper);
    stats->Q5 = Ordena(stats->pordata,compare_person_by_data_glib_wrapper);
    stats->Q6 = Ordena(stats->dmed,compare_person_by_data2_glib_wrapper);
    stats->Q7 = Ordena(stats->topcc,compare_person_by_avmed2_glib_wrapper);
    g_ptr_array_sort(stats->Q8,compare_person_by_acc_creation_glib_wrapper);
    g_ptr_array_sort(stats->Q9,compare_person_by_dist_glib_wrapper);
    return stats;
}

// QUERY 1,2 e 3


StatsUsers* preenche_StatsUser(Ride *dados, DriverCatalog *drivers){
    StatsUsers *new = malloc(sizeof(struct um));
    new->id = get_rides_user(dados);
    new->data = get_rides_data(dados);
    new->nviag = 1;
    new->dist = get_rides_distance(dados);
    new->aval = get_rides_score_user(dados);
    new->total_gasto = gasto_por_viagem(dados, drivers,1);
    return new;
}

StatsDrivers* preenche_StatsDriver(Ride *dados, DriverCatalog *drivers){
    StatsDrivers *new = malloc(sizeof(struct um));
    new->id = get_rides_driver(dados);
    new->data = get_rides_data(dados);
    new->nviag = 1;
    new->aval = get_rides_score_driver(dados);
    new->total_gasto = gasto_por_viagem(dados, drivers,1);
    return new;
}

StatsUsers* altera_StatsUser(Ride *dados, DriverCatalog *drivers, GHashTable *stats){
    StatsUsers *new = malloc(sizeof(struct um));
    new->id = get_rides_user(dados);
    StatsUsers *old = g_hash_table_lookup(stats, new->id);
    Date *data = get_rides_data(dados);
    int bigger = comp_datas(data,old->data);
    if(bigger == 1) new->data = data;
    else{
        new->data = old->data;
    }
    new->nviag = old->nviag + 1;
    new->dist = get_rides_distance(dados) + old->dist;
    new->aval = get_rides_score_user(dados) + old->aval;
    new->total_gasto = gasto_por_viagem(dados, drivers,1) + old->total_gasto;
    return new;
}

StatsDrivers* altera_StatsDriver(Ride *dados, DriverCatalog *drivers, GHashTable *stats){
    StatsDrivers *new = malloc(sizeof(struct um));
    new->id = get_rides_driver(dados);
    StatsDrivers *old = g_hash_table_lookup(stats, GINT_TO_POINTER(new->id));
    Date *data = get_rides_data(dados);
    int bigger = comp_datas(data,old->data);
    if(bigger == 1) new->data = data;
    else{
        new->data = old->data;
    }
    new->nviag = old->nviag + 1;
    new->aval = get_rides_score_driver(dados) + old->aval;
    new->total_gasto = gasto_por_viagem(dados, drivers,1) + old->total_gasto;
    return new;
}


gint compare_person_by_avmed_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_avmed((StatsDrivers * const*) a, (StatsDrivers * const*) b);
}

int compare_person_by_avmed(StatsDrivers * const* p1, StatsDrivers * const* p2) {

    double const p1_avmed = (*p1)->aval;
    double const p2_avmed = (*p2)->aval;
    double const p1_viag = (*p1)->nviag;
    double const p2_viag = (*p2)->nviag;
    double avmed1 = p1_avmed/p1_viag;
    double avmed2 = p2_avmed/p2_viag;

    if(fabs(avmed1 - avmed2) < 0.00001){
        int maior = comp_datas((Date* const)(*p1)->data,(Date* const)(*p2)->data);

        if(maior == 0){
            int bla = 0-(((*p1)->id > (*p2)->id) - ((*p1)->id < (*p2)->id));

            return bla;
        }
        else return maior;
    }
    return (avmed1 > avmed2) - (avmed1 < avmed2);
}


gint compare_person_by_distancia_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_distancia((StatsUsers * const*) a, (StatsUsers * const*) b);
}

int compare_person_by_distancia(StatsUsers * const* p1, StatsUsers * const* p2) {
    int const fst_av = (*p1)->dist;
    int const seg_av = (*p2)->dist;

    if((fst_av > seg_av) - (fst_av < seg_av) == 0){
        int maior = comp_datas((Date* const)(*p1)->data,(Date* const)(*p2)->data);

        if(maior==0){
            return -1*strcmp((char*)(*p1)->id,(char*)(*p2)->id);
        }
        else return maior;
    }
    return (fst_av > seg_av) - (fst_av < seg_av);
}

void free_q1user_void(void *dados){
    free_q1user(dados);
}

void free_q1user(StatsUsers *data){
    free(data->id);
    free(data);
}

void free_q1driver_void(void *dados){
    free_q1driver(dados);
}

void free_q1driver(StatsDrivers *data){
    free(data);
}


int getStatsDriverInfos(CatalogoStats *stats, int id, int *aval, int *nviag, double *total_gasto){
    StatsDrivers *dados = g_hash_table_lookup(stats->topdriv, GINT_TO_POINTER(id));
    if(!dados) return 0;
    *aval = dados->aval;
    *nviag = dados->nviag;
    *total_gasto = dados->total_gasto;
    return 1;
}

int getStatsUserInfos(CatalogoStats *stats, char *id, int *aval, int *nviag, double *total_gasto){
    StatsUsers *dados = g_hash_table_lookup(stats->topuser, id);
    if(!dados) return 0;
    *aval = dados->aval;
    *nviag = dados->nviag;
    *total_gasto = dados->total_gasto;
    return 1;
}

void getTopDrivInfos(CatalogoStats *stats, int *id, int *aval, int *nviag, int i){
    StatsDrivers *dados = stats->Q2->pdata[i];
    *aval = dados->aval;
    *nviag = dados->nviag;
    *id = dados->id;
}

void getTopUserInfos(CatalogoStats *stats, char **username, int *distancia, int i){
    StatsUsers *dados = stats->Q3->pdata[i];
    *username = strdup(dados->id);
    *distancia = dados->dist;
}

int getLengthTopDriv(CatalogoStats *stats){
    return stats->Q2->len;
}

int getLengthTopUser(CatalogoStats *stats){
    return stats->Q3->len;
}





// QUERY 4

CityAvg* preenche_pmed(Ride *dados, DriverCatalog *drivers){
    CityAvg *new = malloc(sizeof(struct pmedcidade));
    double preco = gasto_por_viagem(dados,drivers,0);
    new->preco = preco;
    new->n_viagens = 1;
    return new;
}

CityAvg* altera_pmed(Ride *dados, DriverCatalog *drivers, GHashTable *stats){
    CityAvg *new = malloc(sizeof(struct pmedcidade));
    char *dcity = get_rides_city(dados);
    CityAvg *info = g_hash_table_lookup(stats,dcity);
    new->preco = gasto_por_viagem(dados,drivers,0) + info->preco;
    new->n_viagens = info->n_viagens +1;
    free(dcity);
    return new;
}

double gasto_por_viagem(Ride* dados, DriverCatalog *driver, int inclui_tip){
    double total_gasto=0;
    int driver_id = get_rides_driver(dados);
    Driver *infos = getDriverByID(driver,driver_id);
    int car_class = get_driver_car_class(infos);
    int dados_distance = get_rides_distance(dados);
    double dados_tip = get_rides_tip(dados);
    if(car_class == 1){
        total_gasto = 3.25 + 0.62*((double)dados_distance);
    }
    else if(car_class == 2){
        total_gasto = 4 + 0.79*((double)dados_distance);
    }
    else if(car_class == 3){
        total_gasto = 5.20 + 0.94*((double)dados_distance);
    }
    if (inclui_tip) {
        total_gasto += dados_tip;
    }
    free_clone_driver(infos);
    return total_gasto;
}

void free_pmed_void (void* stats){
    free_pmed(stats);
}

void free_pmed(CityAvg* data){
    free(data);
}

int getCityAvgInfos(CatalogoStats *stats, double *preco, int *nviag, char *key){
    CityAvg *dados = g_hash_table_lookup(stats->pmed, key);
    if(!dados) return 0;
    *preco = dados->preco;
    *nviag = dados->n_viagens;
    return 1;
}








// QUERY 5:

DataStats *preenche_datastats(Ride *dados, DriverCatalog *drivers){
    DataStats *new = malloc(sizeof(struct pdt));
    new->preco = gasto_por_viagem(dados,drivers,0);
    new->nviag = 1;
    new->data = get_rides_data(dados);
    return new;
}

DataStats *altera_datastats(Ride *dados, DriverCatalog *drivers, GHashTable *stats){
    DataStats *new = malloc(sizeof(struct pdt));
    char* data = DateToString(get_rides_data(dados));
    DataStats *old = g_hash_table_lookup(stats, data);
    new->nviag = old->nviag + 1;
    new->preco = old->preco + gasto_por_viagem(dados,drivers,0);
    new->data = get_rides_data(dados);
    free(data);
    return new;
}

gint compare_person_by_data_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_data((DataStats * const*) a, (DataStats * const*) b);
}

int compare_person_by_data(DataStats * const* p1, DataStats * const* p2) {

    Date* const p1_data = (*p1)->data;
    Date* const p2_data = (*p2)->data;
    int maior = comp_datas(p1_data,p2_data);
    
    return maior;
}

void free_pdata_void (void* stats){
    free_pdata(stats);
}

void free_pdata(DataStats* data){
    free(data);
}

void getDataStatsInfo(CatalogoStats *stats, double *preco, int *nviag, Date **data, int i){
    DataStats *dados = stats->Q5->pdata[i];
    *preco = dados->preco;
    *nviag = dados->nviag;
    *data = clone_date(dados->data);
}

int getLengthQ5(CatalogoStats *stats){
    return stats->Q5->len;
}









// QUERY 6

DMed* preenche_dmed(Ride *dados){
    DMed *new = malloc(sizeof(struct dmed));
    new->data = get_rides_data(dados);
    new->distancia = get_rides_distance(dados);
    new->city = get_rides_city(dados);
    new->nviag = 1;
    return new;
}

DMed* altera_dmed(Ride *dados, GHashTable *Q6, char *key){
    DMed *new = malloc(sizeof(struct dmed));
    DMed *infos = g_hash_table_lookup(Q6,key);
    new->data = get_rides_data(dados);
    new->distancia = get_rides_distance(dados) + infos->distancia;
    new->city = get_rides_city(dados);
    new->nviag = infos->nviag +1;
    return new;
}

void free_dmed_void (void* driver){
    free_dmed(driver);
}

void free_dmed(DMed* data){
    free(data->city);
    free(data);
}

gint compare_person_by_data2_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_data2((DMed * const*) a, (DMed * const*) b);
}

int compare_person_by_data2(DMed * const* p1, DMed * const* p2) {

    Date* const p1_data = (*p1)->data;
    Date* const p2_data = (*p2)->data;
    int maior = comp_datas(p1_data,p2_data);
    
    return maior;
}


int getLengthQ6(CatalogoStats *stats){
    return stats->Q6->len;
}

void getDMedInfo(CatalogoStats *stats, int *dist, int *nviag,Date **data, char **city, int i){
    DMed *dados = stats->Q6->pdata[i];
    *dist = dados->distancia;
    *nviag = dados->nviag;
    *data = clone_date(dados->data);
    *city = strdup(dados->city);
}








// QUERY 7:

TopCC* preencher_topcc(Ride *dados){
    TopCC *new = malloc(sizeof(struct topcc));
    new->city = get_rides_city(dados);
    new->id = get_rides_driver(dados);
    new->aval = get_rides_score_driver(dados);
    new->nviag = 1;
    return new;
}

TopCC* altera_topcc(Ride *dados, GHashTable *stats, char *key){
    TopCC *new = malloc(sizeof(struct topcc));
    TopCC *infos = g_hash_table_lookup(stats, key);
    new->city = get_rides_city(dados);
    new->id = get_rides_driver(dados);
    new->aval = infos->aval + get_rides_score_driver(dados);
    new->nviag = infos->nviag +1;
    return new;
}

void free_topcc_void (void* driver){
    free_topcc(driver);
}

void free_topcc(TopCC* data){
    free(data->city);
    free(data);
}

gint compare_person_by_avmed2_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_avmed2((TopCC * const*) a, (TopCC * const*) b);
}

int compare_person_by_avmed2(TopCC * const* p1, TopCC * const* p2) {

    double const p1_avmed = (*p1)->aval;
    double const p2_avmed = (*p2)->aval;
    double const p1_viag = (*p1)->nviag;
    double const p2_viag = (*p2)->nviag;
    double avmed1 = p1_avmed/p1_viag;
    double avmed2 = p2_avmed/p2_viag;

    if(fabs(avmed1 - avmed2) < 0.00001){
        return ((*p1)->id > (*p2)->id) - ((*p1)->id < (*p2)->id);
    }
    return (avmed1 > avmed2) - (avmed1 < avmed2);
}


int getLengthQ7(CatalogoStats *stats){
    return stats->Q7->len;
}

void getTopCCInfo(CatalogoStats *stats, int *id, int *aval, int *nviag, char **city, int i){
    TopCC *dados = stats->Q7->pdata[i];
    *id = dados->id;
    *aval = dados->aval;
    *nviag = dados->nviag;
    *city = strdup(dados->city);
}






// QUERY 8:

TopViagem* preenche_topv(Ride *dados, Driver* infos_driver, User* infos_user){
    TopViagem *new = malloc(sizeof(struct topviag));
    new->id_viag = get_rides_id(dados);
    new->id_driver = get_rides_driver(dados);
    new->username = get_rides_user(dados);
    new->data_user = get_user_acc_creation(infos_user);
    new->data_condutor = get_driver_acc_creation(infos_driver);
    new->gender = get_driver_gender(infos_driver);
    new->idade_user = idade(new->data_user);
    new->idade_condutor = idade(new->data_condutor);
    new->nome_user = get_user_name(infos_user);
    new->nome_condutor = get_driver_name(infos_driver);
    return new;
}

void free_topv_void (void* driver){
    free_topv(driver);
}

void free_topv(TopViagem* data){
    free(data->username);
    free(data->nome_condutor);
    free(data->nome_user);
    free(data);
}

gint compare_person_by_acc_creation_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_acc_creation((TopViagem * const*) a, (TopViagem * const*) b);
}

int compare_person_by_acc_creation(TopViagem * const* p1, TopViagem * const* p2) {
    Date* const p1_driv = (*p1)->data_condutor;
    Date* const p2_driv = (*p2)->data_condutor;
    int maior = comp_datas(p1_driv, p2_driv);

    if(maior == 0){
        Date* const p1_user = (*p1)->data_user;
        Date* const p2_user = (*p2)->data_user;
        int maior2 = comp_datas(p1_user, p2_user);
        if(maior2 == 0){
            int const id1 = (*p1)->id_viag;
            int const id2 = (*p2)->id_viag;
            return -((id1 > id2) - (id1 < id2));
        }
        return -maior2;
    }
    return -maior;
}


int getLengthQ8(CatalogoStats *stats){
    return stats->Q8->len;
}

void getTopViagemInfoConditions(CatalogoStats *stats, char *gender, int *idade_condutor, int *idade_user, int i){
    TopViagem *dados = stats->Q8->pdata[i];
    *gender = dados->gender;
    *idade_condutor = dados->idade_condutor;
    *idade_user = dados->idade_user;
}

void getTopViagemInfo(CatalogoStats *stats, int *id_driver, char **username, char **nome_user, char **nome_condutor, int i){
    TopViagem *dados = stats->Q8->pdata[i];
    *id_driver = dados->id_driver;
    *username = strdup(dados->username);
    *nome_user = strdup(dados->nome_user);
    *nome_condutor = strdup(dados->nome_condutor);
}







// QUERY 9:

VG* preenche_vg(Ride *dados){
    VG *new = malloc(sizeof(struct gorj));
    new->data = get_rides_data(dados);
    new->dist = get_rides_distance(dados);
    new->city = get_rides_city(dados);
    new->id = get_rides_id(dados);
    new->tip = get_rides_tip(dados);
    return new;
}

gint compare_person_by_dist_glib_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_person_by_dist((VG * const*) a, (VG * const*) b);
}

int compare_person_by_dist(VG * const* p1, VG * const* p2) {

    int const p1_dist = (*p1)->dist;
    int const p2_dist = (*p2)->dist;

    if((p1_dist > p2_dist) - (p1_dist < p2_dist) == 0){
        Date* const data1 = (*p1)->data;
        Date* const data2 = (*p2)->data;
        int maior = comp_datas(data1,data2);
        if(maior == 0){
            int const id1 = (*p1)->id;
            int const id2 = (*p2)->id;
            return ((id1 > id2) - (id1 < id2));
        }
        return maior;
    }
    return (p1_dist > p2_dist) - (p1_dist < p2_dist);
}



void free_vg_void (void* driver){
    free_vg(driver);
}

void free_vg(VG* data){
    free(data->city);
    free(data);
}

GPtrArray* Ordena(GHashTable *stats, GCompareFunc compare_func){
    guint tamanho = g_hash_table_size(stats);
    GPtrArray* array = g_ptr_array_sized_new(tamanho);
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, stats);
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        void* data = g_hash_table_lookup(stats,key);
        if(data) g_ptr_array_add (array, (data));
    }
    g_ptr_array_sort(array,compare_func);
    return array;
}

int getLengthQ9(CatalogoStats *stats){
    return stats->Q9->len;
}


void getVGInfoConditions(CatalogoStats *stats, Date **data, int i){
    VG *dados = stats->Q9->pdata[i];
    *data = clone_date(dados->data);
}

void getVGInfo(CatalogoStats *stats, int *id, int *dist, char **city, double *tip, int i){
    VG *dados = stats->Q9->pdata[i];
    *id = dados->id;
    *dist = dados->dist;
    *city = strdup(dados->city);
    *tip = dados->tip;
}
