// Author: ig: @damixdamixx
// Version 1.0
// - Dodano możliwość dodawania kolejnego okna
// Version 1.1
// - Dodano możliwość nadawania swoich nazw dla boxów
// - Dodano możliwość wyświetlania listy z dodanymi już wcześniej boxami

#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <conio.h>

#define fg_white (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define blue_int (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define red_int (FOREGROUND_RED | FOREGROUND_INTENSITY)

using namespace std;

// FUNKCJE
bool IsFileExists(const string& filePath);
void InstallProg();
void ScanPath();
void newbox(string box);
void NewBroken();   
void SaveListOfBox(const string& box);
void ReadingListOfBox();

int main() {
    system("cls");
    ScanPath();
    SetConsoleTitleA("Config Broken Multi BETA");
    return 0;
}

bool IsFileExists(const string& filePath) {
    ifstream file(filePath);
    return file.good();
}

void ScanPath(){
    string filePath = "C:\\Sandboxie\\Start.exe";
    if (IsFileExists(filePath)) {
        NewBroken();
    } else {
        InstallProg();
    }
}

void NewBroken(){
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string dysk, boxx;
    char znaktwo;
    do{
        SetConsoleTextAttribute(hConsole, blue_int);
        cout << "1. Uruchom\n";
        cout << "2. Dodawanie kolejnego srodowiska\n";
        cout << "3. Lista srodowisk\n";
        cout << "4. Wylacz program\n\n";
        SetConsoleTextAttribute(hConsole, fg_white);
        cout << "Wybierz opcje: ";
        znaktwo = getch();
        
        switch(znaktwo){
            case '1':
                system("cls");
                ReadingListOfBox();
                SetConsoleTextAttribute(hConsole, red_int);
                cout << "TESTOWY WYBOR\n\n\n";
                SetConsoleTextAttribute(hConsole, fg_white);
                cout << "Podaj w ktorym srodowisku uruchomic nowe okno Broken Ranks: "; cin >> boxx;
                cout << "\nPodaj litere dysku na ktorym jest zainstalowany Broken Ranks: "; cin >> dysk;
                system(("C:\\Sandboxie\\Start.exe /box:"+ boxx + " " +dysk + ":\\Whitemoon\\BrokenRanks\\client\\BrokenRanks.exe").c_str());
                system("cls");
                break;
            case '2':
                system("cls");
                newbox("");
                system("pause");
                system("cls");
                break;
            case '3':
                system("cls");
                ReadingListOfBox();
                break;
            case '4':
                exit(0);
            default:
                system("cls");
                SetConsoleTextAttribute(hConsole, red_int);
                cout << "Nie ma takiej opcji!!!!" << "\n\n";
                SetConsoleTextAttribute(hConsole, fg_white);
                Sleep(1000);
                system("cls");
                break;
        }

    }while(znaktwo = '1');
};

void InstallProg() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char znak;

    do {
        SetConsoleTextAttribute(hConsole, blue_int);
        cout << "1. Zainstaluj program\n";
        cout << "2. Przejdz dalej\n";
        cout << "3. Wylacz program\n\n";
        cout << "Wybierz opcje: ";
        SetConsoleTextAttribute(hConsole, fg_white); znak = getch();

        switch (znak) {

        case '1':
            system("cls");
            system("mkdir C:\\Sandboxie");
            system("winget install --id=Sandboxie.Plus -e --location C:\\Sandboxie");
            Sleep(1000);
            system("cls");
            SetConsoleTextAttribute(hConsole, red_int);
            cout << "PO URUCHOMIENIU PROGRAMU KLIKAJ DALEJ, A PO PRZEJSCIU DALEJ WYJDZ Z PROGRAMU";
            SetConsoleTextAttribute(hConsole, fg_white);
            system("C:\\Sandboxie\\SandMan.exe");
            break;
        case '2':
            NewBroken();
            break;
        case '3':
            system("exit");
            break;
        default:
            system("cls");
            SetConsoleTextAttribute(hConsole, red_int);
            cout << "Nie ma takiej opcji!!!\n\n";
            SetConsoleTextAttribute(hConsole, fg_white);
            break;
        }
    } while (znak == '1' && znak != '2');
};

void SaveListOfBox(const string& box){
    system("cls");
    ofstream tabela("tabela.txt", ios::out | ios::app);
    if(tabela.is_open()){
        tabela << box << "\n";
        tabela.close();
    };
}

void newbox(string box){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string program = R"(C:\Sandboxie\SbieIni.exe)";
    cout << "Podaj nazwe dla nowego srodowiska: "; cin >> box;
    SaveListOfBox(box);
    system ((program + " set " + box + " ConfigLevel 7").c_str());
    system ((program + " set " + box + " Enabled y").c_str());
    system ((program + " set " + box + " AutoDelete n").c_str());
    system ((program + " set " + box + " BorderColor #00FFFF").c_str());
    system ((program + " set " + box + " BoxNameTitle" + box).c_str());
    system ((program + " set " + box + " AutoRecover y").c_str());
    system ((program + " set " + box + " DropAdminRights n").c_str());
    system("cls");
    cout << "\nSrodowisko ";
    SetConsoleTextAttribute(hConsole, red_int);
    cout << box;
    SetConsoleTextAttribute(hConsole, fg_white);
    cout << " zostal dodany\n\n";
    Sleep(1000);
    system("cls");
    NewBroken();
}


void ReadingListOfBox(){
    string tabela = "tabela.txt";
    ifstream file(tabela);
    cout << "Lista srodowisk:\n";
    if(file.is_open()){
        string line;
        while (getline(file, line)){
            cout << "- " << line << "\n";
        }
        file.close();
        cout << "\n\n";
    } else {
        cerr << "Nie udalo sie otworzyc pliku: " << tabela << "\n";
    }
}

