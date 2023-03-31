//
// Created by Andrii Yeremenko on 3/31/2023.
//

#include "tasks_blok2.h"
#include <stdio.h>
#include <windows.h>
#include <intrin.h>
#include <time.h>
#include <conio.h>
#include <string.h>

static int a, b, result;

int main(int argc, char* argv[])
{
    // All this will work only in VISUAL STUDIO!

    printf("First task answer is: %d \n", blok2_task1()); // 1 bod
    printf("Second task answer is: %d \n", blok2_task2()); // 1 bod
    printf("Third task answer is: %x \n", blok2_task3()); // 3 body

    blok2_task4(); // 1 bod
    blok2_task22(); // 3 body
    blok2_task26(); // 4 body
    blok2_task251(); // 0.5 bod
    blok2_task252(); // 3 bod

    return 0;
}

int blok2_task1() {

    /* Vložte do C-programu kúsok assemblerovského kódu, ktorým vypočítate súčet dvoch premenných */

    a = 12;
    b = 33;
    result = 0;

    __asm
    {
            MOV EAX, a
            ADD EAX, b
            MOV result, EAX
    }

    return result;
}
int blok2_task2() {

    /* Napíšte pomocou vloženého (embedded) asembleru C-program v ktorom
     * použijete vlastnú funkciu na násobenie dvomi bez použitia súčinu. */

    a = 27;
    result = 0;

    __asm
    {
            MOV EAX, a
            SHL EAX, 0x2
            MOV result, EAX
    }
    return result;
}
int blok2_task3() {

    /*Napíšte pomocou vloženého (embedded) asembleru C-program s funkciou na prevod číslice (0 – 15)
     * na príslušný ASCII znak predstavujúci hodnotu v hexadecimálnej sústave.
     * Pre čísla 0 – 9 bude výstupom znak ‘0’ – ‘9’, pre čísla 10 – 15 znaky ‘A’ – ‘F’.
     * Celé jadro programu musí byť napísané v jazyku symbolických inštrukcií, nesmietie použiť polia.
     * Jazyk C smiete použiť len na výpis výsledku.*/

    a = 9;
    result = 0;

    __asm
    {
            mov EAX, a
            cmp    a, 10
            jl     Less

            add EAX, 55
            mov result, EAX
            jmp    Both

            Less :
            mov result, EAX
            Both :
    }
    return result;
}

int blok2_task4() {

    /* Napíšte pomocou inline asembleru a inštrukcie cpuid program, ktorý zistí,
     * aký typ procesora máte v počítači (Intel, AMD, Cyrix,…). Výstup musí byť uložený v poli.*/

    char result_str[13];
    __asm {
            mov eax, 0
            cpuid
            mov dword ptr[result_str], ebx
            mov dword ptr[result_str + 4], edx
            mov dword ptr[result_str + 8], ecx
    }
    result_str[12] = '\0';
    printf(result_str, "%s", result_str[1]);
    return 0;
}

int blok2_task22() {

    /*Viete už pracovať so smerníkmi (pointre). Viete ale, čo je naozaj v pointri uložené? Samozrejme, reálna adresa.
     * Deklarujte pole znakov, priraďte doň hodnoty (napr. “architektura_pocitacov_je_super_predmet”)
     * a vypíšte výsledok na obrazovku. Ďalej deklarujte smerník na toto pole a vypíšte na obrazovku skutočnú adresu
     * na ktorú ukazuje (napr. printf(“%p”,pointer); ). Potom zmeňte hodnotu adresy (pripočítajte jednotku).
     * Zapíšte nejakú hodnotu na túto adresu a opäť vypíšte reťazec na obrazovku. Čo sa stalo?
     * Nakoniec zmeňte hodnotu adresy na veľmi vysokú hodnotu a opäť sa pokúste na ňu niečo zapísať.
     * Čo sa stane? Program by mal spadnúť. Vysvetlite, prečo.*/

    char str[] = "architektura_pocitacov_je_super_predmet";
    printf("Variable with srting: %s\n", str);
    char* ptr = str;
    printf("Adress: %p\n", ptr);
    *(ptr + 3) = 'X';

    printf("After changes: %s\n", str);

    ptr += 10000;
    *ptr = 'Y';

    printf("String after big changes in adress: %s\n", str);
    return 0;
}

int blok2_task251(){

    /*Napíšte program, ktorý bude postupne vypisovať čísla od 0 po 50,
     * pričom v závislosti od veľkosti čísla sa bude meniť jeho farba, napríklad pre čísla od 0 po 10 bude zelená,
     * 11 až 22 červená a 23 až 35 modrá, atď.
     * Rýchlosť výpisu na obrazovku obmedzte na cca 1 znak/sekundu. Výpis musí byť v cykle.*/

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i <= 50; i++) {
        if (i >= 0 && i <= 10) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
        else if (i >= 11 && i <= 22) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        }
        else if (i >= 23 && i <= 35) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        }

        printf("%d\n", i);
        Sleep(1000); // 1 second = 1000 tics
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    return 0;
}

void printHorizontalLine(int x, int y,int length){
    HANDLE  console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 6);
    for (int i = x; i <= length; i++)
    {
        COORD point = { i,y };
        SetConsoleCursorPosition(console, point);
        putchar(196);
    }

}
void printVerticalLine(int x, int y, int length) {
    HANDLE  console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 6);
    for (int i = y; i <= length; i++)
    {
        COORD point = { x,i };
        SetConsoleCursorPosition(console, point);
        putchar(179);
    }

}

void printWord(int x, int y, char str[]) {
    HANDLE  console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    COORD point = { x,y };
    SetConsoleCursorPosition(console, point);
    printf("%s",str);
}

void printCrest(int x, int y, unsigned char c) {
    HANDLE  console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 6);
    COORD point = { x,y };
    SetConsoleCursorPosition(console, point);
    putchar(c);
}

void printCorners(int adaptiveLentgh) {
    const unsigned char RohVpravoDole = 217;
    const unsigned char RohVlavoDole = 192;
    const unsigned char RohVpravoHore = 191;
    const unsigned char RohVlavoHore = 218;
    const unsigned char KrestVpravo = 180;
    const unsigned char KrestVlavo = 195;
    const unsigned char KrestHore = 193;
    const unsigned char KrestDole = 194;
    const unsigned char Krest = 197;
    printCrest(5, 0, RohVlavoHore);
    printCrest(19 + adaptiveLentgh, 0, RohVpravoHore);
    printCrest(19 + adaptiveLentgh, 9, RohVpravoDole);
    printCrest(5, 9, RohVlavoDole);
    printCrest(16, 1, KrestDole);
    printCrest(16, 9, KrestHore);
    for (int i = 1; i <= 7; i+=2)
    {
        printCrest(19 + adaptiveLentgh, i, KrestVpravo);
        printCrest(5, i, KrestVlavo);
        if(i != 1) printCrest(16, i, Krest);
    }
}

int maxLength(int x, int y){
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
}

int blok2_task252() {

    /*Napíšte program, ktorý na miesto v okne zadané pri spustení súradnicami [x,y] vypíše tabuľku s informáciami o Vašej osobe.
     * Parametre uvedené na obrázku sú ilustračné, ale musia byť zadané v premenných, nemôže byť celý výpis “natvrdo” naprogramovaný.
     * Parametrom zobrazenia teda bude pozícia v okne a premenné s hodnotami vypisovaných údajov.
     * Pri zmene niektorého údaja (napr. meno) sa musí rámik prispôsobiť textu, nie naopak.*/

    char meno[] = "Andrii YeremenkoKJGFBSDBG;KJD'";
    char vyska[] = "190 cm";
    char hmotnost[] = "90 kg";
    char tel[] = "1234567890";
    int maxlength = maxLength(maxLength(strlen(meno), strlen(vyska)), maxLength(strlen(hmotnost), strlen(tel)));

    printHorizontalLine(5, 0, 18 + maxlength);
    for (int i = 1; i <= 9; i += 2) {
        printHorizontalLine(5, i, 18 + maxlength);
    }

    printVerticalLine(5, 0, 9);
    printVerticalLine(16, 1, 9);
    printVerticalLine(19 + maxlength, 0, 9);

    printWord(10,0," Zoznam 001 ");
    printWord(7, 2, "Meno");
    printWord(7, 4, "Vyska");
    printWord(7, 6, "Hmotnost");
    printWord(7, 8, "Tel.");
    printWord(18, 2, meno);
    printWord(18, 4, vyska);
    printWord(18, 6, hmotnost);
    printWord(18, 8, tel);
    printCorners(maxlength);
    scanf_s("?");
    return 0;
}


int blok2_task26() {

    /*Napíšte program, ktorý po stlačení klávesy F1 vypíše návod na použitie, F2 spustí meranie a program skončí F10 alebo ESC.
     * Meranie bude spočívať v tom, že program vygeneruje náhodný znak (stačí písmená), zobrazí ho do stredu okna a spustí meranie času.
     * Meranie sa zastaví v okamihu, keď užívateľ stlačí rovnakú klávesu. Ak užívateľ stlačí niečo iné, program to bude ignorovať.
     * Napokon program vypíše zmeraný čas, ktorý uplynie od vypísania po stlačenie rovnakej klávesy.
     * Po prvom meraní ide ďalšie meranie a po ňom ďalšie, až kým používateľ program neukončí (použite cyklus).*/

    clock_t start, end;
    int key, num_attempts = 0;
    char random_char;
    printf("Press F1 for help, F2 to start measuring, F10 or ESC to exit.\n");
    while (1) {

        key = _getch();

        if (key == 0 || key == 224) { // extended keys
            key = _getch();
        }

        if (key == 59) { // F1 key
            printf("User manual:\n");
            printf("- Press F2 to start measuring.\n");
            printf("- Press the same key as shown to stop measuring.\n");
            printf("- Press F10 or ESC to exit.\n\n");
        }
        else if (key == 60) { // F2 key
            num_attempts++;
            random_char = 'a' + rand() % 26;
            printf("\t\t\t\t\t\tType the character '%c': ", random_char);
            start = clock();

            do {
                key = _getch();
                if (key == random_char) {
                    end = clock();
                    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("\n\t\t\t\t\t\tTime taken: %.2f seconds.\n\n", time_taken);
                }
            } while (key != random_char && key != 27 && key != 68); // ESC key, F10 key or wrong key

            if (key == 27 || key == 68) { // exit
                printf("Exiting program.\n");
                break;
            }
        }
        else if (key == 68 || key == 27) { // F10 key or ESC key
            printf("Exiting program.\n");
            break;
        }
    }
    printf("Total attempts made: %d\n", num_attempts);
    return 0;
}

