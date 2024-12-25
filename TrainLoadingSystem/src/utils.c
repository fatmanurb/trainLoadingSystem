#include <stdlib.h>
#include <stdio.h>

// Ekranı temizleme fonksiyonu
void clear_screen() {
#ifdef _WIN32
    system("cls"); // Windows için
#elif defined(__APPLE__) || defined(__linux__)
    system("clear"); // MacOS veya Linux için
#else
    printf("\033[H\033[J"); // ANSI kaçış kodları
#endif
}