#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "train.h"

// Dosya işlemleri fonksiyon prototipleri
void save_train_to_file(const Train* train, const char* filename);
Train* load_train_from_file(const char* filename);

#endif // FILE_OPS_H