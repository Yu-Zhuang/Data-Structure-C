#include<stdio.h>
#include<stdlib.h>
//========== DEFINE ==========
typedef struct tree{
   int val;
   struct tree *left, *right;
}NODE;
//========== FUNCTION ANNOUNCEMENT ==========
NODE* AVL_INSERT(NODE *root, int element); //insert element to avl-tree
NODE* AVL_NODE(int element); //create node

int AVL_BF(NODE *root); //calculate BF value
int AVL_HEIGHT(NODE* root);

NODE* AVL_L_ROTATE(NODE *root); // rotate
NODE* AVL_R_ROTATE(NODE *root);
NODE* AVL_LR_ROTATE(NODE *root);
NODE* AVL_RL_ROTATE(NODE *root);

void AVL_PRINT(NODE *root); //preorder print
//========== MAIN ===========
int main(void){
   NODE *root=NULL;
   // insert element
   for(int i=1;i<15;i++) root = AVL_INSERT(root, i);
   // print avl-tree (preorder)
   AVL_PRINT(root); 
   //END
   return 0;
}
//========== FUNCTION ==========
// insert element to avl-tree
NODE* AVL_INSERT(NODE* root, int element){
   if(root == NULL) root = AVL_NODE(element);
   else if(element < root->val) root->left = AVL_INSERT(root->left, element);
   else if(element > root->val) root->right = AVL_INSERT(root->right, element);
   else { printf("\n( element is exist! )\n"); return root; }

   if(AVL_BF(root)>1 && element < root->left->val)
      return AVL_R_ROTATE(root);
   if(AVL_BF(root)<-1 && element > root->right->val)
      return AVL_L_ROTATE(root);
   if(AVL_BF(root)>1 && element > root->left->val)
      return AVL_LR_ROTATE(root);
   if(AVL_BF(root)<-1 && element < root->right->val)
      return AVL_RL_ROTATE(root);

   return root;
}
// calculate BF value
int AVL_BF(NODE* root){
   int left_H = AVL_HEIGHT(root->left);
   int right_H = AVL_HEIGHT(root->right);
   return (left_H - right_H);
}
int AVL_HEIGHT(NODE* root){
   if(root == NULL) return 0;
   else{
      int lh = AVL_HEIGHT(root->left);
      int rh = AVL_HEIGHT(root->right);
      return (lh > rh) ? (lh + 1) : (rh + 1);
   }
}
// rotate
NODE* AVL_L_ROTATE(NODE *root){
   NODE* aux = root->right;
   root->right = aux->left;
   aux->left = root;
   return aux;
}
NODE* AVL_R_ROTATE(NODE *root){
   NODE* aux = root->left;
   root->left = aux->right;
   aux->right = root;
   return aux;
}
NODE* AVL_LR_ROTATE(NODE *root){
   root->left = AVL_L_ROTATE(root->left);
   return AVL_R_ROTATE(root);
}
NODE* AVL_RL_ROTATE(NODE *root){
   root->right = AVL_R_ROTATE(root->right);
   return AVL_L_ROTATE(root);
}
// preorder print
void AVL_PRINT(NODE *root){
   if(root!=NULL){
      printf("[%d]->", root->val);
      AVL_PRINT(root->left);
      AVL_PRINT(root->right);
   }
}
// create newnode
NODE* AVL_NODE(int element){
   NODE *newnode = (NODE*)malloc(sizeof(NODE));
   newnode->val = element; newnode->left=NULL; newnode->right=NULL;
   return newnode;
}

