#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024
#define INITCAP 8

char **read(FILE *fp, char **lines, int *lSize){
    int cap=INITCAP;
    *lSize=0;
    lines=(char **)malloc(sizeof(char *)*cap);
    lines[*lSize]=malloc(1024);
    while(fgets(lines[*lSize],BUFFSIZE,fp)!=NULL){
        if(*lSize==cap){
            cap*=2;
            lines=realloc(lines,sizeof(char *)*cap);
        }
        (*lSize)++;
        lines[*lSize]=malloc(1024);
    }
    free(lines[*lSize]);
    return lines;
}

void write(char **lines, int *lSize){
    int l=0;
    int cnt=*lSize;
    for (int i = (*lSize)-1; i >=0 ; i--)
    {
        printf("%d ",cnt );
        if(cnt==*lSize){
            l=strlen(lines[i]);
            lines[i][l]='\0';
            for(int a=l;a>1;a--)
                printf("%c",lines[i][a] );
        }
        cnt--;
        l=strlen(lines[i]);
        lines[i][l-1]='\0';
        l=strlen(lines[i])-2;
        for(int a=l;a>=0;a--){
            printf("%c",lines[i][a] );    
        }
        printf("\n");
    }
}

void reverse(FILE *fp){
    char **lines=NULL;
    int lSize;
    lines=read(fp,lines,&lSize);
    write(lines,&lSize);
}

int main(int argc, char *argv[])
{
    FILE* fp=NULL;
    if(argc>1)
        fp=fopen(argv[1],"r");

    if(fp==NULL){
        printf("ERROR READING FILE!!\n");
        return 1;
    }
    reverse(fp);
    fclose(fp);
}