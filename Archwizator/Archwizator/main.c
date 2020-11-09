#include "Struktury.h"

int main(int argc, char **argv) {
	katalog *NowyRoot = NULL;
	char *Path = NULL, **FileNames = NULL;
	
	if (!PobierzArchiwum(&NowyRoot)) {
		printf("Brak Archiwum\n");
		if (!UtworzArchiwum()) {
			printf("Archiwum jest puste, musisz najpierw dodac katalog\n");
			return 0;
		}
		else {
			printf("Tworze Archiwum...\nSproboj ponownie\n");
			return 0;
		}
	}

	if (!CzytajParametry(argc, argv, &Path, &FileNames)) {
		MemoryRemove(&NowyRoot, Path, FileNames, argc);
		return 0;
	}

	if (!strcmp(argv[1], "-o")) {
		Menu(&NowyRoot);
		if (!ZapiszStruktureWArchiwum(NowyRoot))
			printf("Puste archiwum\n");
		MemoryRemove(&NowyRoot, Path, FileNames, argc);
		return 0;
	}

	for (int i = 0; i < argc - 2; i++) {
		if (!ZnajdzPlik(ZnajdzKatalog(NowyRoot, Path), FileNames[i])) {

			int prawda = OdczytajPlik(&NowyRoot, FileNames[i], Path);
			if (prawda == -1) {
				printf("Nie ma takiego katalogu\n");
				MemoryRemove(&NowyRoot, Path, FileNames, argc);
				return 0;
			}
			else if (prawda == 0) {
				if (i + 1 < argc - 2);
				else {
					printf("Nie ma takiego pliku\n");
					MemoryRemove(&NowyRoot, Path, FileNames, argc);
					return 0;
				}
			}
		}
	}

	Menu(&NowyRoot);
	if (!ZapiszStruktureWArchiwum(NowyRoot))
		printf("Puste archiwum\n");
	MemoryRemove(&NowyRoot, Path, FileNames, argc);
	return 0;
}