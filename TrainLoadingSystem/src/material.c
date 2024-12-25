#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/material.h"

// Yeni malzeme oluşturma
MaterialType* create_material(const char* name, float weight, int quantity) {
    MaterialType* material = (MaterialType*)malloc(sizeof(MaterialType));
    if (!material) {
        fprintf(stderr, "Bellek tahsisi başarısız oldu!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(material->name, name, sizeof(material->name));
    material->weight = weight;
    material->quantity = quantity;
    material->loaded = 0;
    return material;
}

// Malzeme bilgilerini gösterme
void display_material(const MaterialType* material) {
    if (!material) return;

    printf("Material: %s, Weight: %.2f, Quantity: %d, Loaded: %d\n",
           material->name, material->weight, material->quantity, material->loaded);
}

// Malzeme belleğini serbest bırakma
void free_material(MaterialType* material) {
    free(material);
}