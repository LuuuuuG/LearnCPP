#include <iostream>
#include <stack>
#include <queue>
#include "util.h"
using namespace std;

/*

                      A
                    /    \
                  B       C
                /   \     /  \     
               D    E   F   G


深度优先遍历(DFS) : A B D E C F G

广度优先遍历(BFS) : A B C D E F G

*/

//深度优先遍历(DFS)
void depthFirstSearch(TreeNode* root){
	stack<TreeNode *> nodeStack;  //使用C++的STL标准模板库
	nodeStack.push(root);
	TreeNode *node;
	while (!nodeStack.empty()){
		node = nodeStack.top();
		cout << node->val;
		nodeStack.pop();
		if (node->right){
			nodeStack.push(node->right);  //先将右子树压栈
		}
		if (node->left){
			nodeStack.push(node->left);  //再将左子树压栈
		}
	}
}

//DFS 递归实现
void dfs(TreeNode* root)
{
	if (root){
		cout << root->val;
		dfs(root->left);
		dfs(root->right);
	}
}

//广度优先遍历(BFS)
void breadthFirstSearch(TreeNode* root){
	queue<TreeNode *> nodeQueue;  //使用C++的STL标准模板库
	nodeQueue.push(root);
	TreeNode *node;
	while (!nodeQueue.empty()){
		node = nodeQueue.front();
		nodeQueue.pop();
		cout << node->val;
		if (node->left){
			nodeQueue.push(node->left);  //先将左子树入队
		}
		if (node->right){
			nodeQueue.push(node->right);  //再将右子树入队
		}
	}
}

int main_bfs_dfs()
{

	TreeNode *tree = TreeCreate(7, 1, 2, 3, 4, 5, 6, 7);
	TreePrint(tree);
	cout << "DFS : " << endl;
	depthFirstSearch(tree);
	cout << "\n递归实现：" << endl;
	dfs(tree);
	cout << "\n--------------------" << endl;
	cout << "BFS :" << endl;
	breadthFirstSearch(tree);
	system("pause");
	return 0;
}

