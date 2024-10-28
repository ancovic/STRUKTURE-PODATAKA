#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct _person* position;

typedef struct _person {
    char name[MAX];
    char surname[MAX];
    int birthyear;

    position next;
}person;

position create(char* name, char* surname, int birthyear);
void dodajnapocetak(position*, char*, char*, int);
void ispis(position);
void dodajnakraj(position*, char*, char*, int);
position findperson(position, char*);
void persondelete(position*, char*);

int main() {
    position head = NULL;

    dodajnapocetak(&head, "Ivan", "Ivic", 1990);
    dodajnapocetak(&head, "Marko", "Maric", 1985);
    dodajnakraj(&head, "Ana", "Anic", 1992);

    ispis(head);

    position found = findperson(head, "Maric");
    if (found != NULL) {
        printf("Pronadena osoba: %s %s, Godina rodjenja: %d\n", found->name, found->surname, found->birthyear);
    }
    else {
        printf("\nOsoba nije pronadena.\n");
    }

    printf("\nBrisanje osobe s imenom Ivic\n");
    persondelete(&head, "Ivic");

    return 0;
}

position create(char* name, char* surname, int birthyear) {

    position newperson = NULL;
    newperson = (position)malloc(sizeof(person));
    if (newperson == NULL) {
        printf("Greska u alokaciji memorije\n");
    }

    strcpy(newperson->name, name);
    strcpy(newperson->surname, surname);
    newperson->birthyear = birthyear;
    newperson->next = NULL;

    return newperson;

}

void dodajnapocetak(position* head, char* name, char* surname, int birthyear) {

    position newperson = create(name, surname, birthyear);
    if (newperson != NULL) {
        newperson->next = *head;
        *head = newperson;
    }
}

void ispis(position head) {

    position temp = head;
    while (temp != NULL) {
        printf("Ime: %s, Prezime: %s, Godina Rodjenja: %d\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }

}

void dodajnakraj(position* head, char* name, char* surname, int birthyear) {
    position newperson = create(name, surname, birthyear);

    if (newperson == NULL) return;

    if (*head == NULL) {
        *head = newperson;
    }
    else {
        position temp = *head;

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newperson;
    }
}

position findperson(position head, char* surname) {
    position temp = head;
    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void persondelete(position* head, char* surname) {
    position temp = *head;
    position prev = NULL;

    if (temp != NULL && strcmp(temp->surname, surname) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}