#ifndef DB_H
#define DB_H
#include <string>
#include "calculation.h"

void __init_db();
bool __load_base_stats(Pokemon &A);
void __save_base_stats(Pokemon &A);

#endif