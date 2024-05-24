#include <stdio.h>
#include "date.h"
#include "input.h"

Date constr_Date() { // structure pour récupérer la date demandée à l'utilisateur
    Date x;
    int verifdays;
    do {
        printf("Which day? \n");
        x.days = get_int_input(); // vérification que c'est bien correct (pas un caractère)
        printf("Which month? (1-12)\n");
        x.month = get_int_input();
        printf("Which year? (0-2024)\n");
        x.year = get_int_input();

        switch (x.month) {// vérifie que c'est bien réaliste (12 mois max, 31/30/28/29 jours...)
            case 2:
                if ((x.year % 4 == 0 && x.year % 100 != 0) || x.year % 400 == 0) {
                    verifdays = 29;
                } else {
                    verifdays = 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                verifdays = 30;
                break;
            default:
                verifdays = 31;
                break;
        }

        if (x.days < 1 || x.days > verifdays || x.month < 1 || x.month > 12 || x.year < 0 || x.year > 2024) {
            printf("Invalid input. Please enter the date in the correct format.\n");
        }

    } while (x.days < 1 || x.days > verifdays || x.month < 1 || x.month > 12 || x.year < 0 || x.year > 2024);
    return x;
}

int compare_dates(Date date1, Date date2) { // fonction permettant de vérifier quelle date est avant l'autre et que la progression du joueur soit logique
    if (date1.year != date2.year) {
        return date1.year - date2.year;
    } else if (date1.month != date2.month) {
        return date1.month - date2.month;
    } else {
        return date1.days - date2.days;
    }
}
