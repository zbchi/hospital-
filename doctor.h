#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct doctor
{
    char name[64];
    int id;
    char dept[64];
};
void clear();
void add_doctor(FILE *fp, char *name, int id, char *dept);
void del_doctor();

void doctor_patients(int doctor_id);
void del_doctor_bynameid(char *name, int id);

struct doctor *load_doctor(int *count);

void sort_doctor(char ch);