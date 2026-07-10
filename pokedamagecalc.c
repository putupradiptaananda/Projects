#include <stdio.h>

// Stat calculation for HP and other stats, with optional nature multiplier
int StatCalc(int base, int iv, int ev, int lvl, int isHP, float natureMult) {
    int stat;
    stat = 2 * base;
    stat = stat + iv + ev / 4;
    stat = stat * lvl / 100;
    if (isHP) {
        stat = stat + lvl + 10;
    } else {
        stat = stat + 5;
        stat = (int)(stat * natureMult);
    }
    return stat;
}


enum PokeStat{
    Hp, Atk, Def, Spatk, Spdef, Spe, Statcount//(there are 6 type of base stats)
};

enum nature{
    Hardy, Lonely, Brave, Adamant, Naughty,
    Bold, Docile, Relaxed, Impish, Lax,
    Timid, Hasty, Serious, Jolly, Naive,
    Modest, Mild, Quiet, Rash, Calm,
    Gentle, Sassy, Careful, Quirky
};

int nature_multipliers[25][6] = {
    {1,1,1,1,1,1}, //Hardy
    {1,1.1,0.9,1,1,1}, //Lonely
    {1,1.1,1,1,1,0.9}, //Brave
    {1,1.1,1,0.9,1,1}, //Adamant
    {1,1.1,1,1,0.9,1}, //Naughty
    {1,0.9,1.1,1,1,1}, //Bold
    {1,1,1,1,1,1}, //Docile
    {1,0.9,1,1.1,1,1}, //Relaxed
    {1,0.9,1,1,1.1,1}, //Impish
    {1,0.9,1,1,1,1.1}, //Lax
    {1,0.9,1,1,1,1.1}, //Timid
    {1,1,0.9,1,1,1.1}, //Hasty
    {1,1,1,1,1,1}, //Serious
    {1,1,0.9,1.1,1,1}, //Jolly
    {1,0.9,1,0.9,1,1.1}, //Naive
    {1,0.9,0.9,1.1,1,1}, //Modest
    {1,0.9,1,0.9,1.1,1}, //Mild
    {1,0.9,0.9,1,1.1,1}, //Quiet
    {1,0.9,1,1.1,0.9,1}, //Rash
    {1,0.9,0.9,1,0.9,1.1}, //Calm
    {1,1,0.9,0.9,1.1,1}, //Gentle
    {1,1,0.9,1.11,.9,11}, //Sassy
    {11,1,1,0.9,1.1,0.9}, //Careful
    {1,1,1,1,1,1} //Quirky
};

typedef struct
{
    int EV[Statcount], IV[Statcount], BS[Statcount], finalStat[Statcount];
    int lvl;
    int nature_index; // index into available nature table
}Poke;


int main () 
{
    const char *statnames[Statcount] = {"HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed"};
    Poke A, B;
    int lvl;
    int i; 
    //Base Stats
    printf("Base Stats\n");
    for (i = 0; i < Statcount; i++)\
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.BS[i]);
    }

    //IV's
    printf("IV's\n");
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.IV[i]);
    }

    //EV's
    printf("EV's\n");
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.EV[i]);
    }

    printf("Level: ");
    scanf("%d", A.lvl);

    printf("Nature index (Bulbapedia as reference, including zero): ");
    scanf("%d", &A.nature_index);

    //StatCalcs
    for (i = 0; i < Statcount; i++)
    {
        if (i == Hp)
            A.finalStat[i] = StatCalc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 1, 1);
        else
            A.finalStat[i] = StatCalc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i]);
    }

    //print stats
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        printf("%d\n", A.finalStat[i]);
    }
    return 0;
}
