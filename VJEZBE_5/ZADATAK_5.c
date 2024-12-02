#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024

typedef struct cvor* position;
typedef struct cvor {
	
	int number;

	position next;

}stog;

position create(int nmbr);
void readFromFile(char* filename);
position findLast(position head);
void push(position head, int nmbr);
int pop(position head);
int solvePostfix(char* buffer, position head);

int main() {

	stog head = { .number = 0, .next = NULL };

	char buffer[MAX] = { '\0'};

	readFromFile(buffer);
	printf("Postfix: %s\n", buffer);

	int result = solvePostfix(buffer, &head);
	printf("Rezultat: %d\n", result);

	return 0;
}

position create(int nmbr) {

	position newElement = NULL;
	newElement = (position)malloc(sizeof(stog));
	if (newElement == NULL) {
		printf("Greska u mallocu (create)");
		return NULL;
	}

	newElement->number = nmbr;
	newElement->next = NULL;

	return newElement;
}

void readFromFile(char* buffer) {

	FILE* fp = fopen("POSTFIX.txt", "r");
	if (fp == NULL) {
		printf("Greska u fopenu (readFromFile)\n");
		return;
	}

	if (fgets(buffer, MAX, fp) == NULL) {
		printf("Greska u readfromfile ");
		fclose(fp);
		return;
	}

	fclose(fp);
}

position findLast(position head) {
	position temp = NULL;
	temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	return temp;
}

void push(position head, int nmbr) {

	position temp = NULL;
	temp = head;
	if (temp == NULL) {
		printf("Greska u tempu (push)");
		return;
	}

	temp = findLast(head);
	position new = create(nmbr);

	temp->next = new;
	
}

int pop(position head) {

	position temp = findLast(head);
	position prev = NULL;

	prev = head;
	while (prev->next != temp)
		prev = prev->next;

	int lastInt = temp->number;

	prev->next = NULL;
	free(temp);
	
	return lastInt;
}

int solvePostfix(char* buffer, position head) {
	int op1 = 0, op2 = 0;
	int result = 0;

	for (int i = 0; buffer[i] != '\0'; i++) {

		if (buffer[i] == ' ')
			continue;

		else if (isdigit(buffer[i])) {
			int num = 0;

			while (isdigit(buffer[i])) {
				num = num * 10 + (buffer[i] - '0');
				i++;
			}
			i--;
				push(head, num);
		}

		else {
			op2 = pop(head);
			op1 = pop(head);

			switch (buffer[i]) {
			case '+':
				push(head, op1 + op2);
				break;
			case'-':
				push(head, op1 - op2);
				break;
			case'*':
				push(head, op1 * op2);
				break;
			case'/':
				if (op2 == 0) {
					printf("Djeljitelj ne moze biti 0");
					return -1;
				}
				push(head, op1 / op2);
				break;
			default:
				printf("Greska u switch");
				return -1;
			}
		}
	}

	return result = pop(head);
}
