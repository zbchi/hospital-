#include <stdio.h>
struct patient
{
    char name[64];
    int id;
};
void add_patient(FILE *fp, char *name, int id);
void del_patient();
void print_patient();
void pos_patient_byid(int patient_id);
void pos_patient_byname(char patient_name);
void del_patient_byid(FILE *fp, int id);
void del_patient_byname(FILE *fp, char *name);
