#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void fix(char *name){
    if ( name[strlen(name)-1] = '\n')
    name[strlen(name)-1] = '\0';
}

int main(){
    FILE *p;
    int count=0;
    p=fopen("file.txt","r");
    if (p==NULL){
        printf("File not found\n");
        return 0;
    }
    char str[100];
    char word[30];
    printf("Hay nhap tu muon tim : ");
    scanf("%s",word);
    while (!feof(p)){
        fgets(str,100,p);
        fix(str);
        if (strstr(str,word)!=NULL){
            printf("%s\t",str);
            count++;
        }
    }
    if (count==0){
        printf("Khong co xau nao thoa man\n");
    }
    fclose(p);
    return 0;
}