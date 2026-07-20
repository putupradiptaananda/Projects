# Pokemon Tool
## What is it?
This is just a CLI for a stat calculator that has saves. It calculates the final stats or possible IV's of a Pokemon, which you can save to a `.csv` file.

This was made solely to aid me while playing DS Pokemon games. I was motivated when my Hydreigon dropped to an ice beam from a Vanilluxe from full health, during my attempt to reach the subway boss in Pokemon Black. I couldn't find a calculator that's simple enough, so I made this ( There probably is a better one, but I was too lazy to find it ). The save feature was added also because I'm too lazy to note them manually. 

This is my first useful "app" of some sort, so there are most likely going to be anomalies in the code ( I found a show_lvl variable thats never actually used ). You can find that the stat calculator is made in C, while the rest is C++. Well, most of it.

## How to build?
You can just download the `.exe`, but if you want to compile it, run;
```
 g++ main.cpp include/calculation.cpp include/database.cpp -o poke_tool.exe
```

## How to use?
Just type `-help` or read this;
    
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
