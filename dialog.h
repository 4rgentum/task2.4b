#ifndef DIALOG_H
#define DIALOG_H

#include "get.h"
#include "root.h"

int D_Insert(RBNode** root);
int D_Erase(RBNode** root);
int D_Inorder(RBNode** root);
int D_Search(RBNode **root);
int D_TaskSearch(RBNode **root);
int D_Print(RBNode** root);
int D_load(RBNode **root);
int D_Timing();
int dialog(const char* msgs[], int flag);

#endif
