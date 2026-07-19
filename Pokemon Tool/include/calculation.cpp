#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "calculation.h"
#include "database.h"

using namespace std;

const char *statnames[Statcount] = {"HP", "Attack", "Defense", "Special Attack", "Special Defense", "Speed"};

float nature_multipliers[25][5] = { //note: i forgot about the hp enumeration so i solved it with i-1 when retrieving nature_multiplier 
            //-atk          -defense         -spatk           -spdef           -spe
/*+atk  */  {1,1,1,1,1}    , {1.1,0.9,1,1,1}, {1.1,1,0.9,1,1}, {1.1,1,1,0.9,1}, {1.1,1,1,1,0.9},
/*+def  */  {0.9,1.1,1,1,1}, {1,1,1,1,1}    , {1,1.1,0.9,1,1}, {1,1.1,1,0.9,1}, {1,1.1,1,1,0.9},
/*+spatk*/  {0.9,1,1.1,1,1}, {1,0.9,1.1,1,1}, {1,1,1,1,1}    , {1,1,1.1,0.9,1}, {1,1,1.1,1,0.9},
/*+spdef*/  {0.9,1,1,1.1,1}, {1,0.9,1,1.1,1}, {1,1,0.9,1.1,1}, {1,1,1,1,1}    , {1,1,1,1.1,0.9},
/*+spe  */  {0.9,1,1,1,1.1}, {1,0.9,1,1,1.1}, {1,1,0.9,1,1.1}, {1,1,1,0.9,1.1}, {1,1,1,1,1}
};

unordered_map<std::string, int> nature_index_list = {
    {"hardy", Hardy},   {"lonely", Lonely}, {"adamant", Adamant}, {"naughty", Naughty}, {"brave", Brave},
    {"bold", Bold},     {"docile", Docile}, {"impish", Impish},   {"lax", Lax},         {"relaxed", Relaxed},
    {"modest", Modest}, {"mild", Mild},     {"bashful", Bashful}, {"rash", Rash},       {"quiet", Quiet},
    {"calm", Calm},     {"gentle", Gentle}, {"careful", Careful}, {"quirky", Quirky},   {"sassy", Sassy},
    {"timid", Timid},   {"hasty", Hasty},   {"jolly", Jolly},     {"naive", Naive},     {"serious", Serious}
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
        if(input == "q" || input == "Q") {
            cout<<"\nExiting program\n";
            exit(0);
        }
        else if (input == "b" || input == "B"){
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

void _stat_input (calculator_mode calc_mode, Pokemon &A){ //apparently, c++ has a feature where you dont need to use * and & for pass-by-reference. You just type & once and its done. no -> and stuff
    int i;

    cout<<"\n[======Input Pokemon Data======]\n";

    __init_db();
    bool loaded; 


    int section = 0;
    while (section <= 7){ //7 ={Identity, Base stat, IV, EV, level, nature, final stat, characteristic}
        switch (section){
        case 0: {
            cout<<"<--Identification-->\n";
            //Dex Number
            cout<<"National Dex Number: ";
            string input;
            cin>>input;
            if(input == "q" || input == "Q") {
                cout<<"\nExiting program\n";
                exit(0);
            }
            else if (input == "b" || input == "B"){
                cout<<"Yo this the first prompt\n";
                continue;
            } else {
                try{
                    A.natdex_num = stoi(input);
                }
                catch(...){
                    cout<<"Input invalid\n";
                    continue;
                }
                
            }
            //Name
            cout<<"Pokemon Name: ";
            cin>>A.name;

            if (__load_base_stats(A)){
                loaded = true;
                section+=2;
            }
            else {
                loaded = false;
                section++;
            }
            break;
        }
        case 1://Base stat
            if (loaded){
                section--;
                break;
            } 
            if (__indv_stat_input("Base Stats", A.BS)) {
                __save_base_stats(A);
                section++;
            }
            else section--; 
            break;
        
        case 2://IV
            if (calc_mode == MODE_STAT){
                if (__indv_stat_input("IV", A.IV)) section++;
                else section--;
            }
            else section++;
            break;

        case 3: //EV
            if (__indv_stat_input("EV", A.EV)) section++;
            else {
                if (calc_mode==MODE_STAT) section--;
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
            } else {
                for (char &c : nature_input) c = tolower(c);
                A.nature=nature_input;
                section++;
            }
            break;
        }

        case 6: //Final stat
            if(calc_mode== MODE_IV){
                if (__indv_stat_input("Final Stats", A.finalStat)) section++;
                else section--;
            } else section++;
            break;

        case 7: 
            if (calc_mode==MODE_IV) {
                cout<<"| List of Characteristics |\n";
                for (int j = 0; j<16; j++){
                    printf("%2d. %-24s %2d. %-24s\n", j+1, characteristics[j].text, j+17, characteristics[j+16].text);
                }

                cout<<"Characteristic Number: ";
                string char_input;
                cin>>char_input;

                if (char_input == "q" || char_input == "Q"){
                    cout<<"\nExiting Program\n";
                    exit(0);
                }
                else if (char_input == "b" || char_input == "B") section--;
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

void _save_prompt(Pokemon& A){
    cout<<"Save Pokemon? (y/n): ";
    string answer;
    cin>>answer;
    if(answer=="y" || answer == "Y"){
        cout<<"Enter Nickname: ";
        cin>>A.nickname;
        __save_pokemon(A);
    }
}

void find_iv_mode(){
    
    
    cout<<"#######[POKEMON IV CALCULATOR]#######\n";
    Pokemon A;
    int i; 
    _stat_input(MODE_IV, A);
    
    cout<<"\n[======IV Range======]\n";
    for (i = 0; i < Statcount; i++){
        A.iv_range[i]="";
        printf("%s: ", statnames[i]);
        for (int j = 0; j <=31; j++){
            if (i == characteristics[A.char_index].best_stat){
                if (j%5 != characteristics[A.char_index].mod_val) continue;
            }
            if(i==0){
                if (A.finalStat[i] == _stat_calc(A.BS[i], j, A.EV[i], A.lvl, 1, 1)){
                    printf("%d ",  j);
                    A.iv_range[i]+= to_string(j) + " ";
                } 
            } else {
                if (A.finalStat[i] == _stat_calc(A.BS[i], j, A.EV[i], A.lvl, 0, nature_multipliers[A.nature_index][i-1])) {
                    printf("%d ",  j);
                    A.iv_range[i]+= to_string(j) + " ";
                }
            }
        }
        cout<<endl;
    }
    _save_prompt(A);
    return;
}

void stat_calculator_mode(){
    cout<<"#######[POKEMON STAT CALCULATOR]######\n";
    Pokemon A;
    int i; 

    _stat_input(MODE_STAT, A);

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

    ///save pokemon
    for (i=0;i<Statcount;i++) A.iv_range[i] = to_string(A.IV[i]);
    A.char_index = -1;//means no characteristic
    _save_prompt(A);
}