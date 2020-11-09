#include "Struktury.h"

bool WyodrebnijPlikNaDysk(katalog **root, const char *filename) {
	file pFile = fopen(filename, "wb");
	plik *fil = ZnajdzPlik(*root, filename);

	if (fil) {
		fwrite(fil->tresc_pliku, fil->rozmiar_pliku, iloscZnakow, pFile);
		fil = (*root)->pFile;
		UsunPlik(&fil, filename);
		(*root)->pFile = fil;
	}
	else {
		fclose(pFile);
		return false;
	}

	fclose(pFile);
	return true;
}

plik *ZnajdzPlik(katalog *root, const char *filename) {

	if (root->pFile) {
		if (!strcmp(root->pFile->nazwa_pliku, filename))
			return root->pFile;
		else {
			plik *tmp = root->pFile->pNextPlik;
			while (tmp) {
				if (!strcmp(tmp->nazwa_pliku, filename))
					return tmp;
				tmp = tmp->pNextPlik;
			}
			return NULL;
		}
	}
	else
		return NULL;
}

int UsunPlik(plik **head, const char *filename) {
	int flag = 0;
	if (!(*head))
		return flag;

	if (!strcmp((*head)->nazwa_pliku, filename)) {
		plik *tmp = (*head)->pNextPlik;
		free((*head)->tresc_pliku);
		free((*head));
		(*head) = tmp;
		flag = 1;
	}
	else {
		plik *p = (*head);
		while (p && p->pNextPlik) {

			if (!strcmp(p->pNextPlik->nazwa_pliku, filename)) {
				plik *q = p->pNextPlik;
				p->pNextPlik = p->pNextPlik->pNextPlik;
				
				free(q->tresc_pliku);
				free(q);
				flag = 1;
			}
			p = p->pNextPlik;
		}
	}
	return flag;
}

void Wyswietl_Plik(plik *head, int wciecie) {

	if (!(head)) {
		printf("Brak danych\n");
		return;
	}
	plik *p = head;
	char Format[DATA_FORMAT * 5];
	sprintf(Format, "%%%ds", wciecie * 4);

	while (p) {
		printf(Format, "");printf("[Nazwa pliku] %s\n", p->nazwa_pliku);
		printf(Format, ""); printf("[Data dodania] %s\n", p->data_modyfikacji);
		printf(Format, ""); printf("[Rozmiar] %i B\n", p->rozmiar_pliku);
		printf(Format, ""); printf("[Zawartosc] %X\n\n", p->tresc_pliku);
		p = p->pNextPlik;
	}
}

plik* WypelnijPlik(plik *pNowy, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc) {
	pNowy = malloc(sizeof(plik));
	pNowy->tresc_pliku = malloc(rozmiar + 1);
	memset(pNowy->tresc_pliku, 0, rozmiar + 1);

	pNowy->rozmiar_pliku = rozmiar;
	strcpy(pNowy->nazwa_pliku, filename);
	strcpy(pNowy->data_modyfikacji, data_modyfikacji);
	memcpy(pNowy->tresc_pliku, tresc, rozmiar);

	return pNowy;
}

bool PlikDoKatalogu(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc, char *Sciezka) {
	
	if (*root) {

		katalog *current = ZnajdzKatalog(*root, Sciezka);
		if (!current)
			return false;
		if (strcmp((*root)->nazwa_katalogu, current->nazwa_katalogu))
			if (PlikDoKatalogu(&(*root)->pCatalog, filename, data_modyfikacji, rozmiar, tresc, Sciezka))
				return true;
		if (strcmp((*root)->nazwa_katalogu, current->nazwa_katalogu))
			if (PlikDoKatalogu(&(*root)->pNextCatalog, filename, data_modyfikacji, rozmiar, tresc, Sciezka))
				return true;

		if (!DodajPlik(root, filename, data_modyfikacji, rozmiar, tresc))
			return false;
		
		return true;
	}
	return false;
}

bool DodajPlik(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc) {

	if (!(*root)->pFile) { 
		plik *pNowy = NULL; 
		pNowy = WypelnijPlik(pNowy, filename, data_modyfikacji, rozmiar, tresc);
		pNowy->pNextPlik = NULL;
		(*root)->pFile = pNowy;

		return true;
	}
	else {

		if (strcmp(filename, (*root)->pFile->nazwa_pliku) < 0) { 
			plik *pNowy = NULL;
			pNowy = WypelnijPlik(pNowy, filename, data_modyfikacji, rozmiar, tresc);
			pNowy->pNextPlik = (*root)->pFile;
			(*root)->pFile = pNowy;
		}
		else {
			plik *tmp = (*root)->pFile;

			while (tmp->pNextPlik && strcmp(filename, tmp->pNextPlik->nazwa_pliku) > 0) //filename > tmp->next->nazwa
				tmp = tmp->pNextPlik;

			if (!tmp->pNextPlik) {
				tmp->pNextPlik = WypelnijPlik(tmp->pNextPlik, filename, data_modyfikacji, rozmiar, tresc);
				tmp->pNextPlik->pNextPlik = NULL;
			}
			else {
				plik *pNowy = NULL;
				pNowy = WypelnijPlik(pNowy, filename, data_modyfikacji, rozmiar, tresc);
				pNowy->pNextPlik = tmp->pNextPlik;
				tmp->pNextPlik = pNowy;
			}
		}
		return true;
	}
	return false;
}

int OdczytajPlik(katalog **root, const char* filename, char *Sciezka) {
	file pfile = fopen(filename, "rb");
	unsigned int result = 0;

	if (pfile) {
		fseek(pfile, 0, SEEK_END);
		unsigned int flong = ftell(pfile);
		rewind(pfile);

		char *timee = (char*)malloc(60 * sizeof(char));
		czas(timee);

		char *tresc = malloc(flong + 1);
		result = (int)fread(tresc, 1, flong, pfile);

		if (!PlikDoKatalogu(root, filename, timee, result, tresc, Sciezka)) {
			free(timee);
			free(tresc);
			return -1;
		}

		free(timee);
		free(tresc);

		return 1;
	}

	return 0;
}