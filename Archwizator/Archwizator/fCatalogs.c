#include "Struktury.h"

void ZwolnijStukture(katalog **root) {

	if ((*root)) {
		ZwolnijStukture(&(*root)->pCatalog);
		ZwolnijStukture(&(*root)->pNextCatalog);

		while ((*root)->pFile) {
			plik *p = (*root)->pFile->pNextPlik;
			free((*root)->pFile->tresc_pliku);
			free((*root)->pFile);
			(*root)->pFile = p;
		}
		free((*root)->sciezka);
		(*root)->sciezka = NULL;
		free(*root);
		*root = NULL;
	}
}

void WyswietlKatalogi(katalog *root, int wciecie) {
	katalog *p = root;
	if (p) {
		char Format[DATA_FORMAT * 3], Formar[DATA_FORMAT * 3];

		sprintf(Format, "%%%ds ", wciecie * 3);
		sprintf(Formar, "[%%%ds]\n", 3);

		printf(Format, p->nazwa_katalogu);
		printf(Formar, p->sciezka);

		plik *tmp = p->pFile;
		if (tmp)
			Wyswietl_Plik(tmp, wciecie - 1);

		WyswietlKatalogi(p->pCatalog, wciecie + 2);
		WyswietlKatalogi(p->pNextCatalog, wciecie);
	}
}

katalog *ZnajdzKatalog(katalog *root, char *Sciezka) {
	katalog *p = root;
	char **Path;
	Init2DTab(&Path, LiczbaNawigacji);

	Wytnij_poczatek(Sciezka, &Path[wyciety], &Path[NowaSciezka]);
	Wytnij_Koniec(Sciezka, &Path[catalog]);

	while (p) {
		if (!strcmp(p->nazwa_katalogu, Path[catalog])) {
			Free2DTab(&Path, LiczbaNawigacji);
			return p;
		}
		if (!strcmp(p->nazwa_katalogu, Path[wyciety])) {
			p = p->pCatalog;
			Wytnij_poczatek(Path[NowaSciezka], &Path[wyciety], &Path[NowaSciezka]);
		}
		else
			p = p->pNextCatalog;
	}

	Free2DTab(&Path, LiczbaNawigacji);
	return NULL;
}

int UsunKatalog(katalog **root, char *Sciezka) {
	int flag = 0;
	if (*root) {
		
		char **Nawigacja;
		Init2DTab(&Nawigacja, LiczbaNawigacji);
		Wytnij_poczatek(Sciezka, &Nawigacja[wyciety], &Nawigacja[NowaSciezka]);
		Wytnij_Koniec(Sciezka, &Nawigacja[catalog]);

		if ((*root)->pNextCatalog == NULL && !strcmp((*root)->nazwa_katalogu, Nawigacja[catalog])) {
			ZwolnijStukture(root);
			Free2DTab(&Nawigacja, LiczbaNawigacji);
			flag = 1;
			return flag;
		}
		else if ((*root)->pNextCatalog && !strcmp((*root)->nazwa_katalogu, Nawigacja[catalog])) {
			katalog *tmp = (*root)->pNextCatalog;
			(*root)->pNextCatalog = NULL;
			ZwolnijStukture(root);
			(*root) = tmp;
			Free2DTab(&Nawigacja, LiczbaNawigacji);
			flag = 1;
			return flag;
		}
		else if (!strcmp((*root)->nazwa_katalogu, Nawigacja[wyciety])) {
			UsunKatalog(&(*root)->pCatalog, Nawigacja[NowaSciezka]);
			Free2DTab(&Nawigacja, LiczbaNawigacji);
			flag = 1;
			return flag;
		}

		katalog *iterator = *root;
		while(iterator && iterator->pNextCatalog){

			if (!strcmp(iterator->pNextCatalog->nazwa_katalogu, Nawigacja[catalog])) {	
				katalog *q = iterator->pNextCatalog->pNextCatalog;
				iterator->pNextCatalog->pNextCatalog = NULL;
				ZwolnijStukture(&iterator->pNextCatalog);
				iterator->pNextCatalog = q;
				flag = 1;
				break;
			}
			if (!strcmp(iterator->pNextCatalog->nazwa_katalogu, Nawigacja[wyciety])) {
				UsunKatalog(&(*root)->pNextCatalog->pCatalog, Nawigacja[NowaSciezka]);
				flag = 1;
				break;
			}
			else
				iterator = iterator->pNextCatalog;
		}

		Free2DTab(&Nawigacja, LiczbaNawigacji);
	}

	return flag;
}

void Wypelnij_Katalog(katalog **root, const char *catalogName, char *Sciezka) {
	katalog *tmp = malloc(sizeof(katalog));
	tmp->sciezka = malloc(strlen(Sciezka) + 1);
	memset(tmp->sciezka, 0, strlen(Sciezka) + 1);

	strcpy(tmp->nazwa_katalogu, catalogName);
	strcpy(tmp->sciezka, Sciezka);

	tmp->pFile = NULL;
	
	tmp->pCatalog = NULL;
	tmp->pNextCatalog = NULL;
	*root = tmp;
}

void DodajKatalog(katalog **root, char *Sciezka) {
	char **NamePaths;
	Init2DTab(&NamePaths, LiczbaNawigacji);
	Wytnij_Koniec(Sciezka, &NamePaths[catalog]);

	if (!(*root))
		Wypelnij_Katalog(root, NamePaths[catalog], Sciezka);
	else {
		katalog *p = *root;
		Wytnij_poczatek(Sciezka, &NamePaths[wyciety], &NamePaths[NowaSciezka]);
		while (true) {

			if (!strcmp(p->nazwa_katalogu, NamePaths[wyciety])) {
				if (p->pCatalog) {
					p = p->pCatalog;
					Wytnij_poczatek(NamePaths[NowaSciezka], &NamePaths[wyciety], &NamePaths[NowaSciezka]);
				}
				else {
					Wypelnij_Katalog(&p->pCatalog, NamePaths[catalog], Sciezka);
					break;
				}
			}
			else {
				if (p->pNextCatalog)
					p = p->pNextCatalog;
				else {
					Wypelnij_Katalog(&p->pNextCatalog, NamePaths[catalog], Sciezka);
					break;
				}
			}
		}
	}
	Free2DTab(&NamePaths, LiczbaNawigacji);
}