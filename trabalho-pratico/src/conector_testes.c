#include <stdio.h>
#include <glib.h>


#include "date.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_drivers.h"
#include "catalogo_users.h"
#include "catalogo_rides.h"
#include "estatisticas.h"
#include "executer_tests.h"
#include "conector_tests.h"


char* path_driver(char *argv[]){
    const gchar* input = argv[1];
    char *driver = g_build_path("/", input, "drivers.csv", NULL);
    return driver;
}

char* path_user(char *argv[]){
    const gchar* input = argv[1];
    char *user = g_build_path("/", input, "users.csv", NULL);
    return user;
}

char* path_rides(char *argv[]){
    const gchar* input = argv[1];
    char *rides = g_build_path("/", input, "rides.csv", NULL);
    return rides;
}

void start_testes(char *argv[]){
    char *driver_path = path_driver(argv);
    char *user_path = path_user(argv);
    char *rides_path = path_rides(argv);


    DriverCatalog *driver = DriverToStruct(driver_path);
    UserCatalog *user = UserToStruct(user_path);
    RidesCatalog *rides = RidesToStruct(rides_path);
    CatalogoStats *stats = loadStats(rides,driver,user);
    execute_test(argv,stats,driver,user);


    free_user_catalog(user);
    free_driver_catalog(driver);
    free_rides_catalog(rides);
    free(driver);
    free(user);
    free(rides);
    free_catalogo_stats(stats);
    free(stats);
} 