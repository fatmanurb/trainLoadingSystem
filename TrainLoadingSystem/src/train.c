#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/train.h"

// Yeni tren oluşturma
Train* create_train(const char* train_id) {
    Train* train = (Train*)malloc(sizeof(Train));
    if (!train) {
        fprintf(stderr, "Bellek tahsisi başarısız oldu!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(train->train_id, train_id, sizeof(train->train_id));
    train->first_wagon = NULL;
    train->wagon_count = 0;
    return train;
}

// Trene vagon ekleme
void add_wagon(Train* train, Wagon* wagon) {
    if (!train || !wagon) return;

    if (!train->first_wagon) {
        train->first_wagon = wagon;
    } else {
        Wagon* current = train->first_wagon;
        while (current->next) {
            current = current->next;
        }
        current->next = wagon;
        wagon->prev = current;
    }
    train->wagon_count++;
}

// Boş vagonları kaldırma
void remove_empty_wagons(Train* train) {
    if (!train) return;

    Wagon* current = train->first_wagon;
    while (current) {
        Wagon* next = current->next;
        if (current->current_weight == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            if (train->first_wagon == current) {
                train->first_wagon = current->next;
            }
            free(current);
            train->wagon_count--;
        }
        current = next;
    }
}

// Tren durumunu gösterme
void display_train_status(const Train* train) {
    if (!train) return;

    printf("Train ID: %s\n", train->train_id);
    printf("Wagon Count: %d\n", train->wagon_count);

    Wagon* current = train->first_wagon;
    while (current) {
        printf("Wagon ID: %d, Current Weight: %.2f / %.2f\n",
               current->wagon_id, current->current_weight, current->max_weight);
        current = current->next;
    }
}

// Belleği serbest bırakma
void free_train(Train* train) {
    if (!train) return;

    Wagon* current = train->first_wagon;
    while (current) {
        Wagon* next = current->next;
        free(current);
        current = next;
    }
    free(train);
}