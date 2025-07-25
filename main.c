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

// Clear input buffer to avoid leftover characters
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

    printf("\nEnter Patient ID(Number): ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID. Please enter a numeric value.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Patient Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Patient Age: ");
    if (scanf("%d", &age) != 1) {
        printf("Invalid age. Please enter a numeric value.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Disease: ");
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = '\0';

    // Check for duplicate ID
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("A patient with ID %d already exists.\n", id);
            return;
        }
        temp = temp->next;
    }

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
    printf("Patient Memory Address: %p\n", (void*)newPatient);
}

// Display all patients
void viewPatients() {
    if (head == NULL) {
        printf("\nNo patient records found.\n");
        return;
    }

    Patient* temp = head;
    printf("\n--- Patient List ---\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("ID\tName\t\tAge\tDisease\t\tMemory Address\n");
    printf("----------------------------------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("%d\t%-15s\t%d\t%-15s\t%p\n",
               temp->id, temp->name, temp->age, temp->disease, (void*)temp);
        temp = temp->next;
    }
}

// Search patient by ID
void searchPatient() {
    int id;
    printf("\nEnter Patient ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a numeric ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\nMemory Address: %p\n",
                   temp->id, temp->name, temp->age, temp->disease, (void*)temp);
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
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a numeric ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

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

    printf("Deleting patient at memory address: %p\n", (void*)temp);
    free(temp);
    printf("Patient record deleted.\n");
}

// Free all allocated memory
void freeAllPatients() {
    Patient* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        printf("Freeing memory at address: %p\n", (void*)temp);
        free(temp);
    }
}

// Main Menu
int main() {
    int choice;

    do {
    printf("\nChoose an operation:\n");
    printf(" 1. ➕ Add New Patient\n");
    printf(" 2. 📋 View All Patients\n");
    printf(" 3. 🔍 Search for a Patient\n");
    printf(" 4. ❌ Delete a Patient Record\n");
    printf(" 5. 🚪 Exit the System\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5:
                freeAllPatients();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select from 1 to 5.\n");
        }

    } while (choice != 5);

    return 0;
}
