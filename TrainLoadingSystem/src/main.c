#include <stdio.h>
#include <stdlib.h>
#include "../include/train.h"
#include "../include/wagon.h"
#include "../include/material.h"
#include "../include/file_ops.h"
#include "../include/utils.h"

// Menü başlığını yazdırma
void display_menu() {
    printf("=== Train Loading Management System ===\n");
    printf("1. Load train status from file\n");
    printf("2. Load material to train (from first suitable wagon)\n");
    printf("3. Load material to specific wagon\n");
    printf("4. Unload material (starting from the last wagon)\n");
    printf("5. Unload material from a specific wagon\n");
    printf("6. Display train status\n");
    printf("7. Display materials status\n");
    printf("8. Empty the train (remove all wagons and materials)\n");
    printf("9. Save train status to file\n");
    printf("10. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    Train* train = create_train("T123"); // Tren oluşturuluyor
    Wagon* default_wagon = create_wagon(1, 1000.0); // 1. vagon, max ağırlık 1000kg
    add_wagon(train, default_wagon); // Varsayılan vagona ekle
    int choice;
    char filename[50];
    MaterialType* materials[3]; // Üç tür malzeme için dizi

    // Malzemeleri oluştur
    materials[0] = create_material("Large Box", 200.0, 50);
    materials[1] = create_material("Medium Box", 150.0, 50);
    materials[2] = create_material("Small Box", 100.0, 50);

    while (1) {
        clear_screen();
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Tren durumunu dosyadan yükleme
                printf("Enter filename to load train status: ");
                scanf("%s", filename);
                Train* loaded_train = load_train_from_file(filename);
                if (loaded_train) {
                    free_train(train); // Mevcut treni serbest bırak
                    train = loaded_train; // Yeni treni ata
                    printf("Train status loaded successfully from %s.\n", filename);
                } else {
                    printf("Failed to load train status from file.\n");
                }
                getchar(); getchar(); // Kullanıcının enter basmasını bekle
                break;

            case 2:
                // İlk uygun vagona malzeme yükle
                printf("Choose material to load:\n");
                for (int i = 0; i < 3; i++) {
                    printf("%d. ", i + 1);
                    display_material(materials[i]);
                }
                int material_choice;
                printf("Enter material choice: ");
                scanf("%d", &material_choice);
                if (material_choice < 1 || material_choice > 3) {
                    printf("Invalid material choice!\n");
                } else {
                    MaterialType* selected_material = materials[material_choice - 1];
                    if (selected_material->quantity > 0) {
                        int result = load_material_to_wagon(train->first_wagon, selected_material->name,
                                                            selected_material->weight, 1);
                        if (result) { // Eğer başarılıysa
                            selected_material->quantity--;
                            selected_material->loaded++;
                            printf("Material loaded successfully.\n");
                        } else {
                            printf("Failed to load material to the wagon.\n");
                        }
                    } else {
                        printf("No more materials available to load.\n");
                    }
                }
                getchar(); getchar();
                break;

            case 3:
                // Belirli bir vagona malzeme yükleme
                printf("Enter wagon ID to load material: ");
                int wagon_id;
                scanf("%d", &wagon_id);
                Wagon* target_wagon = train->first_wagon;
                while (target_wagon && target_wagon->wagon_id != wagon_id) {
                    target_wagon = target_wagon->next;
                }
                if (target_wagon) {
                    printf("Choose material to load:\n");
                    for (int i = 0; i < 3; i++) {
                        printf("%d. ", i + 1);
                        display_material(materials[i]);
                    }
                    scanf("%d", &material_choice);
                    if (material_choice >= 1 && material_choice <= 3) {
                        MaterialType* selected_material = materials[material_choice - 1];
                        load_material_to_wagon(target_wagon, selected_material->name,
                                               selected_material->weight, 1);
                        selected_material->quantity--;
                        selected_material->loaded++;
                        printf("Material loaded successfully to wagon %d.\n", wagon_id);
                    } else {
                        printf("Invalid material choice!\n");
                    }
                } else {
                    printf("Wagon with ID %d not found.\n", wagon_id);
                }
                getchar(); getchar();
                break;

            case 4:
                // Malzeme boşaltma (sondan başlayarak)
                printf("Unloading materials from the last wagon...\n");
                Wagon* last_wagon = train->first_wagon;
                while (last_wagon && last_wagon->next) {
                    last_wagon = last_wagon->next; // Son vagona git
                }
                if (last_wagon) {
                    // Boşaltma işlemi
                    while (last_wagon->loaded_materials) {
                        LoadedMaterial* material = last_wagon->loaded_materials;
                        last_wagon->loaded_materials = material->next;
                        free(material); // Bellek boşaltma
                    }
                    last_wagon->current_weight = 0; // Vagonu boşalt
                    printf("Materials unloaded successfully from the last wagon.\n");
                }
                getchar(); getchar();
                break;

            case 5:
                // Belirli bir vagondan malzeme boşaltma
                printf("Enter wagon ID to unload material: ");
                scanf("%d", &wagon_id);
                target_wagon = train->first_wagon;
                while (target_wagon && target_wagon->wagon_id != wagon_id) {
                    target_wagon = target_wagon->next;
                }
                if (target_wagon) {
                    free_wagon(target_wagon); // Vagonu boşalt
                    printf("Wagon %d unloaded successfully.\n", wagon_id);
                } else {
                    printf("Wagon with ID %d not found.\n", wagon_id);
                }
                getchar(); getchar();
                break;

            case 6:
                // Tren durumunu görüntüleme
                display_train_status(train);
                getchar(); getchar();
                break;

            case 7:
                // Malzemelerin durumunu görüntüleme
                for (int i = 0; i < 3; i++) {
                    display_material(materials[i]);
                }
                getchar(); getchar();
                break;

            case 8:
                // Treni boşaltma
                free_train(train);
                train = create_train("T123");
                printf("Train emptied successfully.\n");
                getchar(); getchar();
                break;

            case 9:
                // Tren durumunu dosyaya kaydetme
                printf("Enter filename to save train status: ");
                scanf("%s", filename);
                save_train_to_file(train, filename);
                printf("Train status saved successfully to %s.\n", filename);
                getchar(); getchar();
                break;

            case 10:
                // Programdan çıkış
                printf("Exiting program...\n");
                free_train(train);
                for (int i = 0; i < 3; i++) {
                    free_material(materials[i]);
                }
                return 0;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
                getchar(); getchar();
        }
    }

    return 0;
}