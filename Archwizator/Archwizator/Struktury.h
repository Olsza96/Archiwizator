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

/** Okreœla maksymaln¹ liczbê znaków nazw plików i katalogów. */
#define MAX_SIZE_FILENAME 261
/** Wielkoœæ tablicy dynamicznej przechowuj¹cej format daty. */
#define DATA_FORMAT 20
/** Okreœla liczbê s³ów do zainicjalizowania w tablicy s³ów, potrzebnej do operowania na wydzielaniu œcie¿ek katalogu. */
#define LiczbaNawigacji 3
/** £añcuch znakowy okreœlaj¹cy nazwê archiwum, plik binarny przechowuj¹cy zarchiwizowane dane. */
#define ARCHIWUM "Archiwum"
/** £añcuch znakowy okreœlaj¹cy wyraz koñcz¹cy wydzielanie œcie¿ek katalogów. */
#define KONIEC "KONIEC"
/** Okreœla indeks w tablicy s³ów pod którym znajduje siê ostatni wyraz œcie¿ki. */
#define catalog 2
/** Okreœla indeks w tablicy s³ów pod którym znajduje siê reszta œcie¿ki po wydzieleniu. */
#define NowaSciezka 0
/** Okreœla indeks w tablicy s³ów pod którym znajduje siê pierwszy wyraz œcie¿ki. */
#define wyciety 1
/** Okreœla liczbê znaków jaka ma zostaæ wpisana lub odczytana do lub z pliku. */
#define iloscZnakow 1

typedef FILE* file;

/** Struktura dynamiczna opisuj¹ca plik. Jest w postaci listy jednokierunkowej.
	@param nazwa_pliku tablica znaków przechowuj¹ca nazwê pliku, ograniczona do 261 znaków
	@param data_modyfikacji tablica znaków przechowuj¹ca datê zarchiwizowania pliku, ograniczona do 20 znaków
	@param rozmiar_pliku przechowuje liczbê znaków odczytanych z pliku
	@param tresc_pliku wskaŸnik na tablicê dynamiczn¹ znaków, która przechowuje zawartoœæ odczytanego pliku
*/
typedef struct plik {
	char nazwa_pliku[MAX_SIZE_FILENAME],
		data_modyfikacji[DATA_FORMAT];
	unsigned int rozmiar_pliku;
	char *tresc_pliku;
	struct plik *pNextPlik;
} plik;

/** Struktura dynamiczna opisuj¹ca katalog. Jest w postaci drzewa - BST z podwieszonymi listami jednokierunkowymi plików.
	@param nazwa_katalogu tablica znaków przechowuj¹ca nazwê katalogu, ograniczona do 261 znaków
	@param sciezka wskaŸnik na tablicê dynamiczn¹ znaków, która przechowuje lokalizacjê katalogu
*/
typedef struct katalog {
	char nazwa_katalogu[MAX_SIZE_FILENAME];
	char *sciezka;
	struct plik *pFile;
	struct katalog *pCatalog;
	struct katalog *pNextCatalog;
} katalog;

/** Funkcja odczytuje czas, który up³yn¹³ od 1970r. i na tej podstawie okreœla datê, w której zosta³ dodany plik do archiwum.
	@param godzina C-string, w którym jest zapisywany format pobranego czasu
*/
void czas(char *godzina);

/** Funkcja zlicza iloœæ s³ów w œcie¿ce.
	@param s1 C-string, docelowo ma przyjmowaæ œcie¿ke do katalogu
	@return zwraca liczbe s³ów
*/
size_t PoliczSlowa(char *s1);

/** Funkcja dzieli podawan¹ œcie¿kê na pierwszy wyraz oraz resztê œcie¿ki nie modyfikuj¹c orygina³u.
	@param sciezka C-string, z którego wycinany jest wyraz
	@param wyrazWydzielony wskaŸnik na C-string, do którego wpisywany jest wyraz wyciêty
	@param nowaSciezka wskaŸnik na C-string, do którego jest wpisywana reszta œcie¿ki
*/
void Wytnij_poczatek(char *sciezka, char **wyrazWydzielony, char **nowaSciezka);

/** Funkcja wydziela z podawanej œcie¿ki wyraz ostatni, nie modyfikuj¹c orygina³u.
	@param Sciezka C-string, z którego wydzielany jest ostatni wyraz
	@param wyrazWyciety wskaŸnik na C-string, do którego jest wpisywany wydzielony wyraz
*/
void Wytnij_Koniec(char *Sciezka, char **wyrazWyciety);

/** Funkcja inicjalizuje tablice s³ów.
	@param Dynamic wskaŸnik na dwuwymiarow¹ tablicê
	@param size liczba zawieraj¹ca jak wiele miejsca na s³owa ma zostaæ zainicjalizowane
*/
void Init2DTab(char ***Dynamic, int size);

/** Funkcja zwalnia pamiêæ tablicy s³ów.
	@param Dynamic wskaŸnik na dwuwymiarow¹ tablicê
	@param size liczba zawieraj¹ca jak wiele pamiêci zostanie zwolnione
*/
void Free2DTab(char ***Dynamic, int size);

/** Funkcja zliczaj¹ca liczbe plików w danym wêŸle drzewa-BST.
	@param root wskaŸnik na korzeñ drzewa katalogów
	@return zwraca liczbê znalezionych plików w wêŸle
*/
int PoliczPliki(katalog *root);

/** Funkcja wypisuje na ekran informacje o b³êdzie.
*/
void printERROR();


/** Funkcja wype³nia strukture pliku danymi.
	@param pNowy wskaŸnik na liste plików w danym wêŸle drzewa-BST
	@param filename C-string zawieraj¹cy nazwe pliku
	@param data_modyfikacji C-string zawieraj¹cy datê odczytania pliku
	@param rozmiar przechowuje liczbê elementów sczytanych z pliku
	@param tresc C-string przechowuj¹cy zawartoœæ odczytanego pliku
	@return zwraca wskaŸnik na utworzony element pliku
*/
plik* WypelnijPlik(plik *pNowy, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc);

/** Funkcja dodaje nowy element do listy plików w sposób posortowany wzglêdem nazwy pliku
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST 
	@param filename C-string zawieraj¹cy nazwe pliku
	@param data_modyfikacji C-string zawieraj¹cy datê odczytania pliku
	@param rozmiar przechowuje liczbê elementów sczytanych z pliku
	@param tresc C-string przechowuj¹cy zawartoœæ odczytanego pliku
	@return zwraca prawdê, gdy element zosta³ dodany poprawnie w przeciwnym wypadku zwraca fa³sz
*/
bool DodajPlik(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc);

/** Funkcja odczytuje plik do zarchiwizowania.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST 
	@param filename C-string zawieraj¹cy nazwê pliku
	@param Sciezka lokalizacja, w której ma zostaæ umieszczony odczytany plik
	@return zwraca 0 w przypadku, gdy plik do odczytu nie istnieje, -1 gdy nie zosta³ dodany poprawnie, 1 gdy plik zosta³ odczytany i dodany poprawnie
*/
int OdczytajPlik(katalog **root, const char* filename, char *Sciezka);

/** Funkcja usuwa plik ze listy plików na podstawie nazwy pliku.
	@param head wskaŸnik na oryginalny wskaŸnik listy plików
	@param filename C-string zawieraj¹cy nazwê pliku
	@return zwraca 1 - w przypadku poprawnego wykonania funkcji, 0 - gdy usuniêcie pliku nie by³o mo¿liwe
*/
int UsunPlik(plik **head, const char *filename);

/** Funkcja wyœwietla informacje zawarte liœcie plików.
	@param head oryginalny wskaŸnik na listê plików
	@param wciecie liczba okreœlaj¹ca z jak wielkim wciêciem maj¹ zostaæ wypisane informacje
*/
void Wyswietl_Plik(plik *head, int wciecie);

/** Funkcja znajduje plik w liœcie plików na podstawie nazwy.
	@param root wskaŸnik na drzewo katalogów
	@param filename C-string zawieraj¹cy nazwê pliku
	@return zwraca wskaŸnik na znaleziony element
*/
plik *ZnajdzPlik(katalog *root, const char *filename);

/** Funkcja na podstawie nazwy wyodrêbnia plik na dysk z archiwum.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param filename C-string zawieraj¹cy nazwê pliku
	@return zwraca prawdê - gdy funkcja zostanie poprawnie wykonana, w momencie gdy nie ma pliku do wyodrêbnienia - fa³sz
*/
bool WyodrebnijPlikNaDysk(katalog **root, const char *filename);

/** Funkcja wype³nia element struktury katalogów.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param catalogName C-string zawieraj¹cy nazwê katalogu
	@param Sciezka C-string zawieraj¹cy lokalizacjê katalogu
*/
void Wypelnij_Katalog(katalog **root, const char *catalogName, char *Sciezka);

/** Funkcja dodaje element do drzewa katalogów wzglêdem lokalizacji okreœlonej w œcie¿ce.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param Sciezka C-string zawieraj¹cy lokalizacjê katalogu
*/
void DodajKatalog(katalog **root, char *Sciezka);

/** Funkcja wypisuje na ekran wszystkie informacje zawarte w ca³ej strukturze.
	@param root wskaŸnik na drzewo katalogów
	@param wciecie liczba okreœlaj¹ca z jak wielkim wciêciem maj¹ zostaæ wypisane informacje
*/
void WyswietlKatalogi(katalog *root, int wciecie);

/** Funkcja usuwa z pamiêci ca³¹ strukturê.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
*/
void ZwolnijStukture(katalog **root);

/** Funkcja usuwa z pamiêci wêze³ drzewa(katalog) oraz wszystkie lewe poddrzewa(katalogi w nim umieszczone) i doczepione listy plików. Katalog docelowy jest usuwany na podstawie podanej œcie¿ki.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param Sciezka C-string zawieraj¹cy lokalizacjê katalogu
	@return zwraca wartosc 1, gdy znaleziono katalog do usuniêcia, wartosc 0 gdy element nie zosta³ znaleziony
*/
int UsunKatalog(katalog **root, char *Sciezka);

/** Funkcja wyszukuje katalog na podstawie podanej œcie¿ki do katalogu.
	@param root wskaŸnik na drzewo katalogów
	@param Sciezka C-string zawieraj¹cy lokalizacjê katalogu
	@return zwraca wskaŸnik na znaleziony katalog
*/
katalog *ZnajdzKatalog(katalog *root, char *Sciezka);

/** Funkcja dodaje plik do katalogu na podstawie œcie¿ki.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param filename C-string zawieraj¹cy nazwê pliku
	@param data_modyfikacji C-string zawieraj¹cy datê odczytania pliku
	@param rozmiar przechowuje liczbê elementów sczytanych z pliku
	@param tresc C-string przechowuj¹cy zawartoœæ odczytanego pliku
	@param Sciezka C-string zawieraj¹cy lokalizacjê katalogu
	@return zwraca - prawdê, gdy plik zosta³ dodany poprawnie do katalogu. Fa³sz - katalog nie zosta³ znaleziony
*/
bool PlikDoKatalogu(katalog **root, const char *filename, char *data_modyfikacji, unsigned int rozmiar, char *tresc, char *Sciezka);

/** Funkcja wpisuje do pliku binarnego(archiwum) zawartoœæ listy plików.
	@param head wskaŸnik na listê plików
	@param pfile wskaŸnik na plik binarny
	@param liczbaPlikow przechowuje liczbê plików do wpisania
*/
void WpiszPlikDoArchiwum(plik *head, file pfile, int liczbaPlikow);

/** Funkcja wpisuje do pliku binarnego(archiwum) zawartoœæ ca³ej struktury, wszystkie drzewa katalogów i listy plików.
	@param root wskaŸnik na drzewo katalogów
	@param pfile wskaŸnik na plik binarny
*/
void WypelnijArchiwum(katalog *root, file pfile);

/** Funkcja otwiera plik binarny i wykonuje funkcje WypelnijArchiwum.
	@see WypelnijArchiwum(katalog *root, file pfile)
	@param root wskaŸnik na drzewo katalogów
	@return zwraca prawdê jeœli funkcja wykona³a siê poprawnie, fa³sz - nie istnieje struktura do wpisania
*/
bool ZapiszStruktureWArchiwum(katalog *root);

/** Funkcja odczytuje informacje o zarchiwizowanych plikach w pliku binarnym(archiwum) i dodaje element do struktury
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param prfile wskaŸnik na plik binarny(archiwum)
*/
void OdczytajPlikiKataloguZArchiwum(katalog **root, file prfile);

/** Funkcja odczytuje informacje o zarchiwizowanych katalogach i plikach w nich zawartych. Na tej podstawie wype³nia strukture elementami.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param pFile wskaŸnik na plik binarny(archiwum)
	@return zwraca prawdê, gdy element zostanie odczytany w przeciwnym wypadku fa³sz
*/
bool OdczytajStrukture(katalog **root, file pFile);

/** Funkcja otwiera archiwum i wykonuje OdczytajStrukture.
	@see OdczytajStrukture(katalog **root, file pFile)
	@param NowyRoot wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@return zwraca prawdê, gdy wykonana siê poprawnie, w przypadku braku archiwum lub pustego archiuwm zwraca fa³sz
*/
bool PobierzArchiwum(katalog **NowyRoot);

/** Funkcja g³ówna programu. Wyœwietla na ekran zawartoœæ struktury i podaje u¿ytkownikowi opcje wyboru do wykonania na danych zawartych w strukturze oraz je wykonuje przy pomocy funkcji pomocniczych.
	@param root wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
*/
void Menu(katalog **root);

/** Funkcja dostaje parametry jakimi s¹ prze³¹czniki oraz nazwy plików z lini poleceñ.
	@param argc iloœæ parametrów z lini poleceñ
	@param argv tablica ci¹gu znaków z lini poleceñ
	@param Path zwraca odzielony fragment z argv reprezentuj¹cy lokalizacjê katalogu
	@param FileNames zwraca nazwy plików wydzielone z argv
	@return zwraca prawdê jeœli funkcja zosta³a wykonana prawid³owo lub zwraca fa³sz, gdy funkcja natrafi³a na b³êdne dane
*/
bool CzytajParametry(int argc, char **argv, char **Path, char ***FileNames);

/** Funkcja tworzy plik binarny archiwum.
	@return zwraca prawdê kiedy archiwum zosta³o utowrzone lub fa³sz gdy archiwum ju¿ istnia³o
*/
bool UtworzArchiwum();

/** Funkcja zbiorczo zwalnia pamiêæ struktury, tablicy s³ów oraz C-string w funkcji g³ównej main.
	@param NowyRoot wskaŸnik na oryginalny wskaŸnik struktury katalogów drzewa-BST
	@param FileNames przyjmuje tablicê s³ów, zawieraj¹c¹ nazwy plików
	@param argc iloœæ parametrów z lini poleceñ
*/
void MemoryRemove(katalog **NowyRoot, char *Path, char **FileNames, int argc);

#endif // !STRUKTURY_h