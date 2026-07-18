#ifndef CALC_H
#define CALC_H
#include <string>

enum PokeStat{
    Hp, Atk, Def, Spatk, Spdef, Spe, Statcount//(there are 6 type of base stats)
};

extern const char *statnames[Statcount];

enum nature{
            // -stats ->
/*+stats*/  Hardy, Lonely, Adamant, Naughty, Brave, 
/*  |   */  Bold, Docile, Impish, Lax, Relaxed, 
/*  v   */  Modest, Mild, Bashful, Rash, Quiet,
            Calm, Gentle, Careful, Quirky, Sassy, 
            Timid, Hasty, Jolly, Naive, Serious
};

enum calculator_mode{
    MODE_STAT,
    MODE_IV
};

struct char_data{
    const char* text;
    int best_stat;
    int mod_val;
};

typedef struct
{
    int EV[Statcount], IV[Statcount], BS[Statcount], finalStat[Statcount];
    int lvl;
    int nature_index; // index into available nature table
    int char_index;
}Pokemon;

void stat_calculator_mode();
void find_iv_mode();

#endif