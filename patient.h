#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
struct patient
{
    char name[64];
    int id;
};
void clear1();
void add_patient(FILE *fp, char *name, int id, const int isGuahao);
void del_patient();

void del_patient_bynameid(char *name, int id);
struct patient *load_patient(int *count);