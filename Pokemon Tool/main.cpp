#include <iostream>
#include <string>
#include "include/calculation.h"
#include "include/database.h"
using namespace std;

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
    else cout<<"Uknown mode\n";
        

    return 0;
}
