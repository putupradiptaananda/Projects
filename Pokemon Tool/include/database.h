#ifndef DB_H
#define DB_H
#include <string> 
#include "calculation.h"

enum SortTypes{
        SORT_NONE,
        SORT_IV, //-si
        SORT_EV, //-se
        SORT_LVL, //-sl
        SORT_NICK, // -sni
        SORT_FINAL // -sf
};


struct DisplayOption{
    bool detailed=false; //-d
    bool show_iv=false; //-i
    bool show_evs=false; //-e
    bool show_final=false; //-f
    bool show_nature=false; //-n
    bool show_char=false; //-c
    bool show_lvl=false; // -l
    std::string species = ""; //-species <pokemon>

    SortTypes sort_meth=SORT_NONE;
    int sort_stat=-1;
};

int sstoi(std::string stat); //stat string to index
void __init_db();
bool __load_base_stats(Pokemon &A);
void __save_base_stats(Pokemon &A);
void __save_pokemon(Pokemon &A);
void saves_mode(DisplayOption opts);
void delete_mode(std::string nickname);

#endif