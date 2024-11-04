#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct _person* position;
typedef struct _person {
    char name[MAX];
    char surname[MAX];
    int birthyear;

    position next;
}person;

position create(char* name, char* surname, int birthyear);
void dodajnapocetak(position, char*, char*, int);
void ispis(position);
void dodajnakraj(position, char*, char*, int);
position findperson(position, char*);
void persondelete(position, char*);
void dodajiza(position, char*, char*, int);
void dodajispred(position, char*, char*, int);
position findprev(position, position);
void sort(position);
void write(position, char*);
void read(position, char*);


int main() {
    person head = {
        .name = {0},
        .surname = {0},
        .birthyear = 0,
        .next = NULL
    };

    char datoteka[MAX] = "persons.txt";


    dodajnapocetak(&head, "Ivan", "Ivic", 1990);
    dodajnapocetak(&head, "Marko", "Maric", 1985);
    dodajnakraj(&head, "Ana", "Anic", 1992);

    ispis(&head);

    position found = findperson(&head, "Maric");
    if (found != NULL) {
        printf("Pronadena osoba: %s %s, Godina rodjenja: %d\n", found->name, found->surname, found->birthyear);
    }
    else {
        printf("\nOsoba nije pronadena.\n");
    }

    printf("\nBrisanje osobe s imenom Ivic\n");
    persondelete(&head, "Ivic");

    dodajiza(&head, "Pero", "Peric", 1995);
    dodajispred(&head, "Jure", "Kovanica", 1991);

    ispis(&head);
    printf("\n");

    sort(&head);

    ispis(&head);

    write(&head, datoteka);

    read(&head, datoteka);

    return 0;
}

position create(char* name, char* surname, int birthyear) {
    position newperson = NULL;
    newperson = (position)malloc(sizeof(person));
    if (newperson == NULL) {
        printf("\nGreska u alokaciji memorije\n");
    }

    strcpy(newperson->name, name);
    strcpy(newperson->surname, surname);
    newperson->birthyear = birthyear;
    newperson->next = NULL;

    return newperson;
}

void dodajnapocetak(position head, char* name, char* surname, int birthyear) {
    position newperson = create(name, surname, birthyear);
    if (newperson != NULL) {
        newperson->next = head->next;
        head->next = newperson;
    }
}

void ispis(position head) {
    position temp = head->next;
    while (temp != NULL) {
        printf("Ime: %s, Prezime: %s, Godina Rodjenja: %d\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }
}

void dodajnakraj(position head, char* name, char* surname, int birthyear) {
    position newperson = create(name, surname, birthyear);

    if (newperson == NULL) return;

    position temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newperson;
    newperson->next = NULL;
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

void persondelete(position head, char* surname) {
    position temp = head;
    position prev = NULL;

    if (temp != NULL && strcmp(temp->surname, surname) == 0) {
        head = temp->next;
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

void dodajiza(position head, char* name, char* surname, int birthyear) {
    position newperson = create(name, surname, birthyear);
    position found = findperson(head, "Maric");

    if (newperson != NULL && found != NULL) {
        newperson->next = found->next;
        found->next = newperson;
    }
}

position findprev(position head, position found) {
    position temp = head;

    while (temp != NULL) {
        temp = temp->next;
        if (temp->next == found) {
            return temp;
        }
    }

    return NULL;

}

void dodajispred(position head, char* name, char* surname, int birthyear) {
    position newperson = create(name, surname, birthyear);
    position found = findperson(head, "Peric");
    position prev = findprev(head, found);

    if (newperson != NULL && found != NULL && prev != NULL) {
        newperson->next = found;
        prev->next = newperson;

    }
    else {
        if (newperson != NULL && (found == NULL || prev == NULL)) {
            printf("Could not insert: target person 'Peric' not found.\n");
        }
    }
}

void sort(position head) {
    int swapped;
    position temp;
    position lastSorted = NULL;

    do {
        swapped = 0;
        temp = head;

        while (temp->next != lastSorted && temp->next != NULL && temp->next->next != NULL) {
            if (strcmp(temp->next->surname, temp->next->next->surname) > 0) {
                position first = temp->next;
                position second = first->next;

                first->next = second->next;
                second->next = first;
                temp->next = second;
                swapped = 1;
            }
            temp = temp->next;
        }
        lastSorted = temp;
    } while (swapped);
}

void write(position head, char* datoteka) {
    position temp = head->next;

    FILE* fp;
    fp = fopen(datoteka, "w");
    if (fp == NULL) {
        printf("Greska u otvaranju dat. (ucitaj)\n");
        return;
    }

    while (temp != NULL) {
        fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }
    fclose(fp);
}

void read(position head, char* datoteka) {
    FILE* fp;
    position temp;
    temp = head->next;
    fp = fopen(datoteka, "r");
    if (fp == NULL) {
        printf("Greska u otvaranju dat.\n");
        return;
    }


    while (temp->next != NULL) {
        fscanf(fp, "%s %s %d", temp->name, temp->surname, &temp->birthyear);
        temp = temp->next;
    }

    fclose(fp);
}