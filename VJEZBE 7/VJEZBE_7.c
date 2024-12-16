#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 256

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _dir* dirPosition;
typedef struct _dir {
	char name[MAX_LENGTH];
	dirPosition sibling;
	dirPosition child;
}dir;

typedef struct _stack* stackPosition;
typedef struct _stack {
	dirPosition data;
	stackPosition next;
}stack;

int push(dirPosition current, stackPosition stackHead);
dirPosition pop(stackPosition stackHead);
stackPosition mallocStack();
dirPosition makeDir(dirPosition current, char* name);
dirPosition changeDir(dirPosition current, stackPosition stackHead, char* name);
dirPosition prevDirectory(stackPosition stackHead);
int printDir(dirPosition current);
void delete(dirPosition current);
int cmdPrompt(dirPosition current, stackPosition stackHead);

int main() {

	dir C;
	C.sibling = NULL;
	C.child = NULL;
	strcpy(C.name, "C:");

	stack stackHead;
	stackHead.data = NULL;
	stackHead.next = NULL;


	push(&C, &stackHead);

	cmdPrompt(&C, &stackHead);


	return 0;
}

int push(dirPosition current, stackPosition stackHead) {

	stackPosition newElement;
	stackPosition temp = stackHead;

	if (newElement = mallocStack()) {

		while (temp->next)
			temp = temp->next;

		newElement->next = temp->next;
		temp->next = newElement;
		newElement->data = current;

		return 0;
	}

	else
		return 1;
}

dirPosition pop(stackPosition stackHead) {

	stackPosition temp = stackHead->next;
	stackPosition prev = stackHead->next;

	if (temp->next == NULL)
		return NULL;

	while (temp->next) {
		prev = temp;
		temp = temp->next;
	}

	dirPosition directory = temp->data;
	prev->next = temp->next;
	
	free(temp);

	return directory;
}

stackPosition mallocStack() {

	stackPosition newElement = (stackPosition)malloc(sizeof(stack));
	if (newElement == NULL) {
		printf("Greska u allociranju memorije (mallocStack)\n");
		return NULL;
	}

	return newElement;
}

dirPosition mallocDir() {

	dirPosition newDir = (dirPosition)malloc(sizeof(dir));
	if (newDir == NULL) {
		printf("Greska u alociranju memorije (mallocDir)\n");
		return NULL;
	}
	newDir->child = NULL;
	newDir->sibling = NULL;
	return newDir;
}

dirPosition makeDir(dirPosition current, char* name) {

	dirPosition newDir = mallocDir();

	strcpy(newDir->name, name);

	if (!current->child) {
		current->child = newDir;
	}

	else {

		dirPosition currentChild = current->child;
		
		while (currentChild->sibling)
			currentChild = currentChild->sibling;
		currentChild->sibling = newDir;

	}

	return current;
}

dirPosition changeDir(dirPosition current, stackPosition stackHead, char* name) {

	if (!current->child) {
		printf("Prazan direktorij\n");
		return current;
	}

	else {

		dirPosition parent = current;
		dirPosition findDir = current->child;

		while (findDir) {

			if (!strcmp(findDir->name, name)) {

				push(findDir, stackHead);
				return(findDir);
			}

			findDir = findDir->sibling;
		}

		printf("Direktorij ne postoji\n");
		
		return parent;
	}
}

dirPosition prevDirectory(stackPosition stackHead) {

	return pop(stackHead);
}

int printDir(dirPosition current) {

	if (!current->child)
		printf("Direktorij je prazan\n");

	else {
		
		current = current->child;

		while (current) {
			printf(" %s\n", current->name);
			current = current->sibling;
		}
	}

	return 0;
}

void delete(dirPosition current) {
	
	if (!current)
		return;

	delete(current->sibling);
	delete(current->child);
	free(current);
}

int path(dirPosition current, stackPosition stackHead)
{
	char stringToPrint[MAX_LENGTH] = "";
	
	while (stackHead)
	{
		strcat(stringToPrint, stackHead->data->name);
		strcat(stringToPrint, "\\");
		stackHead = stackHead->next;
	}

	strcat(stringToPrint, ">");
	printf("%s ", stringToPrint);
	return 0;
}

int cmdPrompt(dirPosition current, stackPosition stackHead) {

	dirPosition C = current;
	char userInput[MAX_LENGTH];
	char cmd[5];
	char dirName[MAX_LENGTH];

	path(current, stackHead->next);

	do {
		fgets(userInput, MAX_LENGTH, stdin);
		sscanf(userInput, "%s %s", cmd, dirName);
		if (!strcmp(cmd, "md"))
		{
			current = makeDir(current, dirName);
			path(current, stackHead->next);
		}
		else if (!strcmp(cmd, "cd"))
		{
			current = changeDir(current, stackHead, dirName);
			path(current, stackHead->next);
		}
		else if (!strcmp(cmd, "cd.."))
		{
			if (current = prevDirectory(stackHead) == NULL)
				current = C;
			path(current, stackHead->next);
		}
		else if (!strcmp(cmd, "dir"))
		{
			printDir(current);
			path(current, stackHead->next);
		}
		else if (!strcmp(cmd, "exit"))
			delete(current);
		else
			printf("To nije opcija!");
	} while (strcmp(cmd, "exit"));
	return 0;
}