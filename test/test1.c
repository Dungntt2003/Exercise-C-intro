#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int count;
    char word[30];
} data; // specify a type for the data
typedef struct node_s {
  data key;
  struct node_s *left;
  struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(int num, tree_t Root) {
  if (Root == NULL)
    return NULL;           // not found
  else if (Root->key.count == num) /* found x */
    return Root;
  else if (Root->key.count < num)
    // continue searching in the right sub tree
    return Search(num, Root->right);
  else {
    // continue searching in the left sub tree
    return Search( num, Root->left);
  }
}

void Insertnode_t(int x,char word[], tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    (*pRoot)->key.count = x;
    strcpy((*pRoot)->key.word,word);
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (x < (*pRoot)->key.count)
    Insertnode_t(x,word, &((*pRoot)->left));
  else if (x > (*pRoot)->key.count)
    Insertnode_t(x,word, &((*pRoot)->right));
}

data DeleteMin(tree_t *Root) {
  data k;
  if ((*Root)->left == NULL) {
    k = (*Root)->key;
    (*Root) = (*Root)->right;
    return k;
  } else
    return DeleteMin(&(*Root)->left);
}

void Deletenode_t(int x, tree_t *Root) {
  if (*Root != NULL)
    if (x < (*Root)->key.count)
      Deletenode_t(x, &(*Root)->left);
    else if (x > (*Root)->key.count)
      Deletenode_t(x, &(*Root)->right);
    else if (((*Root)->left == NULL) && ((*Root)->right == NULL))
      *Root = NULL;
    else if ((*Root)->left == NULL)
      *Root = (*Root)->right;
    else if ((*Root)->right == NULL)
      *Root = (*Root)->left;
    else
      (*Root)->key = DeleteMin(&(*Root)->right);
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}


void print(tree_t tree){
  if (tree!=NULL){
    print(tree->left);
    printf("%d\t%s\n",tree->key.count,tree->key.word);
    print(tree->right);
  }
}


void print2(tree_t tree){
  if (tree!=NULL){
    print2(tree->right);
    printf("%d\t%s\n",tree->key.count,tree->key.word);
    print2(tree->left);
  }
}

int main(){
    char word[30];
    int count;
    int key;
    FILE *p;
    data b[100];
    int i=0,n=0;
    FILE *f;
    char str[100];
    tree_t tree=NULL;
    tree_t s=NULL;
    while (1){
        printf("Menu\n");
        printf("1.Doc file A\n");
        printf("2.Doc file B\n");
        printf("3.Tim kiem\n");
        printf("4.Tong hop\n");
        printf("5.Thong ke\n");
        printf("6.Thoat\n");
        printf("Chon : ");
        scanf("%d",&key);
        switch (key){
            case 1 :
                p=fopen("a.txt","r");
                if (p==NULL){
                  printf("Can not open\n");
                  return 1;
                }
                while (!feof(p)){
                  fgets(str,100,p);
                  sscanf(str,"%d %s",&count,word);
                  if (strcmp(word,"")==0){
                    printf("Hay nhap tu them : ");
                    scanf("%s",word);
                  }
               Insertnode_t(count,word,&tree);
                }
               print(tree);
               fclose(p);
               break;
              case 2:
                f=fopen("b.txt","r");
                if (f==NULL){
                  printf("Error\n");
                  return 1;
                }
                while (!feof(f)){
                  fgets(str,100,f);
                  sscanf(str,"%d %s",&b[i].count,b[i].word);
                  if (strcmp(b[i].word,"")==0){
                    printf("Hay nhap tu them : ");
                    scanf("%s",b[i].word);
                  }
                  i++;
                  n++;
                }
                for (int j=0; j<n; j++){
                  printf("%d %s\n",b[j].count,b[j].word);
                }
                fclose(f);
                break;
            case 3:
              for (int j=0;j<n;j++){
                s=Search(b[j].count,tree);
                if (s!=NULL){
                  Deletenode_t(b[j].count,&tree);
                }
              }
              print(tree);
              break;
            case 4:
              for (int j=0;j<n;j++){
                Insertnode_t(b[j].count,b[j].word,&tree);
              }
              print2(tree);
              break;
            case 5:
              print(tree);
              break;
            case 6:
              return 1;
        }
    }
    return 0;
}