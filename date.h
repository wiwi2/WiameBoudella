#ifndef DATE_H
#define DATE_H

typedef struct {
    int days;
    int month;
    int year;
} Date;

Date constr_Date();
int compare_dates(Date date1, Date date2);

#endif
