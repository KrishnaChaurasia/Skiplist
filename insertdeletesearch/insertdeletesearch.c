#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct skipList{
  int key, height;
  char *value;
  struct skipList **forward;
}skipList;

int MAXHEIGHT = 16;

skipList **update;
skipList *mySkipList;

int totalNodes;

int search(skipList *mySkipList, int searchKey){
  int i;
  skipList *x = mySkipList;
  for(i=MAXHEIGHT-1; i>=0; i--){
  	while((x->forward[i] != NULL) && (x->forward[i]->key < searchKey)){
      x = x->forward[i];
    }
    update[i] = x;
  }
  if(x->forward[0] != NULL){
    x = x->forward[0];
  }
  if(x->key == searchKey){
  	printf("Value found at the location is %s\n", x->value);
    return 1;
  }
  return 0;
}

void inserth(skipList* mySkipList, int key, char* newValue, int height){
  int i;
  skipList *x, *newNode;
  
  x = (skipList*)calloc(1,sizeof(skipList));
  x = mySkipList;
  for(i=MAXHEIGHT-1; i>=0; i--){
    while((x->forward[i] != NULL) && (x->forward[i]->key < key)){
      x = x->forward[i];
    }
    update[i] = x;
  }
  if(x->forward[0] != NULL){
    x = x->forward[0];
  }
  if(x->key == key){
    printf("Key already present. Value is updated\n");
    strcpy(x->value,newValue);
  }
  else{
    totalNodes++;
    newNode = (skipList*)calloc(1,sizeof(skipList));
    newNode->forward = (skipList**)calloc(1,sizeof(skipList*));
    for(i=0;i<height;i++){
      newNode->forward[i] = (skipList*)calloc(1,sizeof(skipList));
      newNode->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = newNode;
    }
    newNode->key = key;
    newNode->value = (char*)calloc(100, sizeof(char));
    strcpy(newNode->value,newValue);
    newNode->height = height;
  }
  return;
}

int delete(skipList *mySkipList, int searchKey){
  int i, ht;
  skipList *x = mySkipList;
  for(i=MAXHEIGHT-1; i>=0; i--){
    while((x->forward[i] != NULL) && x->forward[i]->key < searchKey){
      x = x->forward[i];      
    }
    update[i] = x;
  }
  if(x->forward[0] != NULL){
    x = x->forward[0];
  }
  ht = x->height;
  if(x->key == searchKey){
    for(i=0;i<ht;i++){
      update[i]->forward[i] = x->forward[i];
      x->forward[i] = NULL;
    }
    return 1;
  }
  return 0;
}

void display(){
  FILE *graph;
  skipList *temp;
  int i=0,j=0,k=0;
 
   temp = mySkipList;
  
  //create a output file to contain .dot file
  graph = fopen("myGraph.dot","w");
  fprintf(graph,"%s","digraph skiplist { \n rankdir = LR; \n node [shape=record, style = filled];\n");
  fprintf(graph,"\n");
  fprintf(graph,"node%d [label=\"",0);
  for(j=MAXHEIGHT-1; j>= 0 ; j--){ 
    fprintf(graph,"<l%d> level%d | ",j,j);
  }
  fprintf(graph,"%d\",fillcolor = \"deepskyblue\"];\n",temp->key);
  fprintf(graph,"\n");

 for(i=0;i<totalNodes;i++){
    temp = temp->forward[0];
    //traverse each node at lower level and make declarations for node object in outGraph.dot file
    fprintf(graph,"node%d [label=\"",temp->key);  //ex: node1,node2....
    //fprintf(graph,"\n");
    for(j=temp->height-1;j>=0;j--){ 
      fprintf(graph,"<l%d> level%d | ",j,j);
    }
    //append the key field of node
    fprintf(graph,"%d\",fillcolor = \"deepskyblue\"];\n",temp->key);
    fprintf(graph,"\n");
  }
  
  //create a null node
  fprintf(graph,"node%d [label=\"",999);
  fprintf(graph,"<l%d> NULL\", fillcolor = \"deepskyblue\"];\n",0);
  
  fprintf(graph,"\n\n\n");
  
  //create the edges
  temp = mySkipList;
  for(i=0;i<=totalNodes;i++){
    j=0;
    while(temp->forward[j]!=NULL){
      fprintf(graph,"node%d:l%d -> node%d:l%d;\n",temp->key,j,temp->forward[j]->key,j);
      j++;
      if(j==temp->height)
      	break;
    }
    if(temp->forward[0]!=NULL)
      temp = temp->forward[0];
  }
  
  temp = mySkipList;
  for(i=0;i<=totalNodes;i++){
    j=0;
    while(temp->forward[j]!=NULL){
      j++;
      if(j==16)
		break;
    }
    for(k=j;k<temp->height;k++)
    fprintf(graph,"node%d:l%d -> node%d:l%d;\n",temp->key,k,999,0);
    
    if(temp->forward[0]!=NULL)
      temp = temp->forward[0];
  }
  
  fprintf(graph,"}");
  fclose(graph);

}

int main(){
  //dot -Tps myGraph.dot -o graph1.ps
  
  int i=0, key=0, height=0;
  FILE *fp;
  char *read, *token, *value;
  int n = 100, flag=0, bytes;
  char option;
  
  srand(time(NULL));
  update = (skipList**)calloc(1,sizeof(skipList*));
  for(i=0;i<16;i++){
    update[i] = (skipList*)calloc(1,sizeof(skipList));
    update[i] = NULL;
  }
  
  mySkipList = (skipList*)calloc(1,sizeof(skipList));
  mySkipList->forward = (skipList**)calloc(1,sizeof(skipList*));
  for(i=0;i<16;i++){
    mySkipList->forward[i] = (skipList*)calloc(1,sizeof(skipList));
    mySkipList->forward[i] = NULL;
  }
  
  mySkipList->value = (char*)calloc(6, sizeof(char));
  mySkipList->key = 0;
  strcpy(mySkipList->value,"Empty");
  mySkipList->height = 16;

  display();
  totalNodes = 0;
  printf("\n\n1. Insert a node in the SkipList\n2. Delete a node from the SkipList\n3. Search for a node in the SkipList\n4. Exit\n");
  value = (char*)calloc(100, sizeof(char));
  while(1){
    scanf("%c", &option);
    switch(option){
    case '1':
      printf("Enter key, value and height\n");
      scanf("%d %s %d", &key, value, &height);
      inserth(mySkipList, key, value, height);
      //update totalNodes only if new node is added
      display();
      break;
    case '2':
      if(totalNodes == 0){
	printf("No node to be deleted\n");
	break;
      }
      
      printf("Enter key to delete a node from the SkipList\n");
      scanf("%d", &key);
      if(delete(mySkipList, key)){
	printf("Key deleted successfully\n");
	//update totalNodes only if the node is found and deleted
	totalNodes--;
      }
      else
	printf("Key not found\n");
      printf("%d\n", totalNodes);
      display();
      break;
    case '3':
      printf("Enter a key to search for a node in the SkipList\n");
      scanf("%d", &key);
      if(search(mySkipList, key))
	printf("Key found!\n");
      else 
	printf("Key not found in the SkipList\n");
      break;
    case '\n':
      continue;
    case '4': return 0;
    default:
      printf("Invalid input. Please try again\n");
      break;
    }
    printf("\n\n1. Insert a node in the SkipList\n2. Delete a node from the SkipList\n3. Search for a node in the SkipList\n4. Exit\n");
  }
  return 0;
}
