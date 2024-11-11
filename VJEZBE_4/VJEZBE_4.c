#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

typedef struct _polinom* position;
typedef struct _polinom {

	int koeficijent;
	int eksponent;
	
	position next;

}polinom;

position create(int koeficijent, int exponent);
void insertSorted(position head, int koef, int exp);
void readFromDat(position head, const char* dat);
void print(position head);
void sum(position head1, position head2, position headSum);
void product(position head1, position head2, position headSum);


int main() {

	polinom head1 = { 0, 0, NULL };
	polinom head2 = { 0, 0, NULL };
	polinom headSum = { 0, 0, NULL };
	polinom headProd = { 0, 0, NULL };

	readFromDat(&head1, "polinom1.txt");
	readFromDat(&head2, "polinom2.txt");

	printf("Prvi polinom: ");
	print(&head1);
	printf("Drugi polinom: ");
	print(&head2);
	
	sum(&head1, &head2, &headSum);

	printf("Suma: ");
	print(&headSum);

	product(&head1, &head2, &headProd);

	printf("Produkt: ");
	print(&headProd);

	return 0;
}

position create(int koeficijent, int eksponent) {

	position newPolynom = NULL;
	newPolynom = malloc(sizeof(polinom));
	if (newPolynom == NULL) {
		printf("Greska u alokaciji memorije (create)\n");
		return NULL;
	}

	newPolynom->koeficijent = koeficijent;
	newPolynom->eksponent = eksponent;
	newPolynom->next = NULL;

	return newPolynom;
}

void insertSorted(position head, int koef, int exp) {

	position newPolynom = create(koef, exp);
	if (newPolynom == NULL) {
		printf("\nGreska u create - insertSorted");
		return;
	}
	position temp = head;
	position prev = NULL;

	if (head->next == NULL) {
		head->next = newPolynom;
		return;
	}

	while (temp != NULL && temp->eksponent < exp) {
		prev = temp;
		temp = temp->next;
	}
	
	if (temp != NULL && temp->eksponent == exp) {
		temp->koeficijent += koef;
		free(newPolynom);
	}
	else {
		newPolynom->next = temp;
		prev->next = newPolynom;
	}
}

void readFromDat(position head, const char* dat) {

	int koef = 0, exp = 0;
	char buffer[MAX];

	FILE* fp;
	fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke (readFromDat)\n");
		return;
	}

	if (fgets(buffer, MAX, fp) != NULL) {
		char* ptr = buffer;


		while (sscanf(ptr, "%d %d", &koef, &exp) == 2) {
			insertSorted(head, koef, exp);

			for (int i = 0; i < 2; i++) {

				while (*ptr != ' ' && *ptr != '\0')
					ptr++;
				while (*ptr == ' ')
					ptr++;
				if (*ptr == '\0')
					break;
			}

			if (*ptr == '\0')
				break;
		}
	}

	fclose(fp);
}

void print(position head) {

	position temp = head->next;

	while (temp != NULL) {
		printf("%d^%d", temp->koeficijent, temp->eksponent);
		temp = temp->next;
		if (temp != NULL)
			printf(" + ");
	}

	printf("\n\n");
}

void sum(position head1, position head2, position headSum) {

	position temp1 = head1->next;
	position temp2 = head2->next;
	position tempProv = NULL;

	while (temp1 != NULL && temp2 != NULL) {

		if (temp1->eksponent == temp2->eksponent) {
			insertSorted(headSum, temp1->koeficijent + temp2->koeficijent, temp1->eksponent);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}

		else if (temp1->eksponent > temp2->eksponent) {
			insertSorted(headSum, temp1->koeficijent, temp1->eksponent);
			temp1 = temp1->next;
		}
		else {
			insertSorted(headSum, temp2->koeficijent, temp2->eksponent);
			temp2 = temp2->next;
		}

	}

	if (temp1 != NULL)
		tempProv = temp1;
	else
		tempProv = temp2;
	while (tempProv != NULL) {
		insertSorted(headSum, tempProv->koeficijent, tempProv->eksponent);
		tempProv = tempProv->next;
	}
		

}

void product(position head1, position head2, position headProd) {

	for (position i = head1->next; i != NULL; i = i->next) {
		for (position j = head2->next; j != NULL; j = j->next) {
			int newKoef = i->koeficijent * j->koeficijent;
			int newExp = i->eksponent + j->eksponent;
			insertSorted(headProd, newKoef, newExp);
		}
	}

}