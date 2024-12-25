#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct MaterialType {
    char name[50];     // Malzeme adı
    float weight;      // Ağırlık (kg)
    int quantity;      // Mevcut toplam miktar
    int loaded;        // Trene yüklenmiş miktar
} MaterialType;

// Malzeme fonksiyon prototipleri
MaterialType* create_material(const char* name, float weight, int quantity);
void display_material(const MaterialType* material);
void free_material(MaterialType* material);

#endif // MATERIAL_H