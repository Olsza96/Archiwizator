/**	
	@file
*/
#ifndef STRUKTURY_H
#define STRUKTURY_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/** Okre�la maksymaln� liczb� znak�w nazw plik�w i katalog�w. */
#define MAX_SIZE_FILENAME 261
/** Wielko�� tablicy dynamicznej przechowuj�cej format daty. */
#define DATA_FORMAT 20
/** Okre�la liczb� s��w do zainicjalizowania w tablicy s��w, potrzebnej do operowania na wydzielaniu �cie�ek katalogu. */
#define LiczbaNawigacji 3
/** �a�cuch znakowy okre�laj�cy nazw� archiwum, plik binarny przechowuj�cy zarchiwizowane dane. */
#define ARCHIWUM "Archiwum"
/** �a�cuch znakowy okre�laj�cy wyraz ko�cz�cy wydzielanie �cie�ek katalog�w. */
#define KONIEC "KONIEC"
/** Okre�la indeks w tablicy s��w pod kt�rym znajduje si� ostatni wyraz �cie�ki. */
#define catalog 2
/** Okre�la indeks w tablicy s��w pod kt�rym znajduje si� reszta �cie�ki po wydzieleniu. */
#define NowaSciezka 0
/** Okre�la indeks w tablicy s��w pod kt�rym znajduje si� pierwszy wyraz �cie�ki. */
#define wyciety 1
/** Okre�la liczb� znak�w jaka ma zosta� wpisana lub odczytana do lub z pliku. */
#define iloscZnakow 1

typedef FILE* file;

/** Struktura dynamiczna opisuj�ca plik. Jest w postaci listy jednokierunkowej.
	@param nazwa_pliku tablica znak�w przechowuj�ca nazw� pliku, ograniczona do 261 znak�w
	@param data_modyfikacji tablica znak�w przechowuj�ca dat� zarchiwizowania pliku, ograniczona do 20 znak�w
	@param rozmiar_pliku przechowuje liczb� znak�w odczytanych z pliku
	@param tresc_pliku wska�nik na tablic� dynamiczn� znak�w, kt�ra przechowuje zawarto�� odczytanego pliku
*/
typedef struct plik {
	char nazwa_pliku[MAX_SIZE_FILENAME],
		data_modyfikacji[DATA_FORMAT];
	unsigned int rozmiar_pliku;
	char *tresc_pliku;
	struct plik *pNextPlik;
} plik;

/** Struktura dynamiczna opisuj�ca katalog. Jest w postaci drzewa - BST z podwieszonymi listami jednokierunkowymi plik�w.
	@param nazwa_katalogu tablica znak�w przechowuj�ca nazw� katalogu, ograniczona do 261 znak�w
	@param sciezka wska�nik na tablic� dynamiczn� znak�w, kt�ra przechowuje lokalizacj� katalogu
*/
typedef struct katalog {
	char nazwa_katalogu[MAX_SIZE_FILENAME];
	char *sciezka;
	struct plik *pFile;
	struct katalog *pCatalog;
	struct katalog *pNextCatalog;
} katalog;

/** Funkcja odczytuje czas, kt�ry up�yn�� od 1970r. i na tej podstawie okre�la dat�, w kt�rej zosta� dodany plik do archiwum.
	@param godzina C-string, w kt�rym jest zapisywany format pobranego czasu
*/
void czas(char *godzina);

/** Funkcja zlicza ilo�� s��w w �cie�ce.
	@param s1 C-string, docelowo ma przyjmowa� �cie�ke do katalogu
	@return zwraca liczbe s��w
*/
size_t PoliczSlowa(char *s1);

/** Funkcja dzieli podawan� �cie�k� na pierwszy wyraz oraz reszt� �cie�ki nie modyfikuj�c orygina�u.
	@param sciezka C-string, z kt�rego wycinany jest wyraz
	@param wyrazWydzielony wska�nik na C-string, do kt�rego wpisywany jest wyraz wyci�ty
	@param nowaSciezka wska�nik na C-string, do kt�rego jest wpisywana reszta �cie�ki
*/
void Wytnij_poczatek(char *sciezka, char **wyrazWydzielony, char **nowaSciezka);

/** Funkcja wydziela z podawanej �cie�ki wyraz ostatni, nie modyfikuj�c orygina�u.
	@param Sciezka C-string, z kt�rego wydzielany jest ostatni wyraz
	@param wyrazWyciety wska�nik na C-string, do kt�rego jest wpisywany wydzielony wyraz
*/
void Wytnij_Koniec(char *Sciezka, char **wyrazWyciety);

/** Funkcja inicjalizuje tablice s��w.
	@param Dynamic wska�nik na dwuwymiarow� tablic�
	@param size liczba zawieraj�ca jak wiele miejsca na s�owa ma zosta� zainicjalizowane
*/
void Init2DTab(char ***Dynamic, int size);

/** Funkcja zwalnia pami�� tablicy s��w.
	@param Dynamic wska�nik na dwuwymiarow� tablic�
	@param size liczba zawieraj�ca jak wiele pami�ci zostanie zwolnione
*/
void Free2DTab(char ***Dynamic, int size);

/** Funkcja zliczaj�ca liczbe plik�w w danym w�le drzewa-BST.
	@param root wska�nik na korze� drzewa katalog�w
	@return zwraca liczb� znalezionych plik�w w w�le
*/
int PoliczPliki(katalog *root);

/** Funkcja wypisuje na ekran informacje o b��dzie.
*/
void printERROR();


/** Funkcja wype�nia strukture pliku danymi.
	@param pNowy wska�nik na liste plik�w w danym w�le drzewa-BST
	@param filename C-string zawieraj�cy nazwe pliku
	@param data_modyfikacji C-string zawieraj�cy dat� odczytania pliku
	@param rozmiar przechowuje liczb� element�w sczytanych z pliku
	@param tresc C-string przechowuj�cy zawarto�� odczytanego pliku
	@return zwraca wska�nik na utworzony element pliku
*/
plik* WypelnijPlik(plik *pNowy, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc);

/** Funkcja dodaje nowy element do listy plik�w w spos�b posortowany wzgl�dem nazwy pliku
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST 
	@param filename C-string zawieraj�cy nazwe pliku
	@param data_modyfikacji C-string zawieraj�cy dat� odczytania pliku
	@param rozmiar przechowuje liczb� element�w sczytanych z pliku
	@param tresc C-string przechowuj�cy zawarto�� odczytanego pliku
	@return zwraca prawd�, gdy element zosta� dodany poprawnie w przeciwnym wypadku zwraca fa�sz
*/
bool DodajPlik(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc);

/** Funkcja odczytuje plik do zarchiwizowania.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST 
	@param filename C-string zawieraj�cy nazw� pliku
	@param Sciezka lokalizacja, w kt�rej ma zosta� umieszczony odczytany plik
	@return zwraca 0 w przypadku, gdy plik do odczytu nie istnieje, -1 gdy nie zosta� dodany poprawnie, 1 gdy plik zosta� odczytany i dodany poprawnie
*/
int OdczytajPlik(katalog **root, const char* filename, char *Sciezka);

/** Funkcja usuwa plik ze listy plik�w na podstawie nazwy pliku.
	@param head wska�nik na oryginalny wska�nik listy plik�w
	@param filename C-string zawieraj�cy nazw� pliku
	@return zwraca 1 - w przypadku poprawnego wykonania funkcji, 0 - gdy usuni�cie pliku nie by�o mo�liwe
*/
int UsunPlik(plik **head, const char *filename);

/** Funkcja wy�wietla informacje zawarte li�cie plik�w.
	@param head oryginalny wska�nik na list� plik�w
	@param wciecie liczba okre�laj�ca z jak wielkim wci�ciem maj� zosta� wypisane informacje
*/
void Wyswietl_Plik(plik *head, int wciecie);

/** Funkcja znajduje plik w li�cie plik�w na podstawie nazwy.
	@param root wska�nik na drzewo katalog�w
	@param filename C-string zawieraj�cy nazw� pliku
	@return zwraca wska�nik na znaleziony element
*/
plik *ZnajdzPlik(katalog *root, const char *filename);

/** Funkcja na podstawie nazwy wyodr�bnia plik na dysk z archiwum.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param filename C-string zawieraj�cy nazw� pliku
	@return zwraca prawd� - gdy funkcja zostanie poprawnie wykonana, w momencie gdy nie ma pliku do wyodr�bnienia - fa�sz
*/
bool WyodrebnijPlikNaDysk(katalog **root, const char *filename);

/** Funkcja wype�nia element struktury katalog�w.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param catalogName C-string zawieraj�cy nazw� katalogu
	@param Sciezka C-string zawieraj�cy lokalizacj� katalogu
*/
void Wypelnij_Katalog(katalog **root, const char *catalogName, char *Sciezka);

/** Funkcja dodaje element do drzewa katalog�w wzgl�dem lokalizacji okre�lonej w �cie�ce.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param Sciezka C-string zawieraj�cy lokalizacj� katalogu
*/
void DodajKatalog(katalog **root, char *Sciezka);

/** Funkcja wypisuje na ekran wszystkie informacje zawarte w ca�ej strukturze.
	@param root wska�nik na drzewo katalog�w
	@param wciecie liczba okre�laj�ca z jak wielkim wci�ciem maj� zosta� wypisane informacje
*/
void WyswietlKatalogi(katalog *root, int wciecie);

/** Funkcja usuwa z pami�ci ca�� struktur�.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
*/
void ZwolnijStukture(katalog **root);

/** Funkcja usuwa z pami�ci w�ze� drzewa(katalog) oraz wszystkie lewe poddrzewa(katalogi w nim umieszczone) i doczepione listy plik�w. Katalog docelowy jest usuwany na podstawie podanej �cie�ki.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param Sciezka C-string zawieraj�cy lokalizacj� katalogu
	@return zwraca wartosc 1, gdy znaleziono katalog do usuni�cia, wartosc 0 gdy element nie zosta� znaleziony
*/
int UsunKatalog(katalog **root, char *Sciezka);

/** Funkcja wyszukuje katalog na podstawie podanej �cie�ki do katalogu.
	@param root wska�nik na drzewo katalog�w
	@param Sciezka C-string zawieraj�cy lokalizacj� katalogu
	@return zwraca wska�nik na znaleziony katalog
*/
katalog *ZnajdzKatalog(katalog *root, char *Sciezka);

/** Funkcja dodaje plik do katalogu na podstawie �cie�ki.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param filename C-string zawieraj�cy nazw� pliku
	@param data_modyfikacji C-string zawieraj�cy dat� odczytania pliku
	@param rozmiar przechowuje liczb� element�w sczytanych z pliku
	@param tresc C-string przechowuj�cy zawarto�� odczytanego pliku
	@param Sciezka C-string zawieraj�cy lokalizacj� katalogu
	@return zwraca - prawd�, gdy plik zosta� dodany poprawnie do katalogu. Fa�sz - katalog nie zosta� znaleziony
*/
bool PlikDoKatalogu(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc, char *Sciezka);

/** Funkcja wpisuje do pliku binarnego(archiwum) zawarto�� listy plik�w.
	@param head wska�nik na list� plik�w
	@param pfile wska�nik na plik binarny
	@param liczbaPlikow przechowuje liczb� plik�w do wpisania
*/
void WpiszPlikDoArchiwum(plik *head, file pfile, int liczbaPlikow);

/** Funkcja wpisuje do pliku binarnego(archiwum) zawarto�� ca�ej struktury, wszystkie drzewa katalog�w i listy plik�w.
	@param root wska�nik na drzewo katalog�w
	@param pfile wska�nik na plik binarny
*/
void WypelnijArchiwum(katalog *root, file pfile);

/** Funkcja otwiera plik binarny i wykonuje funkcje WypelnijArchiwum.
	@see WypelnijArchiwum(katalog *root, file pfile)
	@param root wska�nik na drzewo katalog�w
	@return zwraca prawd� je�li funkcja wykona�a si� poprawnie, fa�sz - nie istnieje struktura do wpisania
*/
bool ZapiszStruktureWArchiwum(katalog *root);

/** Funkcja odczytuje informacje o zarchiwizowanych plikach w pliku binarnym(archiwum) i dodaje element do struktury
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param prfile wska�nik na plik binarny(archiwum)
*/
void OdczytajPlikiKataloguZArchiwum(katalog **root, file prfile);

/** Funkcja odczytuje informacje o zarchiwizowanych katalogach i plikach w nich zawartych. Na tej podstawie wype�nia strukture elementami.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param pFile wska�nik na plik binarny(archiwum)
	@return zwraca prawd�, gdy element zostanie odczytany w przeciwnym wypadku fa�sz
*/
bool OdczytajStrukture(katalog **root, file pFile);

/** Funkcja otwiera archiwum i wykonuje OdczytajStrukture.
	@see OdczytajStrukture(katalog **root, file pFile)
	@param NowyRoot wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@return zwraca prawd�, gdy wykonana si� poprawnie, w przypadku braku archiwum lub pustego archiuwm zwraca fa�sz
*/
bool PobierzArchiwum(katalog **NowyRoot);

/** Funkcja g��wna programu. Wy�wietla na ekran zawarto�� struktury i podaje u�ytkownikowi opcje wyboru do wykonania na danych zawartych w strukturze oraz je wykonuje przy pomocy funkcji pomocniczych.
	@param root wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
*/
void Menu(katalog **root);

/** Funkcja dostaje parametry jakimi s� prze��czniki oraz nazwy plik�w z lini polece�.
	@param argc ilo�� parametr�w z lini polece�
	@param argv tablica ci�gu znak�w z lini polece�
	@param Path zwraca odzielony fragment z argv reprezentuj�cy lokalizacj� katalogu
	@param FileNames zwraca nazwy plik�w wydzielone z argv
	@return zwraca prawd� je�li funkcja zosta�a wykonana prawid�owo lub zwraca fa�sz, gdy funkcja natrafi�a na b��dne dane
*/
bool CzytajParametry(int argc, char **argv, char **Path, char ***FileNames);

/** Funkcja tworzy plik binarny archiwum.
	@return zwraca prawd� kiedy archiwum zosta�o utowrzone lub fa�sz gdy archiwum ju� istnia�o
*/
bool UtworzArchiwum();

/** Funkcja zbiorczo zwalnia pami�� struktury, tablicy s��w oraz C-string w funkcji g��wnej main.
	@param NowyRoot wska�nik na oryginalny wska�nik struktury katalog�w drzewa-BST
	@param FileNames przyjmuje tablic� s��w, zawieraj�c� nazwy plik�w
	@param argc ilo�� parametr�w z lini polece�
*/
void MemoryRemove(katalog **NowyRoot, char *Path, char **FileNames, int argc);

#endif // !STRUKTURY_h