#include <stdio.h>
#include <string.h>
#include "file_io.h"

void write_training_data(const char* filename, Training* trainings, int num_trainings) {// permet d'écrire les informations de chaque athlète dans un fichier créé à leur nom
    FILE *file = fopen(filename, "w"); // ouverture du fichier pour écrire dans celui-ci
    if (file == NULL) {
        printf("Error while opening the file %s.\n", filename);
        return;
    }
    
    for (int i = 0; i < num_trainings; i++) {
         if(strcmp(trainings[i].type, "Relay4x400m")==0){
        fprintf(file, "%s ; %s ; %s ; %d\n", trainings[i].date, trainings[i].type, trainings[i].time, trainings[i].position);
         }
        else {fprintf(file, "%s ; %s ; %s\n", trainings[i].date, trainings[i].type, trainings[i].time);
    }}
    fclose(file);
}

void get_trainings(const char *filename) {  // permet d'afficher l'historique des entraînements de l'athlète demandé
    FILE *file;
    char line[256];
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("No training found in the file %s.\n", filename);
        return;
    }
    printf("History of the athlete practices :\n");
      while (fgets(line, sizeof(line), file)) {   // lecture du fichier ligne à ligne
       printf("%s", line);
    }
    fclose(file);
}


void add_training(const char *filename) { // fonction pour ajouter des entrainements à l'athlete choisi 
    FILE* file;
    Training new;
    Date date;
    Time time;
    char linedate[100];
    char linetime[100];
    char line[256];
    char date1[100];


    file = fopen(filename, "r"); // ouverture du fichier en mode lecture pour vérifier les entrées existantes
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("What is the date ?\n");
    date = constr_Date();
    sprintf(linedate, "%04d-%02d-%02d", date.year, date.month, date.days); // on met la date dans le format que l'on veut et la stocke dans linedate pour pouvoir la copier directement après 

    int type_code;
    do {
        printf("What is the type of the practice ? Write:\n 1 for 100m\n 2 for 400m\n 3 for 5000m\n 4 for marathon\n 5 for Relay4x400m\n");
        type_code = get_int_input(); 
    } while (type_code > 5 || type_code < 1);

    if (type_code == 5) { // on vérifie la condition pour le relais : pas 2 relais le même jour !
        int found = 0;  // variable nous indiquant si une même date est trouvée
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%s ; %*s ; %*s ; %*d", date1); // on stocke la date de chaque ligne dans date1
            if (strcmp(date1, linedate) == 0) { // on vérifie si les deux sont les mêmes...
                printf("Error: you can’t add a second relay practice in the same day.\n");
                found = 1;
                break;  // on quitte la boucle si la même date est trouvée pour le relais

            }
        }
        fclose(file); 
        if (found) {
            return; // on quitte la fonction si la même date est trouvée
        }
    } else {
        fclose(file); 
    }

    file = fopen(filename, "a"); // ouverture en a nous permettra d'ajouter à la fin du fichier des nouveaux entrainements
    if (file == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    switch (type_code) { // permet, en fonction du choix de l'utilisateur, de stocker dans new.type l'entraînement correspondant
        case 1:
            strcpy(new.type, "100m");
            break;
        case 2:
            strcpy(new.type, "400m");
            break;
        case 3:
            strcpy(new.type, "5000m");
            break;
        case 4:
            strcpy(new.type, "marathon");
            break;
        case 5:
            strcpy(new.type, "Relay4x400m");
            break;
        default:
            printf("Input error\n");
            fclose(file);
            return;
    }

    printf("What is the time of your athlete?\n");
    time = Constr_time(); // on récupère le temps grâce à cette fonction
    sprintf(linetime, "%dh%dm%.2fs", time.hours, time.minutes, time.seconds);
    if (type_code == 5) {
        do {
            printf("Enter the position of the athlete during the relay: ");
            scanf("%d", &new.position);
            if (new.position < 1 || new.position > 4) {
                printf("False input. Please try again, enter a number between 1 and 4 inclusive.\n");
            }
        } while (new.position < 1 || new.position > 4);
    }
    if (type_code==5){
        fprintf(file, "%s ; %s ; %s ; %d\n", linedate, new.type, linetime, new.position);
    }
    else{
        fprintf(file, "%s ; %s ; %s\n", linedate, new.type, linetime);} // enfin, copie toutes les informations récoltées sur une nouvelle ligne à la fin du fichier 
    fclose(file);
}
