#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// Patient structure
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient* next;
} Patient;

Patient* head = NULL;  // Head of the patient linked list

// Create a new patient
Patient* createPatient(int id, const char* name, int age, const char* disease) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (newPatient == NULL) return NULL;

    newPatient->id = id;

    strncpy(newPatient->name, name, sizeof(newPatient->name) - 1);
    newPatient->name[sizeof(newPatient->name) - 1] = '\0';

    newPatient->age = age;

    strncpy(newPatient->disease, disease, sizeof(newPatient->disease) - 1);
    newPatient->disease[sizeof(newPatient->disease) - 1] = '\0';

    newPatient->next = NULL;
    return newPatient;
}

// Add patient to the list
DLL_EXPORT void add_patient(int id, const char* name, int age, const char* disease) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Duplicate ID found at address: %p\n", (void*)temp);
            return; // Duplicate found
        }
        temp = temp->next;
    }

    Patient* newPatient = createPatient(id, name, age, disease);
    if (!newPatient) return;

    if (head == NULL) {
        head = newPatient;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPatient;
    }

    printf("Added patient at memory address: %p\n", (void*)newPatient);
}

// Search patient by ID
Patient* search_patient(int id) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Found patient at address: %p\n", (void*)temp);
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Get patient details (for Python call)
DLL_EXPORT int get_patient_info(int id, char* name, int* age, char* disease) {
    Patient* p = search_patient(id);
    if (!p) return 0;

    strcpy(name, p->name);
    *age = p->age;
    strcpy(disease, p->disease);
    return 1;
}

// Free all patient memory
DLL_EXPORT void free_all_patients() {
    Patient* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}