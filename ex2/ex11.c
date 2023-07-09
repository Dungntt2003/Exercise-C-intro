#include<stdio.h>

int main(){
    FILE *f,*s;
    f=fopen("file.txt","r");
    s=fopen("file1.txt","w");
    if (f == NULL || s==NULL) {
        printf("Can not open file\n");
        return 1;
    }
    while (!feof(f)){
        char c =fgetc(f);
        fputc(c, s);
    }
    fclose(f);
    fclose(s);
    return 0;
}