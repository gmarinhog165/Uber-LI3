#include <stdio.h>
#include <glib.h>
#include <time.h>

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
#include "conector.h"




int main(int argc, char *argv[]){
    clock_t begin = clock();
    start(argc, argv);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n%f\n",time_spent);
    return 0;
}
