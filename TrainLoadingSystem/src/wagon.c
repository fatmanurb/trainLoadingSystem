#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/wagon.h"

// Yeni vagon oluşturma
Wagon* create_wagon(int wagon_id, float max_weight) {
    Wagon* wagon = (Wagon*)malloc(sizeof(Wagon));
    if (!wagon) {
        fprintf(stderr, "Bellek tahsisi başarısız oldu!\n");
        exit(EXIT_FAILURE);
    }
    wagon->wagon_id = wagon_id;
    wagon->max_weight = max_weight;
    wagon->current_weight = 0.0f;
    wagon->loaded_materials = NULL;
    wagon->next = NULL;
    wagon->prev = NULL;
    return wagon;
}

// Vagona malzeme yükleme
int load_material_to_wagon(Wagon* wagon, const char* material_name, float weight, int quantity) {
    if (!wagon || weight * quantity > (wagon->max_weight - wagon->current_weight)) {
        fprintf(stderr, "Yükleme hatası: Kapasite aşımı!\n");
        return 0; // Hata durumunda 0 döndür
    }

    LoadedMaterial* material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
    if (!material) {
        fprintf(stderr, "Bellek tahsisi başarısız oldu!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(material->material_name, material_name, sizeof(material->material_name));
    material->weight = weight;
    material->quantity = quantity;
    material->next = wagon->loaded_materials;
    wagon->loaded_materials = material;
    wagon->current_weight += weight * quantity;

    return 1; // Başarılı durumunda 1 döndür
}
// Vagon durumunu görüntüleme
void display_wagon(const Wagon* wagon) {
    if (!wagon) return;

    printf("Wagon ID: %d, Current Weight: %.2f / %.2f\n",
           wagon->wagon_id, wagon->current_weight, wagon->max_weight);

    LoadedMaterial* current = wagon->loaded_materials;
    while (current) {
        printf(" - Material: %s, Weight: %.2f, Quantity: %d\n",
               current->material_name, current->weight, current->quantity);
        current = current->next;
    }
}

// Belleği serbest bırakma
void free_wagon(Wagon* wagon) {
    if (!wagon) return;

    LoadedMaterial* current = wagon->loaded_materials;
    while (current) {
        LoadedMaterial* next = current->next;
        free(current);
        current = next;
    }
    free(wagon);
}