#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient Structure
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient* next;
} Patient;

Patient* head = NULL; // Head pointer for linked list

// Function to create a new patient node
Patient* createPatient(int id, char name[], int age, char disease[]) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->next = NULL;
    return newPatient;
}

// Add patient to list
void addPatient() {
    int id, age;
    char name[50], disease[50];

    printf("\nEnter Patient ID: ");
    scanf("%d", &id);
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Patient Age: ");
    scanf("%d", &age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", disease);

    Patient* newPatient = createPatient(id, name, age, disease);

    if (head == NULL) {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPatient;
    }

    printf("Patient added successfully!\n");
}

// Display all patients
void viewPatients() {
    if (head == NULL) {
        printf("\nNo patient records found.\n");
        return;
    }

    Patient* temp = head;
    printf("\n--- Patient List ---\n");
    while (temp != NULL) {
        printf("\nID: %d\nName: %s\nAge: %d\nDisease: %s\n", temp->id, temp->name, temp->age, temp->disease);
        temp = temp->next;
    }
}

// Search patient by ID
void searchPatient() {
    int id;
    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n", temp->id, temp->name, temp->age, temp->disease);
            return;
        }
        temp = temp->next;
    }

    printf("Patient with ID %d not found.\n", id);
}

// Delete patient by ID
void deletePatient() {
    int id;
    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &id);

    Patient* temp = head;
    Patient* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Patient record deleted.\n");
}

// Main Menu
int main() {
    int choice;

    do {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addPatient(); break;
        case 2: viewPatients(); break;
        case 3: searchPatient(); break;
        case 4: deletePatient(); break;
        case 5: printf("Exiting...\n"); break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}