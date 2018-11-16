#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

void transform2(Node* head, Node* &head1, Node* &head2){
	if (head == NULL){
		head1 = head2 = NULL;
		return;
	}
	Node* n1 = head, *n2 = n1->next;
	head1 = n1, head2 = n2;
	//这儿设计的比较好，只需要两个指针不断的轮换
	while (n2){
		n1->next = n2->next;
		n1 = n1->next;
		swap(n1, n2);
	}
}

void transform(Node* head, Node* &head1, Node* &head2){
	if (head == NULL){
		head1 = head2 = NULL;
		return;
	}
	Node* n1 = head, *n2 = n1->next;
	head1 = n1, head2 = n2;
	//每次轮换两个指针就行了，不用像上个例子那样进行交换指针（swap） 
	while (n2){
		n1->next = n2->next;
		n1 = n2;
		n2 = n2->next;
	}
}
Node* nd[10];

int main_split_list()
{
	for (int i = 0; i<10; i++){
		nd[i] = new Node();
		nd[i]->data = i;
	}
	for (int i = 0; i<9; i++)
		nd[i]->next = nd[i + 1];
	nd[9]->next = NULL;
	Node* p1, *p2;
	p1 = p2 = NULL;
	transform2(nd[0], p1, p2);
	cout << "p1:" << endl;
	while (p1){
		cout << p1->data << " ";
		p1 = p1->next;
	}
	cout << endl;
	cout << "p2:" << endl;
	while (p2){
		cout << p2->data << " ";
		p2 = p2->next;
	}
	cout << endl;
	system("pause");
	return 0;
}