#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;



enum PokeStat{
    Hp, Atk, Def, Spatk, Spdef, Spe, Statcount//(there are 6 type of base stats)
};

enum nature{
            // -stats ->
/*+stats*/  Hardy, Lonely, Adamant, Naughty, Brave, 
/*  |   */  Bold, Docile, Impish, Lax, Relaxed, 
/*  v   */  Modest, Mild, Bashful, Rash, Quiet,
            Calm, Gentle, Careful, Quirky, Sassy, 
            Timid, Hasty, Jolly, Naive, Serious
};

float nature_multipliers[25][5] = { //note: i forgot about the hp enumeration so i solved it with i-1 when retrieving nature_multiplier 
            //-atk          -defense         -spatk           -spdef           -spe
/*+atk  */  {1,1,1,1,1}    , {1.1,0.9,1,1,1}, {1.1,1,0.9,1,1}, {1.1,1,1,0.9,1}, {1.1,1,1,1,0.9},
/*+def  */  {0.9,1.1,1,1,1}, {1,1,1,1,1}    , {1,1.1,0.9,1,1}, {1,1.1,1,0.9,1}, {1,1.1,1,1,0.9},
/*+spatk*/  {0.9,1,1.1,1,1}, {1,0.9,1.1,1,1}, {1,1,1,1,1}    , {1,1,1.1,0.9,1}, {1,1,1.1,1,0.9},
/*+spdef*/  {0.9,1,1,1.1,1}, {1,0.9,1,1.1,1}, {1,1,0.9,1.1,1}, {1,1,1,1,1}    , {1,1,1,1.1,0.9},
/*+spe  */  {0.9,1,1,1,1.1}, {1,0.9,1,1,1.1}, {1,1,0.9,1,1.1}, {1,1,1,0.9,1.1}, {1,1,1,1,1}
};

unordered_map<string, int> nature_index_list = {
    {"hardy", Hardy},   {"lonely", Lonely}, {"adamant", Adamant}, {"naughty", Naughty}, {"brave", Brave},
    {"bold", Bold},     {"docile", Docile}, {"impish", Impish},   {"lax", Lax},         {"relaxed", Relaxed},
    {"modest", Modest}, {"mild", Mild},     {"bashful", Bashful}, {"rash", Rash},       {"quiet", Quiet},
    {"calm", Calm},     {"gentle", Gentle}, {"careful", Careful}, {"quirky", Quirky},   {"sassy", Sassy},
    {"timid", Timid},   {"hasty", Hasty},   {"jolly", Jolly},     {"naive", Naive},     {"serious", Serious}
};

typedef struct
{
    int EV[Statcount], IV[Statcount], BS[Statcount], finalStat[Statcount];
    int lvl;
    int nature_index; // index into available nature table
}Pokemon;



int find_nature_multipliers(string name);
int StatCalc(int base, int iv, int ev, int lvl, int isHP, float natureMult);
void stat_calculator_mode(int gen);
void find_iv_mode(int gen);









int find_nature_multiplier(string name){
    for (char &c : name) c = tolower(c);

    if (nature_index_list.count(name)) {
        return nature_index_list[name];
    } else return -1;
}

// Stat calculation for HP and other stats, with optional nature multiplier
int StatCalc(int base, int iv, int ev, int lvl, int isHP, float natureMult) {
    int stat;
    if (isHP) {
        stat = ((((2*base)+iv+(ev/4))*lvl)/100)+lvl+10;
    } else {
        stat = (((((2*base)+iv+(ev/4))*lvl)/100)+5)*natureMult;
    }
    return stat;
}

void find_iv_mode(int gen){
    if (gen < 3) {
        cout<<"Not implemented yet\n";
        return;
    }
    const char *statnames[Statcount] = {"HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed"};
    Pokemon A;
    int i; 
    //Base Stats
    printf("Base Stats\n");
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.BS[i]);
    }
    
    //EV's
    printf("EV's\n");
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.EV[i]);
    }
    
    //level
    printf("Level: ");
    scanf("%d", &A.lvl);
    
    //nature
    printf("Nature name: ");
    string nature_input;
    cin>>nature_input;
    A.nature_index = find_nature_multiplier(nature_input);
    if(A.nature_index == -1){
        cout<<"Nature not found";
        return;
    }
    
    //FinalStat
    printf("Final Stats\n");
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        scanf("%d", &A.finalStat[i]);
    }

    cout<<"\nIV Range\n";
    for (i = 0; i < Statcount; i++){
        printf("%s: ", statnames[i]);
        for (int j = 0; j <=31; j++){
            if(i==0){
                if (A.finalStat[i] == StatCalc(A.BS[i], j, A.EV[i], A.lvl, 1, A.nature_index)) 
                    printf("%d ",  j);
            } else {
                if (A.finalStat[i] == StatCalc(A.BS[i], j, A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i-1])) 
                    printf("%d ",  j);
            }
        }
        cout<<endl;

    }
    return;
}

void stat_calculator_mode(int gen){
    if (gen < 3) {
        cout<<"Not implemented yet\n";
        return;
    }
    const char *statnames[Statcount] = {"HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed"};
    Pokemon A;
    int lvl;
    int i; 
    //Base Stats
    printf("Base Stats\n");
    for (i = 0; i < Statcount; i++)
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
    scanf("%d", &A.lvl);

    printf("Nature name: ");
    string nature_input;
    cin>>nature_input;
    A.nature_index = find_nature_multiplier(nature_input);
    if(A.nature_index == -1){
        cout<<"Nature not found";
        return;
    }

    //StatCalcs
    for (i = 0; i < Statcount; i++)
    {
        if (i == Hp)
            A.finalStat[i] = StatCalc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 1, 1);
        else
            A.finalStat[i] = StatCalc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i-1]); //here is the hp enumeration solution
    }

    //print stats
    for (i = 0; i < Statcount; i++)
    {
        printf("%s: ", statnames[i]);
        printf("%d\n", A.finalStat[i]);
    }
}



int main (int argc, char *argv[]) 
{
    cout<<"hai\n";
    string calc_mode;
    int generation;
    if (argc == 3) {
        calc_mode = argv[1];
        generation = atoi(argv[2]);
    } else if (argc > 3){
        cout<<"Too many arguments\n";
        return 1;
    } else if (argc < 3){
        cout<<"Too little arguments\n";
        return 1;
    }

    //mode selection
    if (calc_mode == "stat") stat_calculator_mode(generation);
    else if(calc_mode == "iv") find_iv_mode(generation);

    return 0;
}
