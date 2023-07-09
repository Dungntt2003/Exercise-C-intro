#include<stdio.h>
#include<string.h>

typedef struct {
    char str[100];
} data;

void* fix(char* word){
    int i;
    while (word[i]!='\0'){
        if (word[i]=='\n')
        {
            word[i]='\0';
            break;
        }
        i++;
    }
}


int main(){
    data a[100];
    int i=0,n=0;
    data b[100];
    FILE *p;
    p=fopen("data.txt","r");
    if (p==NULL){
        printf("Can not open the file\n");
        return 1;
    }
    char c;
    char word[100];
    char meaning[100];
    while (!feof(p)){
        fscanf(p,"%s",a[i].str);
        c=fgetc(p);
        fgets(b[i].str,100,p);
        fix(b[i].str);
        i++;
        n++;
    }
    printf("English\n");
    for (int j=0;j<n;j++)
    {
        printf("%s\t",a[j].str);
    }
    printf("\nMeaning\n");
    for (int j=0;j<n;j++){
        printf("%s",b[j].str);
    }
    fclose(p);
    return 0;
}