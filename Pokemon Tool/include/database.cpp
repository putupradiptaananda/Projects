#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "database.h"
using namespace std;

const string DB_FILENAME = "pokemon_base_stats.csv";
const string PERSONAL_DB = "saved_pokemon.csv";

int sstoi(string stat){ //Stat string to index
    int stat_index;
    for (char &c : stat) c = tolower(c);
    
    if (stat=="hp") stat_index=Hp;
    else if (stat=="atk"||stat=="attack") stat_index=Atk;
    else if (stat=="def"||stat=="defense") stat_index=Def;
    else if (stat=="spa"||stat=="spatk") stat_index=Spatk;
    else if (stat=="spdef") stat_index=Spdef;
    else if (stat=="spe"||stat=="spd"||stat=="speed") stat_index=Spe;

    return stat_index;
}

void __init_db(){
    ifstream db;
    db.open(DB_FILENAME);
    if (db.fail()){
        cout<<"Database file doesn't exist or is unreadable\nCreating new file\n";
        ofstream db_create;
        db_create.open(DB_FILENAME, ofstream::app);
        db_create << "NatDexNum,Name,Hp,Atk,Def,SpAtk,Spdef,Speed\n";
        cout<<"File created\n";
        db_create.close();
    }
    db.close();
}

bool __load_base_stats(Pokemon &A){
    ifstream db;
    db.open(DB_FILENAME);
    string input_line;
    for (char &c : A.name) c = tolower(c);

    getline(db, input_line);//skip the header row

    while (getline(db, input_line)){
        stringstream ss;
        ss.str(input_line);
        string token;

        //get dex number
        getline(ss, token, ',');
        int input_dex = stoi(token);
        //get name
        getline(ss, token, ',');
        string input_name=token;
        for (char &c : input_name) c = tolower(c);

        if (input_dex==A.natdex_num && input_name==A.name){
            cout<<"Pokemon found in database, retrieving base stats...\n";
            for (int i = 0; i<Statcount; i++){
                getline(ss, token, ',');
                A.BS[i] = stoi(token);
                printf("%s : %d\n", statnames[i], A.BS[i]);
            }
            return true;
        }
    }
    db.close();
    return false;
}

void __save_base_stats(Pokemon &A){
    ofstream db;
    db.open(DB_FILENAME, ios::app);
    db << A.natdex_num << "," << A.name;
    for (int i = 0; i<Statcount; i++) db<<","<< A.BS[i];
    db<<endl;
    db.close();
}

void __save_pokemon(Pokemon &A){
    ifstream p_db;
    p_db.open(PERSONAL_DB);
    ofstream p_db_temp;
    p_db_temp.open("temp.csv", ofstream::app);
    string line;
    bool isNew=true;
    if (p_db.fail()){
        cout<<"Save file doesn't exist or is unreadable\nCreating new file\n";
        p_db_temp   << "Nickname,Species,Level,Nature,Characteristic,"
                    << "HP_IV,Atk_IV,DEF_IV,Spatk_IV,Spdef_IV,Spe_IV,"
                    << "HP_EV,Atk_EV,Def_EV,Spatk_EV,Spdef_EV,Spe_EV,"
                    << "HP_fin,Atk_fin,Def_fin,Spatk_fin,Spdef_fin,Spe_fin\n";
        cout<<"File Created\n";
    } else {
        while(getline(p_db, line)){
            stringstream ss;
            ss.str(line);
            string input_nick;
            getline(ss, input_nick, ',');
            if (A.nickname == input_nick){
                isNew=false;
                p_db_temp << A.nickname << "," << A.name << "," << A.lvl << "," << A.nature << "," <<A.char_index;
                for (int i = 0; i<Statcount; i++) p_db_temp<< "," << A.iv_range[i];
                for (int i = 0; i<Statcount; i++) p_db_temp << "," << A.EV[i];
                for (int i = 0; i<Statcount; i++) p_db_temp << "," << A.finalStat[i];
                p_db_temp << endl;
            }
            else p_db_temp << line <<endl;
        }
        p_db.close();
    }

    //put the save pokemon in temp file
    if(isNew){
        p_db_temp << A.nickname << "," << A.name << "," << A.lvl << "," << A.nature << "," << A.char_index;
        for (int i = 0; i<Statcount; i++) p_db_temp<< "," << A.iv_range[i];
        for (int i = 0; i<Statcount; i++) p_db_temp << "," << A.EV[i];
        for (int i = 0; i<Statcount; i++) p_db_temp << "," << A.finalStat[i];
        p_db_temp << endl;        
    }

    p_db_temp.close();
    remove(PERSONAL_DB.c_str());
    rename("temp.csv", PERSONAL_DB.c_str());
}

void saves_mode(DisplayOption opts){
    ifstream p_db;
    p_db.open(PERSONAL_DB);
    if (p_db.fail()) {
        cout<<"No save file detected\n";
        return;
    }

    string line;
    getline(p_db, line);

    vector<Pokemon> saved_pokemon;
    while(getline(p_db, line)){
        stringstream ss;
        ss.str(line);
        string token;
        Pokemon A;

        //read
        getline(ss, A.nickname, ',');
        getline(ss, A.name, ',');
        getline(ss, token, ',');
        A.lvl = stoi(token);

        //species filter
        if (opts.species != ""){
            for (char &c : opts.species) c = tolower(c);
            if (A.name != opts.species) continue;
        } 
        
    //parse everything cause everything is needed (assume that way)
        //nature and characteristics
        getline(ss, A.nature,',');
        getline(ss, token,',');
        A.char_index=stoi(token);

        //Iv
        for (int i=0; i<Statcount;i++){
            getline(ss, A.iv_range[i], ',');
        }
        //ev
        for (int i=0;i<Statcount;i++){
            getline(ss,token,',');
            A.EV[i]=stoi(token);
        }
        //final stat
        for(int i=0;i<Statcount;i++){
            getline(ss,token,',');
            A.finalStat[i]=stoi(token);
        }
        
        saved_pokemon.push_back(A);
    }

    //Sort
    if (opts.sort_meth!=SORT_NONE&&saved_pokemon.size()>1){
        sort(saved_pokemon.begin(), saved_pokemon.end(), 
            [&opts](const Pokemon &a, const Pokemon &b){
                if(opts.sort_meth==SORT_IV){
                    int iv_a = a.iv_range[opts.sort_stat].empty() ? -1 : stoi(a.iv_range[opts.sort_stat]);
                    int iv_b = b.iv_range[opts.sort_stat].empty() ? -1 : stoi(b.iv_range[opts.sort_stat]);
                    return iv_a>iv_b;
                }
                if(opts.sort_meth==SORT_EV) return a.EV[opts.sort_stat]>b.EV[opts.sort_stat];
                if(opts.sort_meth==SORT_LVL) return a.lvl>b.lvl;
                if(opts.sort_meth==SORT_NICK) return a.nickname<b.nickname;
                if(opts.sort_meth==SORT_FINAL)
                    return a.finalStat[opts.sort_stat]>b.finalStat[opts.sort_stat];
                
                return false;
            }
        );
    }

    //display
    cout<<"\n#######[SAVED POKEMON]#######\n";

    for (const auto &A : saved_pokemon){
        printf("[] %-15s %-15s Lvl.%d\n", A.nickname.c_str(), A.name.c_str(), A.lvl);

        if (opts.detailed || opts.show_nature) printf("   Nature: %s\n", A.nature.c_str());
        if (opts.detailed || opts.show_char){
            string char_text;
            if(A.char_index >= 0 && A.char_index < 32)
                char_text = characteristics[A.char_index].text;
            else char_text = "N/A";
            printf("   \"%s\"\n", char_text.c_str());
        }
        
        if(opts.detailed || opts.show_iv){
            cout<<"   <--IV-->\n";
            for (int i=0; i<Statcount; i++) 
                printf("   %-15s: %s\n", statnames[i], A.iv_range[i].c_str());
        }
        if(opts.detailed || opts.show_evs){
            cout<<"   <--EV-->\n";
            for (int i=0; i<Statcount; i++) 
                printf("   %-15s: %d\n", statnames[i], A.EV[i]);
        }
        if(opts.detailed || opts.show_final){
            cout<<"   <--Final Stats-->\n";
            for (int i=0; i<Statcount; i++) 
                printf("   %-15s: %d\n", statnames[i], A.finalStat[i]);
        }
        cout<<"\n";
    }
    cout<<"Total pokemon shown: "<<saved_pokemon.size()<<"\n";

}
