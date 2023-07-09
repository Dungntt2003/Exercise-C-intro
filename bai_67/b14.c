#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char word[20];
    char meaning[20];
} data;



void fix(char *word){
    while (word!=NULL && word[strlen(word)-1]=='\n')
    word[strlen(word)-1]='\0';
}

int main(){
    data a[100];
    FILE *p,*s;
    int n=0;
    char str[100];
    int i=0;
    char filename[30],name[30];
    printf("Nhap file doc : ");
    fflush(stdin);
    scanf("%s", filename);
    printf("Nhap file ghi : ");
    fflush(stdin);
    scanf("%s", name);
    p=fopen(filename,"r");
    s=fopen(name,"w");
    if (p==NULL|| s==NULL ){
        printf("Can not open\n");
        return 0;
    }
    char c;
    while (!feof(p)){
        // đọc từ tiếng anh trước 
        fscanf(p,"%s",a[i].word);
        // đọc khoảng trắng giữa từ tiếng anh và từ tiếng việt
        c=fgetc(p);
        // đọc cả dòng còn lại chứa từ tiếng việt và dấu xuống dòng
        fgets(a[i].meaning,100,p);
        // vì chứa dấu xuống dòng nên hàm này để loại bỏ dấu xuống dòng
        fix(a[i].meaning);
        i++;
        n++;
    }
    // viết ra file nhé
    for (int j=0;j<n;j++){
        fprintf(s,"%s\t%s\n",a[j].word,a[j].meaning);
    }
    fclose(p);
    fclose(s);
    return 0;
}