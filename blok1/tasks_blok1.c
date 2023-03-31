//
// Created by Andrii Yeremenko on 2/27/2023.
//

#include <stdio.h>
#include <float.h>
#include <math.h>
#include "tasks_blok1.h"
#define PI 3.14159265359

char convertToChar(int a) {
    return (a < 10)? (a + 48) : (a + 55);
}

void DecToHex(int dec) {
    int hex_length;
    char hex[16];
    for(hex_length = 0; dec > 0; hex_length++)
    {
        hex[hex_length] = convertToChar(dec % 16);
        dec = dec / 16;
    }
    for (int i = hex_length - 1; i >= 0; --i) {
        printf("%c",hex[i]);
    }
    printf("\n");
}

void DecToBin(int dec) {
    int bin_length;
    int bin[16];
    for(bin_length = 0; dec > 0; bin_length++)
    {
        bin[bin_length] = dec % 2;
        dec = dec / 2;
    }
    for (int i = bin_length - 1; i >= 0; --i) {
        printf("%d",bin[i]);
    }
    printf("\n");
}

double sinus(int x, double epsilon) {
    double radians = x * PI / 180;
    double sum = 0, series = radians;
    int i = 1;
    while(fabs(series) > epsilon){
        i += 2;
        sum += series;
        series = -series*radians * radians/(i * (i-1));
    }
    return sum;
}

void fibo(int prev, int now, int limit) {
    if(prev + now > limit){
        return;
    }
    else {
        printf("%d ",(prev + now));
        fibo(now, prev + now, limit);
    }
}

void blok1_task5() {

    /*Napíšte program na výpočet funkcie sin(x) alebo cos(x) pomocou rozvoja do Taylorovho radu v okolí bodu 0.
     * Inými slovami, budete programovať funkciu sínus alebo kosínus sami, bez toho,
     * aby ste použili iné existujúce riešenie.
     * Uhly môžete zadávať v stupňoch alebo v radiánoch. Program musí fungovať pre akékoľvek vstupy,
     * napr. -4500° alebo +8649°. Funkcia bude mať dva argumenty:

        float sinus(float radians, float epsilon);

    Na Vašu vlastnú implementáciu použite jeden z nasledovných vzťahov (stačí programovať buď sínus alebo kosínus, netreba obe):*/

    int angle = 30;
    printf("Sinus of angle %d is %f\n",angle,sinus(angle,DBL_EPSILON));
}

void blok1_task4() {

    /*Napíšte program, ktorý zistí a vypíše na obrazovku strojové epsilon pre dátové typy float a double.
     Zároveň vypíšte aj hodnoty __FLT_EPSILON__ a __DBL_EPSILON__ zadefinované vo float.h.
     Pripomenutie – slovné spojenie dátový typ hovorí o tom, ako kompilátor „rozumie“ jednotkám a nulám, s ktorými pracujete.
     Identifikujete tak, či pracujete s celými číslami, písmenami, reálnymi číslami a podobne.*/

    float float_eps = 1.0f;
    while ((float) (1 + float_eps / 2.0) != 1)
        float_eps /= 2;

    printf( "Float = %e\n", float_eps );

    double double_eps = 1.0f;
    while ((double) (1 + double_eps / 2.0) != 1)
        double_eps /= 2;

    printf( "Double = %e\n", double_eps );

    printf( "FLT_EPSILON = %e\n", FLT_EPSILON );
    printf( "DBL_EPSILON = %e\n", DBL_EPSILON );
}

void blok1_task3() {

    /*Napíšte program, ktorý vypíše všetky Fibonacciho čísla,
     *ktoré sú menšie alebo sa rovnajú číslu k (k≥2), ktoré zadal užívateľ.*/

    int limit;
    printf("\nEnter a limit: ");
    scanf("%d", &limit);
    printf("1 1 ");
    fibo(1,1,limit);
}

void blok1_task2() {

    /* Napíšte program, ktorý dokáže zapísať zadané číslo (stačí rozsah 1-100) rímskymi číslicami. */

    int arabian_num;
    printf("Enter a number: ");
    scanf("%d", &arabian_num);
    printf("Arabic %d into roman ",arabian_num);
    while(arabian_num != 0)
    {
        if (arabian_num >= 1000)
        {
            printf("M");
            arabian_num -= 1000;
        }
        else if (arabian_num >= 900)
        {
            printf("CM");
            arabian_num -= 900;
        }
        else if (arabian_num >= 500)
        {
            printf("D");
            arabian_num -= 500;
        }
        else if (arabian_num >= 400)
        {
            printf("CD");
            arabian_num -= 400;
        }

        else if (arabian_num >= 100)
        {
            printf("C");
            arabian_num -= 100;
        }

        else if (arabian_num >= 90)
        {
            printf("XC");
            arabian_num -= 90;
        }

        else if (arabian_num >= 50)
        {
            printf("L");
            arabian_num -= 50;
        }

        else if (arabian_num >= 40)
        {
            printf("XL");
            arabian_num -= 40;
        }

        else if (arabian_num >= 10)
        {
            printf("X");
            arabian_num -= 10;
        }

        else if (arabian_num >= 9)
        {
            printf("IX");
            arabian_num -= 9;
        }

        else if (arabian_num >= 5)
        {
            printf("V");
            arabian_num -= 5;
        }

        else if (arabian_num >= 4)
        {
            printf("IV");
            arabian_num -= 4;
        }

        else if (arabian_num >= 1)
        {
            printf("I");
            arabian_num -= 1;
        }
    }
}

void blok1_task1() {

    /* Napíšte program, ktorý zobrazí nasledovné dva vstupy: číslo 33777 a ASCII kód znaku ‘X’,
     * v dvojkovej, desiatkovej a šestnástkovej sústave. */

    int x = 'x';
    printf("bin number: ");
    DecToBin(33777);
    printf("hex number: ");
    DecToHex(33777);
    printf("dec char: %d\n",x);
    printf("bin char: ");
    DecToBin(x);
    printf("hex char: ");
    DecToHex(x);
}