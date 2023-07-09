#include <string.h>
#include <stdio.h>
 

 typedef struct {
    char word[30];
    char meaning[30];
 } data;


void fix(char *word){
    while ( word !=NULL && word[strlen(word)-1] =='\n')
    word[strlen(word)-1] = '\0';
}

 int main(){
    data a[100];
    int n=0,i=0;
    FILE *f;
    char str[200];
    f=fopen("data.txt","r");
    if (f==NULL)
    {
        printf("Can not open file\n");
        return 1;
    }
    while (!feof(f)){
        fscanf(f,"%s",a[i].word);
        char c= fgetc(f);
        fgets(a[i].meaning,30,f);
        fix(a[i].meaning);
        i++;
        n++;
    }
    for (int j=0;j<n;j++){
        printf("%s\t",a[j].word);
    }
    printf("\n\n");
    for (int j=0;j<n;j++){
        printf("%s\t",a[j].meaning);
    }
    fclose(f);
    return 0;
 }