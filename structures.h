#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct { // structure pour récupérer le temps 
    int hours;
    int minutes ;
    float seconds;
} Time;

typedef struct{  // structure pour récupérer la date 
    int days ;
    int month ;
    int year;
}Date ;

typedef struct {  // structure pour récupérer les informations d’un entraînement 
    char date[50];
    char type[50];
    char time[50];
    int position;
} Training;

typedef struct { // structure pour le nom d'un athlète 
    char name[50];
} Athlete;

#endif /* STRUCTURES_H */
