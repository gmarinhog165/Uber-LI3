#include <stdio.h>
#include <glib.h>
#include <ctype.h>
#include <time.h>

#include "date.h"
#include "output.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "catalogo_users.h"
#include "catalogo_drivers.h"
#include "catalogo_rides.h"
#include "estatisticas.h"
#include "queries.h"


void query1(CatalogoStats *stats, UserCatalog *users, DriverCatalog *drivers, char *ID, char *path, int i, Paginacao *p);
void query2(CatalogoStats *stats, DriverCatalog *drivers, int N, char *path, Paginacao *p);
void query3(CatalogoStats *stats, UserCatalog *users, int N, char *path, Paginacao *p);
void query4(CatalogoStats *stats, char *city, char *path, Paginacao *p);
void query5(CatalogoStats *stats, char *data1, char *data2, char* path, Paginacao *p);
void query6(CatalogoStats *stats, char *data1, char *data2, char *city, char *path, Paginacao *p);
void query7(CatalogoStats *stats, DriverCatalog *drivers, char *city, int N, char *path, Paginacao *p);
void query8(CatalogoStats *stats, char *gender, int anos, char *path, Paginacao *p);
void query9(CatalogoStats *stats, char *data1, char *data2, char *path, Paginacao *p);



void query1(CatalogoStats *stats, UserCatalog *users, DriverCatalog *drivers, char *ID, char *path, int i, Paginacao *p){
    char *output = NULL;
    if(i){
        int id = atoi(ID);
        Driver *driv = getDriverByID(drivers,id);
        if(!driv){
            gere_output(output,path, p);
            return;
        }
        int aval, nviag;
        double total_gasto;
        int j = getStatsDriverInfos(stats,id,&aval,&nviag,&total_gasto);
        if(!j){
            free_clone_driver(driv);
            gere_output(output,path, p);
            return;
        }
        char *nome = get_driver_name(driv);
        char gender = get_driver_gender(driv);
        double avmed = (double)aval/(double)nviag;
        Date *data = get_driver_birth_date(driv);
        output = g_strdup_printf("%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idade(data),avmed,nviag,total_gasto);
        gere_output(output,path, p);
        free(output);
        free(nome);
        free_clone_driver(driv);
    }
    else{
        User *user = getUserByUsername(users, ID);
        if(!user){
            gere_output(output,path, p);
            return;
        }
        int aval, nviag;
        double total_gasto;
        int j = getStatsUserInfos(stats,ID,&aval,&nviag,&total_gasto);
        if(!j){
            free_clone_user(user);
            gere_output(output,path, p);
            return;
        }
        char *nome = get_user_name(user);
        char gender = get_user_gender(user);
        double avmed = (double)aval/(double)nviag;
        Date *data = get_user_birth_date(user);
        output = g_strdup_printf("%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idade(data),avmed,nviag,total_gasto);
        gere_output(output,path, p);
        free(output);
        free(nome);
        free_clone_user(user);
    }
}



void query2(CatalogoStats *stats, DriverCatalog *drivers, int N, char *path, Paginacao *p){
    int id, aval, nviag, i=1, tamanho = getLengthTopDriv(stats), index;
    char *output = NULL;
    while(i<=N && i<tamanho){
        index = tamanho - i;
        getTopDrivInfos(stats,&id, &aval,&nviag, index);
        Driver *driv = getDriverByID(drivers, id);
        char *nome = get_driver_name(driv);
        double avmed = (double)aval/(double)nviag;
        output = g_strdup_printf("%012d;%s;%.3f\n",id,nome,avmed);
        i++;
        gere_output(output,path, p);
        free(output);
        free(nome);
        free_clone_driver(driv);
    }
    if(N == 0) gere_output(output,path, p);
}


void query3(CatalogoStats *stats, UserCatalog *users, int N, char *path, Paginacao *p){
    int dist, tamanho = getLengthTopUser(stats), index, i=1;
    char *username, *output = NULL;
    while(i<=N && i<tamanho){
        index = tamanho - i;
        getTopUserInfos(stats,&username,&dist,index);
        User *user = getUserByUsername(users, username);
        char *nome = get_user_name(user);
        output = g_strdup_printf("%s;%s;%d\n",username,nome,dist);
        gere_output(output,path, p);
        i++;
        free(output);
        free(nome);
        free(username);
        free_clone_user(user);
    }
    if(N == 0) gere_output(output,path, p);
}


void query4(CatalogoStats *stats, char *city, char *path, Paginacao *p){
    int nviag;
    double preco;
    char *output = NULL;
    int i = getCityAvgInfos(stats, &preco, &nviag, city);
    if(!i) {
        gere_output(output,path, p);
        return;
    }
    double avg = preco/(double)nviag;
    output = g_strdup_printf("%.3f\n",avg);
    gere_output(output,path, p);
    free(output);
}

void query5(CatalogoStats *stats, char *data1, char *data2, char* path, Paginacao *p){
    char *output = NULL;
    int i = 0, tamanho = getLengthQ5(stats), nviag, count = 0;
    Date *date1 = StringToDate(data1);
    Date *date2 = StringToDate(data2);
    double preco, total = 0;
    Date *atual;
    while(i<tamanho){
        getDataStatsInfo(stats,&preco,&nviag, &atual, i);
        if(comp_datas(date1,atual) > 0){
            i++; 
            free_date(atual);
            continue;
        }
        if(comp_datas(date2,atual) == -1) {
            free_date(atual);
            break;
        }
        count += nviag;
        total += preco;
        i++;
        free_date(atual);
    }
    if(!total || !count){
        gere_output(output,path, p);
        free_date(date1);
        free_date(date2);
        return;
    }
    double pmedio = total/(double)(count);
    output = g_strdup_printf("%.3f\n",pmedio);
    gere_output(output,path, p);
    free(output);
    free_date(date1);
    free_date(date2);
}


void query6(CatalogoStats *stats, char *data1, char *data2, char *city, char *path, Paginacao *p){
    int i = 0, tamanho = getLengthQ6(stats), count = 0, dist, nviag, total = 0;
    Date *atual;
    Date *date1 = StringToDate(data1);
    Date *date2 = StringToDate(data2);
    char *city2, *output = NULL;
    while(i<tamanho){
        getDMedInfo(stats, &dist, &nviag, &atual, &city2, i);
        if(strcmp(city, city2) == 0){
            if(comp_datas(date1,atual) > 0){
                free(city2);
                free_date(atual);
                i++; 
                continue;
            }
            if(comp_datas(date2,atual) == -1) {
                free(city2);
                free_date(atual);
                break;
            }
            count += nviag;
            total += dist;
        }
        i++;
        free_date(atual);
        free(city2);
    }
    if(!total || !count){
        gere_output(output,path, p);
        free_date(date1);
        free_date(date2);
        return;
    }
    double dmedia = (double)total/(double)(count);
    output = g_strdup_printf("%.3f\n", dmedia);
    gere_output(output,path, p);
    free(output);
    free_date(date1);
    free_date(date2);
}

void query7(CatalogoStats *stats, DriverCatalog *drivers, char *city, int N, char *path, Paginacao *p){
    int i =1, id, nviag, aval, tamanho = getLengthQ7(stats), index, flag = 0;
    char *city2, *output = NULL;
    while(i<=N && i<tamanho){
        index = tamanho - i;
        getTopCCInfo(stats,&id, &aval, &nviag,&city2, index);
        if(strcmp(city, city2) != 0){
            free(city2);
            i++; 
            N++; 
            continue;
        }
        flag = 1;
        Driver *driv = getDriverByID(drivers, id);
        char *nome = get_driver_name(driv);
        double avmed = (double)aval/(double)nviag;
        output = g_strdup_printf("%012d;%s;%.3f\n", id, nome, avmed);
        gere_output(output,path, p);
        free(output);
        i++;
        free(nome);
        free(city2);
        free_clone_driver(driv);
    }
    if(flag == 0) gere_output(output,path, p);
}


void query8(CatalogoStats *stats, char *gender, int anos, char *path, Paginacao *p){
    int i =1, tamanho = getLengthQ8(stats), idade_driver, idade_user, id_driver, index, flag = 0;
    char gender1, *username, *nome_user, *nome_driver, *output = NULL;
    while(i<tamanho){
        index = tamanho - i;
        getTopViagemInfoConditions(stats, &gender1, &idade_driver, &idade_user, index);
        if((gender1 != gender[0]) || (idade_driver < anos) || (idade_user < anos)){
            i++;
            continue;
        }
        getTopViagemInfo(stats, &id_driver, &username, &nome_user, &nome_driver, index);
        i++;
        output = g_strdup_printf("%012d;%s;%s;%s\n", id_driver, nome_driver, username, nome_user);
        gere_output(output,path, p);
        free(output);
        free(nome_driver);
        free(username);
        free(nome_user);
        flag = 1;
    }
    if(!flag) gere_output(output,path, p);
}


void query9(CatalogoStats *stats, char *data1, char *data2, char *path, Paginacao *p){
    Date *date1 = StringToDate(data1);
    Date *date2 = StringToDate(data2);
    Date *atual;
    int i=1, tamanho = getLengthQ9(stats), dist, id, index, flag = 0;
    double tip;
    char *city, *output=NULL;
    while(i<tamanho){
        index = tamanho - i;
        getVGInfoConditions(stats, &atual, index);
        if((comp_datas(date1, atual) > 0) || (comp_datas(date2, atual) == -1)){
            i++; 
            free_date(atual);
            continue;
        }
        getVGInfo(stats, &id, &dist, &city, &tip, index);
        i++;
        output = g_strdup_printf("%012d;%02d/%02d/%04d;%d;%s;%.3f\n",id, getDateDia(atual), getDateMes(atual), getDateAno(atual), dist, city, tip);
        gere_output(output,path, p);
        free(output);
        free_date(atual);
        free(city);
        flag = 1;
    }
    if(!flag) gere_output(output,path, p);
    free_date(date1);
    free_date(date2);
}


void query(CatalogoStats *stats, DriverCatalog *drivers, UserCatalog *users, char *id, int nquery, char *path, Paginacao *p){
    int i;
    int comp_list;
    char *data1, *data2, *city;
    if(isdigit(id[0]) != 0) i=1;
    else i=0;
    switch(nquery){
        case 1:
        query1(stats,users,drivers,id,path,i, p);
        break;

        case 2:
        comp_list = atoi(id);
        query2(stats,drivers, comp_list, path, p);
        break;

        case 3:
        comp_list = atoi(id);
        query3(stats,users,comp_list,path, p);
        break;

        case 4:
        query4(stats,id,path, p);
        break;

        case 5:
        data1 = strtok(id," ");
        data2 = strtok(NULL," ");
        query5(stats,data1,data2,path, p);
        break;

        case 6:
        city = strtok(id," ");
        data1 = strtok(NULL," ");
        data2 = strtok(NULL," ");
        query6(stats,data1,data2,city,path, p);
        break;

        case 7:
        char *N = strtok(id," ");
        comp_list = atoi(N);
        city = strtok(NULL," ");
        query7(stats,drivers,city,comp_list,path, p);
        break;

        case 8:
        char *gender = strtok(id, " ");
        int anos = atoi(strtok(NULL," "));
        query8(stats,gender,anos,path, p);
        break;

        case 9:
        data1 = strtok(id," ");
        data2 = strtok(NULL," ");
        query9(stats,data1,data2,path, p);
        break;

        default:
        printf("Nao existe\n");
    }
}