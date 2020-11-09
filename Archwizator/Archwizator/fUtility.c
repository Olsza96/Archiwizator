#include "Struktury.h"

void czas(char *godzina) {
	time_t czas;
	struct tm * data;
	time(&czas);
	data = localtime(&czas);

	strftime(godzina, 60, "%x %X", data);
}

size_t PoliczSlowa(char *s1) {
	size_t liczbaSlow = 1;

	for (int i = 0; i < strlen(s1); i++) {
		if (s1[i] == '/')
			liczbaSlow++;
	}
	return liczbaSlow;
}

void Wytnij_poczatek(char *sciezka, char **wyrazWydzielony,char **nowaSciezka) {
	strcpy(*wyrazWydzielony, sciezka);
	if (PoliczSlowa(sciezka) == 1) {
		strcpy(*wyrazWydzielony, sciezka);
		strcpy(*nowaSciezka, KONIEC);
	}
	else {
		char *p = strpbrk(sciezka, "/");
		strcpy(*nowaSciezka, p + 1);
		strtok(*wyrazWydzielony, "/");
	}
}

void Wytnij_Koniec(char *Sciezka, char **wyrazWyciety) {

	if (PoliczSlowa(Sciezka) == 1)
		strcpy(*wyrazWyciety, Sciezka);
	else {
		char *tmp;
		tmp = strrchr(Sciezka, '/');
		strcpy(*wyrazWyciety, tmp + 1);
	}
}

void Init2DTab(char ***Dynamic, int size) {
	*Dynamic = malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		(*Dynamic)[i] = malloc(MAX_SIZE_FILENAME * sizeof(char));
		memset((*Dynamic)[i], 0, MAX_SIZE_FILENAME);
	}
}

void Free2DTab(char ***Dynamic,int size) {
	for (int i = 0; i < size; i++) {
		if ((*Dynamic)[i]) {
			free((*Dynamic)[i]);
			memset((*Dynamic)[i], 0, MAX_SIZE_FILENAME);
		}
	}
	free(*Dynamic);
	*Dynamic = NULL;
}

int PoliczPliki(katalog *root) {
	int countPlik = 0;
	if (root) {
		plik *tmp = root->pFile;
		while (tmp) {
			tmp = tmp->pNextPlik;
			countPlik++;
		}
	}
	return countPlik;
}

void printERROR() {
	printf("Nie ma takiej nazwy, sproboj ponownie\n");
	system("pause");
}