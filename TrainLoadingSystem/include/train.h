#ifndef TRAIN_H
#define TRAIN_H

#include "wagon.h"

// Tren yapısı
typedef struct {
    char train_id[20];
    Wagon* first_wagon;
    int wagon_count;
} Train;

// Tren fonksiyon prototipleri
Train* create_train(const char* train_id);
void add_wagon(Train* train, Wagon* wagon);
void remove_empty_wagons(Train* train);
void display_train_status(const Train* train);
void free_train(Train* train);

#endif // TRAIN_H