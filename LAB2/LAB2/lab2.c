#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

struct _person;
typedef struct _person *position;
typedef struct _person {

	//ime
	char name[MAX_SIZE];
	char lastName[MAX_SIZE];
	int birthYear;

	position next;
}Person;

position createPerson(char *name, char *lastName, int birthYear);
int printList(position first);
int appendList(position head, char*, char*, int);
position findLast(position head);
int insertAfter(position prev, position newPerson);
position findByLastName(position first, char *lastName);
int delete (position head, char *name);
position findPrev(position head, char*);

int main() {

	Person head = { 
		.name = {0},
		.lastName = {0},
		.birthYear = 0,
		.next = NULL; 
	};
	


	return 0;
}

position createPerson(char *name, char *lastName, int birthYear) {

	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Greska u malloc\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->)
}

int prependList(position head, char*name, char*lastName) {

	position newPerson = createPerson(name, lastName, birthYear);
	//if ... 

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int printList(position first) {

	position temp = NULL;
	temp = first;
	while (temp != NULL) {

		printf("%s %s %d".temp->name, temp->lastName, temp->birthYear);
		temp = temp->next;

	}

	return EXIT_SUCCESS;
}

int appendList(position head, char* name, char* lastName, int birthYear) {

	position newPerson = NULL;
	position temp = NULL;

	newPerson = createPerson(name, lastName, birthYear);
	//if...

	last = findLast(head);

	insertAfter()

	return EXIT_SUCCESS;

}

position findLast(position head) {

	position last = NULL;
	last = head;

	while (last->next != NULL) {

		last = last->next;
	}

	return last;
}

int insertAfter(position prev, position newPerson) {

	newPerson->next = last->next;
	last->next = newPerson;

}

position findByLastName(position first, char *lastName) {

	position temp = NULL;
	temp = first;

	while (temp) {

		if (strcmp(lastName, temp->lastName) == 0) {

			return temp;
		}

		temp = temp->next;
	}

	return NULL;
}

int delete (position head, char * name) {

	position prev = NULL;
	position toDelete = NULL;

	prev = findPrev(head, name);

	toDelete = prev->next;
	prev->next = toDelete;
	return EXIT_SUCCESS;
}

position findPrev(position head, char* name) {


	position temp = head;
	
}