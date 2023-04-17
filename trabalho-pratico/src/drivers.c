#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>

#include "date.h"
#include "drivers.h"

void free_driver(Driver* data);


typedef enum {basic = 1, green = 2, premium = 3} CC;

typedef struct drivers{
    int id;
    char* name;
    Date *birth_date;
    char gender;
    CC car_class;
    char* license_plate;
    char* city;
    Date* account_creation;
    int account_status;
}Driver;

Driver* drivers_create(){
    return malloc(sizeof(struct drivers));
}


int check_carclass(char *car_class){
    if (strcasecmp(car_class,"basic") == 0) return basic;
    else if(strcasecmp(car_class, "green") == 0) return green;
    else if(strcasecmp(car_class, "premium") == 0) return premium;
    else return 4;
}


Driver* preenche_drivers_tokens(char** tokens){
    Driver* cliente = drivers_create();
    cliente->id = atoi(tokens[0]);
    cliente->name = strdup(tokens[1]);
    cliente->birth_date = preenche_data(tokens[2]);
    cliente->gender = tokens[3][0];
    cliente->car_class = check_carclass(tokens[4]);
    cliente->city = strdup(tokens[6]);
    cliente->account_creation = preenche_data(tokens[7]);
    cliente->account_status = check_acc_status(tokens[8]);
    return cliente;
}

int validate_drivers_tokens(char **tokens){
    if(strlen(tokens[0]) == 0) return 1;
    if(strlen(tokens[1]) == 0) return 1;
    if(validate_date(tokens[2])) return 1;
    if(strlen(tokens[3]) == 0) return 1;
    if(check_carclass(tokens[4]) == 4) return 1;
    if(strlen(tokens[5]) == 0) return 1;
    if(strlen(tokens[6]) == 0) return 1;
    if(validate_date(tokens[7])) return 1;
    if(check_acc_status(tokens[8]) == 4) return 1;
    return 0;
}


void free_driver(Driver* data){

    free(data->name);
    free_date(data->birth_date);
    free(data->city);
    free_date(data->account_creation);
    free(data);
}

void free_driver_void (gpointer user){
    free_driver(user);
}

void free_clone_driver(Driver* data){

    free(data->name);
    free(data);
}


int get_driver_id(Driver* dados){
    return (dados->id);
}

char* get_driver_name(Driver* dados){
    return strdup(dados->name);
}

char get_driver_gender(Driver* dados){
    return (dados->gender);
}

Date* get_driver_birth_date(Driver* dados){
    return (dados->birth_date);
}

int get_driver_car_class(Driver* dados){
    return dados->car_class;
}

Date* get_driver_acc_creation(Driver* dados){
    return (dados->account_creation);
}

int get_driver_acc_status(Driver* dados){
    return dados->account_status;
}


Driver *clone_driver(Driver *dados){
    Driver *new = drivers_create();
    new->id = get_driver_id(dados);
    new->name = get_driver_name(dados);
    new->birth_date = get_driver_birth_date(dados);
    new->gender = get_driver_gender(dados);
    new->car_class = get_driver_car_class(dados);
    new->account_creation = get_driver_acc_creation(dados);
    new->account_status = get_driver_acc_status(dados);
    return new;
}
