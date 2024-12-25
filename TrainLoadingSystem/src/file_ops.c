#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_ops.h"

// Treni dosyaya kaydetme
void save_train_to_file(const Train* train, const char* filename) {
    if (!train || !filename) return;

    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Dosya açılamadı: %s\n", filename);
        return;
    }

    fprintf(file, "TRAIN:%s:%d\n", train->train_id, train->wagon_count);
    Wagon* current = train->first_wagon;
    while (current) {
        fprintf(file, "WAGON:%d:%.2f:%.2f\n", current->wagon_id, current->max_weight, current->current_weight);
        LoadedMaterial* material = current->loaded_materials;
        while (material) {
            fprintf(file, "L:%s:%.2f:%d\n", material->material_name, material->weight, material->quantity);
            material = material->next;
        }
        current = current->next;
    }

    fclose(file);
}

// Treni dosyadan yükleme
Train* load_train_from_file(const char* filename) {
    if (!filename) return NULL;

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Dosya açılamadı: %s\n", filename);
        return NULL;
    }

    char line[256];
    Train* train = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "TRAIN:", 6) == 0) {
            char train_id[20];
            int wagon_count;
            sscanf(line, "TRAIN:%19[^:]:%d", train_id, &wagon_count);
            train = create_train(train_id);
        } else if (strncmp(line, "WAGON:", 6) == 0 && train) {
            int wagon_id;
            float max_weight, current_weight;
            sscanf(line, "WAGON:%d:%f:%f", &wagon_id, &max_weight, &current_weight);
            Wagon* wagon = create_wagon(wagon_id, max_weight);
            wagon->current_weight = current_weight;
            add_wagon(train, wagon);
        } else if (strncmp(line, "L:", 2) == 0) {
            char material_name[50];
            float weight;
            int quantity;
            sscanf(line, "L:%49[^:]:%f:%d", material_name, &weight, &quantity);
            Wagon* wagon = train->first_wagon;
            while (wagon && wagon->next) wagon = wagon->next; // Son vagonu bul
            if (wagon) load_material_to_wagon(wagon, material_name, weight, quantity);
        }
    }

    fclose(file);
    return train;
}