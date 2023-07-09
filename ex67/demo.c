#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Loi\n");
        return 1;
    }
    char filename[30];
    strcpy(filename,argv[1]);
    FILE *p;
    p=fopen(filename,"r");
    while (!feof(p)){
        char c = fgetc(p);
        printf("%c",c);

    }
    fclose(p);
    return 0;
}