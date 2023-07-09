#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
 	char word[30];
	char meaning[30];
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

void inorderprint(tree_t tree){
  if (tree!=NULL)
  {
    inorderprint(tree->left);
    printf("%s %s\n",tree->key.word,tree->key.meaning);
    inorderprint(tree->right);
  }
}

void fix(char* word){
  int i=0;
  while (word[i]!='\0'){
    if (word[i]=='\n')
    {
      word[i]='\0';
      break;
    }
    i++;
  }
}

void lowwercase( char* word){
  int i=0;
  while (word[i]!='\0'){
    if (word[i]>='A' && word[i]<='Z'){
      word[i]=word[i]+32;
      i++;
    }
  }
}

int main(){
  int key;
  tree_t tree=NULL;
  tree_t t=NULL;
  FILE *p;
  char c;
  char word[30];
  char meaning[30];
  char chuoi[100];
  while (1){
    printf("Menu\n");
    printf("1.Doc file\n");
    printf("2.In cay\n");
    printf("3.Dich Anh Viet\n");
    printf("4.Thoat\n");
    printf("chon 1-4 : ");
    scanf("%d",&key);
    switch (key){
      case 1:
        p=fopen("data.txt","r");
        if (p==NULL){
          printf("Can not open the file\n");
          return 1;
        }
        while (!feof(p)){
          fscanf(p,"%s",word);
          c=fgetc(p);
          fgets(meaning,30,p);
          fix(meaning);
          Insertnode_t(word,meaning,&tree);
        }
        fclose(p);
        break;
      case 2:
        inorderprint(tree);
        break;
      case 3:
        printf("Hay nhap vao 1 dong tieng anh : ");
        fflush(stdin);
        gets(chuoi);
        lowwercase(chuoi);
        p=fopen("demo.txt","w+");
        if (p==NULL){
          printf("Error occur when open file\n");
          return 1;
        }
        fprintf(p,"%s",chuoi);
        fseek(p,0,SEEK_SET);
        while (!feof(p)){
          fscanf(p,"%s ",chuoi);
          printf("%s\n",chuoi);
        }
        fclose(p);
        break;
    }
  }
  freetree(tree);
  return 0;
}

