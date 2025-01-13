#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct _tree* treePointer;
struct _tree {
	int data;
	treePointer left;
	treePointer right;
}tree;

treePointer create(int data);
treePointer insert(treePointer root, int value);
void inorder(treePointer root);
void preorder(treePointer root);
void postorder(treePointer root);
void levelorder(treePointer root);
int height(treePointer root);
int Search(treePointer root, int value);
treePointer minimal(treePointer root);
treePointer delete(treePointer root, int value);

int main() {


	treePointer root = NULL;

	int nodes[] = {3,1,6,4,5,8,7};

	int n = sizeof(nodes) / sizeof(int);

	int choice, value;

	for (int i = 0; i < n; i++)
		root = insert(root, nodes[i]);

	do {
		printf("\n1. Dodaj element\n");
		printf("2. Ispis (inorder)\n");
		printf("3. Ispis (preorder)\n");
		printf("4. Ispis (postorder)\n");
		printf("5. Ispis (levelorder)\n");
		printf("6. Pronadi element\n");
		printf("7. Izbrisi element\n");
		printf("8. Izlaz\n");
		printf("Unesi izbor: ");	
		
		scanf("%d", &choice);

		switch (choice) {
		case 1:

			printf("Unesi vrijednost: ");
			scanf("%d", &value);
			root = insert(root, value); 

			break;
		case 2:
			inorder(root); 
			printf("\n");
			break;
		case 3:

			preorder(root);
			printf("\n");
			
			break;
		case 4:

			postorder(root); 
			printf("\n");
			
			break;
		case 5:

			levelorder(root); 
			printf("\n");

			break;
		case 6:
			printf("Unesi vrijednost za pretragu: ");	
			scanf("%d", &value);
			
			if (Search(root, value))
				printf("Element pronaden.\n");
			else
				printf("Element ne postoji.\n");
			
			break;
		case 7:

			printf("Unesi vrijednost za brisanje: ");	
			scanf("%d", &value);
			root = delete(root, value);

			break;
		case 8:

			printf("Izlaz\n");

			break;
		default:
			printf("Pogresan odabir, unesi broj od 1 do 8\n");

		}

	} while (choice != 8);

	return 0;
}


treePointer create(int data) {

	treePointer new = (treePointer)malloc(sizeof(tree));
	new->data = data;
	new->left = new->right = NULL;

	return new;
}

treePointer insert(treePointer root, int value) {

	if (root == NULL) {
		
		return create(value);
	}


	if (value < root->data)
		root->left = insert(root->left, value);
	else if (value > root->data)
		root->right = insert(root->right, value);

	return root;
}

void inorder(treePointer root) {

	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void preorder(treePointer root) {

	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(treePointer root) {

	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

void printCurrentLevel(treePointer root, int level) {

	if (root == NULL) {
		
		return;
	}

	if (level == 1)
		printf("%d ", root->data);
	else if (level > 1) {
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

void levelorder(treePointer root) {

	if (root == NULL) {
		
		return 0;
	}

	int h = height(root);

	for (int i = 0; i <= h; i++)
		printCurrentLevel(root, i);
}

int height(treePointer root) {

	if (root == NULL) {
		
		return 0;
	}

	int LH = height(root->left);
	int RH = height(root->right);
	int max;

	if (LH > RH)
		max = LH;
	else
		max = RH;

	return max + 1;
}

int Search(treePointer root, int value) {

	if (root == NULL)	
		return 0;

	if (root->data == value)	
		return 1;

	if (value < root->data)	
		return Search(root->left, value);

	return Search(root->right, value);
}

treePointer minimal(treePointer root) {

	while (root->left != NULL)
		root = root->left;

	return root;
}

treePointer delete(treePointer root, int value) {

	if (root == NULL)	
		return root;

	if (value < root->data)
		root->left = delete(root->left, value);

	else if (value > root->data)
		root->right = delete(root->right, value);

	else {
		if (root->left == NULL) {
			treePointer temp = root->right; 
			free(root);

			return temp;
		}
		else if (root->right == NULL) {
			treePointer temp = root->left; 
			free(root);

			return temp;
		}

		treePointer temp = minimal(root->right);
		root->data = temp->data;
		root->right = delete(root->right, temp->data);
	}

	return root;
}
