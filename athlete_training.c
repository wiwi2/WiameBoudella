#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "athlete_training.h"
#include "input.h"
#include "datetime_util.h"
#include "file_util.h"


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
void athlete_summary(const char* filename, const char* type) {  // résumé des performances avec pire et meilleur temps d’un athlète pour un type d’entraînement, tel qu'enregistrer dans un fichier    
    FILE *file;
    Time t;
    char line[256];
    double best_time = -20;  // Initialisation avec une valeur arbitrairement basse destinée à être mise à jour     
    double worst_time = 9999999; // Initialisation avec une valeur arbitrairement haute destinée à être mise à jour
double total_time = 0;
    int num_trainings = 0; // compteur pour le nombre d’entraînements
    file = fopen(filename, "r");  // ouverture du fichier en mode lecture
    if (file == NULL) {
        printf("No training found in the file %s.\n", filename);
        return;
    }

    while (fgets(line, sizeof(line), file)) { // lecture du fichier ligne par ligne
        char temp_type[50];
        double time_seconds = 0.0;
        char recuptime[100];
        sscanf(line, "%*s ; %s ; %s", temp_type, recuptime); // extraction du type et du temps depuis la ligne, ignore la date 
        time_seconds = get_time_seconds(recuptime);  // conversion en secondes
        if (strcmp(temp_type, type) == 0) { // si le type dans le fichier correspond au type demandé 
            num_trainings++; // comptage du nombre d’entraînement pour le calcul du temps moyen
            if (time_seconds > best_time) { // mise à jour du meilleur temps si nécessaire
                best_time = time_seconds;
            }
            if (time_seconds < worst_time) {  // mise à jour du pire temps si nécessaire
                worst_time = time_seconds;
            }
            total_time += time_seconds;// accumulation du temps total pour calculer le temps moyen plus tard
        }
    } 
// }
    fclose(file);
    if (num_trainings == 0) {  // si aucun entraînement trouvé
        printf("\nNo type training %s found for this athlete.\n", type);
    } else {
        printf("Summary of the athlete performances for the %s :\n", type); // affichage du résumé
        printf("Best time : %.2lf seconds\n", best_time); // meilleur temps
        printf("Worst time : %.2lf seconds\n", worst_time);  // pire temps
        printf("Average time : %.2lf seconds\n", total_time/num_trainings); // temps moyen
    }
}

int partition(double arr[], char names[][100], int low, int high) {
// tri rapide, fait un tableau en deux parties autour d'un pivot tel que les éléments à gauche du pivot soient plus petits ou égaux au pivot, et ceux à droite soient plus grands
    double pivot = arr[high]; // le dernier élément du tableau est utilisé comme pivot
    char pivot_name[100]; 
    strcpy(pivot_name, names[high]);  // copie le nom du dernier élément dans le pivot
    int i = low - 1; // initialisation de i, index pour le placement des éléments plus petits que le pivot
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) { // compare les éléments avec le pivot 
            i++; // on déplace i pour un nouvel élément inférieur ou égal au pivot
           // Échanger arr[i] et arr[j]
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            // Échanger names[i] et names[j]
            char temp_name[100];
            strcpy(temp_name, names[i]);
            strcpy(names[i], names[j]);
            strcpy(names[j], temp_name);
        }
    }
    // Échanger arr[i + 1] et arr[high] (ou le pivot), on place le pivot à la position correcte pour séparer les 2 parties du tableau
    double temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

 // Échanger names[i + 1] et names[high]
    strcpy(names[high], names[i + 1]);
    strcpy(names[i + 1], pivot_name);
    return i + 1;  // retourne la position du pivot
}

void quicksort(double arr[], char names[][100], int low, int high) { // sert à faire du tri rapide (utilisation d’un pivot (pi) + trie de manière récursive) 
    if (low < high) {
        int pi = partition(arr, names, low, high); // met les éléments inférieurs ou égaux au pivot à gauche ; les éléments supérieurs à droite 
        quicksort(arr, names, low, pi - 1);  // Trie à gauche du pivot (récursif)
        quicksort(arr, names, pi + 1, high); // Trie à droite du pivot (récursif)
    }
}
void top_athletes(Athlete *athletes, int num_ath, const char* type, int num_top) { // fonction pour classer les athlètes du meilleur au moins bon
   double times[100]; // stockera les temps moyens
    char names[100][100];
    int num_athletes = 0;
    for (int i = 0; i < num_ath; i++) { // boucle pour récupérer les performances de chaque athlète
        char filename[100];
        sprintf(filename, "%s.txt", athletes[i].name);  // création du nom de fichier
        FILE* file = fopen(filename, "r"); // ouverture en mode lecture
        if (file == NULL) {
            printf("\nImpossible to open the file %s.\n", filename);
            continue;
        }
        char line[256];
        int count = 0; // correspondra au nombre d’entraînements en fonction du type demandé
        double total_time = 0.0; // somme des temps pour calculer la moyenne
        if (strcmp(type, "Relay4x400m") == 0) { // si c’est un relais (car le relais a la position en plus)
            while (fgets(line, sizeof(line), file)) { // lecture ligne par ligne
                char temp_type[500]; 
                char temp_time[500];
                int temp_position;
                int items_parsed = sscanf(line, "%*s ; %s ; %s ; %*d", temp_type, temp_time); // on vérifie que sscanf lit bien deux éléments avant de continuer
                if (items_parsed == 2 && strcmp(temp_type, type) == 0) { 
                    total_time += get_time_seconds(temp_time);
                    count++; //on incrémenté pour ensuite l’utiliser pour le calcul de la moyenne 
                }
            }
        } else { // si ce n’est pas un relais (pas de position à prendre en compte) 
            while (fgets(line, sizeof(line), file)) { //lecture ligne par ligne 
                char temp_type[500]; 
                char temp_time[500];
                int items_parsed = sscanf(line, "%*s ; %s ; %s", temp_type, temp_time); 
                if (items_parsed == 2 && strcmp(temp_type, type) == 0) {
                    total_time += get_time_seconds(temp_time);
                    count++;
                }
            }
        }
        fclose(file);
        
        if (count > 0) {
            times[num_athletes] = total_time / count;  // calcul de la moyenne des temps
            strcpy(names[num_athletes], athletes[i].name);   // stockage du nom de l’athlète dans le tableau des noms 
            num_athletes++; // on incrémente pour pouvoir savoir combien d’athlètes participent à l’entraînement dont il est question 
        } else {
            printf("\nNo valid data for %s in file %s.\n", type, filename); 
        }
    }

    quicksort(times, names, 0, num_athletes - 1);   // tri des athlètes par temps moyen 
// affichage des meilleurs athlètes
    printf("\nFor the %s practice, the best athletes are :\n", type);
    for (int i = 0; i < num_top && i < num_athletes; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }

    if (num_top == 3 && num_athletes >= 3) { // message si l’utilisateur demande le top 3 uniquement 
        printf("\nYou should send them to the JO !!!\n");
    }
}
void athlete_progression(const char* filename, const char* type, Date date1, Date date2) { // calcule la différence entre 2 temps à 2 dates et pour un type donné 
    FILE *file;
    char line[256];  //tampon pour lire chaque ligne
    double time1 = 0.0, time2 = 0.0;
    int found1 = 0, found2 = 0; // indicateurs pour savoir si les temps ont été trouvés
    char firstdate[256]; 
    char secdate[256];
    sprintf(firstdate, "%04d-%02d-%02d", date1.year, date1.month, date1.days); // stocke la première date dans ‘firstdate’ sous la forme d’une ligne
    sprintf(secdate, "%04d-%02d-%02d", date2.year, date2.month, date2.days); //stocke la seconde date dans ‘secdate’ sous la forme d’une ligne

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nNo training found in file %s.\n", filename);
        return;
    }

     // Recherche du temps de l'athlète pour l'épreuve à chaque date

    while (fgets(line, sizeof(line), file)) { // lecture ligne par ligne
        char temp_type[50], temp_date[50], temp_time[50]; // on y stockera le type, date et temps de chaque ligne
        if (strcmp(type, "Relay4x400m") == 0) {
            sscanf(line, "%*s ; %s ; %s ; %*d", temp_type, temp_time); // extrait le type et temps, ignore la date (en respectant le même format)
        } else {
            sscanf(line, "%*s ; %s ; %s", temp_type, temp_time); // extrait le type et temps, ignore la date (en respectant le même format)
        }
        if (strcmp(temp_type, type) == 0) { // vérifie si les types correspondent 
            if (strcmp(type, "Relay4x400m") == 0) {
                sscanf(line, "%s ; %*s ; %s ; %*d", temp_date, temp_time);
            } else {
                sscanf(line, "%s ; %*s ; %s", temp_date, temp_time); 
            }
            if (strcmp(temp_date, firstdate) == 0) {
                time1 = get_time_seconds(temp_time);  // temps est converti en secondes et stocké dans time1
                found1 = 1; // indique que le temps est trouvé
            }
            if (strcmp(temp_date, secdate) == 0) {
                time2 = get_time_seconds(temp_time);
                found2 = 1;
            }
            if (found1 && found2) { //  si on a 2 temps, on continue : on peut faire les calculs 
                double difference = time2 - time1;
                if (compare_dates(date1, date2) > 0) { 
                    difference = time1 - time2;
                }
                if (difference < 0) { // 1er cas : il s’est amélioré entre les deux dates
                    printf("\nBetween %s and %s, the time of this athlete decreased by %.2f seconds\n", firstdate, secdate, -difference);
                    printf("YOUHOU! The athlete has progressed!\n");
                } else if (difference > 0) { // 2e cas : il a régressé entre les deux dates
                    printf("\nBetween %s and %s, the time of this athlete increased by %.2f seconds\n", secdate, firstdate, difference);
                    printf("Olala, the athlete has regressed! He should run faster! :(\n");
                } else {
                    printf("\nThe athlete's time has remained the same, that's already something.\n");
                }
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("\nNo matching data found for the given dates.\n");
}

