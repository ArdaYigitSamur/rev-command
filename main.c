#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define INITCAP 8

char **read(FILE *fp, char **lines, int *lSize){
    int cap = INITCAP;
    *lSize = 0;
    lines=(char **)malloc(sizeof(char *)*cap);
    lines[*lSize]=malloc(BUFSIZE);
    while(fgets(lines[*lSize],BUFSIZE,fp)!=NULL){
        if(*lSize==cap){
            cap*=2;
            lines=realloc(lines,sizeof(char *)*cap);
        }
        (*lSize)++;
        lines[*lSize]=malloc(BUFSIZE);
    }
    free(lines[*lSize]);
    return lines;
}

void write(char **lines, int *lSize){
    int len=0;
    for(int l=0;l<(*lSize);l++){
        len = strlen(lines[l])-1;
        for(int i=len-1;i>=0;i--)
            printf("%c",lines[l][i]);
        printf("\n");
    }
}

void reverse(FILE *fp, char **lines){
    int lSize;
    lines=read(fp,lines,&lSize);
    write(lines,&lSize);
}

int main(int argc, char *argv[])
{
    FILE *filep=NULL;
    if(argc > 1)
        filep=fopen(argv[1],"r");

    if(filep==NULL){
        printf("ERROR WHILE READING FILE!!!\n");
        return 1;
    }
    char **lines = NULL;
    reverse(filep, lines);
    fclose(filep);
    free(lines);
    return 0;
}