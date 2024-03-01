#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "dialog.h"

int D_Insert(RBNode** root) {
  int rc;
  const char* errmsgs[] = {"Ok", "Duplicate"};
  printf("Input Key:\n");
  unsigned int key = get_unsigned_int();
  if (key == -1){
    printf("End Of File\n");
    return 0; 
  }
  printf("Input Info:\n");
  unsigned int info = get_unsigned_int();
  if (info == -1){
    printf("End Of File\n");
    return 0;
  }
  Item *elem = createItem(info);
  rc = insert(root, key, elem);
  printf("\n");
  printf("%s: %u\n", errmsgs[rc], key);
  return 1;
}

int D_Erase(RBNode** root) {
  int rc;
  printf("Input Key:\n");
  unsigned int key = get_unsigned_int();
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  if (key == -1){ 
    printf("End Of File\n");
    return 0; 
  }
  rc = deleteNode(root, key);
  printf("\n");
  printf("%s \n", errmsgs[rc]);;
  return 1;
}

int D_Inorder(RBNode** root) {
  int rc;
  const char* errmsgs[]={"Ok", "Table Is Empty"};
  if (root == NULL) {
    rc = 1;
  } else {
    printf("Input minKey:\n");
    unsigned int minkey = get_unsigned_int();
    if (minkey == -1) {
      printf("End Of File\n");
      return 0;
    }
    printf("Input maxKey:\n");
    unsigned int maxkey = get_unsigned_int();
    if (maxkey == -1) {
      printf("End Of File\n");
      return 0;
    }
    inOrder(*root, minkey, maxkey);
    rc = 0;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_Search(RBNode **root) {
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist"};
  printf("Input Key:\n");
  unsigned int key = get_unsigned_int();
  if (key == -1){
    printf("End Of File\n");
    return 0; 
  }
  int rc;
  RBNode* node = findNodeByKey(*root, key);
  if (node == NULL) {
    rc = 1;
  } else {
    rc = 0;
    printf("Key: %u, Info: %u\n", node->key, node->elem->info);
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_TaskSearch(RBNode **root) {
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist"};
  int rc;
  RBNode* node = findMaxKeyNode(*root);
  if (node == NULL) {
    rc = 1;
  } else {
    rc = 0;
    printf("Key: %u, Info: %u\n", node->key, node->elem->info);
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_Print(RBNode** root) {
  int rc;
  const char* errmsgs[]={"Ok", "Table Is Empty"};
  if (root == NULL) {
    rc = 1;
  } else {
    printTree(*root, 0);
    rc = 0;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_load(RBNode **root) {
  const char* errmsgs[]={"Table Is Loaded", "File Can't Be Open"}; 
  printf("Input File Name:\n");
  char *name = readline();
  if (!name) {
    printf("End");
    return 1;
  }
  int rc = load(&name, root);
  printf("\n");
  printf("%s %s\n", errmsgs[rc], name);
  free(name);
  return 1;
}

int D_Timing() {
  RBNode* root = ELIST;
  int n = 10, cnt = 1000000, i, m;
  unsigned int key[10000];
  clock_t first, last;
  srand(time(NULL));
  while (n-- > 0) {
    for (i = 0; i < 10000; ++i) {
      key[i] = rand() * rand();
    }
    for (i = 0; i < cnt; ) {
      int k = rand() * rand();
      if (insert(&root, k, createItem(0)) == 0) {
        ++i;
      }
    }
    m = 0;
    first = clock();
    for (i = 0; i < 10000; ++i) {
      if (findNodeByKey(root, key[i]) != NULL) {
        ++m;
      }
    }
    last = clock();
    printf("%d items were found\n", m);
    printf("test #%d, number of nodes = %d, time = %ld\n", 10 - n, (10 - n) * cnt, last - first);
  }
  clearTree(root);
  return 1;
}

int dialog(const char* msgs[], int flag) {
  char* errmsg = "";
  int rc;
  do {
    puts(errmsg);
    errmsg = "Invalid Input, Repeat\n";
    for (int i = 0; i < flag; i++) {
      puts(msgs[i]);
    }
    puts("Enter:\n");
    rc = get_int();
    printf("\n");
    
  } while (rc < 0 || rc >= flag);
  return rc;
}
