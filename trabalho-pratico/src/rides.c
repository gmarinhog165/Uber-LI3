#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>
#include <math.h> 


#include "date.h"
#include "rides.h"

int validate_distance(char *distance);
int validate_tip(char *tip);

typedef struct rides{
    int id;
    Date *data;
    int driver;
    char* user;
    char* city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
}Ride;


Ride* rides_create(){
    return malloc(sizeof(struct rides));
}


Ride* preenche_rides_tokens(char** tokens) {
    Ride* viagem = rides_create();
    viagem->id = atoi(tokens[0]);
    viagem->data = preenche_data(tokens[1]);
    viagem->driver = atoi(tokens[2]);
    viagem->user = strdup(tokens[3]);
    viagem->city = strdup(tokens[4]);
    viagem->distance = atoi(tokens[5]);
    viagem->score_user = atoi(tokens[6]);
    viagem->score_driver = atoi(tokens[7]);
    viagem->tip = atof(tokens[8]);
    return viagem;
}

void free_rides(Ride* data){
    free_date(data->data);
    free(data->user);
    free(data->city);
    free(data);
}

void free_clone_rides(Ride* data){
    free(data->user);
    free(data->city);
    free(data);
}

void free_rides_void (gpointer user){
    free_rides(user);
}

int get_rides_id(Ride* dados){
    return (dados->id);
}

Date* get_rides_data(Ride* dados){
    return (dados->data);
}

int get_rides_driver(Ride* dados){
    return (dados->driver);
}

char* get_rides_user(Ride* dados){
    return strdup(dados->user);
}

char* get_rides_city(Ride* dados){
    return strdup(dados->city);
}

int get_rides_distance(Ride* dados){
    return (dados->distance);
}

int get_rides_score_user(Ride* dados){
    return (dados->score_user);
}

int get_rides_score_driver(Ride* dados){
    return (dados->score_driver);
}

double get_rides_tip(Ride* dados){
    return (dados->tip);
}

int validate_tokens(char **command) {
    if(strlen(command[0]) == 0) return 1;
    if(!command[1] || validate_date(command[1])) return 1;
    if(strlen(command[2]) == 0) return 1;
    if(strlen(command[3]) == 0) return 1;
    if(strlen(command[4]) == 0) return 1;
    if(!command[5] || validate_distance(command[5])) return 1;
    if(!command[6] || validate_distance(command[6])) return 1;
    if(!command[5] || validate_distance(command[7])) return 1;
    if(!command[8] || validate_tip(command[8])) return 1;
    return 0;
}

int validate_distance(char *distance) {
    char *end;
    double dist = strtod(distance, &end);
    if (distance == end || *end != '\0' || isnan(dist) || dist < 0.0001 || strchr(distance, '.')) return 1;
    return 0;
}

int validate_tip(char *tip) {
    char *end;
    double t = strtod(tip, &end);
    if (tip == end || *end != '\0' || isnan(t) || t < 0) return 1;
    return 0;
}

Ride *clone_rides(Ride *dados){
    Ride *new = rides_create();
    new->id = get_rides_id(dados);
    new->data = get_rides_data(dados);
    new->driver = get_rides_driver(dados);
    new->user = get_rides_user(dados);
    new->city = get_rides_city(dados);
    new->distance = get_rides_distance(dados);
    new->score_driver = get_rides_score_driver(dados);
    new->score_user = get_rides_score_user(dados);
    new->tip = get_rides_tip(dados);
    return new;
}