#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {
	int value;
	struct node* left, * right;
} node;

node* createnode(int value) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->value = value;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

node* insert(node* root, int value);
int replace(node* root);
void inOrder(node* root, FILE* file);
int rngVal();

int main() {

	int tree[] = { 2,5,7,8,11,1,4,2,3,7 };
	int i, n = sizeof(tree) / sizeof(int);
	FILE* file;

	node* root = NULL;
	for (i = 0; i < n; i++)
		root = insert(root, tree[i]);

	//a)
	file = fopen("inOrder_a.txt", "w");
	if (!file) {
		printf("Greska 1");
		return 1;
	}
	inOrder(root, file);
	fclose(file);

	//b)
	replace(root);
	file = fopen("inOrder_b.txt", "w");
	if (!file) {
		printf("Greska 2");
		return 1;
	}
	inOrder(root, file);
	fclose(file);

	//c)
	
	node* randomRoot = NULL;
	srand(time);

	for (i = 0; i < n; i++) {
		int randomVal = rngVal();
		randomRoot = insert(randomRoot, randomVal);
	}

	file = fopen("inOrder_c.txt", "w");
	if (!file) {
		printf("Greska 3");
		return 1;
	}
	inOrder(randomRoot, file);
	fclose(file);

	return 0;
}

node* insert(node* root, int value) {
	if (root == NULL)
		return createnode(value);

	if (value <= root->value)
		root->left = insert(root->left, value);
	else
		root->right = insert(root->right, value);

	return root;
}

int replace(node* root) {
	if (root == NULL)
		return 0;

	int LSum = replace(root->left);
	int RSum = replace(root->right);
	int oldValue = root->value;

	root->value = LSum + RSum;
	return oldValue + root->value;
}

void inOrder(node* root, FILE* file) {
	if (root == NULL)
		return 0;

	inOrder(root->left, file);
	fprintf(file, "%d ", root->value);
	inOrder(root->right, file);
}

int rngVal() {
	return 10 + rand() % 81;
}