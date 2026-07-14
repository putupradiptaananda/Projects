#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;



enum PokeStat{
    Hp, Atk, Def, Spatk, Spdef, Spe, Statcount//(there are 6 type of base stats)
};

const char *statnames[Statcount] = {"HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed"};

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

struct char_data{
    const char* text;
    int best_stat;
    int mod_val;
};

const char_data characteristics[32] = {
    {"A little quick tempered", Atk, 2},
    {"Alert to sounds", Spe, 1},
    {"Capable of taking hits", Def, 1},
    {"Good endurance", Def, 3},
    {"Good perserverance", Def, 4},
    {"Hates to lose", Spdef, 3},
    {"Highly curious", Spatk, 0},
    {"Highly persistent", Def, 2},
    {"Impetuous and silly", Spe, 2},
    {"Likes to fight", Atk, 3},
    {"Likes to relax", Hp, 4},
    {"Likes to run", Spe, 0},
    {"Likes to thrash about", Atk, 1},
    {"Loves to eat", Hp, 0},
    {"Mischievous", Spatk, 1},
    {"Nods off a lot", Hp, 2},
    {"Often dozes off", Hp, 1},//mistranslation gen IV & V
    {"Often lost in thought", Spatk, 3},
    {"Often scatter things", Hp, 2}, //mistranslation IV & V
    {"Proud of it's power", Atk, 0},
    {"Quick tempered", Atk, 4},
    {"Quick to flee", Spe, 4},
    {"Scatter things often", Hp, 3},
    {"Somewhat of a clown", Spe, 3},
    {"Somewhat stubborn", Spdef, 4},
    {"Somewhat vain", Spdef, 1},
    {"Strongly defiant", Spdef, 2},
    {"Strong willed", Spdef, 0},
    {"Sturdy body", Def, 0},
    {"Takes plenty of siestas", Hp, 1},
    {"Thoroughly cunning", Spatk, 2},
    {"Very finicky", Spatk, 4}
};

typedef struct
{
    int EV[Statcount], IV[Statcount], BS[Statcount], finalStat[Statcount];
    int lvl;
    int nature_index; // index into available nature table
    int char_index;
}Pokemon;

int __find_nature_multipliers(string name);
int _stat_calc(int base, int iv, int ev, int lvl, int isHP, float natureMult);
bool __indv_stat_input(const string &title, int stat_arr[]);
void _stat_input (string calc_mode, Pokemon &A);
void stat_calculator_mode(int gen);
void find_iv_mode(int gen);






int __find_nature_multiplier(string name){
    for (char &c : name) c = tolower(c);

    if (nature_index_list.count(name)) {
        return nature_index_list[name];
    } else return -1;
}

int _stat_calc(int base, int iv, int ev, int lvl, int isHP, float natureMult) {
    int stat;
    if (isHP) {
        stat = ((((2*base)+iv+(ev/4))*lvl)/100)+lvl+10;
    } else {
        stat = (((((2*base)+iv+(ev/4))*lvl)/100)+5)*natureMult + 0.001; //apparently, the computer multiplies by 0.899 because of binary limitations or something so +0.001 is needed
    }
    return stat;
}

bool __indv_stat_input(const string &title, int stat_arr[]){
    
    cout<<"<--"<<title<<"-->"<<endl;
    int i=0;
    while (i < Statcount){
        printf("%s: ", statnames[i]);

        string input;
        cin>>input;
        if(input == "q") {
            cout<<"\nExiting program\n";
            exit(0);
        }
        else if (input == "b"){
            if (i>0) i--;
            else return false;
        } else {
            try{
                stat_arr[i] = stoi(input);
                i++;
            }
            catch(...){
                cout<<"Input invalid\n";
            }
            
        }

    }
    return true;
}

void _stat_input (string calc_mode, Pokemon &A){ //apparently, c++ has a feature where you dont need to use * and & for pass-by-reference. You just type & once and its done. no -> and stuff
    int i;

    cout<<"\n[======Input Pokemon Stat======]\n";

    int section = 1;
    while (section <= 7){ //7 ={Base stat, IV, EV, level, nature, final stat, characteristic}
        switch (section)
        {
        case 1://Base stat
            if (__indv_stat_input("Base Stats", A.BS)) section++;
            else cout<<"Yo this the first input section\n";
            break;
        
        case 2://IV
            if (calc_mode=="stat"){
                if (__indv_stat_input("IV", A.IV)) section++;
                else section--;
            }
            else section++;
            break;

        case 3: //EV
            if (__indv_stat_input("EV", A.EV)) section++;
            else {
                if (calc_mode=="stat") section--;
                else section-=2;
            }
            break;
        
        case 4: { //Level
            cout<<"Level: ";
            string input;
            cin>>input;
            if(input=="b") section--;
            else {
                try{
                    A.lvl = stoi(input);
                    section++;
                }
                catch(...){
                    cout<<"Input invalid\n";
                }
                
            }
            break;
        }

        case 5: {//nature
            cout<<"Nature: ";
            string nature_input;
            cin>>nature_input;
            A.nature_index = __find_nature_multiplier(nature_input);
            if(A.nature_index == -1){
                cout<<"Nature not found";
                section--;
            } else section++;
            break;
        }

        case 6: //Final stat
            if(calc_mode=="iv"){
                if (__indv_stat_input("Final Stats", A.finalStat)) section++;
                else section--;
            } else section++;
            break;

        case 7: 
            if (calc_mode=="iv") {
                cout<<"| List of Characteristics |\n";
                for (int j = 0; j<16; j++){
                    printf("%2d. %-24s %2d. %-24s\n", j+1, characteristics[j].text, j+17, characteristics[j+16].text);
                }

                cout<<"Characteristic Number: ";
                string char_input;
                cin>>char_input;

                if (char_input=="b") section--;
                else {
                    try{
                        int char_num;
                        char_num = stoi(char_input);
                        if (char_num >= 1&& char_num <= 32){
                            A.char_index = char_num - 1;
                            cout<<"Best: "<<statnames[characteristics[A.char_index].best_stat]<<endl;
                            section++;
                        }
                        else cout<<"The list has numbers 1-32\n";
                    }
                    catch(...){
                        cout<<"Invalid Input\n";
                    }
                }
            }
            else section++;
            break;

        default:
            cout<<"How did we get here?\n";
            break;
        }
    }
}

void find_iv_mode(int gen){
    if (gen < 3) {
        cout<<"Not implemented yet\n";
        return;
    }
    cout<<"#######[POKEMON IV CALCULATOR]#######\n";
    Pokemon A;
    int i; 
    
    _stat_input("iv", A);

    cout<<"\n[======IV Range======]\n";
    for (i = 0; i < Statcount; i++){
        printf("%s: ", statnames[i]);
        for (int j = 0; j <=31; j++){
            if (i == characteristics[A.char_index].best_stat){
                if (j%5 != characteristics[A.char_index].mod_val) continue;
            }
            if(i==0){
                if (A.finalStat[i] == _stat_calc(A.BS[i], j, A.EV[i], A.lvl, 1, 1)) 
                    printf("%d ",  j);
            } else {
                if (A.finalStat[i] == _stat_calc(A.BS[i], j, A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i-1])) 
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
    cout<<"#######[POKEMON STAT CALCULATOR]######\n";
    Pokemon A;
    int i; 

    _stat_input("stat", A);

    //StatCalcs
    cout<<"\n[======Final Stats======]\n";
    for (i = 0; i < Statcount; i++)
    {
        if (i == Hp)
            A.finalStat[i] = _stat_calc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 1, 1);

        else
            A.finalStat[i] = _stat_calc(A.BS[i], A.IV[i], A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i-1]); //here is the hp enumeration solution

        printf("%s: %d\n", statnames[i], A.finalStat[i]);
    }
}



int main (int argc, char *argv[]) 
{
    string calc_mode;
    int generation;
    if (argc == 3) {
        calc_mode = argv[1];
        try{
            generation = stoi(argv[2]); 
        }
        catch(...){
            cout<<"Generation ain't a number\n";
            return 1;
        }
        
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
    else cout<<"Uknown mode\n";
    

    return 0;
}
