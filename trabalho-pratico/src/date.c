#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

#include "date.h"

#define DIA 9
#define MES 10
#define ANO 2022


typedef struct dat{
    int dia;
    int mes;
    int ano;
} Date;


int validate_date(char *date) {
    if (strlen(date) != 10) return 1;

    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) return 1;

    if (month < 1 || month > 12 || day < 1 || day > 31) return 1;

    return 0;
}

int check_acc_status(char *account_status){
    if(!account_status) return 4;
    if(strcasecmp(account_status, "active") == 0) return 1;
    else if (strcasecmp(account_status, "inactive") == 0) return 2;
    else return 4;
}

int getDateDia(Date *dados){
    return dados->dia;
}

int getDateMes(Date *dados){
    return dados->mes;
}

int getDateAno(Date *dados){
    return dados->ano;
}

Date* clone_date(Date *dados){
    Date *new = malloc(sizeof(struct dat));
    new->dia = dados->dia;
    new->mes = dados->mes;
    new->ano = dados->ano;
    return new;
}

Date* preenche_data(char *command){
    Date *new = malloc(sizeof(struct dat));
    new->dia = atoi(strtok(command,"/"));
    new->mes = atoi(strtok(NULL,"/"));
    new->ano = atoi(strtok(NULL,"/"));
    return new;
}

char *DateToString(Date *data){
    char *date_string = g_strdup_printf("%02d/%02d/%04d", data->dia, data->mes, data->ano);
    return date_string;
}

void free_date(Date *data){
    free(data);
}

Date* StringToDate(char *command){
    Date *data = malloc(sizeof(struct dat));
    sscanf(command, "%d/%d/%d", &data->dia, &data->mes, &data->ano);
    return data;
}

int comp_datas(Date *data, Date *data2){
    int ano_data = getDateAno(data);
    int ano_date = getDateAno(data2);


    if(ano_data > ano_date) return 1;
    else if (ano_data < ano_date) return -1;
    else{
        int mes_data = getDateMes(data);
        int mes_date = getDateMes(data2);
        if(mes_data > mes_date) return 1;
        else if (mes_data < mes_date) return -1;
        else{
            int dia_data = getDateDia(data);
            int dia_date = getDateDia(data2);
            if(dia_data > dia_date) return 1;
            else if (dia_data < dia_date) return -1;
            else return 0;
        }
    }
}

int idade(Date* birthdate) {
    int ano = getDateAno(birthdate);
    int mes = getDateMes(birthdate);
    int dia = getDateDia(birthdate);
    int age = ANO - ano;
    if (MES < mes || (MES == mes && DIA < dia)) age--;
    return age;
}
