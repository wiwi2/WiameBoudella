#ifndef FILE_IO_H
#define FILE_IO_H

#include "athlete_training.h" 

void write_training_data(const char* filename, Training* trainings, int num_trainings);
void get_trainings(const char *filename);
//void add_training(const char *filename);

#endif /* FILE_IO_H */
