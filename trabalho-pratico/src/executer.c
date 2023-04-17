#include <stdio.h>
#include <glib.h>
#include <string.h>


#include "date.h"
#include "output.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_drivers.h"
#include "catalogo_users.h"
#include "catalogo_rides.h"
#include "estatisticas.h"
#include "queries.h"
#include "executer.h"


void execute(char *path, CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users){
    if(path){
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
            query(stats,drivers,users,id,nquery,name, NULL);
            i++;
            free(id);
            free(command);
        }
        free(line);
    }
    else{
        int k = -1;
        while(k!=0){
            Paginacao *p = paginacao_create();
            int numero;
            char *valores = malloc(100 * sizeof(char));
            get_query_info(&numero, &valores);
            query(stats,drivers,users,valores,numero,NULL, p);
            interativo(p);
            free_paginacao_wrapper(p);
            printf_mini_menu(&k);
            free(valores);
        }
    }
}