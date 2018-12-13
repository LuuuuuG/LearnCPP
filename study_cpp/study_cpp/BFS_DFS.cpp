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


������ȱ���(DFS) : A B D E C F G

������ȱ���(BFS) : A B C D E F G

*/

//������ȱ���(DFS)
void depthFirstSearch(TreeNode* root){
	stack<TreeNode *> nodeStack;  //ʹ��C++��STL��׼ģ���
	nodeStack.push(root);
	TreeNode *node;
	while (!nodeStack.empty()){
		node = nodeStack.top();
		cout << node->val;
		nodeStack.pop();
		if (node->right){
			nodeStack.push(node->right);  //�Ƚ�������ѹջ
		}
		if (node->left){
			nodeStack.push(node->left);  //�ٽ�������ѹջ
		}
	}
}

//DFS �ݹ�ʵ��
void dfs(TreeNode* root)
{
	if (root){
		cout << root->val;
		dfs(root->left);
		dfs(root->right);
	}
}

//������ȱ���(BFS)
void breadthFirstSearch(TreeNode* root){
	queue<TreeNode *> nodeQueue;  //ʹ��C++��STL��׼ģ���
	nodeQueue.push(root);
	TreeNode *node;
	while (!nodeQueue.empty()){
		node = nodeQueue.front();
		nodeQueue.pop();
		cout << node->val;
		if (node->left){
			nodeQueue.push(node->left);  //�Ƚ����������
		}
		if (node->right){
			nodeQueue.push(node->right);  //�ٽ����������
		}
	}
}

int main_bfs_dfs()
{

	TreeNode *tree = TreeCreate(7, 1, 2, 3, 4, 5, 6, 7);
	TreePrint(tree);
	cout << "DFS : " << endl;
	depthFirstSearch(tree);
	cout << "\n�ݹ�ʵ�֣�" << endl;
	dfs(tree);
	cout << "\n--------------------" << endl;
	cout << "BFS :" << endl;
	breadthFirstSearch(tree);
	system("pause");
	return 0;
}

