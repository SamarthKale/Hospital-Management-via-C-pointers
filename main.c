#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The Patient struct, modified to match the frontend's needs.
// It still uses a pointer (`next`) to link patients together.
typedef struct Patient {
    int id;
    char name[100];
    char service_type[50];
    char status[20]; // "waiting", "called", "served", "skipped"
    struct Patient* next;
} Patient;

// --- Global Pointers & State ---
// We're still using your pointer system to manage the list.
Patient* queue_head = NULL; // Head pointer for the linked list
Patient* queue_tail = NULL; // Tail pointer for efficient additions
int next_patient_id = 1;    // Global counter for unique IDs

/**
 * Adds a new patient to the end of the queue.
 * This function no longer uses scanf; it takes data as parameters.
 * @param name The name of the patient from the web form.
 * @param service The service type from the web form.
 * @return The ID of the newly created patient.
 */
int enqueue_patient(const char* name, const char* service) {
    Patient* new_patient = (Patient*)malloc(sizeof(Patient));
    if (!new_patient) {
        return -1; // Memory allocation failed
    }

    // Assign data
    new_patient->id = next_patient_id++;
    strncpy(new_patient->name, name, sizeof(new_patient->name) - 1);
    strncpy(new_patient->service_type, service, sizeof(new_patient->service_type) - 1);
    strcpy(new_patient->status, "waiting");
    new_patient->next = NULL;

    // Add to the linked list using our head/tail pointers
    if (queue_head == NULL) { // If the list is empty
        queue_head = new_patient;
        queue_tail = new_patient;
    } else { // Add to the end of the list
        queue_tail->next = new_patient;
        queue_tail = new_patient;
    }

    return new_patient->id;
}

/**
 * Finds the first "waiting" patient and changes their status to "called".
 * This is for the "Call Next Patient" button.
 * @return The ID of the patient who was called, or -1 if no one is waiting.
 */
int dequeue_patient() {
    Patient* current = queue_head;
    while (current != NULL) {
        if (strcmp(current->status, "waiting") == 0) {
            strcpy(current->status, "called");
            return current->id; // Found and updated a waiting patient
        }
        current = current->next;
    }
    return -1; // No waiting patients found
}

/**
 * Updates the status of a specific patient by their ID.
 * This is for the "Serve" and "Skip" buttons.
 * @param id The ID of the patient to update.
 * @param new_status The new status to set.
 * @return 0 on success, -1 if patient not found.
 */
int update_patient_status(int id, const char* new_status) {
    Patient* current = queue_head;
    // Loop through the linked list to find the patient
    while (current != NULL) {
        if (current->id == id) {
            strncpy(current->status, new_status, sizeof(current->status) - 1);
            return 0; // Success
        }
        current = current->next;
    }
    return -1; // Patient not found
}

/**
 * Generates a JSON string representing the entire current queue.
 * This function replaces `viewPatients` and creates output for the web.
 * @param buffer A character buffer to write the JSON string into.
 * @param buffer_size The size of the buffer.
 */
void get_queue_as_json(char* buffer, int buffer_size) {
    // Clear the buffer and start the JSON array
    memset(buffer, 0, buffer_size);
    int offset = snprintf(buffer, buffer_size, "[");

    Patient* current = queue_head;
    int first_item = 1; // Flag to handle commas between JSON objects

    // Traverse the linked list
    while (current != NULL) {
        // We only show patients who are actively in the queue
        if (strcmp(current->status, "served") != 0 && strcmp(current->status, "skipped") != 0) {
            if (!first_item) {
                offset += snprintf(buffer + offset, buffer_size - offset, ",");
            }
            // Append the patient's data as a JSON object
            offset += snprintf(buffer + offset, buffer_size - offset,
                "{\"id\": %d, \"name\": \"%s\", \"service_type\": \"%s\", \"status\": \"%s\"}",
                current->id, current->name, current->service_type, current->status);
            first_item = 0;
        }
        current = current->next;
    }

    // End the JSON array
    snprintf(buffer + offset, buffer_size - offset, "]");
}