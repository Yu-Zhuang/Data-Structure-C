# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define AND &&
# define OR ||
# define IS ==
# define IS_NOT !=
# define MAX 100

typedef struct tree{
	char val;
	struct tree *left, *right;
}NODE;
typedef struct s{
	NODE **val;
	struct s *next;
}STACK;

void PUSH(STACK *head, NODE **element){
	STACK *newnode = (STACK*)malloc(sizeof(STACK));
	newnode->val = element;
	newnode->next = head->next;
	head->next = newnode;
}

NODE** POP(STACK *head){
	NODE **ret = head->next->val;
	head->next = head->next->next;
	return ret;
}

NODE* NODE_CREATE(char element){
	NODE *newnode = (NODE*)malloc(sizeof(NODE));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->val = element;
	return newnode;	
}

bool PARENTHESES_CHECK_NEED(char pre, NODE *current, NODE *preNode){
	if( (pre IS '/' AND current->val IS '+') OR (pre IS '/' AND current->val IS '-')\
		OR (pre IS '*' AND current->val IS '+') OR (pre IS '*' AND current->val IS '-')\
		OR (pre IS '/' AND current->val IS '/' AND preNode->right IS current)\
		OR (pre IS '/' AND current->val IS '*' AND preNode->right IS current)\
		OR (pre IS '-' AND current->val IS '-' AND preNode->right IS current)\
		OR (pre IS '-' AND current->val IS '+' AND preNode->right IS current) )
		return true;
	return false;
}

void EXPRESSION_TREE_PRINT(NODE *root, char pre, NODE *preNode){
	if(root){
		// if element is operand
		if( ((root->val>='A')AND(root->val<='Z')) OR ((root->val>='a')AND(root->val<='z')) )
			printf("%c ", root->val);
		else{
		// if element is operator
			if( PARENTHESES_CHECK_NEED(pre, root, preNode) )
				printf("( ");
			EXPRESSION_TREE_PRINT(root->left, root->val, root);
			printf("%c ", root->val);
			EXPRESSION_TREE_PRINT(root->right, root->val, root);
			if( PARENTHESES_CHECK_NEED(pre, root, preNode) )
				printf(") ");
		}
	}
}

NODE* EXPRESSION_TREE_CREATE(char *prefix){
	// stack : store child of tree node
	STACK *stack = (STACK*)malloc(sizeof(STACK));
	stack->next = NULL;
	// tree root for return
	NODE *ret = NODE_CREATE(prefix[0]);
	PUSH(stack, &ret->right); 
	PUSH(stack, &ret->left);
	printf(" Current tree(inorder): ");
	EXPRESSION_TREE_PRINT(ret, '\0', NULL);
	printf("\n");
	// go through prefix
	int str_len = strlen(prefix);
	for(int i=1; i<str_len; i++){
		// create newnode
		NODE *newnode = NODE_CREATE(prefix[i]); 
		// if element is operand
		if( ((prefix[i]>='A')AND(prefix[i]<='Z')) OR ((prefix[i]>='a')AND(prefix[i]<='z')) )
			POP(stack)[0] = newnode;
		// if element is operator
		else if((prefix[i] IS '+') OR (prefix[i] IS '-') OR (prefix[i] IS '*') OR (prefix[i] IS '/')){
			POP(stack)[0] = newnode;	
			PUSH(stack, &newnode->right);
			PUSH(stack, &newnode->left);	
		}
		printf(" Current tree(inorder): ");
		EXPRESSION_TREE_PRINT(ret, '\0', NULL);
		printf("\n");
	}
	return ret;
}

int main(void){
	// read a prefix expression
	char prefix[MAX] = "+-abc";
	// create expression tree
	NODE *root = EXPRESSION_TREE_CREATE(prefix);
	// print tree
	printf("\n #Result: ");
	EXPRESSION_TREE_PRINT(root, '\0', NULL);
	// end
	printf("\n");
	return 0;
}
