#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
 	char word[30];
	int count;
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

void Insertnode_t(char word[], tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    strcpy((*pRoot)->key.word,word);
    (*pRoot)->key.count=1;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(word,(*pRoot)->key.word)<0)
    Insertnode_t(word, &((*pRoot)->left));
  else if (strcmp(word,(*pRoot)->key.word)>0)
    Insertnode_t(word, &((*pRoot)->right));
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}

void inorderprint(tree_t tree){
  if (tree!=NULL){
    inorderprint(tree->left);
    printf("%s %d\n",tree->key.word,tree->key.count);
    inorderprint(tree->right);
  }
}


int main(int argv, char* argc[]){
  int key;
  FILE *p;
  tree_t t=NULL;
  tree_t tree=NULL;
  char word[20];
  char filename[30];
    while (1){
      printf("Menu\n");
      printf("1.Get information from file\n");
      printf("2.Search and print the times this word appears\n");
      printf("3.Print a table contain all words of tree\n");
      printf("4.Exit\n");
      printf("Choose 1-4 : ");
      scanf("%d",&key);
      switch (key){
        case 1:
        if (argv!=2){
          printf("Not enough\n");
        }
        strcpy(filename,argc[1]);
        p=fopen(filename,"r");
        if (p==NULL)
        {
          printf("Can not open file\n");
          return 1;
        }
        while (!feof(p)){
          fscanf(p,"%s ",word);
          printf("%s ",word);
          t=Search(word,tree);
          if (t==NULL)
          {
            Insertnode_t(word,&tree);
          }
          else {
            t->key.count++;
          }
        }
        fclose(p);
        break;
      case 2:
        printf("Hay nhap vao 1 tu de tim : ");
        scanf("%s",word);
        t=Search(word,tree);
        if (t==NULL)
        {
          printf("Can not find this word\n");
          return 1;
        }
        else {
          printf("The times : %d\n",t->key.count);
        }
        break;
      case 3:
        inorderprint(tree);
        break;
      case 4:
        return 1;
      }
    }
    freetree(tree);
    return 0;
}