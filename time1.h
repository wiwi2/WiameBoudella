#ifndef TIME_H
#define TIME_H

typedef struct {
    int hours;
    int minutes;
    float seconds;
} Time;

double get_time_seconds(const char* time);
Time Constr_time();

#endif
