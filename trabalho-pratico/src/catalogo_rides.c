#include <stdio.h>
#include <glib.h>

#include "date.h"
#include "rides.h"
#include "parse_csv.h"
#include "catalogo_rides.h" 

typedef struct cata3{
    GPtrArray *rides;
} RidesCatalog;

Ride *getRideByIndex(RidesCatalog *info, int index){
    Ride *dados = info->rides->pdata[index];
    return clone_rides(dados);
}

int getRideLength (RidesCatalog *info){
    return info->rides->len;
}

void buildRides(char **tokens, RidesCatalog *stats){
    int i = validate_tokens(tokens);
    if(i) return;
    Ride *d = preenche_rides_tokens(tokens);
    g_ptr_array_add(stats->rides,d);
}

void buildRides_wrapper(char **tokens, void *structure){
    return buildRides(tokens,(RidesCatalog *) structure);
}

RidesCatalog *RidesToStruct(char *path){
    RidesCatalog *new = malloc(sizeof(struct cata3));
    new->rides =  g_ptr_array_new_with_free_func(free_rides_void);
    parseCSV(path, buildRides_wrapper, new);
    free(path);
    return new;
}

void free_rides_catalog(RidesCatalog *dados){
    g_ptr_array_free(dados->rides, TRUE);
}