#include<stdio.h>
#include<string.h>


// Advanced
void fix(char* word){
    word[strlen(word)]='\0';
}



int main(){
    char str[100];
    char tem[100];
    char word[100];
    FILE *p;
    p=fopen("data.txt","r");
    if (p==NULL)
    {
        printf("Can not open file\n");
        return 1;
    }
    printf("Hay nhap vao 1 chuoi can so sanh : ");
    scanf("%s",str);
    while (!feof(p)){
        fgets(tem,100,p);
        fix(tem);
        if (strstr(tem,str)!=NULL)
        {
            printf("%s",tem);
        }
    }
    fclose(p);
    return 0;
}