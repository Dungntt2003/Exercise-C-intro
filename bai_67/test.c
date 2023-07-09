#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/// Đề bài này là tên file được lấy trên câu lệnh. argv[0] chính là ./test còn ảgv[1] chính là tên file

int main(int argc, char *argv[]){
    FILE *p;
    char filename[1024];
    if (argc < 2)
    {
        printf("Error\n");
        return 0;
    }
    strcpy(filename, argv[1]);
    p = fopen(filename, "r");
    while (!feof(p)){
        char c = fgetc(p);
        printf("%c", c);
    }
    fclose(p);
    return 0;
}