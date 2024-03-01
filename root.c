#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "get.h"
#include "root.h"

Item* createItem(unsigned int info) {
  Item *new_item = (Item *) malloc(sizeof(Item));
  new_item->info = info;
  return new_item;
}

RBNode* createRBNode(unsigned int key, Item *elem) {
  RBNode *new_node = (RBNode *) malloc(sizeof(RBNode));
  new_node->key = key;
  new_node->elem = elem;
  new_node->left = ELIST;
  new_node->right = ELIST;
  new_node->parent = ELIST;
  new_node->color = 1;
  return new_node;
}

void rotateRight(RBNode **root, RBNode *parent) {
  RBNode *child = parent->left;
  RBNode *grand_parent = parent->parent;
  parent->left = child->right;
  if (child->right != ELIST) {
    child->right->parent = parent;
  }
  child->parent = grand_parent;
  if (grand_parent == ELIST) {
    *root = child;
  } else if (parent == grand_parent->right) {
    grand_parent->right = child;
  } else {
    grand_parent->left = child;
  }
  child->right = parent;
  parent->parent = child;
}

void rotateLeft(RBNode **root, RBNode *parent) {
  RBNode *child = parent->right;
  RBNode *grand_parent = parent->parent;
  parent->right = child->left;
  if (child->left != ELIST) {
    child->left->parent = parent;
  }
  child->parent = grand_parent;
  if (grand_parent == ELIST) {
    *root = child;
  } else if (parent == grand_parent->left) {
    grand_parent->left = child;
  } else {
    grand_parent->right = child;
  }
  child->left = parent;
  parent->parent = child;
}

void balanceInsert(RBNode **root, RBNode *node) {
  while (node != *root && node->parent->color == 1) {
    if (node->parent == node->parent->parent->left) {
      RBNode *sibling = node->parent->parent->right;
      if (sibling != ELIST && sibling->color == 1) {
        node->parent->color = 0;
        sibling->color = 0;
        node->parent->parent->color = 1;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          if (node != ELIST) {
            rotateLeft(root, node);
          }
        }
        node->parent->color = 0;
        if (node->parent->parent != ELIST) {
          node->parent->parent->color = 1;
          rotateRight(root, node->parent->parent);
        }
      }
    } else {
      RBNode *sibling = node->parent->parent->left;
      if (sibling != ELIST && sibling->color == 1) {
        node->parent->color = 0;
        sibling->color = 0;
        node->parent->parent->color = 1;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          if (node != ELIST) {
            rotateRight(root, node);
          }
        }
        node->parent->color = 0;
        if (node->parent->parent != ELIST) {
          node->parent->parent->color = 1;
          rotateLeft(root, node->parent->parent);
        }
      }
    }
  }
  (*root)->color = 0;
}

void balanceDelete(RBNode **root, RBNode *node) {
  while (node != *root && node->color == 0) {
    if (node == node->parent->left) {
      RBNode *sibling = node->parent->right;
      if (sibling->color == 1) {
        sibling->color = 0;
        node->parent->color = 1;
        rotateLeft(root, node->parent);
        sibling = node->parent->right;
      }
      if (sibling->left->color == 0 && sibling->right->color == 0) {
        sibling->color = 1;
        node = node->parent;
      } else {
        if (sibling->right->color == 0) {
          sibling->left->color = 0;
          sibling->color = 1;
          rotateRight(root, sibling);
          sibling = node->parent->right;
        }
        sibling->color = node->parent->color;
        node->parent->color = 0;
        sibling->right->color = 0;
        rotateLeft(root, node->parent);
        node = *root;
      }
    } else {
      RBNode *sibling = node->parent->left;
      if (sibling->color == 1) {
        sibling->color = 0;
        node->parent->color = 1;
        rotateRight(root, node->parent);
        sibling = node->parent->left;
      }
      if (sibling->right->color == 0 && sibling->left->color == 0) {
        sibling->color = 1;
        node = node->parent;
      } else {
        if (sibling->left->color == 0) {
          sibling->right->color = 0;
          sibling->color = 1;
          rotateLeft(root, sibling);
          sibling = node->parent->left;
        }
        sibling->color = node->parent->color;
        node->parent->color = 0;
        sibling->left->color = 0;
        rotateRight(root, node->parent);
        node = *root;
      }
    }
  }
  node->color = 0;
}

RBNode *findNodeByKey(RBNode *root, unsigned int key) {
  if (root == ELIST || root->key == key) {
    return root;
  }
  if (key < root->key) {
    return findNodeByKey(root->left, key);
  } else {
    return findNodeByKey(root->right, key);
  }
}

int insert(RBNode **root, unsigned int key, Item *elem) {
  if (findNodeByKey(*root, key) != ELIST) {
    return 1;
  }
  RBNode *node = createRBNode(key, elem);
  RBNode *curr = *root;
  RBNode *parent = ELIST;
  while (curr != ELIST) {
    parent = curr;
    if (node->key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  node->parent = parent;
  if (parent == ELIST) {
    *root = node;
  } else if (node->key < parent->key) {
    parent->left = node;
  } else {
    parent->right = node;
  }
  balanceInsert(root, node);
  return 0;
}

void transplant(RBNode **root, RBNode *node1, RBNode *node2) {
  if (node1->parent == ELIST) {
    *root = node2;
  } else if (node1 == node1->parent->left) {
    node1->parent->left = node2;
  } else {
    node1->parent->right = node2;
  }
  node2->parent = node1->parent;
}

RBNode *minimumNode(RBNode *node) {
  while (node->left != ELIST) {
    node = node->left;
  }
  return node;
}

int deleteNode(RBNode **root, unsigned int key) {
  RBNode *node = findNodeByKey(*root, key);
  if (node == ELIST) {
    return 1; // Элемент с данным ключом не найден
  }
  RBNode *deletedNode = node;
  RBNode *replacedNode;
  int deletedNodeOriginalColor = deletedNode->color;
  if (node->left == ELIST) {
    replacedNode = node->right;
    transplant(root, node, node->right);
  } else if (node->right == ELIST) {
    replacedNode = node->left;
    transplant(root, node, node->left);
  } else {
    deletedNode = minimumNode(node->right);
    deletedNodeOriginalColor = deletedNode->color;
    replacedNode = deletedNode->right;
    if (deletedNode->parent == node) {
      replacedNode->parent = deletedNode;
    } else {
      transplant(root, deletedNode, deletedNode->right);
      deletedNode->right = node->right;
      deletedNode->right->parent = deletedNode;
    }
    transplant(root, node, deletedNode);
    deletedNode->left = node->left;
    deletedNode->left->parent = deletedNode;
    deletedNode->color = node->color;
  }
  free(node->elem);
  free(node);
  if (deletedNodeOriginalColor == 0) {
    balanceDelete(root, replacedNode);
  }
  return 0;
}

int clearTree(RBNode *root) {
  if (root != ELIST) {
    clearTree(root->left);
    clearTree(root->right);
    free(root->elem);
    free(root);
    root = ELIST;
    return 0;
  }
  return 1;
}

void inOrder(RBNode *root, unsigned int minKey, unsigned int maxKey) {
  if (root == ELIST) {
    return;
  }
  if (root->key >= minKey && root->key <= maxKey) {
    inOrder(root->left, minKey, maxKey);
    printf("Key: %u, Info: %u\n", root->key, root->elem->info);
    inOrder(root->right, minKey, maxKey);
  } else if (root->key < minKey) {
    inOrder(root->right, minKey, maxKey);
  } else if (root->key > maxKey) {
    inOrder(root->left, minKey, maxKey);
  }
}

RBNode* findMaxKeyNode(RBNode* root) {
  while (root != ELIST && root->right != ELIST) {
    root = root->right;
  }
  return root;
}

int load(char **name, RBNode **root) {
  FILE *file = fopen(*name, "r");
  if (file == NULL) {
    return 1;
  }
  unsigned int key = 0;
  unsigned int info = 0;
  int count = 0;
  while (fscanf(file, "%u\n%u\n", &key, &info) == 2) {
    Item *elem = createItem(info);
    insert(root, key, elem);
    count++;
    free(elem);
  }
  if (!count) {
    fclose(file);
    return 1;
  }
  fclose(file);
  return 0;
}

void printTree(RBNode* root, int space) {
  if (root == ELIST) {
    return;
  }
  int i;
  // Увеличение расстояния между уровнями
  space += 4;
  // Вывод правого поддерева
  printTree(root->right, space);
  // Вывод текущего узла
  printf("\n");
  for (i = 4; i < space; i++) {
    printf(" ");
  }
  printf("%u\n", root->key);
  // Вывод левого поддерева
  printTree(root->left, space);
}
