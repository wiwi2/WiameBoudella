//gère les entrées de l'utilisateur (erreur tout ça)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int is_valid_integer(const char *str) { // vérifie que ce qui est entrer par l'utilisateur est bien un chiffre (elle le fait chiffre par chiffre)
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int get_int_input() { // récupère le choix de l'utilisateur et vérifie que c'est un chiffre entier avant de convertir en entier si c'est bon
    char input[100];
    int number;
    while (1) {
        scanf("%s", input);
        if (is_valid_integer(input)) {
            number = atoi(input); // atoi sert à convertir une chaine de caractère en un entier (exemple : "123" -> 123)
            break;
        } else {
            printf("\nInvalid input. Please enter a valid number.\n");
        }
    }
    return number;
}
float get_float_input() { // récupère le choix de l'utilisateur et vérifie que c'est un chiffre réel avant de continuer  
    char input[100];
    float number;
    while (1) {
        scanf("%s", input);
        char *endptr;
        number = strtof(input, &endptr); // utilisée pour convertir une chaîne de caractères en un nombre à virgule flottante de type float.
        if (*endptr == '\0') {
            break;
        } else {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }
    return number;
}
