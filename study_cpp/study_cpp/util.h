#ifndef _UTIL_H_
#endif	_UTIL_H_

#include <iostream>
#include <vector>
#include <cstdarg>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode *TreeCreate(int count, ...)
{
	va_list argptr;
	va_start(argptr, count);

	TreeNode **treeArr = new TreeNode*[count];
	for (int i = 0; i < count; i++)
	{
		int num = va_arg(argptr, int);
		if (INT_MAX == num)
			treeArr[i] = NULL;
		else
			treeArr[i] = new TreeNode(num);
	}

	int curr = 1;
	for (int i = 0; i < count; i++)
	{
		if (!treeArr[i])
			continue;

		if (curr < count)
			treeArr[i]->left = treeArr[curr++];
		if (curr < count)
			treeArr[i]->right = treeArr[curr++];
	}

	va_end(argptr);
	return treeArr[0];
}


void SubTreePrint(TreeNode *node, int level)
{
	if (!node)
		return;

	SubTreePrint(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%02d\n", node->val);
	SubTreePrint(node->left, level + 1);
}

void TreePrint(TreeNode *root)
{
	cout << "------------------------------------" << endl;
	SubTreePrint(root, 0);
	cout << "------------------------------------" << endl;
}