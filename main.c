#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define INITCAP 8

char **read(FILE *fp, char **lines, int *lSize){
    int cap = INITCAP;
    *lSize = 0;
    lines=(char **)malloc(sizeof(char *)*cap);
    char *str=malloc(BUFSIZE);
    while(fgets(str,BUFSIZE,fp)!=NULL){
        char *eof=strchr(str,'D' - 'A' + 1);
        if(eof)
            *eof=0;
        if(*lSize==cap){
            cap*=2;
            lines=realloc(lines,sizeof(char *)*cap);
        }
        lines[(*lSize)++]=str;
        if(eof)
            return lines;
        str=malloc(BUFSIZE);
    }
    free(str);
    return lines;
}

void write(char **lines, int lSize){
    int len=0;
    for(int l=lSize-1;l>=0;l--){
        printf("%d ",l+1 );
        len = strlen(lines[l])-1;
        lines[l][len-1]='\0';
        for(int i=len-1;i>=0;i--)
            printf("%c",lines[l][i]);
        printf("\n");
    }
}

char **reverse(FILE *fp, char **lines){
    int lSize;
    lines=read(fp,lines,&lSize);
    write(lines,lSize);
    for (int i = 0; i < lSize; i++) {
        free(lines[i]);
    }
    return lines;
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
    lines=reverse(filep, lines);
    fclose(filep);
    free(lines);
    return 0;
}