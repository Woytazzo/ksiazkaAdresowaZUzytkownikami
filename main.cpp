#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Znajomy {
    Znajomy() {
        idZnajomego=0;
        idUzytkownika=0;
        imie="nowy";
        nazwisko="nowy";
        adres="nowy";
        telefon="nowy";
        mail="nowy";
    }
    int idZnajomego, idUzytkownika;
    string imie, nazwisko, adres, telefon, mail;
};

struct Uzytkownik {
    Uzytkownik() {
        id=0;
        login="nowy";
        haslo="nowy";
    }
    int id;
    string login, haslo;
};


string zWielkiejLitery(string wyraz) {
    wyraz[0] = toupper(wyraz[0]);

    if (wyraz.length()>1)
        for(int i=1; i<wyraz.length(); i++)
            wyraz[i]=tolower(wyraz[i]);
    return wyraz;
}

void dodanieDoPlikuJednegoZnajomego(Znajomy nowy) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    plik<<nowy.idZnajomego<<"|"<<nowy.idUzytkownika<<"|"<<nowy.imie<<"|"<<nowy.nazwisko<<"|"<<nowy.adres<<"|"<<nowy.telefon<<"|"<<nowy.mail<<"|"<<endl;

    plik.close();
}

void dodanieDoPlikuWszystkichZnajomych(vector <Znajomy> znajomi) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    for (int i=0; i<znajomi.size(); i++) {

        plik<<znajomi[i].idZnajomego<<"|"<<znajomi[i].idUzytkownika<<"|"<<znajomi[i].imie<<"|"<<znajomi[i].nazwisko<<"|"<<znajomi[i].adres<<"|"<<znajomi[i].telefon<<"|"<<znajomi[i].mail<<"|"<<endl;
    }
    plik.close();
}

Uzytkownik pobranieUzytkownikaZJednejLinii(string liniaZPliku) {

    string roboczy;
    int iloscPrzerywnikow=0;
    string literaDoDodania;
    Uzytkownik uzytkownikDoDodania;
    int id;
    string login, haslo;

    for (int i=0; i<liniaZPliku.length(); i++) {
        if (liniaZPliku[i]!=124) {
            literaDoDodania=liniaZPliku[i];
            roboczy.insert(roboczy.length(), literaDoDodania);
        } else if (liniaZPliku[i]==124) {
            iloscPrzerywnikow++;

            switch(iloscPrzerywnikow) {
            case 1:
                uzytkownikDoDodania.id = atoi(roboczy.c_str());
                break;
             case 2:
                uzytkownikDoDodania.login = roboczy;
                break;
            case 3:
                uzytkownikDoDodania.haslo = roboczy;
                break;
            }

            roboczy="";
        }
    }

    return uzytkownikDoDodania;
}

Znajomy pobranieZnajomegoZJednejLinii(string liniaZPliku) {

    string roboczy;
    int iloscPrzerywnikow=0;
    string literaDoDodania;
    Znajomy adresatDoDodania;
    int id;
    string imie, nazwisko, adres, telefon, mail;

//pobieranie po kolei liter i dodanie do zmiennej roboczy
    for (int i=0; i<liniaZPliku.length(); i++) {
        if (liniaZPliku[i]!=124) {
            literaDoDodania=liniaZPliku[i];
            roboczy.insert(roboczy.length(), literaDoDodania);
        } else if (liniaZPliku[i]==124) {
            iloscPrzerywnikow++;

            switch(iloscPrzerywnikow) {
            case 1:
                adresatDoDodania.idZnajomego = atoi(roboczy.c_str());
                break;
             case 2:
                adresatDoDodania.idUzytkownika = atoi(roboczy.c_str());
                break;
            case 3:
                adresatDoDodania.imie = roboczy;
                break;
            case 4:
                adresatDoDodania.nazwisko = roboczy;
                break;
            case 5:
                adresatDoDodania.adres = roboczy;
                break;
            case 6:
                adresatDoDodania.telefon = roboczy;
                break;
            case 7:
                adresatDoDodania.mail = roboczy;
                break;
            }
            roboczy="";
        }
    }

    return adresatDoDodania;
}

vector <Znajomy> pobranieWszystkichZnajomychZPlikuDlaDanegoUzytkownika (int id) {
    Znajomy znajomyRoboczy;
    vector <Znajomy> znajomi;
    string liniaZPliku;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == true) {
        while(getline(plik,liniaZPliku)) {
            znajomyRoboczy=pobranieZnajomegoZJednejLinii(liniaZPliku);

            if(znajomyRoboczy.idUzytkownika==id)
            znajomi.push_back(znajomyRoboczy);

        }
        plik.close();
    }
    return znajomi;
}

vector <Znajomy> pobranieWszystkichZnajomychZPliku () {
    Znajomy znajomyRoboczy;
    vector <Znajomy> znajomi;
    string liniaZPliku;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == true) {
        while(getline(plik,liniaZPliku)) {
            znajomyRoboczy=pobranieZnajomegoZJednejLinii(liniaZPliku);

            znajomi.push_back(znajomyRoboczy);

        }
        plik.close();
    }
    return znajomi;
}

vector <Znajomy> dodanieZnajomego(vector <Znajomy> znajomi, int idUzytkownika) { //tutaj oprocz podania nazwy tablicy podajemy nazwe calej struktury, przy samej deklaracji uzywamy tylko nazwy tablicy(bez nawiasow kwadratowych i nazwy struktury)

    Znajomy nowy;
    string ulica, nrMieszkania, kodPocztowy, miejscowosc;

    cout << "Podaj imie znajomego: ";
    cin >> nowy.imie;
    nowy.imie=zWielkiejLitery(nowy.imie);
    system("cls");
    cout << "Podaj nazwisko znajomego " << nowy.imie <<": ";
    cin >> nowy.nazwisko;
    nowy.nazwisko=zWielkiejLitery(nowy.nazwisko);
    system("cls");

    for(int i=0; i<znajomi.size(); i++) {
        if((znajomi[i].imie==nowy.imie) && (znajomi[i].nazwisko==nowy.nazwisko)) {

            cout<<"Taki znajomy juz istnieje."<<endl;
            Sleep(2000);
            system("cls");
            return znajomi;
        }
    }

    cout << "Podaj numer telefonu znajomego " << nowy.imie <<": ";
    cin >> nowy.telefon;
    system("cls");
    cout << "Podaj nazwe ulicy/aleji, przy ktorej mieszka " << nowy.imie <<": ";
    cin >> ulica;
    system("cls");
    cout << "Podaj numer domu i mieszkania, w ktorym mieszka " << nowy.imie <<"(nr domu/nr mieszkania): ";
    cin >> nrMieszkania;
    system("cls");
    cout << "Podaj kod pocztowy dla miejsca, gdzie mieszka " << nowy.imie <<": ";
    cin >> kodPocztowy;
    system("cls");
    cout << "Podaj miejscowosc, w ktorej mieszka " << nowy.imie <<": ";
    cin >> miejscowosc;
    system("cls");
    cin.sync();
    cout << "Podaj e-mail znajomego " << nowy.imie <<": ";
    cin >> nowy.mail;
    system("cls");
    nowy.adres = ulica+" "+ nrMieszkania+", "+ kodPocztowy+", "+ miejscowosc;

    if(znajomi.size()>0)
        nowy.idZnajomego = (znajomi[znajomi.size()-1].idZnajomego)+1;
    else nowy.idZnajomego=1;

    nowy.idUzytkownika = idUzytkownika;

    znajomi.push_back(nowy);

    system("cls");

    dodanieDoPlikuJednegoZnajomego(nowy);

    cout << "Znajomy dodany";
    Sleep(2000);
    system("cls");

    return znajomi;
}


void wyszukiwanieZnajomego(vector <Znajomy> znajomi) {
    string imie, nazwisko;
    int iloscSprawdzonychKontaktow=0;

    if(znajomi.size()>0) {
        cout << "Jak chcesz wyszukac znajomego? " << endl;
        cout << "1. podajac imie" << endl;
        cout << "2. podajac nazwisko" << endl;
        char opcja;
        cin>>opcja;
        system("cls");
        switch(opcja) {
        case '1': {
            cout<<"Podaj imie wyszukiwanego znajomego"<<endl;
            cin>>imie;

            imie=zWielkiejLitery(imie);

            for (int i=0; i<znajomi.size(); i++)
                if (znajomi[i].imie == imie ) {
                    cout<<endl<<znajomi[i].imie<<endl<<znajomi[i].nazwisko<<endl<<znajomi[i].adres<<endl<<znajomi[i].telefon<<endl<<znajomi[i].mail<<endl<<endl;
                    iloscSprawdzonychKontaktow++;
                }
            cout<<"ilosc wyszukanych osob: "<<iloscSprawdzonychKontaktow<<endl;
        }
        break;
        case '2': {


            cout<<"Podaj nazwisko wyszukiwanego znajomego"<<endl;
            cin>>nazwisko;

            nazwisko=zWielkiejLitery(nazwisko);

            for (int i=0; i<znajomi.size(); i++)

                if (znajomi[i].nazwisko == nazwisko) {
                    cout<<endl<<znajomi[i].imie<<endl<<znajomi[i].nazwisko<<endl<<znajomi[i].adres<<endl<<znajomi[i].telefon<<endl<<znajomi[i].mail<<endl<<endl;
                    iloscSprawdzonychKontaktow++;
                }
            cout<<"ilosc wyszukanych osob: "<<iloscSprawdzonychKontaktow<<endl;
        }
        break;
        default: {
            cout << "Blad!! Sprobuj jeszcze raz" <<endl;;

        }
        break;
        }
    } else
        cout<<"nie masz znajomych"<<endl;
    system("pause");
    system("cls");

}


void listaZnajomych (vector<Znajomy> znajomi) {
    if(znajomi.size()>0) {
        for(int i=0; i < znajomi.size(); i++)
            cout<<znajomi[i].imie<<endl<<znajomi[i].nazwisko<<endl<<znajomi[i].adres<<endl<<znajomi[i].telefon<<endl<<znajomi[i].mail<<endl<<endl;

system("pause");

    } else {
        cout<<"nie masz znajomych";

        Sleep(2000);
        system("cls");
    }

}

int okreslenieKtoryZnajomyMaBycEdytowany (vector <Znajomy> znajomi, string wybraneImie, string wybraneNazwisko) {
    for (int i=0; i<znajomi.size(); i++) {
        if (wybraneImie==znajomi[i].imie &&wybraneNazwisko==znajomi[i].nazwisko) {
            cout<<znajomi[i].imie<<" "<< znajomi[i].nazwisko<<endl;
            cout<<znajomi[i].adres<<endl;
            cout<<znajomi[i].telefon<<endl;
            cout<<znajomi[i].mail<<endl;

            return znajomi[i].idZnajomego;
        }
    }
    cout<<"nie ma takiego kontaktu"<<endl;
    system("pause");
    system("cls");
    return -1;
}

vector <Znajomy> edycjaZnajomego(vector <Znajomy> znajomi, int idZnajomego) {
    for (int i=0; i<znajomi.size(); i++) {
        if (znajomi[i].idZnajomego==idZnajomego) {
            char wybor;
            cout<<"Ktore dane chcesz edytowac?"<<endl;
            cout<<"1. imie"<<endl;
            cout<<"2. nazwisko"<<endl;
            cout<<"3. adres"<<endl;
            cout<<"4. telefon"<<endl;
            cout<<"5. mail"<<endl;

            cout<<endl<<"ID "<<znajomi[i].idZnajomego<<" "<<idZnajomego<<endl;
            cin>>wybor;
            switch (wybor) {

            case '1': {
                cout<<"podaj zmienione imie"<<endl;
                cin>>znajomi[i].imie;
                znajomi[i].imie=zWielkiejLitery(znajomi[i].imie);
                system("cls");

            }
            break;
            case '2': {
                cout<<"podaj zmienione nazwisko"<<endl;
                cin>>znajomi[i].nazwisko;
                znajomi[i].nazwisko=zWielkiejLitery(znajomi[i].nazwisko);
                system("cls");
            }
            break;
            case '3': {
                system("cls");
                string ulica, nrMieszkania, kodPocztowy, miejscowosc;
                cout << "Podaj zmieniona nazwe ulicy/aleji, przy ktorej mieszka " << znajomi[i].imie <<": ";
                cin >> ulica;
                system("cls");
                cout << "Podaj zmieniony numer domu i mieszkania, w ktorym mieszka " << znajomi[i].imie <<"(nr domu/nr mieszkania): ";
                cin >> nrMieszkania;
                system("cls");
                cout << "Podaj zmieniony kod pocztowy dla miejsca, gdzie mieszka " << znajomi[i].imie <<": ";
                cin >> kodPocztowy;
                system("cls");
                cout << "Podaj zmieniona miejscowosc, w ktorej mieszka " << znajomi[i].imie <<": ";
                cin >> miejscowosc;
                system("cls");
                znajomi[i].adres=ulica+" "+nrMieszkania+" "+kodPocztowy+" "+miejscowosc;
            }
            break;
            case '4': {
                cout<<"podaj zmieniony numer telefonu"<<endl;
                cin>>znajomi[i].telefon;
                system("cls");
            }
            break;
            case '5': {
                cout<<"podaj zmieniony e-mail"<<endl;
                cin>>znajomi[i].mail;
                system("cls");
            }
            break;
            default: {
                cout << "Blad!! Sprobuj jeszcze raz" <<endl;;

            }
            break;
            }

        }
    }

    return znajomi;
}
void usuniecieWierszaKontakuZPliku(int idZnajomego)
{
   vector <Znajomy> znajomi=pobranieWszystkichZnajomychZPliku();
   for (int i=0; i<znajomi.size(); i++)
       if(idZnajomego==znajomi[i].idZnajomego)
        znajomi.erase(znajomi.begin()+i);
    dodanieDoPlikuWszystkichZnajomych(znajomi);
}

vector <Znajomy> usuniecieZnajomego (vector <Znajomy> znajomi, int idZnajomego) {
    for(int i=0; i<znajomi.size(); i++) {
        if(znajomi[i].idZnajomego==idZnajomego) {
            znajomi.erase(znajomi.begin()+i);

            usuniecieWierszaKontakuZPliku(idZnajomego);

            cout<<"Kontakt zostal pomyslnie usuniety !!"<<endl;
            Sleep(2000);
            system("cls");
        }

    }
    return znajomi;

}

vector <Znajomy> edycjaLubUsuniecieZnajomego(vector <Znajomy> znajomi) {
    listaZnajomych(znajomi);
    char wybor;
    int wybor2;
    if(znajomi.size()>0) {


        string wybraneImie, wybraneNazwisko;

        cout<<"Wybierz z listy kontakt do edycji lub usuniecia."<<endl;
        cout<<"Podaj Imie i Nazwisko tego kontaktu (Imie Nazwisko):"<<endl;
        cin>>wybraneImie>>wybraneNazwisko;
        wybraneImie=zWielkiejLitery(wybraneImie);
        wybraneNazwisko=zWielkiejLitery(wybraneNazwisko);

        system("cls");
        int idWybranejOsoby = okreslenieKtoryZnajomyMaBycEdytowany(znajomi, wybraneImie, wybraneNazwisko);
        if (idWybranejOsoby!=-1) {
            cout<<endl<<"Wybierz co chcesz zrobic z wybranym kontaktem:"<<endl;
            cout<<"1.Edytuj"<<endl;
            cout<<"2.Usun"<<endl;
            cin>>wybor;
            switch (wybor) {

            case '1': {
                znajomi=edycjaZnajomego(znajomi, idWybranejOsoby);
                system("cls");
                cout<<"Dane edytowano pomyslnie !!"<<endl;
                Sleep(2000);
            }
            break;
            case '2': {
                cout<<endl<<"Czy na pewno chcesz usunac ten kontakt? (1 - tak/ 2 - nie)"<<endl;
                cin>>wybor2;

                switch (wybor2) {
                case 1: {
                    znajomi=usuniecieZnajomego(znajomi, idWybranejOsoby);
                }
                break;
                case 2: {
                    cout<<"Kontakt zostal niezmieniony!"<<endl;
                    Sleep(2000);
                }
                break;
                default: {
                    cout << "Blad!! Sprobuj jeszcze raz" <<endl;

                }
                break;
                }
                system("cls");

            }
            break;


            }
            return znajomi;
        } else
            return znajomi;
    } else cout<<"nie masz znajomych"<<endl;
    Sleep(2000);
    system("cls");
    return znajomi;
}

vector <Znajomy> ksiazkaAdresowa(vector <Znajomy> znajomi, string login, int idUzytkownika) {


    cout <<login<<" - witaj w Twojej ksiazce adresowej!" << endl;

    znajomi=pobranieWszystkichZnajomychZPlikuDlaDanegoUzytkownika(idUzytkownika);

    char wybor;

    while(1) {
        cout << "Ilosc wpisanych znajomych: "<< znajomi.size() << endl<<endl;
        cout << "Wybierz co chcesz teraz zrobic:" << endl;
        cout << "1. Dodaj znajomego" << endl;
        cout << "2. Znajdz znajomego" << endl;
        cout << "3. Wyswietl liste wszystkich znajomych" << endl;
        cout << "4. Edytuj lub usun znajomego" << endl;
        cout << "9. Wyloguj" << endl;

        cin >> wybor;
        system("cls");
        switch (wybor) {

        case '1': {
            znajomi=dodanieZnajomego(znajomi, idUzytkownika);
        }
        break;
        case '2': {
            wyszukiwanieZnajomego(znajomi);
        }
        break;
        case '3': {
            listaZnajomych(znajomi);
            system("cls");
        }
        break;
        case '4': {
            znajomi=edycjaLubUsuniecieZnajomego(znajomi);
        }
        break;
        case '9': {
            cout << "Do zobaczenia!";
            Sleep(1000);
            return znajomi;
        }
        break;
        default: {
            cout << "Blad!! Sprobuj jeszcze raz" <<endl;

        }
        break;
        }
    }

    return znajomi;
}







vector <Uzytkownik> wczytanieUzytkownikowZPliku()
{
    Uzytkownik uzytkownikRoboczy;
    vector <Uzytkownik> uzytkownicy;
    string liniaZPliku;
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == true) {
        while(getline(plik,liniaZPliku)) {
            uzytkownikRoboczy=pobranieUzytkownikaZJednejLinii(liniaZPliku);

            uzytkownicy.push_back(uzytkownikRoboczy);

        }
        plik.close();
    }
    return uzytkownicy;
}

void dodanieDoPlikuJednegoUzytkownika(Uzytkownik nowy) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    plik<<nowy.id<<"|"<<nowy.login<<"|"<<nowy.haslo<<"|"<<endl;

    plik.close();
}

void zabezpieczenieTrzechBlednychHasel ()
{
    system("cls");
    for(int k=10; k>0; k--)
    {
        cout<<"Wpisales bledne haslo trzy razy. Musisz odczekac "<<k<<" sekund."<<endl;
        Sleep(1000);
        system("cls");
    }
}

vector <Znajomy> logowanie(vector <Uzytkownik> uzytkownicy)
{
    char wybor;
    vector <Znajomy> znajomi;
    int licznikBlednychHasel=0;
    bool zatwierdzoneHaslo=false;
    int id;
    string login, haslo;

   while(1)
   {

    if (zatwierdzoneHaslo==true) break;
    system("cls");

    cout<<"Podaj login:"<<endl;
    cin>>login;

    for (int i=0; i<uzytkownicy.size(); i++)
    {
     if (uzytkownicy[i].login==login)
     {
         id=uzytkownicy[i].id;
         while(1)
         {
           if (zatwierdzoneHaslo==true) break;
         system("cls");
        cout<<"Podaj haslo dla loginu "<<login<<" lub powroc do menu glownego, wpisujac 0 i zatwierdzajac enterem:"<<endl;
        cin>>haslo;

        if (haslo=="0") return znajomi;

            for (int j=0; j<uzytkownicy.size(); j++)
            {
            if (uzytkownicy[i].haslo==haslo)
                {
                    zatwierdzoneHaslo=true;
                    system("cls");
                cout<<login<<" !! "<<endl;
                znajomi=ksiazkaAdresowa(znajomi, uzytkownicy[i].login, uzytkownicy[i].id);


                break;
                }
            else if (uzytkownicy[i].haslo!=haslo && j==(uzytkownicy.size()-1))
                {
                    system("cls");
                cout<<"Bledne haslo dla loginu "<<login<<"."<<endl;
                cout<<"Sproboj jeszcze raz."<<endl;
                Sleep(1000);
                licznikBlednychHasel++;
                system("cls");
                if(licznikBlednychHasel>=3)
                {
                zabezpieczenieTrzechBlednychHasel();
                break;
                }
                }
            }
         }
     }
     else if(uzytkownicy[i].login!=login && i==(uzytkownicy.size()-1) && zatwierdzoneHaslo==false)
        {
         cout<<"Nie ma takiego loginu. Chcesz sprobowac jeszcze raz? (t/n)"<<endl;
         cin>>wybor;
         if (wybor=='t')
            system("cls");
         else return znajomi;
        }
    }
   }
   return znajomi;
}

vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy)
{
    Uzytkownik nowy;
    string haslo;

    while(1){
    system("cls");
    cout<<"Zaproponuj swoj unikalny login:"<<endl;
    cin>>nowy.login;

    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].login==nowy.login){
            cout<<"Taki login istnieje juz w bazie! Musisz wybrac inny."<<endl;
            Sleep(1300);
            break;
        }
        else if (uzytkownicy[i].login!=nowy.login && i==(uzytkownicy.size()-1))
        {
            while(1)
            {
            system("cls");
            cout<<"Podaj haslo, skladajace sie z conajmniej 5 znakow:"<<endl;
            cin>>haslo;

            if(haslo.length()>=5)
            {
            nowy.haslo=haslo;

            nowy.id=uzytkownicy.size()+1;
            uzytkownicy.push_back(nowy);

            system("cls");
            cout<<"Konto zostalo zalozone."<<endl;
            dodanieDoPlikuJednegoUzytkownika(nowy);
            Sleep(1300);
            return uzytkownicy;
            }
            else
            {
            cout<<"wprowadzone haslo jest zbyt krotkie!"<<endl;
            Sleep(1300);
            }
            }
        }
    }
    }
}

int main()
{
    char wybor='0';
    vector <Uzytkownik> uzytkownicy;
    vector <Znajomy> znajomi;


    uzytkownicy=wczytanieUzytkownikowZPliku();

while(1){
        system("cls");
    cout<<"Witaj w ksiazce adresowej!"<<endl;
    cout<<"Zaloguj sie, a jesli nie masz konta - zarejestruj sie!"<<endl<<endl;
    cout<<"1.Logowanie"<<endl;
    cout<<"2.Rejestracja"<<endl;
    cout<<"3.Zamknij program"<<endl;

    cin>>wybor;


switch(wybor){
     case '1': {
            znajomi=logowanie(uzytkownicy);
        }
        break;
        case '2': {
            uzytkownicy=rejestracja(uzytkownicy);
        }
        break;
        case '3': {
            system("cls");
            cout<<"Program zakonczony pomyslnie. Do zobaczenia!"<<endl;
            Sleep(1000);
            return 0;

        }
        break;
        default: {
            cout << "Blad!! Sprobuj jeszcze raz" <<endl;

        }
        break;

     }
}
    return 0;
}
