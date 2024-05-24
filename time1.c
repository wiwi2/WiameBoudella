#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time1.h"
#include "input.h"

double get_time_seconds(const char* time) { // récupère le temps du joueur dans le format demandé et convertit en secondes
    Time t;
    sscanf(time, "%dh%dm%fs", &t.hours, &t.minutes, &t.seconds);
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

Time Constr_time() { // fonction fonctionnant avec la structure Time : sert à récupérer le temps d'un joueur lorsque c'est nécessaire
    Time t;
    t.hours = 0;
    t.minutes = 0;
    t.seconds = 0;

    do {
        printf("hours? ");
        t.hours = get_int_input(); // vérification que c'est bien un entier avec get_int_input
        printf("minutes? ");
        t.minutes = get_int_input();
        printf("seconds? ");
        t.seconds = get_float_input(); // pareil, avec get_float_input

        if (t.hours < 0 || t.hours > 24 || t.minutes < 0 || t.minutes > 59 || t.seconds < 0 || t.seconds > 59) {
            printf("Invalid input. Please enter the time in the correct format.\n");
        }
    } while (t.hours < 0 || t.hours > 24 || t.minutes < 0 || t.minutes > 59 || t.seconds < 0 || t.seconds > 59);

    return t;
}
