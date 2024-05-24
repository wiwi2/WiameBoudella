#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "athlete_training.h"
#include "input.h"
#include "datetime_util.h"
#include "file_util.h"

void add_training(const char *filename) {
    FILE* file;
    Training new;
    Date date;
    Time time;
    char linedate[100];
    char linetime[100];
    char line[256];
    char date1[100];

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("What is the date?\n");
    date = constr_Date();
    sprintf(linedate, "%04d-%02d-%02d", date.year, date.month, date.days);

    int type_code;
    do {
        printf("What is the type of the practice? Write:\n 1 for 100m\n 2 for 400m\n 3 for 5000m\n 4 for marathon\n 5 for Relay4x400m\n");
        type_code = get_int_input(); 
    } while (type_code > 5 || type_code < 1);

    if (type_code == 5) {
        int found = 0;
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%s ; %*s ; %*s ; %*d", date1);
            if (strcmp(date1, linedate) == 0) {
                printf("Error: you can’t add a second relay practice in the same day.\n");
                found = 1;
                break;
            }
        }
        fclose(file);
        if (found) {
            return;
        }
    } else {
        fclose(file);
    }

    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    switch (type_code) {
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
    time = Constr_time();
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
    if (type_code == 5) {
        fprintf(file, "%s ; %s ; %s ; %d\n", linedate, new.type, linetime, new.position);
    } else {
        fprintf(file, "%s ; %s ; %s\n", linedate, new.type, linetime);
    }
    fclose(file);
}

void athlete_summary(const char* filename, const char* type) {
    FILE *file;
    Time t;
    char line[256];
    double best_time = -20;
    double worst_time = 9999999;
    double total_time = 0;
    int num_trainings = 0;
