#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
  char str[100];
} data;


// Hàm có sẵn trong code thầy
typedef struct {
 	char word[30];
	char meaning[25];
} key_t;
typedef struct node_s {
  key_t key;
  struct node_s *left;
  struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char word[], tree_t Root) {
  if (Root == NULL)
    return NULL;           // not found
  else if (strcmp(Root->key.word,word)==0) /* found x */
    return Root;
  else if (strcmp(Root->key.word,word)<0)
    // continue searching in the right sub tree
    return Search(word, Root->right);
  else {
    // continue searching in the left sub tree
    return Search(word, Root->left);
  }
}

void Insertnode_t(char word[],char meaning[], tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    strcpy((*pRoot)->key.word,word);
    strcpy((*pRoot)->key.meaning,meaning);
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(word,(*pRoot)->key.word)<0)
    Insertnode_t(word,meaning, &((*pRoot)->left));
  else if (strcmp(word,(*pRoot)->key.word)>0)
    Insertnode_t(word,meaning, &((*pRoot)->right));
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}

// Bắt đầu từ đây là hàm tự viết
void inorderprint(tree_t tree){
    if (tree!=NULL){
        inorderprint(tree->left);
        printf("%s\t%s\n",tree->key.word,tree->key.meaning);
        inorderprint(tree->right);
    }
}

char* lowercase(char* str){
  for (int i=0; i<strlen(str); i++){
    if (str[i] >='A' && str[i] <= 'Z'){
      str[i] = str[i] + 'a' - 'A';
    }
  }
  return str;
}

int main(){
    int key;
    tree_t tree=NULL;
    tree_t s=NULL;
    FILE *p;
    FILE *f;
    char str[100];
    data a[100];
    int i=0,n=0;
    char word[30];
    char c;
    char meaning[25];
    while (1){
        printf("Menu\n");
        printf("1.Nap tu dien\n");
        printf("2.Noi dung tu dien\n");
        printf("3.Them / sua tu\n");
        printf("4.Dich Anh - Viet\n");
        printf("5.Thoat\n");
        printf("Chon : ");
        scanf("%d",&key);
        switch (key){
            case 1 :
                p=fopen("dict.txt","r");
                if (p==NULL){
                    printf("Can not open file\n");
                    return 1;
                }
                while (!feof(p)){
                    fgets(str,100,p);
                    printf("%s",str);
                    sscanf(str,"%s %s",word,meaning);
                    Insertnode_t(word,meaning, &tree);
                }
                printf("\n");
                fclose(p);
                break;
            case 2:
                inorderprint(tree);
                break;
            case 3:
                printf("Hay nhap 1 tu tieng anh : ");
                scanf("%s",word);
                s=Search(word,tree);
                if (s==NULL){
                    printf("Hay nhap tu giai nghia : ");
                    scanf("%s",meaning);
                    Insertnode_t(word,meaning,&tree);
                }
                else {
                    printf("Ban co muon cap nhap noi dung khong : ");
                    fflush(stdin);
                    scanf("%c",&c);
                    if (c=='y'){
                        printf("Hay nhap tu giai nghia moi : ");
                        fflush(stdin);
                        scanf("%s",meaning);
                        strcpy(s->key.meaning,meaning);
                    }
                }
                break;
            case 4:
              printf("Hay nhap 1 cau : ");
              fflush(stdin);
              fgets(str,100,stdin);
              p=fopen("demo.txt","w+");
              fprintf(p,"%s",lowercase(str));
              fseek(p,0,SEEK_SET);
              while (!feof(p)){
                fscanf(p,"%s",a[i].str);
                i++;
                n++;
              }
              for (int j=0;j<n-1;j++)
              printf("%s\n",a[j].str);
              for (int i=0;i<n-1;i++){
                s=Search(a[i].str,tree);
                if (s==NULL)
                printf("thieu tu ");
                else printf("%s ",s->key.meaning);
              }
              printf("\n");
              fclose(p);
              break;
            case 5:
                return 1;
        }
    }
    return 0;
}