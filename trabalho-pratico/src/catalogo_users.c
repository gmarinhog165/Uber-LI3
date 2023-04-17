#include <stdio.h>
#include <glib.h>

#include "date.h"
#include "users.h"
#include "parse_csv.h"
#include "catalogo_users.h"

typedef struct cata2{
    GHashTable *users;
} UserCatalog;

User *getUserByUsername(UserCatalog *info, char *key){
    User *dados = g_hash_table_lookup(info->users,key);
    if(!dados) return NULL;
    return clone_user(dados);
}

void buildUser(char **tokens, UserCatalog *stats){
    int i = validate_users_tokens(tokens);
    if(i) return;
    User *d = preenche_users_tokens(tokens);
    char *id = get_user_username(d);
    g_hash_table_insert(stats->users,id,d);
}

void buildUser_wrapper(char **tokens, void *structure){
    return buildUser(tokens,(UserCatalog *) structure);
}

UserCatalog *UserToStruct(char *path){
    UserCatalog *new = malloc(sizeof(struct cata2));
    new->users = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_user_void);
    parseCSV(path, buildUser_wrapper,new);
    free(path);
    return new;
}

void free_user_catalog(UserCatalog *dados){
    g_hash_table_destroy(dados->users);
}