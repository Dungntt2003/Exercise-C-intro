#include<stdio.h>
#include<string.h>
int main(){
    FILE *p;
    char word[30];
    int count;
    p=fopen("demo.txt","r");
    if (p==NULL)
    {
        return 1;
    }
    char str[100];
    fgets(str,100,p);
    sscanf(str,"%d %s",&count,word);
    if (strcmp(word,"")==0)
    scanf("%s",word);
    printf("%d-------%s\n",count,word);
    
    fclose(p);
    return 0;
}