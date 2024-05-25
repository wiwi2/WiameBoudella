#include <stdio.h>
#include "input.h"
#include "datetime_util.h"
#include "athlete_training.h"
#include "file_io.h"

int main() {
// création des athlètes
    Athlete athletes[] = {
        {"Hari"},
        {"Rayan"},
        {"Amine"},
        {"Dahmane"},
        {"Hicham"}
    };

   // données d'entraînement pour chaque athlète
    Training hari_trainings[] = {
        {"2024-05-01" , "100m" , "00h00m12.5s" },
        {"2024-05-05" , "400m" , "00h00m58.3s" },
        {"2024-04-02" , "100m" , "00h00m13.5s" },
        {"2024-11-18" , "100m" , "00h00m10.5s"},
        {"2024-05-10" , "5000m" , "00h21m45s" },
        {"2024-05-12" , "Relay4x400m" , "00h3m32s" , 3},
        {"2024-03-17" , "400m" , "00h00m60.3s"},
        {"2024-06-23" , "5000m" , "00h22m45s"},
        {"2024-05-24" , "Relay4x400m" , "00h3m50s" , 2},
        {"2024-06-24" , "Marathon" , "3h00m32s" },
    };
    Training rayan_trainings[] = {
        {"2024-05-02" , "100m" , "00h00m11.8s"},
        {"2024-05-06" , "Relay4x400m" , "00h3m52s" , 1 },
        {"2024-05-11" , "Marathon" , "3h30m01s"},
        {"2024-05-05" , "400m" , "00h00m58.3s"},
        {"2024-02-10" , "5000m" , "00h22m45s"},
       {"2024-05-12" , "100m" , "00h00m11.21s"},
        {"2024-03-25" , "Relay4x400m" , "00h3m24s", 3},
        {"2024-04-23" , "Marathon" , "3h25m00s"},
        {"2024-02-03" , "400m" , "00h00m58.28s"},
        {"2024-01-04" , "5000m" , "00h21m43s"}
    };
    Training amine_trainings[] = {
        {"2024-05-02" , "100m" , "00h00m11.8s"},
        {"2024-05-03" , "400m" , "00h51.2s"},
        {"2024-05-07" , "5000m" , "00h19m15s"},
        {"2024-05-12" , "Marathon" , "3h15m00s"},
        {"2024-02-23" , "Relay4x400m" , "00h3m36s", 2},
        {"2024-05-23" , "100m" , "00h00m12.2s"},
        {"2024-03-03" , "400m" , "00h50.3s"},
        {"2024-02-14" , "5000m" , "00h21m13s"},
        {"2024-03-13" , "Marathon" , "3h12m00s"},
        {"2024-08-12" , "Relay4x400m" , "00h3m40s", 2}
    };
    Training dahmane_trainings[] = {
        {"2024-05-04" , "100m" , "00h00m11.5s"},
        {"2024-05-08" , "400m" , "00h00m52.4s"},
        {"2024-05-13" , "5000m" , "00h19m20s"},
        {"2024-08-12" , "Relay4x400m" , "00h3m40s", 3},
        {"2024-05-12" , "Marathon" , "3h15m00s"},
        {"2024-05-03" , "100m" , "00h00m10.5s"},
        {"2024-05-17" , "400m" , "00h00m53.4s"},
        {"2024-05-12" , "5000m" , "00h19m18s"},
        {"2024-08-06" , "Relay4x400m" , "00h3m23s", 1},
        {"2024-03-02" , "Marathon" , "3h08m00s"}
    };
    Training hicham_trainings[] = {
        {"2024-05-09" , "100m" , "00h00m11.1s"},
        {"2024-05-14" , "400m" , "00h00m52.1s"},
        {"2024-05-19" , "5000m" , "00h15m45s"},
        {"2024-07-06" , "Relay4x400m" , "00h3m23s", 1},
        {"2024-03-02" , "Marathon" , "3h08m02s"},
        {"2024-05-09" , "100m" , "00h00m12.3s"},
        {"2024-05-14" , "400m" , "00h00m53.1s"},
        {"2024-05-19" , "5000m" , "00h15m22s"},
        {"2024-08-12" , "Relay4x400m" , "00h3m31s", 2},
        {"2024-03-02" , "Marathon" , "3h02m02s"}
    };

 // écriture des données d'entraînement dans des fichiers pour chaque athlète
    write_training_data("Hari.txt", hari_trainings, sizeof(hari_trainings) / sizeof(hari_trainings[0]));
    write_training_data("Rayan.txt", rayan_trainings, sizeof(rayan_trainings) / sizeof(rayan_trainings[0]));
    write_training_data("Amine.txt", amine_trainings, sizeof(amine_trainings) / sizeof(amine_trainings[0]));
    write_training_data("Dahmane.txt", dahmane_trainings, sizeof(dahmane_trainings) / sizeof(dahmane_trainings[0]));
    write_training_data("Hicham.txt", hicham_trainings, sizeof(hicham_trainings) / sizeof(hicham_trainings[0]));

 // affichage de la liste des athlètes avec des numéros associés
    printf("\nAthletes list :\n");
    for (int i = 0; i < sizeof(athletes) / sizeof(athletes[0]); i++) {
        printf("%d. %s\n", i + 1, athletes[i].name);
    }


    int user_choice;

    do {
        printf("\nDo you want the history of an athlete ? (1 for Yes, 2 for No) : \n");
        user_choice = get_int_input(); // on vérifie que ce que l’utilisateur entre est bon (comme à chaque fois)

        if (user_choice == 1) {
            int athlete_choice;
            do {
                printf("Choose the athlete that you want to check up (1 to %ld) : \n", sizeof(athletes) / sizeof(athletes[0])); // sizeof(athletes)/sizeof(athletes[0]) correspond au nombre d’athlètes au total (athlètes étant une structure..)
                athlete_choice = get_int_input(); // vérification que le choix de l’utilisateur est bon 
                if (athlete_choice < 1 || athlete_choice > sizeof(athletes) / sizeof(athletes[0])) { 
                    printf("\nInvalid choice.\n");
                }
            } while (athlete_choice < 1 || athlete_choice > sizeof(athletes) / sizeof(athletes[0]));

            char filename[100];
            sprintf(filename, "%s.txt", athletes[athlete_choice - 1].name); // on récupère grâce au choix de l’utilisateur le nom de l’athlète et ouvre le fichier correspondant
            get_trainings(filename);

            do {
                printf("\nDo you want to add practices to this athlete ? (1 for Yes, 2 for No) : \n");
                user_choice = get_int_input(); // vérification
                if (user_choice == 1) {
                    add_training(filename);
                } else if (user_choice != 2) {
                    printf("\nInvalid answer.\n");
                }
            } while (user_choice != 1 && user_choice != 2);
        } else if (user_choice != 2) {
            printf("\nInvalid answer.\n");
        }
    } while (user_choice != 2);



    do{
    printf("\nDo you want to see a top of the best athletes ? (1 for Yes, 2 for No.)\n");
    user_choice = get_int_input(); // vérification 
    } while(user_choice !=1 && user_choice!=2); 
    char choice2[100];
    int top;

    if (user_choice == 1) {
        do {
            printf("\nOf which practice ? : Write : \n 1 for 100m \n 2 for 400m \n 3 for 5000m \n 4 for Marathon \n 5 for Relay4x400m \n");
            scanf("%s", choice2);
        } while (strcmp(choice2, "5") > 0 || strcmp(choice2, "1") < 0); // on va poser la question jusqu’à ce que ça marche 

        if (strcmp(choice2, "1") == 0) { // on met en lien le choix de l’utilisateur et l'entraînement qui y correspond 
            strcpy(choice2, "100m");
        } else if (strcmp(choice2, "2") == 0) {
            strcpy(choice2, "400m");
        } else if (strcmp(choice2, "3") == 0) {
            strcpy(choice2, "5000m");
        } else if (strcmp(choice2, "4") == 0) {
            strcpy(choice2, "Marathon");
        } else if(strcmp(choice2, "5")==0){
            strcpy(choice2,"Relay4x400m");
        }

        printf("\nYou selected: %s\n", choice2);

        do {
            printf("\nWhat is the top that you want ? (Minimum=1 and Maximum=5)\n");
            top = get_int_input(); // vérification 
        } while (top < 1 || top > 5);

        top_athletes(athletes, 5, choice2, top);
    }

    int choice; 
    int athlete_choice; 
    do {
        printf("\nDo you want to see the summary of an athlete ? (1 for Yes, 2 for No) : \n");
        choice = get_int_input(); // vérification du choix 

        if (choice == 1) {
            char filename[100];
            do {
                printf("Choose an athlete (1: Hari, 2: Rayan, 3: Amine, 4: Dahmane, 5: Hicham) : ");
                athlete_choice = get_int_input(); // vérification 
            } while (athlete_choice < 1 || athlete_choice > 5);

            char word[100];
            int choice3;
            do {
                printf("\nOf which practice ? : Write : \n 1 for 100m \n 2 for 400m \n 3 for 5000m \n 4 for Marathon \n 5 for Relay4x400m \n");
                choice3 = get_int_input();
            } while (choice3 < 1 || choice3 > 5); // on va redemander jusqu’à ce que le choix est bon 

            switch (choice3) { // on met en lien le choix et l’entraînement qui correspond 
                case 1:
                    strcpy(word, "100m");
                    break;
                case 2:
                    strcpy(word, "400m");
                    break;
                case 3:
                    strcpy(word, "5000m");
                    break;
                case 4:
                    strcpy(word, "Marathon");
                    break;
                case 5:
                    strcpy(word, "Relay4x400m");
                    break;
                default:
                    printf("Input error\n");
                    break;
            }

            sprintf(filename, "%s.txt", athletes[athlete_choice - 1].name); // d’après le choix, on récupère l’athlète correspondant, lui ajoute txt pour ensuite pouvoir l’ouvrir dans la fonction athlete_summary 
            athlete_summary(filename, word);
        }
    } while (choice != 2);

    int choice_progress;// variable pour stocker le choix de l'utilisateur (1 ou 2)
    int athletechoice;  // variable pour stocker le choix de l'athlète (1 à 5)
    FILE* file;
    char filename[100];
    char typetraining[100];
    int choice4;

    do {
        printf("\nDo you want to see the athlete progression ? (1 for Yes, 2 for No) : \n");
        choice_progress = get_int_input(); // vérification 

        if (choice_progress == 1) {
            do {
                printf("\nChoose an athlete (1: Hari, 2: Rayan, 3: Amine, 4: Dahmane, 5: Hicham) : \n ");
                athletechoice = get_int_input(); // vérification 
            } while (athletechoice < 1 || athletechoice > 5);

            sprintf(filename, "%s.txt", athletes[athletechoice - 1].name); // on récupère le choix de l’athlète pour ensuite ouvrir le fichier correspondant 
            file = fopen(filename, "r");

            char line[100];
            get_trainings(filename); 

            do {
                printf("\nOf which practice ? : Write : \n 1 for 100m \n 2 for 400m \n 3 for 5000m \n 4 for Marathon \n 5 for Relay 4*400 m \n");
                choice4 = get_int_input(); // vérification 
            } while (choice4 < 1 || choice4 > 5);

            switch (choice4) { // on copie dans typetraining l’entraînement en fonction du choix de l’utilisateur (1, 2, 3, 4 ou 5)
                case 1:
                    strcpy(typetraining, "100m");
                    break;
                case 2:
                    strcpy(typetraining, "400m");
                    break;
                case 3:
                    strcpy(typetraining, "5000m");
                    break;
                case 4:
                    strcpy(typetraining, "Marathon");
                    break;
                case 5:
                    strcpy(typetraining, "Relay4x400m");
                    break;
                default:
                    printf("\nInput error\n");
                    break;
            }
            Date date1;
            Date date2;
            char linedate[256];
            printf("\nWhat is the first date ?\n"); 
            date1 = constr_Date(); // récupération de la date grâce à la fonction 
            sprintf(linedate, "%d-%d-%d", date1.year, date1.month, date1.days); // stocke la date dans ‘linedate’ sous forme d’une ligne de chaîne de caractères
            printf("\nWhat is the second date ?\n");
            date2 = constr_Date();
            sprintf(linedate, "%d-%d-%d", date2.year, date2.month, date2.days); // pareil ici 
            athlete_progression(filename, typetraining, date1, date2); // on renvoie vers la fonction pour calculer la progression 
        }
    } while (choice_progress != 2);
printf("\n\n\n\n\n\n\nGoodbye, see you soon ! :D\n");
    fclose(file);
    return 0;
}
