#include <stdio.h>
#include <glib.h>

#include "date.h"
#include "output.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_drivers.h"
#include "catalogo_users.h"
#include "catalogo_rides.h"
#include "estatisticas.h"
#include "executer.h"
#include "conector.h"


char* path_driver(char *argv[]);
char* path_user(char *argv[]);
char* path_rides(char *argv[]);
char* path_inst(char *argv[]);


void start(int argc, char *argv[]){
    char *driver_path = NULL;
    char *user_path = NULL;
    char *rides_path = NULL;
    char *inst_path = NULL;
    
    if(argc > 1){
        driver_path = path_driver(argv);
        user_path = path_user(argv);
        rides_path = path_rides(argv);
        inst_path = path_inst(argv);
    }
    else {
        user_path = malloc(100 * sizeof(char));
        driver_path = malloc(100 * sizeof(char));
        rides_path = malloc(100 * sizeof(char));
        path_interativo(&user_path, &driver_path, &rides_path);
    }

    DriverCatalog *driver = DriverToStruct(driver_path);
    UserCatalog *user = UserToStruct(user_path);
    RidesCatalog *rides = RidesToStruct(rides_path);
    CatalogoStats *stats = loadStats(rides,driver,user);
    execute(inst_path,stats,driver,user);

    free_user_catalog(user);
    free_driver_catalog(driver);
    free_rides_catalog(rides);
    free(driver);
    free(user);
    free(rides);
    free_catalogo_stats(stats);
    free(stats);
}

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

char* path_inst(char *argv[]){
    return argv[2];
}