#ifndef WAGON_H
#define WAGON_H

typedef struct LoadedMaterial {
    char material_name[50];
    float weight;
    int quantity;
    struct LoadedMaterial* next;
} LoadedMaterial;

typedef struct Wagon {
    int wagon_id;
    float max_weight;
    float current_weight;
    LoadedMaterial* loaded_materials;
    struct Wagon* next;
    struct Wagon* prev;
} Wagon;

// Wagon fonksiyon prototipleri
Wagon* create_wagon(int wagon_id, float max_weight);
int load_material_to_wagon(Wagon* wagon, const char* material_name, float weight, int quantity);
void display_wagon(const Wagon* wagon);
void free_wagon(Wagon* wagon);

#endif // WAGON_H