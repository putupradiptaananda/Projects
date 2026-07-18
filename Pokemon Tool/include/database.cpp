#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "database.h"
using namespace std;

const string DB_FILENAME = "pokemon_base_stats.csv";

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

void _save_pokemon()

void save_mode()
