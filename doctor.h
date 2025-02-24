#include <stdio.h>
struct doctor
{
    char name[64];
    int id;
    char dept[64];
};
void add_doctor(FILE *fp, char *name, int id, char *dept);
void del_doctor();
void print_doctor(struct doctor *doctor);
void doctor_patients(int doctor_id);
void pos_doctor_byid(int doctor_id);
void pos_doctor_byname(char doctor_name);
