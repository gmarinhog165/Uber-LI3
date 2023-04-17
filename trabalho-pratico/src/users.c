#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>

#include "date.h"
#include "users.h"

typedef enum {activ = 1, inactiv = 2} AST;

typedef struct users{
    char* username;
    char* name;
    char gender;
    Date* birth_date;
    Date* account_creation;
    AST account_status;
}User;


User* users_create() {
    return malloc(sizeof(struct users));
}

User* preenche_users_tokens(char** tokens){
    User* cliente = users_create();
    cliente->username = strdup(tokens[0]);
    cliente->name = strdup(tokens[1]);
    cliente->gender = tokens[2][0];
    cliente->birth_date = preenche_data(tokens[3]);
    cliente->account_creation = preenche_data(tokens[4]);
    cliente->account_status = check_acc_status(tokens[6]);
    return cliente;
}


void free_user(User* data){

    free(data->username);
    free(data->name);
    free_date(data->birth_date);
    free_date(data->account_creation);
    free(data);
}

void free_user_void (gpointer user){
    free_user(user);
}

void free_clone_user(User* data){

    free(data->name);
    free(data->username);
    free(data);
}


char* get_user_username(User* dados){
    return strdup(dados->username);
}

char* get_user_name(User* dados){
    return strdup(dados->name);
}

char get_user_gender(User* dados){
    return (dados->gender);
}

Date* get_user_birth_date(User* dados){
    return (dados->birth_date);
}

Date* get_user_acc_creation(User* dados){
    return (dados->account_creation);
}

int get_user_acc_status(User* dados){
    return (dados->account_status);
}

int validate_users_tokens(char **tokens){
    if(strlen(tokens[0]) == 0) return 1;
    if(strlen(tokens[1]) == 0) return 1;
    if(strlen(tokens[2]) == 0) return 1;
    if(validate_date(tokens[3])) return 1;
    if(validate_date(tokens[4])) return 1;
    if(strlen(tokens[5]) == 0) return 1;
    if(check_acc_status(tokens[6]) == 4) return 1;
    return 0;
}


User *clone_user(User *dados){
    User *new = users_create();
    new->username = get_user_username(dados);
    new->name = get_user_name(dados);
    new->gender = get_user_gender(dados);
    new->birth_date = get_user_birth_date(dados);
    new->account_creation = get_user_acc_creation(dados);
    new->account_status = get_user_acc_status(dados);
    return new;
}
