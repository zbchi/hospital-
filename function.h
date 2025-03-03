#include "doctor.h"
#include "patient.h"
#include <stdio.h>
#include <time.h>
struct registration
{
    int doctor_id;
    int patient_id;
    char date[12];
};
struct registration *load_registration(int *count);
void get_time(char *date);
void unregister();
void Register();
void adddel();
void print();
void print_registration();
void print_doctors();
void print_patients();
void add_registration(int doctor_id, int patient_id, char *date);
void any_continue();
void del_registration(struct registration *unreg);
void print_reg_patient(int id, int *undoctor_id, char (*date)[12], int *undoctor_count, struct doctor *undoctor);
void patient_search();
void sort();
void doctor_search();