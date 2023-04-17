#include <stdio.h>
#include <glib.h>
#include <math.h>

#include "output.h"

typedef struct paginacao {
    GPtrArray *dados;
    int liminf;
    int limsup;
    int pagina_atual;
}Paginacao;

Paginacao *paginacao_create(){
    Paginacao *t = malloc(sizeof(struct paginacao));
    t->dados = g_ptr_array_new_with_free_func(g_free);
    t->pagina_atual = -1;
    t->liminf = 0;
    t->limsup = 20;
    return t;
}

void free_paginacao(Paginacao *dados){
    g_ptr_array_free(dados->dados, TRUE);
    free(dados);
}


void free_paginacao_wrapper(void *dados){
    return free_paginacao(dados);
}

void preenche_interativo(Paginacao *dados, char *string){
    if(string){
        char *string2 = strdup(string);
        g_ptr_array_add(dados->dados, string2);
    }
    else {
        char frase[50] = "Não foram encontrados valores.\n";
        char *frase2 = g_strdup_printf("%s", frase);
        g_ptr_array_add(dados->dados,frase2);
    }

}

void gere_output(char *string, char *path, Paginacao *dados){
    if(path){
        FILE *results = fopen(path,"a");
        if(string) fprintf(results,"%s", string);
        fclose(results);
    }
    else{
        preenche_interativo(dados,string);
    }
}

Paginacao* avanca_pag(Paginacao* p) {
    (p->pagina_atual)++;
    p->liminf = (p->pagina_atual)*20;
    p->limsup = ((p->pagina_atual)+1)*20;
    return p;
}

Paginacao* recua_pag(Paginacao* p) {
    if(p->pagina_atual > 0){
        (p->pagina_atual)--;
        p->liminf = (p->pagina_atual)*20;
        p->limsup = ((p->pagina_atual)+1)*20;
    }
    return p;
}

Paginacao* ultima_pag (Paginacao* p) {
    int tamanho = p->dados->len;
    p->liminf = tamanho - (tamanho % 20);
    if(p->liminf == tamanho) p->liminf = tamanho - 20;
    p->limsup = tamanho;
    p->pagina_atual = tamanho/20;
    return p;
}

Paginacao* primeira_pag (Paginacao* p) {
    (p->liminf) = 0; 
    p->limsup = 20;
    p->pagina_atual = 0;
    return p;
}

void imprime_paginacao (Paginacao* t) {
    int tamanho = t->dados->len;
    int liminf, limsup = t->limsup;
    int pagina = t->pagina_atual;
    printf("\n\nRESULTADOS------------------------- PÁGINA %d\n\n", pagina);
    for (liminf = t->liminf; (liminf < limsup) && (liminf < tamanho) ; liminf++) {
        char *output = t->dados->pdata[liminf];
        printf("%s",output);
    }
}


void interativo(Paginacao *t){
    imprime_paginacao(avanca_pag(t));
    int i = -1;
    while (i != 0) {
        printf("+---------------------------------+\n");
        printf("| 0 - Sair                        |\n");
        printf("| 1 - Avançar                     |\n");
        printf("| 2 - Recuar                      |\n");
        printf("| 3 - Regressar à primeira página |\n");
        printf("| 4 - Ir para a última página     |\n");
        printf("+---------------------------------+\n");
        scanf("%d", &i);
        while((i<0) || (i>4)){
            printf("\n Tente outra vez \n");
            scanf("%d", &i);
        }
        if (i == 1) {
            imprime_paginacao(avanca_pag(t));
        } 
        else if (i == 2) {
            imprime_paginacao(recua_pag(t));
        } 
        else if (i == 3) {
            imprime_paginacao(primeira_pag(t));
        } 
        else if (i == 4) {
            imprime_paginacao(ultima_pag(t));
        }
    }
}

void get_query_info(int *numero, char **valores){
    int c;
    printf ("Digite o número da query que pretende efetuar:\n");
    scanf ("%d", numero);
    printf ("Com que valores deseja efetuar a query?\n");
    while (( c = getchar()) != '\n' && c != EOF) {}
    scanf("%[^\n]s", *valores);
}

void path_interativo(char **user, char **driver, char **rides){
    printf("Bem-Vindo a LI3!                      \n");
        printf("Digite o nome do ficheiro dos users:  \n");
        scanf ("%s", *user);

        FILE *fp1;
        fp1 = fopen(*user, "r");
        while (fp1 == NULL) {
            printf("O ficheiro dos users introduzido: '%s' não existe.\n", *user);
            printf("Digite de novo o nome do ficheiro dos users: \n");
            scanf("%s", *user);
            fp1 = fopen(*user, "r");
        }
        fclose(fp1);

        printf ("Digite o nome do ficheiro dos drivers:\n");
        scanf ("%s", *driver);

        FILE *fp2;
        fp2 = fopen(*driver, "r");
        while (fp2 == NULL) {
            printf("O ficheiro dos drivers introduzido: '%s' não existe.\n", *driver);
            printf("Digite de novo o nome do ficheiro dos drivers: \n");
            scanf("%s", *driver);
            fp2 = fopen(*driver, "r");
        }
        fclose(fp2);

        printf ("Digite o nome do ficheiro das rides:  \n");
        scanf ("%s", *rides);

        FILE *fp3;
        fp3 = fopen(*rides, "r");
        while (fp3 == NULL) {
            printf("O ficheiro das rides introduzido: '%s' não existe.\n", *rides);
            printf("Digite de novo o nome do ficheiro das rides: \n");
            scanf("%s", *rides);
            fp3 = fopen(*rides, "r");
        }
        fclose(fp3);
        printf("\n Aguarde pelo load dos catálogos, por favor. \n");
}

void printf_mini_menu(int *k){
    printf("+---------------------------------+\n");
    printf("| 0 - Terminar Programa           |\n");
    printf("| 1 - Próxima Query               |\n");
    printf("+---------------------------------+\n");
    
    scanf("%d", k);
    while((*k != 0) && (*k != 1)){
        printf("\n Tente outra vez \n");
        scanf("%d", k);
    }
}


