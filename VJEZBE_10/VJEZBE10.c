#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256


typedef struct _city {
	char name[MAX_LINE];
	int population;
	struct _city* next;
}city;

typedef struct _country {
	char name[MAX_LINE];
	city* cities;
	struct _country* left, * right;
}country;

city* createCity(char* name, int population);
city* insertCity(city* head, city* new);
country* createCountry(char* name);
country* insertCountry(country* root, country* new);
city* loadCities(const char* fileName);
void printCities(city* head);
void printCountries(country* root);
country* loadCountries(const char* fileName);
void findCities(country* root, char* namecountry, int minPop);

int main() {

	char wanted[MAX_LINE];
	int minPop;

	country* root = loadCountries("drzave.txt");
	if (!root)
		return 1;

	printCountries(root);

	printf("\nUnesite naziv drzave: "); scanf("%s", wanted);
	printf("Unesite minimalan broj stanovnika: "); scanf("%d", &minPop);

	findCities(root, wanted, minPop);

	return 0;
}

city* createCity(char* name, int population) {
	city* new = (city*)malloc(sizeof(city));
	strcpy(new->name, name);
	new->population = population;
	new->next = NULL;
	return new;
}

city* insertCity(city* head, city* new) {
	if (!head || new->population > head->population || (new->population == head->population && strcmp(new->name, head->name) < 0)) {
		new->next = head;
		return new;
	}

	city* current = head;
	while (current->next && (current->next->population > new->population || (current->next->population == new->population && strcmp(current->next->name, new->name) < 0)))
		current = current->next;

	new->next = current->next;
	current->next = new;
	return head;
}

country* createCountry(char* name) {
	country* new = (country*)malloc(sizeof(country));
	strcpy(new->name, name);
	new->cities = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

country* insertCountry(country* root, country* new) {
	if (!root)
		return new;

	if (strcmp(new->name, root->name) < 0)
		root->left = insertCountry(root->left, new);
	else if (strcmp(new->name, root->name) > 0)
		root->right = insertCountry(root->right, new);
	return root;
}

city* loadCities(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("Greska 1");
		return NULL;
	}

	city* head = NULL;
	char name[MAX_LINE];
	int population;

	while (fscanf(file, "%[^,],%d\n", name, &population) == 2) {
		city* new = createCity(name, population);
		head = insertCity(head, new);
	}

	fclose(file);
	return head;
}

void printCities(city* head) {
	while (head) {
		printf("\t%s, %d\n", head->name, head->population);
		head = head->next;
	}
}

void printCountries(country* root) {
	if (!root)
		return;

	printCountries(root->left);
	printf("%s:\n", root->name);
	printCities(root->cities);
	printCountries(root->right);
}

country* loadCountries(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("Greska 2");
		return NULL;
	}

	country* root = NULL;
	char name[MAX_LINE], filecity[MAX_LINE];

	while (fscanf(file, "%s %s\n", name, filecity) == 2) {
		country* new = createCountry(name);
		new->cities = loadCities(filecity);
		root = insertCountry(root, new);
	}

	fclose(file);
	return root;
}

void findCities(country* root, char* namecountry, int minPop) {
	if (!root)
		return;

	if (strcmp(namecountry, root->name) < 0)
		findCities(root->left, namecountry, minPop);
	else if (strcmp(namecountry, root->name) > 0)
		findCities(root->right, namecountry, minPop);
	else {
		printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", namecountry, minPop);
		city* current = root->cities;
		while (current) {
			if (current->population > minPop)
				printf("\t%s, %d\n", current->name, current->population);
			current = current->next;
		}
	}
}