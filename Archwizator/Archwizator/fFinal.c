#include "Struktury.h"

void MemoryRemove(katalog **NowyRoot, char *Path, char **FileNames, int argc) {
	if (Path)
		free(Path);
	if (NowyRoot)
		ZwolnijStukture(NowyRoot);
	if (FileNames)
		Free2DTab(&FileNames, argc - 2);
}

bool CzytajParametry(int argc, char **argv, char **Path, char ***FileNames) {
	if (argc < 2) {
		printf("SPROBOJ PONOWNIE!\n1.Jezeli chcesz zarchiwizowac pliki wykonaj.\n[Archiwizator.exe] [Sciezka docelowa folderu utworzonego w Archiwizatorze] [Nazwa pliku]\n2.Jesli chcesz przejrzec Archiwum wybierz:\n[Archiwizator.exe] -o\n");
		printf("3.Wymagane jest podawanie nazw katalogow oraz plikow bez uzycia spacji w nazwie\n");
		return false;
	}
	else if (argc == 2) {
		if (!strcmp(argv[1], "-o")) {
			return true;
		}
		else {
			printf("Podaj poprawny przelacznik!\n");
			return false;
		}
	}

	*Path = malloc(MAX_SIZE_FILENAME);
	strcpy(*Path, argv[1]);

	Init2DTab(&(*FileNames), argc - 2);
		for (int i = 0; i < argc - 2; i++)
			strcpy((*FileNames)[i], argv[i + 2]);
	return true;
}

void Menu(katalog **root) {
	char *Path = malloc(MAX_SIZE_FILENAME);
	int i = 1, result = 0; katalog *tmp;

	while (i) {

		while (true) {
			system("cls");
			WyswietlKatalogi(*root, 2);
			printf("Wykonaj dzialanie:\n0.Zakoncz\n1.Dodaj Katalog\n2.Usun Katalog\n3.Usun Plik\n4.Wyodrebnij plik na dysk\n");
			result = scanf("%i", &i);
			if (result != EOF && result != 0)
				break;
			else
				result = scanf("%*s");
		}
		if (i != 0) {
			printf("Podaj sciezke katalogu:\n");
			while (true) {
				result = scanf("%259s", Path);
				if (result != EOF && result != 0)
					break;
				else
					result = scanf("%*s");
				printf("Blad, podaj poprawnie!\n");
			}
		}

		switch (i) {
		case 1:
			if (!ZnajdzKatalog(*root, Path))
				DodajKatalog(root, Path);
			else {
				printf("Katalog o takiej nazwie juz istnieje, podaj inna nazwe\n");
				system("pause");
			}
			break;
		case 2:
			if (!UsunKatalog(root, Path))
				printERROR();
			break;
		case 3:
			tmp = ZnajdzKatalog(*root, Path);
			if (tmp) {
				printf("Podaj nazwe pliku:\n");
				while (true) {
					result = scanf("%259s", Path);
					if (result != EOF && result != 0)
						break;
					else
						result = scanf("%*s");
					printf("Blad, podaj poprawnie!\n");
				}
				if (!UsunPlik(&tmp->pFile, Path)) {
					printERROR();
					break;
				}
				else
					break;
			}
			else {
				printERROR();
				break;
			}
		case 4:
			tmp = ZnajdzKatalog(*root, Path);
			if (tmp) {
				printf("Podaj nazwe pliku:\n");
				while (true) {
					result = scanf("%259s", Path);
					if (result != EOF && result != 0)
						break;
					else
						result = scanf("%*s");
					printf("Blad, podaj poprawnie!\n");
				}
				
				if (ZnajdzPlik(tmp, Path)) {
					if (!WyodrebnijPlikNaDysk(&tmp, Path))
						printERROR();
				}
				else
					printERROR();
			}
			else
				printERROR();
			break;
		case 0:
			free(Path);
			return;
		default:
			printERROR();
			break;
		}
	}
}

