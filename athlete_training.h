#ifndef ATHLETE_TRAINING_H
#define ATHLETE_TRAINING_H

#include "date.h"
#include "time1.h"

typedef struct {
    char name[50];
} Athlete;

typedef struct {
    char date[50];
    char type[50];
    char time[50];
    int position;
} Training;

void add_training(const char *filename);
void athlete_summary(const char* filename, const char* type);
void athlete_progression(const char* filename, const char* type, Date date1, Date date2);
void top_athletes(Athlete *athletes, int num_ath, const char* type, int num_top);

#endif
