
#include <iostream>

#include <conio.h>

#include <windows.h>

#include <time.h>

using namespace std;





int y, x;                    //pozycja punktu [0][0] poruszanego klocka

char vv; int zz;             //do znakow i wybranej opcji w menu() i opcje()

char v;                     //do znaku z klawiatury w gra()

bool czynowy;               //czy stworzyc nowy klocek

int ktKlocek;               //ktory klocek z 'lista_klockow'

int noKlocek;               //ktory nowy klocek z 'lista_klockow'

int ktPozycja;              //ktora pozycja klocka z 'lista_klockow'

int stPozycja;              //w razie gdy klocek w 'ktPozycja' nie pasowal

int ktKolor;                //ktory kolor klocka

double czas;                //czas po jakim klocek znizy sie o jeden wiersz

time_t start_czas;          //od kiedy odmierzac 'czas'

time_t start_na_czas;       //od kiedy odmierzac 'na_czas'

int punkty;                 //uzyskane punkty z usuwania linii

int ile_linii;              //ile linii juz usunieto

int linie_pod_rzad;         //ile linii usunieto na raz



int yy = 20, xx = 10;            //dlugosc i szerokosc mapy

double czas_na_pocz = 2.0;    //poczatkowa wartosc 'czas'

int na_czas = 0;              //czas po jakim gra sie skonczy

int szybkosc = 10;            //co ile linii czas zmniejszy sie o sekunde

bool czy_nast_klocek = true;  //czy pokazac nastepny klocek





int** mapa1;                //mapa z postawionymi klockami

int** mapa2;                //mapa z postawionymi klockami, poruszanym klockem i "cieniem"

bool klocek[4][4];          //poruszany klocek



bool lista_klockow[7][4][4][4] =

{

    {

        {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},    //  X

        {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},    //  X

        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},    //  X

        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}     //  X

    },

    {

        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},    //  X

        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},    //  X

        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},    // XX

        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}     //

    },

    {

        {{0,0,1,0},{0,0,1,0},{0,0,1,1},{0,0,0,0}},    //  X

        {{0,0,0,1},{0,1,1,1},{0,0,0,0},{0,0,0,0}},    //  X

        {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}},    //  XX

        {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}}     //

    },

    {

        {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},    //

        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},    //  XX

        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},    // XX

        {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}     //

    },

    {

        {{0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}},    //

        {{0,0,0,1},{0,0,1,1},{0,0,1,0},{0,0,0,0}},    //  XX

        {{0,1,1,0},{0,0,1,1},{0,0,0,0},{0,0,0,0}},    //   XX

        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}     //

    },

    {

        {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},    //

        {{0,0,1,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},    //   X

        {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},    //  XXX

        {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}     //

    },

    {

        {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},    //

        {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},    //  XX

        {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},    //  XX

        {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}     //

    }

};



bool sprawdz();             //czy klocek pasuje czyli nie nachodzi na nic stalego

void ustaw_klocek(int, int); //( ktory klocek , ktora pozycja )

void wykonaj();             //seria zadan ktore sa wykonywane tylko 2 razy w petli

void pokaz();               //pokazuje mape i inne rzeczy



void menu();                //menu do wybrania gra(), opcje() lub wyjscia z gry

void gra();                 //stworzenie map, cala gra i usuniecie map

void opcje();               //zmienia 'yy' , 'xx' , 'czas_na_pocz' , 'na_czas' ,...

//...'szybkosc' i 'czy_nast_klocek'





bool sprawdz()

{

    for (int i = 0; i < 4; i++)

    {

        for (int j = 0; j < 4; j++)

        {

            //jesli ktorys punkt klocka nachodzi na staly punkt mapy

            if (mapa1[y + i][x + j] != 0 && klocek[i][j] != 0)return false;

        }

    }



    return true;

}



void ustaw_klocek(int a, int b)

{

    for (int i = 0; i < 4; i++)

    {

        for (int j = 0; j < 4; j++)

        {

            klocek[i][j] = lista_klockow[a][b][i][j];

        }

    }

}



void wykonaj()

{

    //czysci mapa2[][]

    for (int i = 0; i < yy + 3; i++)

    {

        for (int j = 0; j < xx + 6; j++)

        {

            mapa2[i][j] = 0;

        }

    }



    //kopiuje mapa1[][] do mapa2[][]

    for (int i = 0; i < yy + 3; i++)

    {

        for (int j = 0; j < xx + 6; j++)

        {

            mapa2[i][j] = mapa1[i][j];

        }

    }



    //tworzy "cien"

    for (int i = 0; i < 4; i++)

    {

        if (klocek[0][i] == 1 || klocek[1][i] == 1 ||

            klocek[2][i] == 1 || klocek[3][i] == 1)

        {

            for (int j = 0; j < yy; j++)

            {

                if (mapa2[j][x + i] == 0)mapa2[j][x + i] = 2;

            }

        }

    }



    //wstawia poruszany klocek

    for (int i = 0; i < 4; i++)

    {

        for (int j = 0; j < 4; j++)

        {

            if (mapa2[y + i][x + j] == 0 || mapa2[y + i][x + j] == 2)

            {

                if (klocek[i][j] != 0)mapa2[y + i][x + j] = ktKolor;

            }

        }

    }





}



void pokaz()

{

    system("cls");

    for (int i = 0; i < yy + 1; i++)

    {

        for (int j = 2; j < xx + 4; j++)

        {

            switch (mapa2[i][j])

            {

            case 0:cout << (char)' '; break;//puste

            case 1:cout << (char)219; break;//sciana

            case 2:cout << (char)'X'; break;//"cien"



            case 3:cout << (char)176; break;//1 kolor

            case 4:cout << (char)177; break;//2 kolor

            case 5:cout << (char)178; break;//3 kolor

            }

        }



        switch (i)

        {

        case 0:cout << " Punkty   : " << punkty; break;

        case 1:break;

        case 2:cout << " Linie    : " << ile_linii; break;

        case 3:cout << " Szybkosc : " << czas; break;

        case 4:break;

        case 5:cout << " Nastepny :"; break;

        case 6:break;



        case 7:case 8:case 9:case 10:



            //pokazuje nastepny klocek

            if (czy_nast_klocek)

            {

                cout << "   ";



                for (int j = 0; j < 4; j++)

                {

                    if (lista_klockow[noKlocek][0][i - 7][j] == 0)

                        cout << " "; else cout << (char)219;

                }

            }



            break;



        case 11:break;

        case 12:cout << " Sterowanie : "; break;

        case 13:break;

        case 14:cout << " 'A' w lewo"; break;

        case 15:cout << " 'D' w prawo"; break;

        case 16:cout << " 'S' o 1 w dol"; break;

        case 17:cout << " 'W' na sam dol"; break;

        case 18:cout << " 'Q' obroc w lewo"; break;

        case 19:cout << " 'E' obroc w praw"; break;

        case 20:cout << " 'R' zakoncz"; break;

        }



        cout << endl;

    }

}



void gra()

{

    //tworzy mapa1[][] i mapa2[][]

    mapa1 = new int* [yy + 3]; mapa2 = new int* [yy + 3];



    for (int i = 0; i < yy + 3; i++)

    {

        mapa1[i] = new int[xx + 6]; mapa2[i] = new int[xx + 6];

    }

    //



    //wypelnia mapy

    for (int i = 0; i < yy; i++)

    {

        mapa1[i][0] = 1; mapa2[i][0] = 1;

        mapa1[i][1] = 1; mapa2[i][1] = 1;

        mapa1[i][2] = 1; mapa2[i][2] = 1;



        for (int j = 3; j < xx + 3; j++)

        {

            mapa1[i][j] = 0; mapa2[i][j] = 0;

        }



        mapa1[i][xx + 3] = 1; mapa2[i][xx + 3] = 1;

        mapa1[i][xx + 4] = 1; mapa2[i][xx + 4] = 1;

        mapa1[i][xx + 5] = 1; mapa2[i][xx + 5] = 1;

    }



    for (int i = 0; i < xx + 6; i++)

    {

        mapa1[yy + 0][i] = 1; mapa2[yy + 0][i] = 1;

        mapa1[yy + 1][i] = 1; mapa2[yy + 1][i] = 1;

        mapa1[yy + 2][i] = 1; mapa2[yy + 2][i] = 1;

    }

    //



    //ustawia potrzebne zmienne na wyjsciowe wartosci

    y = 0; x = (xx + 3) / 2;

    czynowy = true;

    ktKlocek = 0;

    ktPozycja = 0;

    punkty = 0;

    ile_linii = 0;

    linie_pod_rzad = 0;

    czas = czas_na_pocz;

    start_na_czas = clock();

    //



    while (1)

    {

        //gdy zostanie postawiony klocek

        if (czynowy == true)

        {

            //czysci pelne linie

            for (int i = yy - 1; i > 0; i--)

            {

                bool czylinia = true;//czy linia jest pelna



                do

                {

                    //sprawdza czy linia jest pelna

                    for (int j = 3; j < xx + 3; j++)

                    {

                        if (mapa1[i][j] == 0)czylinia = false;

                    }



                    //przesuwa kazdy wiersz na dol

                    if (czylinia == true)

                    {

                        for (int j = i; j > 0; j--)

                        {

                            for (int k = 3; k < xx + 3; k++)

                            {

                                mapa1[j][k] = mapa1[j - 1][k];

                            }

                        }



                        ile_linii++;

                        linie_pod_rzad++;

                    }



                } while (czylinia == true);

            }



            punkty += linie_pod_rzad * 100;

            linie_pod_rzad = 0;



            //w zaleznosci od 'szybkosc' skraca 'czas'

            if (szybkosc > 0)

            {

                if (czas_na_pocz - ile_linii / (double)szybkosc > 0.1)

                {

                    czas = czas_na_pocz - ile_linii / (double)szybkosc;

                }

            }



            ustaw_klocek(ktKlocek, 0);



            srand(time(NULL));

            noKlocek = rand() % 7;

            ktKolor = rand() % 3 + 3;



            y = 0; x = (xx + 3) / 2;

            ktPozycja = 0;

            czynowy = false;

            v = 'X';



            //jesli nowo powstaly klocek nie pasuje lub skonczyl sie czas na gre

            //lub uzytkownik zakonczyl gre celowo nacoskajac 'r' na klawiaturze

            if ((na_czas != 0 && (clock() - start_na_czas) / CLOCKS_PER_SEC > na_czas)

                || sprawdz() == false)

            {

                system("cls");



                cout << "> >> >>> >>>> KONIEC GRY <<<< <<< << <" << endl << endl;

                cout << "Twoj wynik :                    " << punkty << endl << endl;

                cout << "Linie :                         " << ile_linii << endl << endl;

                cout << "Dlugosc pola :                  " << yy << endl;

                cout << "Szerokosc pola :                " << xx << endl;

                cout << "Szybkosc na poczatku (w sec.) : " << czas_na_pocz << endl;

                cout << "Co ile linii przysp. o 1 sec. : ";

                if (szybkosc != 0)cout << szybkosc << endl; else cout << "BEZ PRZYSP." << endl;

                cout << "Czas do konca gry :             ";

                if (na_czas != 0)cout << na_czas << endl; else cout << "BEZ CZASU" << endl;

                cout << "Czy pokazac nast. klocek :      ";

                if (czy_nast_klocek == true)cout << "TAK" << endl; else cout << "NIE" << endl;



                _getch();



                break;

            }

        }



        wykonaj();

        pokaz();



        start_czas = clock();



        //porusza klockiem " poki na to czas "

        while ((double)(clock() - start_czas) / CLOCKS_PER_SEC < czas)

        {

            if (_kbhit())

            {

                v = _getch();



                switch (v)

                {

                case 'a':



                    x--; if (sprawdz() == false)x++;



                    break;

                case 'd':



                    x++; if (sprawdz() == false)x--;



                    break;

                case 's':case 'r':



                    //zmniejszenie 'czas' tak by petla sie zakonczyla

                    start_czas -= time_t(czas * CLOCKS_PER_SEC);



                    break;

                case 'q':



                    stPozycja = ktPozycja;



                    switch (ktPozycja)

                    {

                    case 0:ktPozycja = 1; break;

                    case 1:ktPozycja = 2; break;

                    case 2:ktPozycja = 3; break;

                    case 3:ktPozycja = 0; break;

                    }



                    ustaw_klocek(ktKlocek, ktPozycja);



                    if (sprawdz() == false)

                    {

                        ktPozycja = stPozycja;

                        ustaw_klocek(ktKlocek, ktPozycja);

                    }



                    break;

                case 'e':



                    stPozycja = ktPozycja;



                    switch (ktPozycja)

                    {

                    case 0:ktPozycja = 3; break;

                    case 1:ktPozycja = 0; break;

                    case 2:ktPozycja = 1; break;

                    case 3:ktPozycja = 2; break;

                    }



                    ustaw_klocek(ktKlocek, ktPozycja);



                    if (sprawdz() == false)

                    {

                        ktPozycja = stPozycja;

                        ustaw_klocek(ktKlocek, ktPozycja);

                    }



                    break;

                case 'w':



                    //opadanie na dol klocka do opadniecia na stala czesc i...

                    //...zmniejszenie czas tak by petla sie zakonczyla

                    while (1)

                    {

                        if (sprawdz() == true)y++;

                        else

                        {

                            y--;

                            start_czas -= double(czas * CLOCKS_PER_SEC);

                            break;

                        }

                    }



                    break;

                default:



                    break;

                }



                wykonaj();

                pokaz();

            }

        }



        if (v == 'w')y++;



        y++;



        //jesli klocek osiadl

        if (sprawdz() == false)

        {

            y--; if (sprawdz() == false)y--;



            //klocek staje sie stala czescia mapa1[][]

            for (int i = 0; i < 4; i++)

            {

                for (int j = 0; j < 4; j++)

                {

                    if (mapa1[y + i][x + j] == 0)

                    {

                        if (klocek[i][j] != 0)mapa1[y + i][x + j] = ktKolor;

                    }

                }

            }



            czynowy = true;



            ktKlocek = noKlocek;

        }



        if (v == 'r')break;

    }



    //usuwanie map

    for (int i = 0; i < yy; i++)

    {

        delete[] mapa1[i]; delete[] mapa2[i];

    }



    delete[] mapa1; delete[] mapa2;

    //

}



void menu()

{

    zz = 1;



    while (true)

    {

        system("cls");



        cout << "> >> >>> T E T R I S <<< << <" << endl;

        cout << "-----------------------------" << endl;

        if (zz == 1)cout << "> "; else cout << "  "; cout << "Graj" << endl;

        if (zz == 2)cout << "> "; else cout << "  "; cout << "Opcje" << endl;

        if (zz == 3)cout << "> "; else cout << "  "; cout << "Wyjdz" << endl;

        cout << "-----------------------------" << endl;

        cout << "[W]gora | [S]dol | [E]wybierz" << endl;



        vv = _getch();



        switch (zz)

        {

        case 1:



            if (vv == 'w')zz = 3;

            else if (vv == 's')zz++;

            else if (vv == 'e')gra();



            break;

        case 2:



            if (vv == 'w')zz--;

            else if (vv == 's')zz++;

            else if (vv == 'e') { opcje(); zz = 2; }



            break;

        case 3:



            if (vv == 'w')zz--;

            else if (vv == 's')zz = 1;

            else if (vv == 'e')return;



            break;



        }

    }

}



void opcje()

{

    system("cls");



    zz = 1;



    while (true)

    {

        system("cls");



        cout << "> >> >>> >>>> >>>>> OPCJE <<<<< <<<< <<< << <" << endl;

        cout << "---------------------------------------------" << endl;

        if (zz == 1)cout << "> "; else cout << "  ";

        cout << "Dlugosc pola :                  " << yy << endl;

        if (zz == 2)cout << "> "; else cout << "  ";

        cout << "Szerokosc pola :                " << xx << endl;

        if (zz == 3)cout << "> "; else cout << "  ";

        cout << "Szybkosc na poczatku :          " << czas_na_pocz << endl;

        if (zz == 4)cout << "> "; else cout << "  ";

        cout << "Co ile linii przysp. o 1 sec.:  ";

        if (szybkosc != 0)cout << szybkosc << endl; else cout << "BEZ PRZYSP." << endl;

        if (zz == 5)cout << "> "; else cout << "  ";

        cout << "Czas do konca gry (w sec.) :    ";

        if (na_czas != 0)cout << na_czas << endl; else cout << "BEZ CZASU" << endl;

        if (zz == 6)cout << "> "; else cout << "  ";

        cout << "Czy pokazac nast. klocek :      ";

        if (czy_nast_klocek == true)cout << "TAK" << endl; else cout << "NIE" << endl;

        cout << "---------------------------------------------" << endl;

        cout << "[W]gora | [S]dol | [A][D]zmien     " << endl;

        cout << "[Q]wyjdz (zmiany zostana zapisane) " << endl;



        vv = _getch();



        switch (zz)

        {

        case 1:



            if (vv == 'w')zz = 6;

            if (vv == 's')zz++;

            if (yy > 20 && vv == 'a')yy--;

            if (yy < 30 && vv == 'd')yy++;

            if (vv == 'q')return;



            break;

        case 2:



            if (vv == 'w')zz--;

            if (vv == 's')zz++;

            if (xx > 4 && vv == 'a')xx--;

            if (xx < 60 && vv == 'd')xx++;

            if (vv == 'q')return;



            break;

        case 3:



            if (vv == 'w')zz--;

            if (vv == 's')zz++;

            if (czas_na_pocz > 1.0 && vv == 'a')czas_na_pocz -= 1.0;

            if (czas_na_pocz < 5.0 && vv == 'd')czas_na_pocz += 1.0;

            if (vv == 'q')return;



            break;

        case 4:



            if (vv == 'w')zz--;

            if (vv == 's')zz++;

            if (szybkosc > 0 && vv == 'a')szybkosc--;

            if (szybkosc < 100 && vv == 'd')szybkosc++;

            if (vv == 'q')return;



            break;

        case 5:



            if (vv == 'w')zz--;

            if (vv == 's')zz++;

            if (na_czas > 0 && vv == 'a')na_czas -= 10;

            if (na_czas < 600 && vv == 'd')na_czas += 10;

            if (vv == 'q')return;



            break;

        case 6:



            if (vv == 'w')zz--;

            if (vv == 's')zz = 1;

            if (vv == 'a' || vv == 'd')czy_nast_klocek = !czy_nast_klocek;

            if (vv == 'q')return;



            break;

        }

    }

}



int main()

{

    ios_base::sync_with_stdio(0);



    menu();



    return 0;

}
