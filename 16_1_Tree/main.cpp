# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include "subFunc.h"

void ARRAY_CREATE(void *nums, int N, int element){
	int *array = (int*)nums;
	int i = 0, tmp = 0;
	static int cp = 0, mv = 0;
	// find the site to insert
	for(i=0;i<N;i++,cp+=2)
		if(element < array[i]) break;
	// insert element
	cp++;
	if(i == N)
		{ mv++; array[i-1] = element; }
	else{
		for(int j=i;j<N;j++,mv++,cp++){
			tmp = array[j];
			array[j] = element;
			element = tmp;
		}
	}
	// output comparison and movement times
	for(int k=0;k<N;k++)
		{ printf("%5d,", array[k]); if((k+1)%10 IS 0 AND k IS_NOT 0) printf("\n"); }
	printf("\n=============== \tcp:%d\tmv:%d\t=====================\n\n", cp, mv);
}

void BST_CREATE(void *root, int N, int element){
	BST_NODE *tree = (BST_NODE*)root;
	static int cp = 0, mv = 0;
	cp+=1; // 判斷
	if(N IS 1)
		tree->val = element;
	else{
		while(true){
			cp+=3;
			if(element < tree->val){
				if(tree->left IS NULL){
					tree->left = BST_NODE_CREATE(element);
					break;
				}
				else
					tree = tree->left;
			}
			else{
				if(tree->right IS NULL){
					tree->right = BST_NODE_CREATE(element);
					break;
				}
				else
					tree = tree->right;
			}
		}
	} 
	mv++;
	BST_IN_ORDER((BST_NODE*)root);
	printf("\n=============== \tcp:%d\tmv:%d\t=====================\n\n", cp, mv);
}

void M_TREE_CREATE(void *root, int N, int element){
	printf("\n=====\tM_TREE_CREATE: %d| target: %d\t=====\n", N, element);
	M_TREE_NODE *tree = (M_TREE_NODE*)root;
	static int cp = 0, mv = 0;
	cp++;
	if(N IS_NOT 1){
		while(true){
			cp+=2;
			// print node
			M_TREE_NODE_PRINT(tree);
			if(tree->val[0] < 2){ 
				cp++;
				if(tree->val[0] IS 1){
					tree->val[2] = element;
					cp++;
					if(tree->val[1] > element)
						{ SWAP(&tree->val[1], &tree->val[2]); mv++; }
				}
				else
					tree->val[1] = element; 
				tree->val[0]++; 
				M_TREE_NODE_PRINT(tree);
				break; 
			}
			else{ //  if(root->val[0] IS 2)
				cp++;
				if(tree->val[1] > element){
					printf("\t: go to left\n");
					cp++;
					if(tree->left IS NULL){
						tree->left = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->left);
						break;
					}
					else
						tree = tree->left;
				}
				else if(tree->val[1] <= element AND tree->val[2] > element){
					cp+=2;
					printf("\t: go to mid\n");
					cp++;
					if(tree->mid IS NULL){
						tree->mid = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->mid);
						break;
					}
					else
						tree = tree->mid;
				}
				else{
					cp+=2;
					printf("\t: go to right\n");
					cp++;
					if(tree->right IS NULL){
						tree->right = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->right);
						break;
					}
					else
						tree = tree->right;
				}
			}
		}
	}
	else
		{ tree->val[0] += 1; tree->val[1] = element; M_TREE_NODE_PRINT(tree); mv++; return; }
	mv++;
	printf("\n=============== \tcp:%d\tmv:%d\t=====================\n\n", cp, mv);
}

void INSERT(void *ret, int chose, int N, int element){
	switch(chose){
		case 1: ARRAY_CREATE(ret, N, element); break;
		case 2: BST_CREATE(ret, N, element); break;
		case 3: M_TREE_CREATE(ret, N, element); break;
		default: printf("\t[ warning : 404 ]\n"); break;
	}
}
void* FILE_GET(char *file, int N, int chose){
	FILE *fptr = fopen(file, "r");
	void *ret = HEAD_CREATE(chose, N);
	int take = 0;

	if(fptr)
		for(int i=0;i<N;i++){
			fscanf(fptr,"%d", &take);
			INSERT(ret, chose, i+1, take);
		}
	else
		printf("\t[ warning : can't open the file ]\n");
	fclose(fptr);
	return ret;
}

bool ARRAY_BI_SEARCH(void *nums, int start, int end, int target){
	int cp = 0, ret = 0;
	int *array = (int*)nums;

	while(start IS_NOT (start+end)/2){
		cp++;
		if(array[(start+end)/2] IS target)
			{ ret = 1; break; }
		else if(array[(start+end)/2] < target)
			{cp++; start = (start+end)/2;}
		else
			end = (start+end)/2;
	}
	printf("\t# Comparison times of biSearchArray: %d\n", cp);
	return ret;
}

bool BST_BI_SEARCH(void *root, int target){
	BST_NODE *tree = (BST_NODE*)root;
	int cp = 0;
	int ret = 0;

	while(tree IS_NOT NULL){
		cp++;
		if(tree->val IS target)
			{ ret = 1; break; }
		else if(tree->val > target)
			{cp++; tree = tree->left;}
		else
			tree = tree->right;
	}
	printf("\t# Comparison times of biSearchBST: %d\n", cp);
	return ret;
}

void M_TREE_PRINT(void *tree){
	if(tree){
		M_TREE_NODE *root = (M_TREE_NODE*)tree;
		M_TREE_PRINT(root->left);
		for(int i=0;i<root->val[0];i++)
			printf("%d,", root->val[i+1]);
		M_TREE_PRINT(root->mid);
		M_TREE_PRINT(root->right);
	}
}
void M_TREE_DELETE(M_TREE_NODE *node, int target){
	if(node->val[0] IS 0 OR node IS NULL) {printf("err\n");return;}
	printf("Before delete: "); M_TREE_NODE_PRINT(node);
	// if node is not leaf
	if(node->mid IS_NOT NULL AND node->mid->val[0] IS_NOT 0){
		M_TREE_NODE *mxnNode;
		if(node->val[1] IS target){ // target is small one
			mxnNode = M_TREE_MIN(node->mid);
			for(int i=0;i<node->val[0];i++)
				if(node->val[i+1] IS target)
					node->val[i+1] = mxnNode->val[1];
		}
		else{
			mxnNode = M_TREE_MAX(node->mid);
			for(int i=0;i<node->val[0];i++)
				if(node->val[i+1] IS target)
					node->val[i+1] = mxnNode->val[mxnNode->val[0]];			
		}
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		if(node->val[1] IS target)
			M_TREE_DELETE(mxnNode, mxnNode->val[1]);
		else
			M_TREE_DELETE(mxnNode, mxnNode->val[mxnNode->val[0]]);
	}
	else if(node->left IS_NOT NULL AND node->left->val[0] IS_NOT 0){
		M_TREE_NODE *maxNode = M_TREE_MAX(node->left);
		for(int i=0;i<node->val[0];i++)
			if(node->val[i+1] IS target)
				node->val[i+1] = maxNode->val[maxNode->val[0]];
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		M_TREE_DELETE(maxNode, maxNode->val[maxNode->val[0]]);
	}	
	else if(node->right IS_NOT NULL AND node->right->val[0] IS_NOT 0){
		M_TREE_NODE *minNode = M_TREE_MIN(node->right);
		for(int i=0;i<node->val[0];i++)
			if(node->val[i+1] IS target)
				node->val[i+1] = minNode->val[1];
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		M_TREE_DELETE(minNode, minNode->val[1]);
	}
	// if node is leaf
	else{
		if(node->val[0] IS 1){
			M_TREE_NODE *tmp = node;
			node->val[0] -= 1;
			TO_NULL(&node);
			//free(tmp);
		}
		else{
			node->val[0] -= 1;
			if(node->val[1] IS target)
				node->val[1] = node->val[2];
		}
	}
	printf("After delete: "); M_TREE_NODE_PRINT(node);
}
bool M_TREE_SEARCH(void *root, int target){
	M_TREE_NODE *tree = (M_TREE_NODE*)root;
	int cp = 0;
	int ret = 0;
	while(tree IS_NOT NULL){
		for(int i=0;i<tree->val[0];i++, cp++)
			if(tree->val[i+1] IS target)
				{ ret = 1; M_TREE_DELETE(tree, target); break; }
		cp++;
		if(tree->val[1] > target)
			tree = tree->left;
		else if(tree->val[1] <= target AND tree->val[2] > target)
			{cp+=2; tree = tree->mid;}
		else
			{cp+=2; tree = tree->right;}
	}
	printf("\t# Comparison times of serch_M_Tree: %d| target: %d\n", cp, target);
	return ret;
}

bool SEARCH(void *data, int intergerNum, int target, int chose){
	printf("\t# target: %d\n", target);
	switch(chose){
		case 1: return ARRAY_BI_SEARCH(data, 0, intergerNum-1, target); break;
		case 2: return BST_BI_SEARCH(data, target);
		case 3: return M_TREE_SEARCH(data, target);
		default: printf("err\n"); break;
	}
	return false;
}

int main(void){
	srand(time(NULL));
	char file[] = "DB.cpp";
	int chose = 3; // 1: array, 2: BST, 3: m-way tree
	int target = 500;
	int intergerNum = 500;
	void *data = NULL;

	//FILE_CREATE(file, intergerNum);

	data = FILE_GET(file, intergerNum, chose);
	if(SEARCH(data, intergerNum, target, chose))
		printf("\t# result: find\n");
	else
		printf("\t# result: not fount\n");
	free(data);
	return 0;
}
/*

	data = FILE_GET(file, intergerNum, chose);
	//int ary[500] = { -9983,-9927,-9882,-9881,-9863,-9863,-9829,-9800,-9784,-9732,-9679,-9663,-9646,-9599,-9584,-9499,-9478,-9367,-9318,-9292,-9227,-9224,-9208,-9204,-9200,-9146,-9137,-9018,-9013,-8930,-8890,-8841,-8836,-8759,-8680,-8635,-8584,-8496,-8420,-8408,-8405,-8386,-8367,-8341,-8298,-8284,-8167,-8165,-8153,-8144,-8130,-8119,-8076,-8065,-8055,-8049,-8040,-7957,-7947,-7764,-7732,-7731,-7727,-7698,-7637,-7633,-7602,-7582,-7577,-7575,-7565,-7544,-7521,-7491,-7436,-7421,-7364,-7299,-7298,-7298,-7264,-7198,-7181,-7028,-7018,-6990,-6912,-6888,-6856,-6818,-6806,-6802,-6800,-6786,-6783,-6731,-6689,-6673,-6637,-6611,-6608,-6569,-6532,-6512,-6491,-6428,-6388,-6375,-6320,-6308,-6255,-6240,-6155,-6109,-6065,-6043,-5992,-5987,-5983,-5973,-5874,-5832,-5808,-5769,-5728,-5610,-5575,-5500,-5486,-5485,-5479,-5434,-5431,-5388,-5374,-5216,-5183,-5147,-5134,-5091,-5083,-5034,-5031,-4856,-4847,-4826,-4814,-4799,-4798,-4789,-4696,-4656,-4641,-4627,-4597,-4555,-4540,-4537,-4536,-4467,-4437,-4431,-4388,-4373,-4365,-4358,-4303,-4160,-4127,-3993,-3990,-3969,-3946,-3853,-3831,-3703,-3641,-3326,-3301,-3296,-3264,-3243,-3228,-3115,-3111,-2817,-2751,-2717,-2698,-2660,-2657,-2657,-2596,-2513,-2499,-2279,-2260,-2257,-2242,-2152,-2116,-2032,-2025,-2001,-1875,-1855,-1839,-1799,-1778,-1777,-1761,-1741,-1724,-1644,-1610,-1592,-1564,-1377,-1358,-1297,-1163,-1068,-1017,-964,-941,-926,-919,-891,-883,-819,-797,-795,-678,-654,-636,-616,-592,-570,-551,-473,-466,-393,-383,-379,-377,-372,-335,-314,-285,-222,-118,-58,-30,2,35,51,83,84,91,105,138,150,154,203,227,251,433,443,470,532,546,568,648,650,687,765,779,782,790,832,842,878,887,896,943,971,977,985,1023,1109,1167,1265,1328,1340,1382,1407,1489,1504,1569,1672,1767,1799,1870,1927,1944,1969,1994,2025,2037,2211,2258,2342,2346,2347,2355,2416,2430,2487,2498,2574,2659,2692,2722,2731,2753,2867,2876,3023,3132,3173,3175,3178,3276,3288,3289,3340,3372,3443,3444,3449,3449,3487,3525,3530,3532,3547,3552,3603,3684,3769,3801,3817,3877,3999,4056,4304,4353,4464,4495,4509,4517,4591,4666,4711,4766,4807,4836,4841,4865,4897,4933,4947,4971,5075,5208,5254,5335,5358,5413,5459,5513,5517,5588,5600,5615,5656,5859,5874,5906,5929,5934,5944,5988,6026,6081,6085,6086,6087,6121,6165,6188,6227,6243,6326,6345,6360,6399,6400,6446,6517,6543,6580,6627,6639,6656,6698,6745,6893,6960,6998,7023,7032,7053,7181,7265,7279,7435,7437,7477,7542,7585,7603,7664,7679,7702,7743,7762,7898,7939,7940,7942,8206,8295,8346,8384,8420,8482,8511,8561,8561,8616,8632,8713,8715,8844,8875,8884,8887,8893,8927,8938,8955,8961,8968,9008,9079,9087,9144,9156,9192,9206,9225,9263,9267,9273,9315,9317,9339,9347,9360,9368,9407,9426,9455,9467,9509,9539,9590,9747,9779,9823,9824,9841,9845,9853,9863,9907,9979,9984,9991 };
	printf("\n\tbefore: "); M_TREE_PRINT(data); printf("|\n");
	FILE *fptr = fopen("DB.cpp", "r");
	int take = 0;
	for(int i=0;i<intergerNum;i++){
		fscanf(fptr, "%d", &take);
		if(M_TREE_SEARCH(data, take))
			printf("find\n");
		else
			printf("not found\n");		
	}
	
	printf("\n\tafter: "); M_TREE_PRINT(data); printf("|\n");
		return 0;
}
*/
