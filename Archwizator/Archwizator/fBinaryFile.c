#include "Struktury.h"

bool UtworzArchiwum() {
	file prfile = fopen("Archiwum.bin", "rb");
	if (prfile) {
		fclose(prfile);
		return false;
	}
	else {
		file pFile = fopen("Archiwum.bin", "wb");
		fclose(pFile);
	}
	return true;
}

bool PobierzArchiwum(katalog **NowyRoot) {
	file prfile = fopen("Archiwum.bin", "rb");

	if (prfile) {
		if (!OdczytajStrukture(NowyRoot, prfile))
			return false;
	}
	else
		return false;
	fclose(prfile);
	
	return true;
}

bool OdczytajStrukture(katalog **root, file pFile) {

	char nazwaKatalogu[MAX_SIZE_FILENAME];
	int MaxSizeFilename = 0, path = 0, liczbaPlikow = 0;

	fread(&MaxSizeFilename, sizeof(MaxSizeFilename), iloscZnakow, pFile); if (!MaxSizeFilename) return false;
	fread(nazwaKatalogu, MaxSizeFilename, iloscZnakow, pFile);
	fread(&path, sizeof(path), iloscZnakow, pFile);
	char *sciezka = malloc(path + 1);
	memset(sciezka, 0, path + 1);
	fread(sciezka, path, iloscZnakow, pFile);
	fread(&liczbaPlikow, sizeof(liczbaPlikow), 1, pFile);

	DodajKatalog(root, sciezka);
	free(sciezka);
	sciezka = NULL;

	for (int i = 0; i < liczbaPlikow; i++)
		OdczytajPlikiKataloguZArchiwum(root, pFile);

	fread(&path, sizeof(path), iloscZnakow, pFile);
	sciezka = malloc(path + 1);
	memset(sciezka, 0, path + 1);

	fread(sciezka, path, iloscZnakow, pFile);

	if (!strcmp(sciezka, KONIEC)) {
		free(sciezka);
		sciezka = NULL;
		return true;
	}

	size_t pointer = strlen((*root)->sciezka);
	if (!strncmp((*root)->sciezka, sciezka, pointer))
		OdczytajStrukture(&(*root)->pCatalog, pFile);

	free(sciezka);
	OdczytajStrukture(&(*root)->pNextCatalog, pFile);

	return true;
}

void OdczytajPlikiKataloguZArchiwum(katalog **root, file prfile) {
	int liczbaPlikow = 0, MaxSizeFileName = 0, sizeData = 0, fsize = 0, content = 0;
	char *filename = malloc(MAX_SIZE_FILENAME), *data = malloc(DATA_FORMAT);

	fread(&MaxSizeFileName, sizeof(int), 1, prfile);
	fread(filename, MaxSizeFileName, 1, prfile);
	fread(&sizeData, sizeof(int), 1, prfile);
	fread(data, sizeData, 1, prfile);
	fread(&fsize, sizeof(fsize), 1, prfile);
	fread(&fsize, fsize, 1, prfile);
	fread(&content, sizeof(content), 1, prfile);
	char *tresc = malloc(content + 1);
	fread(tresc, content, 1, prfile);
	tresc[content] = '\0';

	DodajPlik(root, filename, data, fsize, tresc);

	free(tresc); free(filename); free(data);
}

void WpiszPlikDoArchiwum(plik *head, file pfile, int liczbaPlikow) {
	unsigned int MaxSizefileName = MAX_SIZE_FILENAME, sizeData = DATA_FORMAT, fsize = sizeof(head->rozmiar_pliku), content = 0;

	int i = 0;
	while (head && i < liczbaPlikow) {
		content = head->rozmiar_pliku;
		fwrite(&MaxSizefileName, sizeof(MaxSizefileName), iloscZnakow, pfile);
		fwrite(head->nazwa_pliku, MaxSizefileName, iloscZnakow, pfile);
		fwrite(&sizeData, sizeof(sizeData), iloscZnakow, pfile);
		fwrite(head->data_modyfikacji, sizeData, iloscZnakow, pfile);
		fwrite(&fsize, sizeof(fsize), iloscZnakow, pfile);
		fwrite(&head->rozmiar_pliku, fsize, iloscZnakow, pfile);
		fwrite(&content, sizeof(content), iloscZnakow, pfile);
		fwrite(head->tresc_pliku, content, iloscZnakow, pfile);

		head = head->pNextPlik; i++;
	}
}

void WypelnijArchiwum(katalog *root, file pfile) {

	if (root) {
		int MaxSizeFilename = MAX_SIZE_FILENAME, path = (int)strlen(root->sciezka);

		fwrite(&MaxSizeFilename, sizeof(MaxSizeFilename), iloscZnakow, pfile);
		fwrite(root->nazwa_katalogu, MaxSizeFilename, iloscZnakow, pfile);
		fwrite(&path, sizeof(path), iloscZnakow, pfile);
		fwrite(root->sciezka, path, iloscZnakow, pfile);

		int liczbaPlikow = PoliczPliki(root);
		fwrite(&liczbaPlikow, sizeof(liczbaPlikow), iloscZnakow, pfile);
		if (root->pFile)
			WpiszPlikDoArchiwum(root->pFile, pfile, liczbaPlikow);

		path = (int)strlen(KONIEC); katalog *p = root;
		char *tmp = malloc(path + 1);
		strcpy(tmp, KONIEC);

		if (p->pCatalog) {
			path = (int)strlen(p->pCatalog->sciezka);
			p = p->pCatalog;
			fwrite(&path, sizeof(path), iloscZnakow, pfile);
			fwrite(p->sciezka, path, iloscZnakow, pfile);
		}
		else if (p->pNextCatalog) {
			path = (int)strlen(p->pNextCatalog->sciezka);
			p = p->pNextCatalog;
			fwrite(&path, sizeof(path), iloscZnakow, pfile);
			fwrite(p->sciezka, path, iloscZnakow, pfile);
		}
		else {
			fwrite(&path, sizeof(path), iloscZnakow, pfile);
			fwrite(tmp, path, iloscZnakow, pfile);
		}
		free(tmp);

		WypelnijArchiwum(root->pCatalog, pfile);
		WypelnijArchiwum(root->pNextCatalog, pfile);
	}
}

bool ZapiszStruktureWArchiwum(katalog *root) {
	file pFile = fopen("Archiwum.bin", "wb");

	if (root)
		WypelnijArchiwum(root, pFile);
	else
		return false;

	fclose(pFile);

	return true;
}
