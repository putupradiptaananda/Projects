#include <iostream>
#include <string>
#include "include/calculation.h"
using namespace std;

int main (int argc, char *argv[]) 
{
    string calc_mode;
    int generation;
    if (argc == 2) {
        calc_mode = argv[1];
    } else if (argc > 2){
        cout<<"Too many arguments\n";
        return 1;
    } else if (argc < 2){
        cout<<"Too little arguments\n";
        return 1;
    }

    //mode selection
    if (calc_mode == "-stat") stat_calculator_mode();
    else if(calc_mode == "-iv") find_iv_mode();
    else cout<<"Uknown mode\n";
    

    return 0;
}
