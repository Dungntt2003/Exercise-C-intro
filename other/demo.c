#include<stdio.h>
#include<string.h>


void upper(char* word){
    for (int i=0;i<strlen(word);i++)
    {
        word[i]=word[i]-32;
    }
}


int main(){
    char word[30];
    scanf("%s",word);
    printf("%s\n",word);
    upper(word);
    printf("%s\n",word);
    return 0;
}