#ifndef ROOT_H
#define ROOT_H

typedef struct Item {
  unsigned int info;
} Item;

typedef struct RBNode {
    unsigned int key;
    Item* elem;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
    int color; // 1 - красный, 0 - черный
} RBNode;

extern RBNode elist;
#define ELIST &elist

Item* createItem(unsigned int info);
RBNode* createRBNode(unsigned int key, Item *elem);
void rotateRight(RBNode **root, RBNode *parent);
void rotateLeft(RBNode **root, RBNode *parent);
void balanceInsert(RBNode **root, RBNode *node);
void balanceDelete(RBNode **root, RBNode *node);
RBNode *findNodeByKey(RBNode *root, unsigned int key);
int insert(RBNode **root, unsigned int key, Item *elem);
void transplant(RBNode **root, RBNode *node1, RBNode *node2);
RBNode *minimumNode(RBNode *node);
int deleteNode(RBNode **root, unsigned int key);
int clearTree(RBNode *root);
void inOrder(RBNode *root, unsigned int minKey, unsigned int maxKey);
RBNode* findMaxKeyNode(RBNode* root);
int load(char **name, RBNode **root);
void printTree(RBNode* root, int space);

#endif
