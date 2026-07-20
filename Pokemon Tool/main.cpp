#include <iostream>
#include <string>
#include "include/calculation.h"
#include "include/database.h"
using namespace std;

void display_help(){
    cout<< R"(
===========================================================
                   POKEMON TOOL - HELP         
===========================================================
    
Main usage:
    pokemon_tool.exe <mode> [options]

Modes Overview:
    -stat           Calculate a Pokemon's final stats
    -iv             Calculate a Pokemon's possible iv range
    -saves          Displays saved calculations
    -delete <name>  Delete a saved calculation
    -help           Displays whatever this is
    

Details:
    -stat
        Inputs are a Pokemon's EV's, IV's, level and 
        nature.
        EV's, IV's and levels are of integer form.
        Nature accepts strings and are not case
        sensitive.
        There is an option to save a pokemons stats at
        the end of calculation, requiring a Nickname 
        as input.

    -iv
        This is made for the DS games, so all info 
        needed are located in the summary of a Pokemon.
        Inputs are a Pokemon's EV's, level, nature,
        characteristic and final stats.
        Only the nature is a string. For characteristics,
        a table of all the existing characteristics are
        show, including mistranslations. Only the number
        on the list is needed for input.
        Output is a range of possible IV's for each stats.
        If one stat outputs no value, then the data is
        incorrect, stuff like wrong EV's.
        Same as -stat mode, there will be an option to
        save a Pokemon's stats, at the end.

    -saves
        Defaults to displaying Nickname, Name and Level of
        all saved Pokemon.

        Filter options ------------------------------------
        
        -spe, -species      Sorts based on Pokemon species
                            A-Z;

        Display options -----------------------------------
        
        -d, -detailed       Displays everything
        -i, -iv             Displays IV range.
        -e, -ev             Displays EV's
        -f, -final          Displays final stats.
        -n, -nature         Displays natures
        -c, -char           Displays characteristic.
        -l, -lvl            Displays level (this is funny)

        Sort options --------------------------------------
        All of these are descending.

        -si, -sort_iv       Sorts based on the IV of a stat
        -se, -sort_ev       Sorts based on the EV of a stat
        -sl, -sort_lvl      Sorts based on level
        -sni, -sort_nick    Sorts based on nickname
        -sf. -sort_final    Sorts based on the final value 
                            of a stat

    -delete
        Only singular deleting exists (I don't need batch
        deleting). There is no confirmation before 
        deleting btw.

    )";
}




int main (int argc, char *argv[]) 
{
    if (argc < 2){
        cout<<"Too little arguments\n";
        return 1;
    }
    //mode select
    string calc_mode=argv[1];

    if (calc_mode == "-stat") stat_calculator_mode();
    else if(calc_mode == "-iv") find_iv_mode();
    else if(calc_mode=="-saves") {
        DisplayOption opts;
        
        for(int i = 2; i<argc;i++){
            string arg = argv[i];
            if(arg=="-d"||arg=="-detailed") opts.detailed=true;
            else if(arg=="-i"||arg=="-iv") opts.show_iv=true;
            else if(arg=="-e"||arg=="-ev") opts.show_evs=true;
            else if(arg=="-f"||arg=="-final") opts.show_final=true;
            else if(arg=="-n"||arg=="-nature") opts.show_nature=true;
            else if(arg=="-c"||arg=="-char") opts.show_char=true;
            else if(arg=="-l"||arg=="-lvl") opts.show_lvl=true;
            else if((arg=="-spe"||arg=="-species")&& i+1<argc) {
                opts.species = argv[i+1];
                i++;
            }
            //sort modes
            else if((arg=="-si"||arg=="-sort_iv")&& i+1<argc) {
                opts.sort_meth=SORT_IV;
                opts.sort_stat=sstoi(argv[i+1]);
                i++;
            }
            else if((arg=="-se"||arg=="-sort_ev")&& i+1<argc) {
                opts.sort_meth=SORT_EV;
                opts.sort_stat=sstoi(argv[i+1]);
                i++;
            }
            else if(arg=="-sl"||arg=="-sort_lvl") opts.sort_meth=SORT_LVL;
            else if(arg=="-sni"||arg=="-sort_nick") opts.sort_meth=SORT_NICK;
            else if((arg=="-sf"||arg=="-sort_final")&& i+1<argc){
                opts.sort_meth=SORT_FINAL;
                opts.sort_stat=sstoi(argv[i+1]);
                i++;
            } 
        }
        saves_mode(opts);
    }
    else if(calc_mode=="-delete"){
        if (argc == 3){
            string arg = argv[2];
            delete_mode(arg);
        }
        else if (argc > 3) cout<<"Too many arguments\n";
        else cout<<"Too little arguments\n";
    }
    else if(calc_mode=="-help") display_help();
    else cout<<"Uknown mode\n";
        

    return 0;
}
