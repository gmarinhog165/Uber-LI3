#include <stdio.h>
#include <glib.h>

#include "date.h"
#include "drivers.h"
#include "parse_csv.h"
#include "catalogo_drivers.h"

typedef struct cata1{
    GHashTable *drivers;
} DriverCatalog;

Driver *getDriverByID(DriverCatalog *info, int key){
    Driver *dados = g_hash_table_lookup(info->drivers,GINT_TO_POINTER(key));
    if(!dados) return NULL;
    return clone_driver(dados);
}


void buildDriver(char **tokens, DriverCatalog *stats){
    int i = validate_drivers_tokens(tokens);
    if(i) return;
    Driver *d = preenche_drivers_tokens(tokens);
    int id = get_driver_id(d);
    g_hash_table_insert(stats->drivers,GINT_TO_POINTER(id),d);
}

void buildDriver_wrapper(char **tokens, void *structure){
    return buildDriver(tokens,(DriverCatalog *) structure);
}

DriverCatalog *DriverToStruct(char *path){
    DriverCatalog *new = malloc(sizeof(struct cata1));
    new->drivers = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,free_driver_void);
    parseCSV(path, buildDriver_wrapper,new);
    free(path);
    return new;
}

void free_driver_catalog(DriverCatalog *dados){
    g_hash_table_destroy(dados->drivers);
}