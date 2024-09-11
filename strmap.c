#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strmap.h"

//Hash function that takes a key and returns a hash value
unsigned int hash(char *key){
    int length = strlen(key);
    unsigned int hash = 0;
    /*for(int i = 0; i < length; i++){
        hash = ((hash << 5) + key[i]) % MAX_BUCKETS;
    }*/
    return hash;
}

strmap_t *strmap_create(int numbuckets) {
    // Ensure the number of buckets is at least MIN_BUCKETS
    if (numbuckets < MIN_BUCKETS) {
        numbuckets = MIN_BUCKETS;
    }

    // Allocate memory for the string map (strmap_t)
    strmap_t *new_map = (strmap_t *)malloc(sizeof(strmap_t));
    if (new_map == NULL) {
        return NULL; // Memory allocation failure
    }

    // Initialize the number of buckets
    new_map->strmap_nbuckets = numbuckets;
    new_map->strmap_size = 0; // Initially, no elements

    // Allocate memory for the bucket array
    new_map->strmap_buckets = (smel_t **)malloc(numbuckets * sizeof(smel_t *));
    if (new_map->strmap_buckets == NULL) {
        free(new_map); // Clean up in case of failure
        return NULL;
    }

    // Initialize all buckets to NULL
    for (int i = 0; i < numbuckets; i++) {
        new_map->strmap_buckets[i] = NULL;
    }

    return new_map; // Return the initialized map
}

void *strmap_put(strmap_t *m, char *key, void *value) {
    // Calculate the hash value and ensure it's within the bucket array bounds
    unsigned int hash_value = hash(key) % m->strmap_nbuckets;

    // Check if the key already exists in the map
    smel_t *current = m->strmap_buckets[hash_value];
    while (current != NULL) {
        if (strcmp(current->sme_key, key) == 0) {
            // Key already exists, update value and return old value
            void *old_value = current->sme_value;
            current->sme_value = value;
            return old_value;
        }
        current = current->sme_next;
    }

    // Key doesn't exist, create a new element
    smel_t *new_element = (smel_t *)malloc(sizeof(smel_t));
    if (new_element == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Duplicate the key to avoid modifying the original string
    new_element->sme_key = strdup(key);
    if (new_element->sme_key == NULL) {
        free(new_element); // Clean up on failure
        return NULL;
    }

    // Assign the value and link the new element to the list
    new_element->sme_value = value;
    new_element->sme_next = m->strmap_buckets[hash_value]; // Insert at the head of the list
    m->strmap_buckets[hash_value] = new_element;           // Update the bucket head

    // Increment the size of the map
    m->strmap_size++;

    // Return NULL because the key was new (no old value to return)
    return NULL;
}

void strmap_dump(strmap_t *m) {

    // Iterate through each bucket
    for (int i = 0; i < m->strmap_nbuckets; i++) {
        smel_t *current = m->strmap_buckets[i];

        // Print bucket index
        printf("Bucket %d:", i);

        // Traverse the linked list in the current bucket
        if (current == NULL) {
            printf(" (empty)\n");
        } else {
            // Iterate through each element in the bucket
            while (current != NULL) {
                printf(" -> {Key: %s, Value: %p}", current->sme_key, current->sme_value);
                current = current->sme_next;
            }
            printf("\n");
        }
    }
}

int strmap_getsize(strmap_t *m) {
    return m->strmap_size;
}

void *strmap_remove(strmap_t *m, char *key) {
    // Calculate the hash value and ensure it's within the bucket array bounds
    unsigned int hash_value = hash(key) % m->strmap_nbuckets;

    // Pointer to traverse the linked list in the bucket
    smel_t *current = m->strmap_buckets[hash_value];
    smel_t *previous = NULL;

    // Traverse the list to find the key
    while (current != NULL) {
        if (strcmp(current->sme_key, key) == 0) {
            // Found the key, we will remove this element
            if (previous == NULL) {
                // The element is at the head of the list
                m->strmap_buckets[hash_value] = current->sme_next;
            } else {
                // Bypass the element in the linked list
                previous->sme_next = current->sme_next;
            }

            // Save the value to return
            void *value = current->sme_value;

            // Free the memory allocated for the key and the element
            free(current->sme_key);
            free(current);

            // Decrease the map size
            m->strmap_size--;

            // Return the value associated with the removed key
            return value;
        }

        // Move to the next element in the list
        previous = current;
        current = current->sme_next;
    }

    // Key was not found
    return NULL;
}

void *strmap_get(strmap_t *m, char *key) {
    // Calculate the hash value and ensure it's within the bucket array bounds
    unsigned int hash_value = hash(key) % m->strmap_nbuckets;

    // Traverse the linked list in the appropriate bucket
    smel_t *current = m->strmap_buckets[hash_value];
    while (current != NULL) {
        // Check if the current element's key matches the given key
        if (strcmp(current->sme_key, key) == 0) {
            return current->sme_value; // Key found, return the associated value
        }
        current = current->sme_next; // Move to the next element
    }

    // Key was not found
    return NULL;
}
int strmap_getnbuckets(strmap_t *m){
    return m->strmap_nbuckets;
}

//
// Created by ferna on 9/8/2024.
//
