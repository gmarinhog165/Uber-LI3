#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_csv.h"

char** parseLine(char* line);


void parseCSV(char *path, void(*buildFunc)(char**,void*), void *structure){
    FILE* fp = NULL;
    fp = fopen(path, "r");
    if (!fp) {
        perror("Error");
        return;
    }
    char* line = NULL;
    ssize_t read;
    size_t len=0;
    read = getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1){
        char* line_copy = strdup(line);
        char* command = strsep(&line_copy, "\n");
        char **tokens = parseLine(command);
        buildFunc(tokens, structure);
        free(command);
        free(tokens);
    }
    free(line);
    fclose(fp);
}


char** parseLine(char* line) {
    char** tokens = malloc(sizeof(char*) * 10);
    int i = 0;
    char* token = strtok(line, ";");
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, ";");
    }
    tokens[i] = NULL;

    return tokens;
}