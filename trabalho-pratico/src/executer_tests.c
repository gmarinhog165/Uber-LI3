#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <ctype.h>

#include "date.h"
#include "output.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_drivers.h"
#include "catalogo_users.h"
#include "catalogo_rides.h"
#include "estatisticas.h"
#include "conector_tests.h"
#include "queries_tests.h"
#include "executer_tests.h"


char* path_inst(char *argv[]);
char* path_test(char *argv[]);


void execute_test(char *argv[], CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users){
    char *path = path_inst(argv);
    char *testes = path_test(argv);
    FILE* fp = NULL;
    fp = fopen(path, "r");
    if (!fp) {
        perror("Error");
        return;
    }
    int i = 1;
    char* line = NULL;
    ssize_t read;
    size_t len=0;
    while ((read = getline(&line, &len, fp)) != -1){
        char* line_copy = strdup(line);
        char* command = strsep(&line_copy, "\n");
        int nquery = command[0] - '0';
        char *id = strdup(command+2);
        char name[64];
        snprintf(name, 64, "Resultados/command%d_output.txt", i);
        char test[64];
        snprintf(test,64, "%s/command%d_output.txt", testes,i);
        query_testes(stats,drivers,users,id,nquery,name,i,test, NULL);
        i++;
        free(id);
        free(command);
    }
    free(line);
}


char* path_inst(char *argv[]){
    return argv[2];
} 

char* path_test(char *argv[]){
    return argv[3];
}

