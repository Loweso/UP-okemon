#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>
#include <cctype>

enum PokemonType {
    Bug,        // 0
    Dragon,     // 1
    Electric,   // 2
    Flying,     // 3
    Fire,       // 4
    Ghost,      // 5
    Grass,      // 6
    Ground,     // 7
    Ice,        // 8
    Normal,     // 9
    Poison,     // 10
    Psychic,    // 11
    Rock,       // 12
    Steel,      // 13
    Water,      // 14
    None        // 15
};

enum TypeEffectiveness {
    NoDmg,
    Weak,
    Neutral,
    Strong
};

TypeEffectiveness typeChart[16][16] = {
    // Def\Atk       Bug,     Drgn,    Eltrc,   Flyng,   Fire,    Ghost,   Grass,   Ground,  Ice,     Normal,  Poison,  Psychic, Rock,    Steel,   Water,   None
    /* Bug      */ { Neutral, Neutral, Neutral, Weak,    Weak,    Weak,    Strong,  Neutral, Neutral, Neutral, Weak,    Strong,  Neutral, Weak,    Neutral, Neutral },
    /* Dragon   */ { Neutral, Strong,  Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Weak,    Neutral, Neutral },
    /* Electric */ { Neutral, Weak,    Weak,    Strong,  Neutral, Neutral, Weak,    NoDmg,   Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Strong,  Neutral },
    /* Flying   */ { Strong,  Neutral, Weak,    Neutral, Neutral, Neutral, Strong,  Neutral, Neutral, Neutral, Neutral, Neutral, Weak,    Weak,    Neutral, Neutral },
    /* Fire     */ { Strong,  Weak,    Neutral, Neutral, Weak,    Neutral, Strong,  Neutral, Strong,  Neutral, Neutral, Neutral, Weak,    Strong,  Weak,    Neutral },
    /* Ghost    */ { Neutral, Neutral, Neutral, Neutral, Neutral, Strong,  Neutral, Neutral, Neutral, NoDmg,   Neutral, Strong,  Neutral, Neutral, Neutral, Neutral },
    /* Grass    */ { Weak,    Weak,    Neutral, Weak,    Weak,    Neutral, Weak,    Strong,  Neutral, Neutral, Weak,    Neutral, Strong,  Weak,    Strong,  Neutral },
    /* Ground   */ { Weak,    Neutral, Strong,  Neutral, Strong,  Neutral, Weak,    Neutral, Neutral, Neutral, Strong,  Neutral, Strong,  Strong,  Neutral, Neutral },
    /* Ice      */ { Neutral, Strong,  Neutral, Strong,  Weak,    Neutral, Strong,  Strong,  Weak,    Neutral, Neutral, Neutral, Neutral, Weak,    Weak,    Neutral },
    /* Normal   */ { Neutral, Neutral, Neutral, Neutral, Neutral, NoDmg,   Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Weak,    Weak,    Neutral, Neutral },
    /* Poison   */ { Neutral, Neutral, Neutral, Neutral, Neutral, Weak,    Strong,  Weak,    Neutral, Neutral, Weak,    Neutral, Weak,    NoDmg,   Neutral, Neutral },
    /* Psychic  */ { Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Strong,  Weak,    Neutral, Weak,    Neutral, Neutral },
    /* Rock     */ { Strong,  Neutral, Neutral, Strong,  Strong,  Neutral, Neutral, Weak,    Neutral, Neutral, Neutral, Neutral, Neutral, Weak,    Neutral, Neutral },
    /* Steel    */ { Neutral, Neutral, Weak,    Neutral, Weak,    Neutral, Neutral, Neutral, Strong,  Neutral, Neutral, Neutral, Strong,  Neutral, Weak,    Neutral },
    /* Water    */ { Neutral, Weak,    Neutral, Neutral, Strong,  Neutral, Weak,    Strong,  Neutral, Neutral, Neutral, Neutral, Strong,  Weak,    Weak,    Neutral },
    /* None     */ { Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral, Neutral }
};

enum PokemonMovePhysOrSp {
    Physical,
    Special
};

struct PokemonMove {
    std::string MoveName;
    PokemonType MoveType;
    PokemonMovePhysOrSp PhysOrSp;
    int Power;
};

struct Pokemon{
    std::string Name;
    PokemonType Type1;
    PokemonType Type2;
    int MaxHP;
    int CurrentHP;
    int ATK;
    int DEF;
    int SpATK;
    int SpDEF;
    int Speed;
    int Level;
    std::string FrontSprite;
    std::string BackSprite;
    PokemonMove Moveset[4];
};

Pokemon definePokemon (std::string pokemonName,
    PokemonType pokemonType1,
    PokemonType pokemonType2,
    int pokemonMaxHP,
    int pokemonCurrentHP,
    int pokemonATK,
    int pokemonDEF,
    int pokemonSpATK,
    int pokemonSpDEF,
    int pokemonSpeed,
    std::string pokemonFrontSprite,
    std::string pokemonBackSprite,
    std::string MoveName1,
    PokemonType MoveType1,
    PokemonMovePhysOrSp PhysOrSp1,
    int Power1,
    std::string MoveName2,
    PokemonType MoveType2,
    PokemonMovePhysOrSp PhysOrSp2,
    int Power2,
    std::string MoveName3,
    PokemonType MoveType3,
    PokemonMovePhysOrSp PhysOrSp3,
    int Power3,
    std::string MoveName4,
    PokemonType MoveType4,
    PokemonMovePhysOrSp PhysOrSp4,
    int Power4){

    int IndividualValue = 31;
    int EffortValue = 102;

    Pokemon Pokemon;
    Pokemon.Level = (rand() % (80 - 70 + 1)) + 70;

    Pokemon.Name = pokemonName;
    Pokemon.Type1 = pokemonType1;
    Pokemon.Type2 = pokemonType2;
    Pokemon.MaxHP = pokemonCurrentHP + 84;
    Pokemon.CurrentHP = Pokemon.MaxHP;
    Pokemon.ATK = floor(floor(2 * pokemonATK + IndividualValue + (EffortValue / 4) * Pokemon.Level / 100) + 5);
    Pokemon.DEF = floor(floor(2 * pokemonDEF + IndividualValue + (EffortValue / 4) * Pokemon.Level / 100) + 5);
    Pokemon.SpATK = floor(floor(2 * pokemonSpATK + IndividualValue + (EffortValue / 4) * Pokemon.Level / 100) + 5);
    Pokemon.SpDEF = floor(floor(2 * pokemonSpDEF + IndividualValue + (EffortValue / 4) * Pokemon.Level / 100) + 5);
    Pokemon.Speed = floor(floor(2 * pokemonSpeed + IndividualValue + (EffortValue / 4) * Pokemon.Level / 100) + 5);
    Pokemon.FrontSprite = pokemonFrontSprite;
    Pokemon.BackSprite = pokemonBackSprite;

    Pokemon.Moveset[0] = {MoveName1, MoveType1, PhysOrSp1, Power1};
    Pokemon.Moveset[1] = {MoveName2, MoveType2, PhysOrSp2, Power2};
    Pokemon.Moveset[2] = {MoveName3, MoveType3, PhysOrSp3, Power3};
    Pokemon.Moveset[3] = {MoveName4, MoveType4, PhysOrSp4, Power4};

    return Pokemon;
};

void allPokemon(Pokemon* listOfPokemon){
            listOfPokemon[0] = definePokemon("PIDGEOT",
                                                Normal,
                                                Flying,
                                                83,
                                                83,
                                                80,
                                                75,
                                                70,
                                                70,
                                                101,
                                                "./PokemonSprite/Pidgeot_Front.png",
                                                "./PokemonSprite/Pidgeot_Back.png",
                                                "Aerial Ace",
                                                Flying,
                                                Physical,
                                                60,
                                                "Steel Wing",
                                                Steel,
                                                Physical,
                                                70,
                                                "Wing Attack",
                                                Flying,
                                                Physical,
                                                60,
                                                "Gust",
                                                Flying,
                                                Special,
                                                40);

            listOfPokemon[1] = definePokemon("DRAGONITE",
                                                Flying,
                                                Dragon,
                                                91,
                                                91,
                                                134,
                                                95,
                                                100,
                                                100,
                                                80,
                                                "./PokemonSprite/Dragonite_Front.png",
                                                "./PokemonSprite/Dragonite_Back.png",
                                                "Outrage",
                                                Dragon,
                                                Physical,
                                                120,
                                                "Wing Attack",
                                                Flying,
                                                Physical,
                                                60,
                                                "Hyper Beam",
                                                Normal,
                                                Special,
                                                150,
                                                "Flamethrower",
                                                Fire,
                                                Special,
                                                90);

            listOfPokemon[2] = definePokemon("AERODACTYL",
                                                Flying,
                                                Rock,
                                                80,
                                                80,
                                                105,
                                                65,
                                                60,
                                                75,
                                                130,
                                                "./PokemonSprite/Aerodactyl_Front.png",
                                                "./PokemonSprite/Aerodactyl_Back.png",
                                                "Fire Blast",
                                                Fire,
                                                Special,
                                                110,
                                                "Aerial Ace",
                                                Flying,
                                                Physical,
                                                60,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Wing Attack",
                                                Flying,
                                                Physical,
                                                60);

            listOfPokemon[3] = definePokemon("ARBOK",
                                                Poison,
                                                None,
                                                60,
                                                60,
                                                95,
                                                69,
                                                65,
                                                79,
                                                80,
                                                "./PokemonSprite/Arbok_Front.png",
                                                "./PokemonSprite/Arbok_Back.png",
                                                "Acid",
                                                Poison,
                                                Special,
                                                40,
                                                "Sludge Bomb",
                                                Poison,
                                                Special,
                                                90,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100);

            listOfPokemon[4] = definePokemon("GENGAR",
                                                Poison,
                                                Ghost,
                                                60,
                                                60,
                                                65,
                                                60,
                                                130,
                                                75,
                                                110,
                                                "./PokemonSprite/Gengar_Front.png",
                                                "./PokemonSprite/Gengar_Back.png",
                                                "Thunderbolt",
                                                Electric,
                                                Special,
                                                90,
                                                "Shadow Ball",
                                                Ghost,
                                                Special,
                                                80,
                                                "Psychic",
                                                Psychic,
                                                Special,
                                                90,
                                                "Shadow Punch",
                                                Ghost,
                                                Physical,
                                                60);

            listOfPokemon[5] = definePokemon("WEEZING",
                                                Poison,
                                                None,
                                                65,
                                                65,
                                                90,
                                                120,
                                                85,
                                                70,
                                                60,
                                                "./PokemonSprite/Weezing_Front.png",
                                                "./PokemonSprite/Weezing_Back.png",
                                                "Sludge Bomb",
                                                Poison,
                                                Special,
                                                90,
                                                "Shadow Ball",
                                                Ghost,
                                                Special,
                                                80,
                                                "Thunderbolt",
                                                Electric,
                                                Special,
                                                90,
                                                "Sludge",
                                                Poison,
                                                Special,
                                                65);

            listOfPokemon[6] = definePokemon("SANDSLASH",
                                                Ground,
                                                None,
                                                75,
                                                75,
                                                100,
                                                110,
                                                45,
                                                55,
                                                65,
                                                "./PokemonSprite/Sandslash_Front.png",
                                                "./PokemonSprite/Sandslash_Back.png",
                                                "Slash",
                                                Normal,
                                                Physical,
                                                70,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Strength",
                                                Normal,
                                                Physical,
                                                80,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100);

            listOfPokemon[7] = definePokemon("MAROWAK",
                                                Ground,
                                                None,
                                                60,
                                                60,
                                                80,
                                                110,
                                                50,
                                                80,
                                                45,
                                                "./PokemonSprite/Marowak_Front.png",
                                                "./PokemonSprite/Marowak_Back.png",
                                                "Double Edge",
                                                Normal,
                                                Physical,
                                                120,
                                                "Bonemerang",
                                                Ground,
                                                Physical,
                                                50,
                                                "Strength",
                                                Normal,
                                                Physical,
                                                80,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100);

            listOfPokemon[8] = definePokemon("DUGTRIO",
                                                Ground,
                                                None,
                                                35,
                                                35,
                                                100,
                                                50,
                                                50,
                                                70,
                                                120,
                                                "./PokemonSprite/Dugtrio_Front.png",
                                                "./PokemonSprite/Dugtrio_Back.png",
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                40,
                                                "Mud-Slap",
                                                Ground,
                                                Physical,
                                                20,
                                                "Scratch",
                                                Normal,
                                                Physical,
                                                40,
                                                "Slash",
                                                Normal,
                                                Physical,
                                                70);

            listOfPokemon[9] = definePokemon("ONIX",
                                                Rock,
                                                None,
                                                35,
                                                35,
                                                45,
                                                160,
                                                30,
                                                45,
                                                70,
                                                "./PokemonSprite/Onix_Front.png",
                                                "./PokemonSprite/Onix_Back.png",
                                                "Double Edge",
                                                Normal,
                                                Physical,
                                                120,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100,
                                                "Rock Slide",
                                                Rock,
                                                Physical,
                                                75,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                40);

            listOfPokemon[10] = definePokemon("GOLEM",
                                                Rock,
                                                Ground,
                                                80,
                                                80,
                                                120,
                                                130,
                                                55,
                                                65,
                                                45,
                                                "./PokemonSprite/Golem_Front.png",
                                                "./PokemonSprite/Golem_Back.png",
                                                "Rock Throw",
                                                Rock,
                                                Physical,
                                                50,
                                                "Rock Slide",
                                                Rock,
                                                Physical,
                                                75,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Double Edge",
                                                Normal,
                                                Physical,
                                                120);

            listOfPokemon[11] = definePokemon("RHYDON",
                                                Rock,
                                                Ground,
                                                105,
                                                105,
                                                130,
                                                120,
                                                45,
                                                45,
                                                40,
                                                "./PokemonSprite/Rhydon_Front.png",
                                                "./PokemonSprite/Rhydon_Back.png",
                                                "Megahorn",
                                                Bug,
                                                Physical,
                                                50,
                                                "Rock Slide",
                                                Rock,
                                                Physical,
                                                75,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Double Edge",
                                                Normal,
                                                Physical,
                                                120);

            listOfPokemon[12] = definePokemon("BUTTERFREE",
                                                Bug,
                                                Flying,
                                                60,
                                                60,
                                                45,
                                                50,
                                                90,
                                                80,
                                                70,
                                                "./PokemonSprite/Butterfree_Front.png",
                                                "./PokemonSprite/Butterfree_Back.png",
                                                "Silver Wind",
                                                Bug,
                                                Special,
                                                60,
                                                "Psybeam",
                                                Psychic,
                                                Special,
                                                65,
                                                "Gust",
                                                Flying,
                                                Special,
                                                40,
                                                "Aerial Ace",
                                                Flying,
                                                Physical,
                                                60);

            listOfPokemon[13] = definePokemon("BEEDRILL",
                                                Bug,
                                                Poison,
                                                65,
                                                65,
                                                90,
                                                40,
                                                45,
                                                80,
                                                75,
                                                "./PokemonSprite/Beedrill_Front.png",
                                                "./PokemonSprite/Beedrill_Back.png",
                                                "Twinneedle",
                                                Bug,
                                                Physical,
                                                25,
                                                "Solar Beam",
                                                Grass,
                                                Special,
                                                120,
                                                "Pin Missle",
                                                Bug,
                                                Physical,
                                                25,
                                                "Cut",
                                                Normal,
                                                Physical,
                                                50);

            listOfPokemon[14] = definePokemon("PINSIR",
                                                Bug,
                                                None,
                                                65,
                                                65,
                                                125,
                                                100,
                                                55,
                                                70,
                                                85,
                                                "./PokemonSprite/Pinsir_Front.png",
                                                "./PokemonSprite/Pinsir_Back.png",
                                                "Cut",
                                                Normal,
                                                Physical,
                                                50,
                                                "Strength",
                                                Normal,
                                                Physical,
                                                80,
                                                "X-Scissor",
                                                Bug,
                                                Physical,
                                                80,
                                                "Bug Bite",
                                                Bug,
                                                Physical,
                                                60);

            listOfPokemon[15] = definePokemon("CHARIZARD",
                                                Fire,
                                                Flying,
                                                78,
                                                78,
                                                84,
                                                76,
                                                109,
                                                85,
                                                100,
                                                "./PokemonSprite/Charizard_Front.png",
                                                "./PokemonSprite/Charizard_Back.png",
                                                "Fire Blast",
                                                Fire,
                                                Special,
                                                110,
                                                "Dragon Claw",
                                                Dragon,
                                                Physical,
                                                80,
                                                "Aerial Ace",
                                                Flying,
                                                Physical,
                                                60,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100);

            listOfPokemon[16] = definePokemon("NINETALES",
                                                Fire,
                                                None,
                                                73,
                                                73,
                                                76,
                                                75,
                                                81,
                                                100,
                                                100,
                                                "./PokemonSprite/Ninetales_Front.png",
                                                "./PokemonSprite/Ninetales_Back.png",
                                                "Flamethrower",
                                                Fire,
                                                Special,
                                                90,
                                                "Heat Wave",
                                                Fire,
                                                Special,
                                                95,
                                                "Fire Blast",
                                                Fire,
                                                Special,
                                                110,
                                                "Quick Attack",
                                                Normal,
                                                Special,
                                                40);

            listOfPokemon[17] = definePokemon("ARCANINE",
                                                Fire,
                                                None,
                                                90,
                                                90,
                                                110,
                                                80,
                                                100,
                                                80,
                                                95,
                                                "./PokemonSprite/Arcanine_Front.png",
                                                "./PokemonSprite/Arcanine_Back.png",
                                                "Extremespeed",
                                                Normal,
                                                Physical,
                                                80,
                                                "Overheat",
                                                Fire,
                                                Special,
                                                130,
                                                "Aerial Ace",
                                                Flying,
                                                Physical,
                                                60,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100);

            listOfPokemon[18] = definePokemon("BLASTOISE",
                                                Water,
                                                None,
                                                79,
                                                79,
                                                83,
                                                100,
                                                85,
                                                105,
                                                78,
                                                "./PokemonSprite/Blastoise_Front.png",
                                                "./PokemonSprite/Blastoise_Back.png",
                                                "Hydro Pump",
                                                Water,
                                                Special,
                                                110,
                                                "Ice Beam",
                                                Ice,
                                                Special,
                                                90,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Skull Bash",
                                                Normal,
                                                Physical,
                                                130);

            listOfPokemon[19] = definePokemon("GYARADOS",
                                                Water,
                                                None,
                                                95,
                                                95,
                                                125,
                                                79,
                                                60,
                                                100,
                                                81,
                                                "./PokemonSprite/Gyarados_Front.png",
                                                "./PokemonSprite/Gyarados_Back.png",
                                                "Hydro Pump",
                                                Water,
                                                Special,
                                                110,
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Hyper Beam",
                                                Normal,
                                                Special,
                                                150,
                                                "Waterfall",
                                                Water,
                                                Physical,
                                                80);

            listOfPokemon[20] = definePokemon("VAPOREON",
                                                Water,
                                                None,
                                                130,
                                                130,
                                                65,
                                                60,
                                                110,
                                                95,
                                                65,
                                                "./PokemonSprite/Vaporeon_Front.png",
                                                "./PokemonSprite/Vaporeon_Back.png",
                                                "Water Pulse",
                                                Water,
                                                Special,
                                                60,
                                                "Quick Attack",
                                                Normal,
                                                Special,
                                                40,
                                                "Aurora Beam",
                                                Ice,
                                                Special,
                                                65,
                                                "Hydro Pump",
                                                Water,
                                                Special,
                                                110);

            listOfPokemon[21] = definePokemon("VENUSAUR",
                                                Grass,
                                                Poison,
                                                80,
                                                80,
                                                82,
                                                83,
                                                100,
                                                100,
                                                80,
                                                "./PokemonSprite/Venusaur_Front.png",
                                                "./PokemonSprite/Venusaur_Back.png",
                                                "Earthquake",
                                                Ground,
                                                Physical,
                                                100,
                                                "Razor Leaf",
                                                Grass,
                                                Physical,
                                                55,
                                                "Sludge Bomb",
                                                Poison,
                                                Special,
                                                90,
                                                "Frenzy Plant",
                                                Grass,
                                                Special,
                                                150);

            listOfPokemon[22] = definePokemon("EXEGGUTOR",
                                                Grass,
                                                Psychic,
                                                95,
                                                95,
                                                95,
                                                85,
                                                125,
                                                75,
                                                55,
                                                "./PokemonSprite/Exeggutor_Front.png",
                                                "./PokemonSprite/Exeggutor_Back.png",
                                                "Egg Bomb",
                                                Normal,
                                                Physical,
                                                100,
                                                "Psychic",
                                                Psychic,
                                                Special,
                                                90,
                                                "Hyper Beam",
                                                Normal,
                                                Special,
                                                150,
                                                "Ancient Power",
                                                Rock,
                                                Special,
                                                60);

            listOfPokemon[23] = definePokemon("VILEPLUME",
                                                Grass,
                                                Poison,
                                                75,
                                                75,
                                                80,
                                                85,
                                                110,
                                                90,
                                                50,
                                                "./PokemonSprite/Vileplume_Front.png",
                                                "./PokemonSprite/Vileplume_Back.png",
                                                "Acid",
                                                Poison,
                                                Special,
                                                40,
                                                "Sludge Bomb",
                                                Poison,
                                                Special,
                                                90,
                                                "Secret Power",
                                                Normal,
                                                Physical,
                                                70,
                                                "Vine Whip",
                                                Grass,
                                                Physical,
                                                45);

            listOfPokemon[24] = definePokemon("ALAKAZAM",
                                                Psychic,
                                                None,
                                                55,
                                                55,
                                                50,
                                                45,
                                                135,
                                                95,
                                                120,
                                                "./PokemonSprite/Alakazam_Front.png",
                                                "./PokemonSprite/Alakazam_Back.png",
                                                "Psychic",
                                                Psychic,
                                                Special,
                                                90,
                                                "Shadow Ball",
                                                Ghost,
                                                Special,
                                                80,
                                                "Psybeam",
                                                Psychic,
                                                Special,
                                                65,
                                                "Thunder Punch",
                                                Electric,
                                                Physical,
                                                75);

            listOfPokemon[25] = definePokemon("MEWTWO",
                                                Psychic,
                                                None,
                                                106,
                                                106,
                                                110,
                                                90,
                                                154,
                                                90,
                                                130,
                                                "./PokemonSprite/Mewtwo_Front.png",
                                                "./PokemonSprite/Mewtwo_Back.png",
                                                "Swift",
                                                Normal,
                                                Special,
                                                60,
                                                "Psychic",
                                                Psychic,
                                                Special,
                                                90,
                                                "Shadow Ball",
                                                Ghost,
                                                Special,
                                                80,
                                                "Flamethrower",
                                                Fire,
                                                Special,
                                                90);

            listOfPokemon[26] = definePokemon("JYNX",
                                                Psychic,
                                                None,
                                                65,
                                                65,
                                                50,
                                                35,
                                                115,
                                                95,
                                                95,
                                                "./PokemonSprite/Jynx_Front.png",
                                                "./PokemonSprite/Jynx_Back.png",
                                                "Psychic",
                                                Psychic,
                                                Special,
                                                90,
                                                "Blizzard",
                                                Ice,
                                                Special,
                                                110,
                                                "Ice Punch",
                                                Ice,
                                                Physical,
                                                75,
                                                "Shadow Ball",
                                                Ghost,
                                                Special,
                                                80);

            listOfPokemon[27] = definePokemon("PIKACHU",
                                                Electric,
                                                None,
                                                35,
                                                35,
                                                55,
                                                40,
                                                50,
                                                50,
                                                90,
                                                "./PokemonSprite/Pikachu_Front.png",
                                                "./PokemonSprite/Pikachu_Back.png",
                                                "Volt Tackle",
                                                Electric,
                                                Physical,
                                                120,
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100,
                                                "Thunderbolt",
                                                Electric,
                                                Special,
                                                90,
                                                "Thunder",
                                                Electric,
                                                Special,
                                                110);

            listOfPokemon[28] = definePokemon("JOLTEON",
                                                Electric,
                                                None,
                                                65,
                                                65,
                                                65,
                                                60,
                                                110,
                                                95,
                                                130,
                                                "./PokemonSprite/Jolteon_Front.png",
                                                "./PokemonSprite/Jolteon_Back.png",
                                                "Iron Tail",
                                                Steel,
                                                Physical,
                                                100,
                                                "Quick Attack",
                                                Normal,
                                                Special,
                                                40,
                                                "Thunderbolt",
                                                Electric,
                                                Special,
                                                90,
                                                "Charge Beam",
                                                Electric,
                                                Special,
                                                50);

            listOfPokemon[29] = definePokemon("ELECTABUZZ",
                                                Electric,
                                                None,
                                                65,
                                                65,
                                                83,
                                                57,
                                                95,
                                                85,
                                                105,
                                                "./PokemonSprite/Electabuzz_Front.png",
                                                "./PokemonSprite/Electabuzz_Back.png",
                                                "Thunderbolt",
                                                Electric,
                                                Special,
                                                90,
                                                "Thunder",
                                                Electric,
                                                Special,
                                                110,
                                                "Quick Attack",
                                                Normal,
                                                Special,
                                                40,
                                                "Swift",
                                                Normal,
                                                Special,
                                                60);

            };


struct CollegeOpponent{
    int errorProbability;
    std::string name;
    std::string spritePath;
    std::string opDialogue;
    std::string WinDialogue;
    std::string LoseDialogue;
    std::string bg[4];
};

CollegeOpponent defineOpponent(int oppErrorProbability,
                                std::string oppName,
                                std::string oppSpritePath,
                                std::string openingDialogue,
                                std::string oppWinDialogue,
                                std::string oppLoseDialogue,
                                std::string bg1,
                                std::string bg2,
                                std::string bg3,
                                std::string bg4){
    CollegeOpponent opponent;
    opponent.errorProbability = oppErrorProbability;
    opponent.name = oppName;
    opponent.spritePath = oppSpritePath;
    opponent.opDialogue =  openingDialogue;
    opponent.WinDialogue = oppWinDialogue;
    opponent.LoseDialogue = oppLoseDialogue;
    opponent.bg[0] = bg1;
    opponent.bg[1] = bg2;
    opponent.bg[2] = bg3;
    opponent.bg[3] = bg4;
    return opponent;
}

struct Item {
    std::string ItemName;
    int Quantity;
};

Item defineItem(std::string tempItemName,
                int tempQuantity) {
    Item currentItem;
    currentItem.ItemName = tempItemName;
    currentItem.Quantity = tempQuantity;
    return currentItem;
};

Pokemon useItemOnPokemon(int itemUsed,
                         Pokemon healedPokemon) {
    Pokemon tempPokemon = healedPokemon;
    std::cout << "Before Healing: " << tempPokemon.CurrentHP << std::endl;
    if (itemUsed == 0){
        tempPokemon.CurrentHP += (tempPokemon.MaxHP * 0.5);
    } else if (itemUsed == 1){
        tempPokemon.CurrentHP += 200;
        if (tempPokemon.CurrentHP > tempPokemon.MaxHP) {
            tempPokemon.CurrentHP = tempPokemon.MaxHP;
        }
    }
    std::cout << "After Healing: " << tempPokemon.CurrentHP << std::endl;

    return tempPokemon;
};

float GetTypeEffectivenessMultiplier(PokemonType attackedType,
                                     PokemonType moveType) {
    if (typeChart[attackedType][moveType] == Strong){
        return 2;
    } else if (typeChart[attackedType][moveType] == Weak){
        return 0.5;
    } else if (typeChart[attackedType][moveType] == Neutral){
        return 1;
    } else if (typeChart[attackedType][moveType] == NoDmg){
        return 0;
    }
};

Pokemon DamagePokemon(Pokemon attackerPokemon,
                      Pokemon attackedPokemon,
                      PokemonMove moveUsed) {
    float STABMultiplier = 1;
    float Type1Effectiveness = GetTypeEffectivenessMultiplier(moveUsed.MoveType, attackedPokemon.Type1);
    float Type2Effectiveness = GetTypeEffectivenessMultiplier(moveUsed.MoveType, attackedPokemon.Type2);

    std::cout << "Move Type: " << moveUsed.MoveType << std::endl;
    std::cout << "Attacked Pokemon Type1: " << attackedPokemon.Type1 << std::endl;
    std::cout << "Attacked Pokemon Type2: " << attackedPokemon.Type2 << std::endl;
    std::cout << "Type1Effectiveness: " << Type1Effectiveness << std::endl;
    std::cout << "Type2Effectiveness: " << Type2Effectiveness << std::endl;

    if (attackerPokemon.Type1 == moveUsed.MoveType || attackerPokemon.Type2 == moveUsed.MoveType){
        STABMultiplier = 1.5;
    }

    float damage;
    if (moveUsed.PhysOrSp == Physical){
        damage = ((((2 * attackerPokemon.Level / 5) + 2) * moveUsed.Power * attackerPokemon.ATK / attackedPokemon.DEF / 50) + 2) * STABMultiplier * Type1Effectiveness * Type2Effectiveness;
    } else if (moveUsed.PhysOrSp == Special){
        damage = ((((2 * attackerPokemon.Level / 5) + 2) * moveUsed.Power * attackerPokemon.SpATK / attackedPokemon.SpDEF / 50) + 2) * STABMultiplier * Type1Effectiveness * Type2Effectiveness;
    }

    std::cout << "Damage: " << damage << std::endl;
    attackedPokemon.CurrentHP -= (int)damage;
    return attackedPokemon;
};

int OpponentMove (PokemonMove OpponentMoveSet[4],
                          Pokemon YourPokemon,
                          int OpponentErrorProbability){
    int bestMove;
    int randomNum = rand() % 101;
    if (randomNum < OpponentErrorProbability){
        randomNum = rand() % 4;
        bestMove = randomNum;
        return bestMove;
    }
    else {
        bestMove = 0;
        for (int i = 1; i < 4; i++){
            if (GetTypeEffectivenessMultiplier(OpponentMoveSet[i].MoveType, YourPokemon.Type1)
                * GetTypeEffectivenessMultiplier(OpponentMoveSet[i].MoveType, YourPokemon.Type2)
                * OpponentMoveSet[i].Power >
                GetTypeEffectivenessMultiplier(OpponentMoveSet[bestMove].MoveType, YourPokemon.Type1)
                * GetTypeEffectivenessMultiplier(OpponentMoveSet[bestMove].MoveType, YourPokemon.Type2)
                * OpponentMoveSet[bestMove].Power) {
                bestMove = i;
            }
        }
        return bestMove;
    }
};

int currentOpponent = 0;
int UsedPokemonIndices[30];
int UsedPokemonSize = 0;
int PokemonChoicesIndices[6];
int PlayerPokemonIndices[3];
int opponentPokemon[3];
Pokemon listOfPokemon[30];
CollegeOpponent CollegeOpponents[5];
Item ListOfItems[2];

void RandomizeOpponentPokemon(int* opponentPokemon) {

    int isFound = 0;
    std::srand(std::time(0));

    for (int i = 0; i < 3; ++i) {
        int randomPokemon;

        do {
            randomPokemon = std::rand() % 30;
            isFound = 0;
            for (int j = 0; j < UsedPokemonSize; j++) {
                if (UsedPokemonIndices[j] == randomPokemon) {
                    isFound = 1;
                    break;
                }
            }
        } while (isFound == 1);

        opponentPokemon[i] = randomPokemon;
        UsedPokemonIndices[i + (currentOpponent * 6 + 3)] = opponentPokemon[i];
        UsedPokemonSize++;
    }
}

class Savescreen {
        private:
            sf::RenderWindow& window;
            sf::RectangleShape background;
            sf::Font font;
            sf::Text SavingText;
            int isDoneSaving = 0;
            int runDone = 0;

            std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

        public:
            Savescreen(sf::RenderWindow& window)
                : window(window)
            {
                font.loadFromFile("pokemon_fire_red.ttf");
                background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
                background.setFillColor(sf::Color::Black);
                SavingText.setFillColor(sf::Color::White);
                SavingText.setPosition(445, 245);
                SavingText.setString("SAVING...");
                SavingText.setFont(font);
                SavingText.setCharacterSize(50);
            }

            void text() {
                float alpha = 1.0f;
                float fadeSpeed = 0.25f;

                while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(5)) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    alpha += fadeSpeed;
                    if (alpha >= 255.0f || alpha <= 0.0f) {
                        fadeSpeed = -fadeSpeed;
                    }

                    SavingText.setFillColor(sf::Color(255, 255, 255, alpha));

                    window.clear();
                    window.draw(background);
                    window.draw(SavingText);
                    window.display();
                }

                runDone = 1;
            }


            void run() {
                while (window.isOpen() && runDone == 0) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    window.clear();
                    text();
                }
            }
};

class Game3
{
public:
    Game3(sf::RenderWindow& window, std::string playerName, int gender)
        : window(window) , playerName(playerName), gender(gender)
    {}


    void attacksoundeffect(int movechosen, int pokemonindex, sf::SoundBuffer& buffer, sf::Sound& sound) {
        int movetype = listOfPokemon[pokemonindex].Moveset[movechosen].MoveType;
        if (movetype == 0) {
            buffer.loadFromFile("./Sounds/bug.ogg");
            sound.setVolume(1100);
        } else if (movetype == 1) {
            buffer.loadFromFile("./Sounds/dragon.ogg");
            sound.setVolume(1100);
        } else if (movetype == 2) {
            buffer.loadFromFile("./Sounds/electric.ogg");
            sound.setVolume(1100);
        } else if (movetype == 3) {
            buffer.loadFromFile("./Sounds/flying.ogg");
            sound.setVolume(1100);
        } else if (movetype == 4) {
            buffer.loadFromFile("./Sounds/fire.ogg");
            sound.setVolume(1100);
        } else if (movetype == 5) {
            buffer.loadFromFile("./Sounds/ghost.ogg");
            sound.setVolume(1100);
        } else if (movetype == 6) {
            buffer.loadFromFile("./Sounds/grass.ogg");
            sound.setVolume(1100);
        } else if (movetype == 7) {
            buffer.loadFromFile("./Sounds/ground.ogg");
            sound.setVolume(1100);
        } else if (movetype == 8) {
            buffer.loadFromFile("./Sounds/ice.ogg");
            sound.setVolume(1100);
        } else if (movetype == 9) {
            buffer.loadFromFile("./Sounds/normal.ogg");
            sound.setVolume(1100);
        } else if (movetype == 10) {
            buffer.loadFromFile("./Sounds/poison.ogg");
            sound.setVolume(1100);
        } else if (movetype == 11) {
            buffer.loadFromFile("./Sounds/psychic.ogg");
            sound.setVolume(1100);
        } else if (movetype == 12) {
            buffer.loadFromFile("./Sounds/rock.ogg");
            sound.setVolume(1100);
        } else if (movetype == 13) {
            buffer.loadFromFile("./Sounds/steel.ogg");
            sound.setVolume(700);
        } else if (movetype == 14) {
            buffer.loadFromFile("./Sounds/water.ogg");
            sound.setVolume(1100);
        }
        sound.setBuffer(buffer);
        sound.play();
    }

    void shakeAnimation(sf::Sprite& sprite, float shakeDistance, float duration,sf::Sprite sprite2, sf::Sprite background,int& attacker,sf::Text pokenem, sf::Text helt, sf::Text pokenem2,sf::Text helt2)
        {
            sf::SoundBuffer buffer;
            sf::Sound sound;
            std::string AttackPokemon = listOfPokemon[attacker].Name + " used \n" + listOfPokemon[attacker].Moveset[chosenMove].MoveName +"!";
            animateText2(DialogueHolder, AttackPokemon ,backgroundSprite[currentOpponent],enemyPokemonSprite[currentOpponent],PokemonSprite,NameOfPokemon[1],Health[1],NameOfPokemon[0],Health[0]);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sf::Clock clock;
            float elapsed = 0.0f;
            sf::Vector2f originalPosition = sprite.getPosition();
            float direction = 1.0f;
            attacksoundeffect(chosenMove,attacker,buffer,sound);
            while (elapsed < duration)
            {
                elapsed = clock.getElapsedTime().asSeconds();

                float offset = shakeDistance * (1 - (elapsed / duration));
                sprite.setPosition(originalPosition.x + (offset * direction), originalPosition.y);

                direction *= -1.0f;

                window.clear();
                window.draw(background);
                window.draw(pokenem);
                window.draw(helt);
                window.draw(pokenem2);
                window.draw(helt2);
                window.draw(sprite);
                window.draw(sprite2);
                window.display(); // Display the window
            }

            sprite.setPosition(originalPosition);
        }

    void saveDataToFile2() {
        std::ofstream outputFile("Save.txt");
        if (outputFile.is_open()) {

            outputFile.seekp(std::ios::beg);
            outputFile.seekp(2, std::ios::cur);

            outputFile << UsedPokemonSize << std::endl;
            outputFile << currentOpponent << std::endl;
            std::cout << UsedPokemonSize << std::endl;
            std::cout << currentOpponent << std::endl;
            for (int i = 0; i < UsedPokemonSize; ++i) {
                if(i == UsedPokemonSize){
                    outputFile << UsedPokemonIndices[i] << std::endl;
                    std::cout << UsedPokemonIndices[i] << '-' ;
                    std::cout << listOfPokemon[UsedPokemonIndices[i]].Name;
                }
                else{
                  outputFile << UsedPokemonIndices[i] << std::endl;
                  std::cout << UsedPokemonIndices[i] << '-';
                  std::cout << listOfPokemon[UsedPokemonIndices[i]].Name << ',';
                }
                std::cout << UsedPokemonIndices[i] << ',';
            }
            outputFile.close();
            std::cout << "Data saved to file." << std::endl;
        } else {
            std::cerr << "Failed to open the file." << std::endl;
        }
    }

    void Actions(int& action){

        sf::Event event;
        while (window.pollEvent(event)){

            if(event.type == sf::Event::MouseMoved){
               for(int i = 0; i < 3; ++i){
                if(Choices[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                        Choices[i].setFillColor(sf::Color(174,174,67));
                    }
                else{
                    Choices[i].setFillColor(sf::Color(72,72,72));
                }

                 if(PokemonToHeal[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                            PokemonToHeal[i].setFillColor(sf::Color(174,174,67));
                        }
                    else{
                        PokemonToHeal[i].setFillColor(sf::Color(72,72,72));
                    }
               }

               for(int i = 0; i < 2; ++i){
                    if(ItemNames[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y) && ListOfItems[i].Quantity != 0){
                        ItemNames[i].setFillColor(sf::Color(174,174,67));
                        }
                    else if(ItemNames[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y) && ListOfItems[i].Quantity == 0){
                        ItemNames[i].setFillColor(sf::Color(196,43,43));
                        }
                    else{
                        ItemNames[i].setFillColor(sf::Color(72,72,72));
                    }
               }

               for(int i = 0; i < 3; ++i){
                    if(PokemonToHeal[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                        if ((listOfPokemon[PlayerPokemonIndices[i]].CurrentHP == 0 && chosenItem == 0) ||
                            ((listOfPokemon[PlayerPokemonIndices[i]].CurrentHP != 0 && chosenItem == 1) &&
                            (listOfPokemon[PlayerPokemonIndices[i]].CurrentHP < listOfPokemon[PlayerPokemonIndices[i]].MaxHP && chosenItem == 1))){
                            PokemonToHeal[i].setFillColor(sf::Color(174,174,67));
                        }
                        else {
                            PokemonToHeal[i].setFillColor(sf::Color(196,43,43));
                        }
                    }
                    else{
                        PokemonToHeal[i].setFillColor(sf::Color(72,72,72));
                    }
               }

                for(int i = 0; i < 4; ++i){
                    if(currentPokemonMoveset[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                        currentPokemonMoveset[i].setFillColor(sf::Color(174,174,67));
                        }
                    else{
                        currentPokemonMoveset[i].setFillColor(sf::Color(72,72,72));
                    }
                }

                if(action == 2){
                    for(int i = 0; i < 2; ++i){
                        if(PlayerPokemonName[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                                if(listOfPokemon[PlayerPokemons[i]].CurrentHP > 0){
                                    PlayerPokemonName[i].setFillColor(sf::Color(174,174,67));
                                }
                                else if(listOfPokemon[PlayerPokemons[i]].CurrentHP <= 0){
                                    PlayerPokemonName[i].setFillColor(sf::Color(196,43,43));
                                }
                            }
                        else{
                            PlayerPokemonName[i].setFillColor(sf::Color(72,72,72));
                        }
                    }
                }

                if(BackButtonText.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                    BackButtonText.setFillColor(sf::Color(174,174,67));
                }
                else{
                    BackButtonText.setFillColor(sf::Color(72,72,72));
                }
            }



            else if(isBattle == true && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    if(Choices[0].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                        action = 1;
                        battleflag = 1;
                    }
                    if(Choices[1].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                        action = 2;
                        battleflag = 1;
                    }
                    if(Choices[2].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                        action = 3;
                        battleflag = 1;
                    }


                      if(BackButtonText.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                            battleflag = 0;
                            action = 0;
                            isItemChosen = 0;
                        }


                    if(action == 1){
                        for(int i = 0; i < 4; i++){
                            if(currentPokemonMoveset[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                                chosenMove = i;

                                if (fromFaint == 1){
                                    battleflag = 0;
                                }
                                else if (fromFaint == 0){
                                    battleflag = 2;
                                }
                            }
                        }
                    }

                if(action == 2){
                        if(PlayerPokemonName[0].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                            pokemonToChange = 1;
                        }
                        if(PlayerPokemonName[1].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                            pokemonToChange = 2;
                        }

                    }

                  if(action == 3){
                    if (isItemChosen == 1){
                        for(int i = 0; i < 3; ++i){
                            if(PokemonToHeal[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                                if ((listOfPokemon[PlayerPokemonIndices[i]].CurrentHP == 0 && chosenItem == 0) ||
                                    ((listOfPokemon[PlayerPokemonIndices[i]].CurrentHP != 0 && chosenItem == 1) &&
                                    (listOfPokemon[PlayerPokemonIndices[i]].CurrentHP < listOfPokemon[PlayerPokemonIndices[i]].MaxHP && chosenItem == 1))){

                                    listOfPokemon[PlayerPokemonIndices[i]] = useItemOnPokemon(chosenItem, listOfPokemon[PlayerPokemonIndices[i]]);
                                    --ListOfItems[chosenItem].Quantity;
                                    hasHealed = 1;

                                }
                            }
                        }
                    }
                    else if (isItemChosen == 0){
                        for(int i = 0; i < 2; i++){
                            if(ItemNames[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && ListOfItems[i].Quantity != 0){
                                chosenItem = i;
                                isItemChosen = 1;
                            }
                        }
                    }
                }
            }

        }

    }

     void Battle(){

                if(pokemonToChange == 0){
                PokemonTexture.loadFromFile(listOfPokemon[currentPokemon].BackSprite);
                PokemonSprite.setTexture(PokemonTexture);
                }
                enemyPokemonTexture[currentOpponent].loadFromFile(listOfPokemon[currentOpponentPokemon].FrontSprite);
                enemyPokemonSprite[currentOpponent].setTexture(enemyPokemonTexture[currentOpponent]);
                PokemonSprite.setPosition(100,161);
                PokemonSprite.setScale(3.5f,3.5f);
                enemyPokemonSprite[currentOpponent].setPosition(590,15);
                enemyPokemonSprite[currentOpponent].setScale(3.6f,3.5f);

                NameOfPokemon[0].setString(listOfPokemon[currentPokemon].Name);
                NameOfPokemon[1].setString(listOfPokemon[currentOpponentPokemon].Name);
                Health[0].setString(std::to_string(listOfPokemon[currentPokemon].CurrentHP) + "/" +  std::to_string(listOfPokemon[currentPokemon].MaxHP));
                Health[1].setString(std::to_string(listOfPokemon[currentOpponentPokemon].CurrentHP) + "/" +  std::to_string(listOfPokemon[currentOpponentPokemon].MaxHP));
                for(int i = 0; i < 2; i++){
                    window.draw(NameOfPokemon[i]);
                    window.draw(Health[i]);
                }

                window.draw(PokemonSprite);
                window.draw(enemyPokemonSprite[currentOpponent]);

                if(battleflag == 0){
                    for(int i = 0; i < 3; i++){
                        window.draw(Choices[i]);
                    }

                    for(int i = 0; i < 3; i++){
                        Choices[i].setScale(1,1);
                    }

                    Actions(action);
                }

                else if(battleflag == 1){
                    for(int i = 0; i < 3; i++){
                        Choices[i].setScale(0,0);
                    }

                    if(fromFaint != 1){
                        window.draw(BackButtonText);
                        BackButtonText.setScale(1,1);
                    }
                    else{
                        BackButtonText.setScale(0,0);
                    }

                    if(action == 1){
                        for(int i = 0; i < 4; ++i){
                            currentPokemonMoveset[i].setString(listOfPokemon[currentPokemon].Moveset[i].MoveName);
                            window.draw(currentPokemonMoveset[i]);
                        }

                        Actions(action);
                    }
                    else if(action == 2){
                        int k = 0;
                        for(int i = 0; i < 3; ++i){
                            if(PlayerPokemonIndices[i] != currentPokemon){
                                PlayerPokemons[k] = PlayerPokemonIndices[i];
                                PlayerPokemonName[k].setString(listOfPokemon[PlayerPokemons[k]].Name);
                                k++;
                            }
                        }

                        window.draw(PlayerPokemonName[0]);
                        window.draw(PlayerPokemonName[1]);


                        Actions(action);

                        if(pokemonToChange == 1 && listOfPokemon[PlayerPokemons[0]].CurrentHP > 0 ){
                            currentPokemon = PlayerPokemons[0];
                            PokemonTexture.loadFromFile(listOfPokemon[PlayerPokemons[0]].BackSprite);
                            PokemonSprite.setTexture(PokemonTexture);
                            battleflag = 2;

                            if (fromFaint == 1){
                                fromFaint = 0;
                                battleflag = 0;
                            }
                        }
                        else if(pokemonToChange == 2 && listOfPokemon[PlayerPokemons[1]].CurrentHP > 0 ){
                            currentPokemon = PlayerPokemons[1];
                            PokemonTexture.loadFromFile(listOfPokemon[PlayerPokemons[1]].BackSprite);
                            PokemonSprite.setTexture(PokemonTexture);
                            battleflag = 2;

                            if (fromFaint == 1){
                                fromFaint = 0;
                                battleflag = 0;
                            }
                        }
                    }
                    else if(action == 3){

                        if (isItemChosen == 0){
                            for(int i = 0; i < 2; ++i){
                            ItemNames[i].setScale(1,1);
                            ItemNames[i].setString(ListOfItems[i].ItemName + " x" + std::to_string(ListOfItems[i].Quantity));
                            window.draw(ItemNames[i]);
                            }
                        }

                        Actions(action);

                        if (isItemChosen == 1){
                            ItemNames[0].setScale(0,0);
                            ItemNames[1].setScale(0,0);
                            for(int i = 0; i < 3; ++i){
                                PokemonToHeal[i].setString(listOfPokemon[PlayerPokemonIndices[i]].Name);
                                window.draw(PokemonToHeal[i]);
                            }

                            if (hasHealed == 1){
                                battleflag = 2;
                                hasHealed = 0;
                            }
                        }
                    }
                }

                    else if(battleflag == 2){ //OpponentAttacks
                        if(action == 1 && listOfPokemon[currentPokemon].Speed >= listOfPokemon[currentOpponentPokemon].Speed){
                            shakeAnimation(enemyPokemonSprite[currentOpponent],30.0,1.0,PokemonSprite,backgroundSprite[currentOpponent],currentPokemon,NameOfPokemon[1],Health[1],NameOfPokemon[0],Health[0]);
                            DialogueHolder.setString("");
                            listOfPokemon[currentOpponentPokemon] = DamagePokemon(listOfPokemon[currentPokemon], listOfPokemon[currentOpponentPokemon], listOfPokemon[currentPokemon].Moveset[chosenMove]);
                            if (listOfPokemon[currentOpponentPokemon].CurrentHP < 0){
                                listOfPokemon[currentOpponentPokemon].CurrentHP = 0;
                            }
                            if (listOfPokemon[opponentPokemon[0]].CurrentHP == 0 && listOfPokemon[opponentPokemon[1]].CurrentHP == 0 && listOfPokemon[opponentPokemon[2]].CurrentHP == 0){
                                isBattle = false;
                                isWin = 1;
                            }
                            if (listOfPokemon[currentOpponentPokemon].CurrentHP == 0){
                                for(int i = 0; i < 3; i++){
                                    if(listOfPokemon[opponentPokemon[i]].CurrentHP != 0){
                                        currentOpponentPokemon = opponentPokemon[i];
                                        break;
                                    }
                                }
                                opponentFaint = 1;
                            }
                        }

                        if(opponentFaint == 0){
                            int opponentMove = OpponentMove (listOfPokemon[currentOpponentPokemon].Moveset, listOfPokemon[currentPokemon], CollegeOpponents[currentOpponent].errorProbability);
                            shakeAnimation(PokemonSprite,30,1,enemyPokemonSprite[currentOpponent],backgroundSprite[currentOpponent],currentOpponentPokemon,NameOfPokemon[1],Health[1],NameOfPokemon[0],Health[0]);
                            DialogueHolder.setString("");
                            listOfPokemon[currentPokemon] = DamagePokemon(listOfPokemon[currentOpponentPokemon], listOfPokemon[currentPokemon], listOfPokemon[currentOpponentPokemon].Moveset[opponentMove]);
                            if (listOfPokemon[currentPokemon].CurrentHP < 0){
                                listOfPokemon[currentPokemon].CurrentHP = 0;
                            }
                            if (listOfPokemon[PlayerPokemonIndices[0]].CurrentHP == 0 && listOfPokemon[PlayerPokemonIndices[1]].CurrentHP == 0 && listOfPokemon[PlayerPokemonIndices[2]].CurrentHP == 0){
                                isBattle = false;
                                isWin = 2;
                            }
                            if (listOfPokemon[currentPokemon].CurrentHP == 0){
                                battleflag = 1;
                                action = 2;
                                fromFaint = 1;
                                pokemonToChange = 0;
                                isItemChosen = 0;
                            }
                        }

                        if(action == 1 && listOfPokemon[currentPokemon].Speed < listOfPokemon[currentOpponentPokemon].Speed && opponentFaint == 0){
                            shakeAnimation(enemyPokemonSprite[currentOpponent],30.0,1.0,PokemonSprite,backgroundSprite[currentOpponent],currentPokemon,NameOfPokemon[1],Health[1],NameOfPokemon[0],Health[0]);
                            DialogueHolder.setString("");
                            listOfPokemon[currentOpponentPokemon] = DamagePokemon(listOfPokemon[currentPokemon], listOfPokemon[currentOpponentPokemon], listOfPokemon[currentPokemon].Moveset[chosenMove]);
                            if (listOfPokemon[currentOpponentPokemon].CurrentHP < 0){
                                listOfPokemon[currentOpponentPokemon].CurrentHP = 0;
                            }
                            if (listOfPokemon[opponentPokemon[0]].CurrentHP == 0 && listOfPokemon[opponentPokemon[1]].CurrentHP == 0 && listOfPokemon[opponentPokemon[2]].CurrentHP == 0){
                                isBattle = false;
                                isWin = 1;
                            }
                            if (listOfPokemon[currentOpponentPokemon].CurrentHP == 0){
                                for(int i = 0; i < 3; i++){
                                    if(listOfPokemon[opponentPokemon[i]].CurrentHP != 0){
                                        currentOpponentPokemon = opponentPokemon[i];
                                        break;
                                    }
                                }
                                opponentFaint = 1;
                            }
                        }

                        if(fromFaint != 1){
                            battleflag = 0;
                            action = 0;
                            pokemonToChange = 0;
                            chosenItem = 0;
                            chosenMove = 0;
                            isItemChosen = 0;
                            opponentFaint = 0;
                        }
                    }
     }

     void animateText(sf::Text& text, const std::string& content, sf::Sprite& background, sf::Sprite& enemy, sf::Sprite& own){
        std::string animatedText;
        for (std::size_t i = 0; i < content.length(); ++i){
            // Append one character at a time to the animated text
            animatedText += content[i];

            // Assign the animated text to the sf::Text object
            text.setString(animatedText);

            // Delay between each character to simulate typing effect
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // Clear the window and redraw the updated background and text
            window.clear();
            window.draw(background);
            window.draw(enemy);
            window.draw(own);
            window.draw(text);
            window.display();
        }
    }

    void animateText2(sf::Text& text,
                      std::string& content,
                      sf::Sprite& background,
                      sf::Sprite& enemy,
                      sf::Sprite& own,
                      sf::Text pokename,
                      sf::Text pokehealth,
                      sf::Text poke,
                      sf::Text imded){
        std::string animatedText;
        for (std::size_t i = 0; i < content.length(); ++i){
            // Append one character at a time to the animated text
            animatedText += content[i];

            // Assign the animated text to the sf::Text object
            text.setString(animatedText);

            // Delay between each character to simulate typing effect
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // Clear the window and redraw the updated background and text
            window.clear();
            window.draw(background);
            window.draw(pokename);
            window.draw(pokehealth);
            window.draw(poke);
            window.draw(imded);
            window.draw(enemy);
            window.draw(own);
            window.draw(text);
            window.display();
        }

    }

        int flag = 0;

    void update()
    {
        if (alpha < 255)
        {
            alpha += fadeSpeed;
            if (alpha > 255)
                alpha = 255;
            backgroundSprite[currentOpponent].setColor(sf::Color(255, 255, 255, alpha));
            enemySprite[currentOpponent].setColor(sf::Color(255, 255, 255, alpha));
            ownSprite.setColor(sf::Color(255, 255, 255, alpha));
        }
        if(alpha == 255 && flag == 0){
            dialogueFlag = 1;
            flag++;
        }

    }

    void handleInput(sf::Event event){

        if ((isBattle == false && isWin == 0 && event.type == sf::Event::KeyPressed) || (isBattle == false && isWin == 0 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
        {
            isBattle = true;
            ownSprite.setScale(0,0);
            enemySprite[currentOpponent].setScale(0,0);
            DialogueHolder.setString("");
        }
         else if((isWin == 1 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) || (isWin == 1 && event.type == sf::Event::KeyPressed)){
                    saveDataToFile2();
                    currentOpponent++;
                    music2.stop();
                    runDone = 1;
                    Savescreen savescreen(window);
                    savescreen.run();
                }

    }

    void run()
    {
        ListOfItems[0].Quantity = 5;
        ListOfItems[1].Quantity = 5;
        if(currentOpponent < 4){
          music2.openFromFile("./Sounds/elitefour.ogg");
        }
        else if(currentOpponent == 4){
         music2.openFromFile("./Sounds/champion.ogg");
        }
        music2.setLoop(true);
        music2.setVolume(40);
        music2.play();
        RandomizeOpponentPokemon(opponentPokemon);
        backgroundTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].bg[0]);
        backgroundSprite[currentOpponent].setTexture(backgroundTexture[currentOpponent]);
        enemyTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].spritePath);
        enemySprite[currentOpponent].setTexture(enemyTexture[currentOpponent]);
        font.loadFromFile("pokemon_fire_red.ttf");
        DialogueHolder.setFont(font);
        DialogueHolder.setCharacterSize(40);
        DialogueHolder.setFillColor(sf::Color::White);
        DialogueHolder.setString("");
        DialogueHolder.setPosition(60,460);
        isBattle = false;
        battleflag = 0;
        pokemonToChange = 0;
        action = 0;
        for(int i = 0; i < 3 ; i++){
            Choices[i].setFont(font);
            Choices[i].setCharacterSize(50);
        }
        Choices[0].setFillColor(sf::Color(72,72,72));
        Choices[1].setFillColor(sf::Color(72,72,72));
        Choices[2].setFillColor(sf::Color(72,72,72));
        BackButtonText.setFillColor(sf::Color(72,72,72));
        BackButtonText.setPosition(865, 495);
        BackButtonText.setString("BACK");
        BackButtonText.setFont(font);
        BackButtonText.setCharacterSize(50);
        Choices[0].setPosition(735, 445);
        Choices[1].setPosition(865, 445);
        Choices[2].setPosition(735, 495);
        Choices[0].setString("FIGHT");
        Choices[1].setString("SWITCH");
        Choices[2].setString("BAG");
        PlayerPokemonName[0].setFillColor(sf::Color(72,72,72));
        PlayerPokemonName[1].setFillColor(sf::Color(72,72,72));
        PlayerPokemonName[0].setPosition(100,465);
        PlayerPokemonName[1].setPosition(370,465);
        PlayerPokemonName[0].setCharacterSize(50);
        PlayerPokemonName[1].setCharacterSize(50);
        PlayerPokemonName[0].setFont(font);
        PlayerPokemonName[1].setFont(font);
        isWin = 0;
        currentPokemon = PlayerPokemonIndices[0];
        currentOpponentPokemon = opponentPokemon[0];
        NameOfPokemon[0].setFillColor(sf::Color(72,72,72));
        NameOfPokemon[1].setFillColor(sf::Color(72,72,72));
        NameOfPokemon[0].setPosition(100,465);
        NameOfPokemon[1].setPosition(370,465);
        NameOfPokemon[0].setCharacterSize(50);
        NameOfPokemon[1].setCharacterSize(50);
        NameOfPokemon[0].setFont(font);
        NameOfPokemon[1].setFont(font);
        Health[0].setFillColor(sf::Color(72,72,72));
        Health[1].setFillColor(sf::Color(72,72,72));
        Health[0].setPosition(100,465);
        Health[1].setPosition(370,465);
        Health[0].setCharacterSize(50);
        Health[1].setCharacterSize(50);
        Health[0].setFont(font);
        Health[1].setFont(font);
        ItemNames[0].setFillColor(sf::Color(72,72,72));
        ItemNames[1].setFillColor(sf::Color(72,72,72));
        ItemNames[0].setPosition(100,465);
        ItemNames[1].setPosition(370,465);
        ItemNames[0].setCharacterSize(50);
        ItemNames[1].setCharacterSize(50);
        ItemNames[0].setFont(font);
        ItemNames[1].setFont(font);
        for(int i = 0; i < 3 ; i++){
                PokemonToHeal[i].setFont(font);
                PokemonToHeal[i].setCharacterSize(50);
                PokemonToHeal[i].setFillColor(sf::Color(72,72,72));
        }
        PokemonToHeal[0].setPosition(30,465);
        PokemonToHeal[1].setPosition(255,465);
        PokemonToHeal[2].setPosition(485,465);
        for(int i = 0; i < 4 ; i++){
            currentPokemonMoveset[i].setFont(font);
            currentPokemonMoveset[i].setCharacterSize(50);
            currentPokemonMoveset[i].setFillColor(sf::Color(72,72,72));
        }
        currentPokemonMoveset[0].setPosition(45,455);
        currentPokemonMoveset[1].setPosition(420,455);
        currentPokemonMoveset[2].setPosition(420,490);
        currentPokemonMoveset[3].setPosition(45,490);
        NameOfPokemon[0].setFillColor(sf::Color(72,72,72));
        NameOfPokemon[1].setFillColor(sf::Color(72,72,72));
        NameOfPokemon[0].setPosition(630,270);
        NameOfPokemon[1].setPosition(100,60);
        NameOfPokemon[0].setCharacterSize(50);
        NameOfPokemon[1].setCharacterSize(50);
        NameOfPokemon[0].setFont(font);
        NameOfPokemon[1].setFont(font);
        Health[0].setFillColor(sf::Color(72,72,72));
        Health[1].setFillColor(sf::Color(72,72,72));
        Health[0].setPosition(740,310);
        Health[1].setPosition(230,100);
        Health[0].setCharacterSize(50);
        Health[1].setCharacterSize(50);
        Health[0].setFont(font);
        Health[1].setFont(font);

        currentPokemon = PlayerPokemonIndices[0];
        chosenItem = 0;
        chosenMove = 0;
        isItemChosen = 0;
        fromFaint = 0;

        if(gender == 0){
            ownTexture.loadFromFile("boySprite.png");
        }
        else if(gender == 1){
            ownTexture.loadFromFile("girlSprite.png");
        }
            ownSprite.setTexture(ownTexture);

        alpha = 0;
        backgroundSprite[currentOpponent].setColor(sf::Color(255, 255, 255, alpha));
        enemySprite[currentOpponent].setColor(sf::Color(255, 255, 255, alpha));
        ownSprite.setColor(sf::Color(255, 255, 255, alpha));
        fadeSpeed = 0.05;

        enemySprite[currentOpponent].setPosition(590,0);
        enemySprite[currentOpponent].setScale(4,4);
        ownSprite.setPosition(100,185);
        ownSprite.setScale(4,4);

        runDone = 0;
        while (window.isOpen() && runDone == 0)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else{
                    handleInput(event);
                }

            }

            update();
            window.clear();

            if(dialogueFlag == 1 && isWin == 0 && alpha == 255){
                animateText(DialogueHolder, CollegeOpponents[currentOpponent].opDialogue, backgroundSprite[currentOpponent], enemySprite[currentOpponent],ownSprite);
                dialogueFlag = 0;
            }
            if(isBattle == false){
                window.draw(backgroundSprite[currentOpponent]);
            }

            if(isBattle == true && battleflag == 0){
                backgroundTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].bg[1]);
                backgroundSprite[currentOpponent].setTexture(backgroundTexture[currentOpponent]);
                window.draw(backgroundSprite[currentOpponent]);
                Battle();
            }

            if(isBattle == true && battleflag == 1){
                backgroundTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].bg[2]);
                backgroundSprite[currentOpponent].setTexture(backgroundTexture[currentOpponent]);
                window.draw(backgroundSprite[currentOpponent]);
                Battle();
            }

            if(isBattle == true && battleflag == 2){
                backgroundTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].bg[3]);
                backgroundSprite[currentOpponent].setTexture(backgroundTexture[currentOpponent]);
                window.draw(backgroundSprite[currentOpponent]);
                Battle();
            }

            if(isBattle == false && isWin != 0){
                backgroundTexture[currentOpponent].loadFromFile(CollegeOpponents[currentOpponent].bg[0]);
                backgroundSprite[currentOpponent].setTexture(backgroundTexture[currentOpponent]);
                window.draw(backgroundSprite[currentOpponent]);
                ownSprite.setScale(4,4);
                enemySprite[currentOpponent].setScale(4,4);
                if (isWin == 1){
                     if(dialogueFlag == 0){
                     music2.stop();
                     music2.openFromFile("./Sounds/winning.ogg");
                     music2.setVolume(50);
                     music2.setLoop(true);
                     music2.play();
                     animateText(DialogueHolder, CollegeOpponents[currentOpponent].LoseDialogue, backgroundSprite[currentOpponent], enemySprite[currentOpponent],ownSprite);
                     dialogueFlag = 1;
                     }

                     if(currentOpponent >= 4){
                        std::ofstream outputFile;
                            outputFile.open("hall-of-fame-database.txt", std::ios::app);

                            if (outputFile.is_open()) {
                                outputFile << playerName << std::endl;
                                outputFile << gender << std::endl;
                                for(int i = 0; i < 3; i++){
                                    outputFile << PlayerPokemonIndices[i] << std::endl;
                                }
                                outputFile.close();
                            } else {
                                std::cout << "Failed to open the file for appending.\n";
                            }
                     }
                }
                else if (isWin == 2){
                    if(dialogueFlag == 0){
                     animateText(DialogueHolder, CollegeOpponents[currentOpponent].WinDialogue, backgroundSprite[currentOpponent], enemySprite[currentOpponent],ownSprite);
                     music2.stop();

                     const std::string filename = "Saved.txt";
                     std::ofstream file(filename, std::ofstream::trunc);
                     file.close();

                     currentPokemon = 0;

                     dialogueFlag = 1;
                     }
                    window.close();
                }
            }

            window.draw(enemySprite[currentOpponent]);
            window.draw(ownSprite);
            window.draw(DialogueHolder);

            window.display();
        }
    }

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture[5];
    sf::Sprite backgroundSprite[5];
    sf::Texture enemyTexture[5];
    sf::Sprite enemySprite[5];
    sf::Texture enemyPokemonTexture[5];
    sf::Sprite enemyPokemonSprite[5];
    sf::Texture PokemonTexture;
    sf::Sprite PokemonSprite;
    sf::Text Choices[3];
    sf::Texture ownTexture;
    sf::Sprite ownSprite;
    sf::Text DialogueHolder;
    sf::Text NameOfPokemon[2];
    sf::Music music2;
    sf::Text Health[2];
    sf::Font font;
    int PlayerPokemons[2];
    sf::Text PlayerPokemonName[2];
    std::string playerName;
    int pokemonToChange;
    int gender;
    float alpha;
    float fadeSpeed;
    bool isBattle;
    int battleflag;
    int action;
    int isWin;
    int currentPokemon;
    int currentOpponentPokemon;
    int chosenItem;
    int isItemChosen;
    int chosenMove;
    int fromFaint = 0;
    int opponentFaint = 0;
    int hasHealed = 0;
    int dialogueFlag;
    sf::Text ItemNames[2];
    sf::Text PokemonToHeal[3];
    sf::Text currentPokemonMoveset[4];
    int runDone = 0;
    sf::Text BackButtonText;
};

class Game2
{
public:
    Game2(sf::RenderWindow& window, std::string playerName, int gender)
        : window(window) , playerName(playerName), gender(gender)
    {allPokemon(listOfPokemon);}

    void handleInput(sf::Event event)
    {
        if(event.type == sf::Event::MouseMoved){
            for(int i = 0; i < 6; i++){
                if(isChosen[i] == 0){
                    if (PokemonSprite[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
                        PokemonSprite[i].setScale(3, 3);
                    }
                    else {
                        PokemonSprite[i].setScale(2.7f, 2.7f);
                    }
                }
            }
        }

        else if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                for(int i = 0; i < 6; i++){
                    if(isChosen[i] == 0 && k < 3){

                        if (PokemonSprite[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                        {
                            PokemonSprite[i].setScale(0,0);
                            PokemonDescriptionSprite[i].setScale(0,0);
                            PokemonName[i].setScale(0,0);
                            PlayerPokemonIndices[k] = PokemonChoicesIndices[i];
                            UsedPokemonIndices[(currentOpponent * 6) + k] = PokemonChoicesIndices[i];
                            UsedPokemonSize++;
                            k++;

                            isChosen[i] = 1;
                        }
                        else{
                            isChosen[i] = 0;
                        }
                        if(k == 3){
                                isTransitioningGame3 = true;
                                music1.stop();
                                runDone = 1;
                        }
                     }
                }
            }
        }
    }

    void initializePokemonIndices()
            {
                std::srand(std::time(0));

                int isFound = 0;
                for (int i = 0; i < 6; ++i) {
                    int randomPokemon;

                    do {
                        randomPokemon = std::rand() % 30;


                        isFound = 0;
                        for (int j = 0; j < UsedPokemonSize; j++) {
                            if (UsedPokemonIndices[j] == randomPokemon) {
                                isFound = 1;
                                break;
                            }
                        }
                        for (int j = 0; j < i; j++) {
                            if (PokemonChoicesIndices[j] == randomPokemon) {
                                isFound = 1;
                                break;
                            }
                        }


                    } while (isFound == 1);

                    PokemonChoicesIndices[i] = randomPokemon;

                }



                for (int i = 0; i < 6; i++) {
                    PokemonTextureSprite[i].loadFromFile(listOfPokemon[PokemonChoicesIndices[i]].FrontSprite);
                    PokemonSprite[i].setTexture(PokemonTextureSprite[i]);
                    PokemonDescriptionTexture[i].loadFromFile("PokemonDescription.png");
                    PokemonDescriptionSprite[i].setTexture(PokemonDescriptionTexture[i]);
                    PokemonName[i].setFont(font);
                    PokemonName[i].setColor(sf::Color(72,72,72));
                    PokemonName[i].setCharacterSize(30);
                    PokemonName[i].setString(listOfPokemon[PokemonChoicesIndices[i]].Name);
                }

                PokemonSprite[0].setPosition(10,60);
                PokemonSprite[0].setScale(2.7f,2.7f);
                PokemonSprite[1].setPosition(320,60);
                PokemonSprite[1].setScale(2.7f,2.7f);
                PokemonSprite[2].setPosition(670,60);
                PokemonSprite[2].setScale(2.7f,2.7f);
                PokemonSprite[3].setPosition(10,300);
                PokemonSprite[3].setScale(2.7f,2.7f);
                PokemonSprite[4].setPosition(320,300);
                PokemonSprite[4].setScale(2.7f,2.7f);
                PokemonSprite[5].setPosition(670,300);
                PokemonSprite[5].setScale(2.7f,2.7f);

                PokemonDescriptionSprite[0].setPosition(190,180);
                PokemonName[0].setPosition(203,195);
                PokemonDescriptionSprite[0].setScale(2.2f,2.2f);
                PokemonDescriptionSprite[1].setPosition(520,180);
                PokemonName[1].setPosition(533,195);
                PokemonDescriptionSprite[1].setScale(2.2f,2.2f);
                PokemonDescriptionSprite[2].setPosition(840,180);
                PokemonName[2].setPosition(853,195);
                PokemonDescriptionSprite[2].setScale(2.2f,2.2f);
                PokemonDescriptionSprite[3].setPosition(190,410);
                PokemonName[3].setPosition(203,425);
                PokemonDescriptionSprite[3].setScale(2.2f,2.2f);
                PokemonDescriptionSprite[4].setPosition(520,410);
                PokemonName[4].setPosition(533,425);
                PokemonDescriptionSprite[4].setScale(2.2f,2.2f);
                PokemonDescriptionSprite[5].setPosition(840,410);
                PokemonName[5].setPosition(853,425);
                PokemonDescriptionSprite[5].setScale(2.2f,2.2f);
            }



    void run()
    {
        music1.openFromFile("./Sounds/selection.ogg");
        music1.setLoop(true);
        music1.setVolume(70);
        music1.play();
        backgroundTexture.loadFromFile("PokemonSelectionBackground.png");
        backgroundSprite.setTexture(backgroundTexture);
        font.loadFromFile("pokemon_fire_red.ttf");
        for (int i = 0; i < 6; i++){
            isChosen[i] = 0;
        }

        k = 0;
        isTransitioningGame3 = false;
        Choose.setFont(font);
        Choose.setString("Choose 3 Pokémon in Order!");
        Choose.setCharacterSize(50);
        Choose.setFillColor(sf::Color(72,72,72));
        Choose.setPosition(312,-5);

        runDone = 0;
        initializePokemonIndices();

        for(int k = 0; k < 6; k++){
                PokemonSprite[k].setScale(2.7f,2.7f);
                PokemonDescriptionSprite[k].setScale(2.2f,2.2f);
                PokemonName[k].setScale(1,1);
        }

        while (window.isOpen() && runDone == 0)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
                else {
                    handleInput(event);
                }
            }

            window.clear();

            window.draw(backgroundSprite);

            for(int i = 0; i < 6; i++){
                window.draw(PokemonSprite[i]);
                window.draw(PokemonDescriptionSprite[i]);
                window.draw(PokemonName[i]);
                }

            window.draw(Choose);
            window.display();
        }
    }


private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture PokemonTextureSprite[6];
    sf::Texture PokemonDescriptionTexture[6];
    sf::Sprite PokemonDescriptionSprite[6];
    sf::Text PokemonName[6];
    sf::Music music1;
    sf::Font font;
    sf::Text Choose;
    sf::Sprite PokemonSprite[6];
    std::string playerName;
    int gender;
    bool isTransitioningGame3;
    int isChosen[6];
    int runDone = 0;
    int k;
};

class Game
{
public:
     Game(sf::RenderWindow& window, std::string playerName, int gender, sf::Music& music)
        : window(window), playerName(playerName), gender(gender), music(music)
    {
        backgroundTexture.loadFromFile("genderselect.png");
        backgroundTexture2.loadFromFile("name.png");
        backgroundSprite2.setTexture(backgroundTexture2);
        boySprite.loadFromFile("Boy.png");
        girlSprite.loadFromFile("Girl.png");
        Boy.setTexture(boySprite);
        Girl.setTexture(girlSprite);
        Girl.setPosition(720,150);
        Boy.setPosition(720,150);
        sparayto.setPosition(720,150);
        backgroundSprite.setTexture(backgroundTexture);
        font.loadFromFile("PKMN RBYGSC.ttf");
        Dialogue.setFont(font);
        Dialogue.setString("");
        Dialogue.setCharacterSize(35);
        Dialogue.setFillColor(sf::Color(72,72,72));
        Dialogue.setPosition(150, 460);
        Dialogue2.setFont(font);
        Dialogue2.setString("");
        Dialogue2.setCharacterSize(35);
        Dialogue2.setFillColor(sf::Color(72,72,72));
        Dialogue2.setPosition(150, 460);
        Gender1.setFont(font);
        Gender1.setString("BOY");
        Gender1.setCharacterSize(35);
        Gender1.setFillColor(sf::Color(72,72,72));
        Gender1.setPosition(130, 135);
        Gender2.setFont(font);
        Gender2.setString("GIRL");
        Gender2.setCharacterSize(35);
        Gender2.setFillColor(sf::Color(72,72,72));
        Gender2.setPosition(130, 185);
        isboySpriteVisible = false;
        isgirlSpriteVisible = false;
        isSelected = false;
        flag = 0;
    }

    void handleInput(sf::Event event)
    {
         if (event.type == sf::Event::MouseMoved)
        {
            // Check if the mouse is hovering over each text
            updateTextColor(Gender1, event.mouseMove.x, event.mouseMove.y);
            updateTextColor(Gender2, event.mouseMove.x, event.mouseMove.y);

            if (!isSelected && Gender1.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                {
                    isboySpriteVisible = true;
                    isgirlSpriteVisible = false;
                }


             if (!isSelected && Gender2.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                {
                    isgirlSpriteVisible = true;
                    isboySpriteVisible = false;

                }


        }

        else if (isSelected && event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128 && event.text.unicode != '\b' && inputText.length() < 5)
            {
                inputText += static_cast<char>(event.text.unicode);
            }
            else if (event.text.unicode == '\b' && !inputText.empty())
            {
                inputText.pop_back();
            }

            TextBox.setString(inputText);
        }

         else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
              if (!isSelected && Gender1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                gender = 0;
                isSelected = true;
                sparayto.setTexture(boySprite);
                flag++;


              }
              if(!isSelected && Gender2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                gender = 1;
                isSelected = true;
                sparayto.setTexture(girlSprite);
                flag++;

              }
            }
            std::cout << gender << std::endl;
        }
        else if(isSelected && event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Enter){
                if(inputText.length() >= 3){
                    playerName = inputText;
                    music.stop();
                    saveDataToFile();
                    runDone = 1;
                }
            }
        }
    }

     void setupTextBox()
    {
        textBoxFont.loadFromFile("PKMN RBYGSC.ttf");

        TextBox.setFont(textBoxFont);
        TextBox.setCharacterSize(35);
        TextBox.setFillColor(sf::Color::Black);
        TextBox.setPosition(135, 155);
    }

        void saveDataToFile() {
        std::ofstream outputFile("Save.txt", std::ios::trunc);
        if (outputFile.is_open()) {
            outputFile << playerName << std::endl;
            outputFile << gender << std::endl;
            std::cout << playerName << std::endl;
            outputFile.close();
            std::cout << "Data saved to file." << std::endl;
        } else {
            std::cerr << "Failed to open the file." << std::endl;
        }
    }

     void updateTextColor(sf::Text& text, int mouseX, int mouseY)
    {
        if (text.getGlobalBounds().contains(mouseX, mouseY))
        {
            text.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(72, 72, 72));
        }
    }

     void animateText(sf::Text& text, const std::string& content, sf::Sprite& background, sf::Sprite sparayto)
        {
    std::string animatedText;
    for (std::size_t i = 0; i < content.length(); ++i)
    {
        // Append one character at a time to the animated text
        animatedText += content[i];

        // Assign the animated text to the sf::Text object
        text.setString(animatedText);

        // Delay between each character to simulate typing effect
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Clear the window and redraw the updated background and text
        window.clear();
        window.draw(background);
        window.draw(sparayto);
        window.draw(text);
        window.display();
    }
        }


   void display(){
        std::string convo = "Are you a boy? \nOr are you a girl?";
        animateText(Dialogue, convo , backgroundSprite, sparayto);
        setupTextBox();
        runDone = 0;

        while (window.isOpen() && runDone == 0)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                handleInput(event);
            }

            window.clear();

            if (!isSelected)
            {
                window.draw(backgroundSprite);
                window.draw(Gender1);
                window.draw(Dialogue);
                window.draw(Gender2);
            }

            if (isboySpriteVisible)
            {
                window.draw(Boy);
            }
            if (isgirlSpriteVisible)
            {
                window.draw(Girl);
            }

            if (isSelected)
            {
                window.draw(backgroundSprite2);

            if (flag == 1)
            {
                animateText(Dialogue2, "What is your name?", backgroundSprite2,sparayto);
                flag++;
            }
            if (isboySpriteVisible)
            {
                window.draw(Boy);


            }
            if (isgirlSpriteVisible)
            {
                window.draw(Girl);
            }
                window.draw(Dialogue2);
                window.draw(TextBox);
            }

            window.display();
        }
}

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture2;
    sf::Sprite backgroundSprite2;
    sf::Sprite sparayto;
    sf::Texture boySprite;
    sf::Texture girlSprite;
    sf::Music& music;
    sf::Sprite Boy;
    sf::Sprite Girl;
    sf::Font font;
    sf::Text Dialogue;
    sf::Text Dialogue2;
    sf::Text Gender1;
    sf::Text Gender2;
    sf::Text TextBox;
    sf::Font textBoxFont;
    std::string inputText;
    std::string playerName;
    int gender;
    bool isboySpriteVisible;
    bool isgirlSpriteVisible;
    int runDone = 0;
    bool isSelected;
    int flag;
    Pokemon listOfPokemon[30];
};


struct PlayerData {
    std::string playerName;
    int genderNumber;
    int usedPokemon[3];
};

class HallOfFame
{
public:
     HallOfFame(sf::RenderWindow& window, sf::Music& music, int currentIndex)
        : window(window), music(music), currentIndex(currentIndex)
    {
        currentIndex = 0;
        backgroundTexture.loadFromFile("menu.png");
        backgroundSprite.setTexture(backgroundTexture);
        boySprite.loadFromFile("Boy.png");
        girlSprite.loadFromFile("Girl.png");
        Boy.setTexture(boySprite);
        Girl.setTexture(girlSprite);
        Girl.setPosition(760,130);
        Boy.setPosition(760,130);

        font.loadFromFile("PKMN RBYGSC.ttf");

        playerName.setFont(font);
        playerName.setString("PLAYER NAME");       /*playerName*/
        playerName.setCharacterSize(30);
        playerName.setFillColor(sf::Color::Blue);
        playerName.setPosition(100, 133);

        gender.setFont(font);
        gender.setString("GENDER");           /*playerGender*/
        gender.setCharacterSize(30);
        gender.setFillColor(sf::Color(72, 72, 72));
        gender.setPosition(100, 185);

        next.setFont(font);
        next.setString("NEXT");
        next.setCharacterSize(20);
        next.setFillColor(sf::Color::Blue);
        next.setPosition(100, 450);

        exit.setFont(font);
        exit.setString("BACK");
        exit.setCharacterSize(20);
        exit.setFillColor(sf::Color::Blue);
        exit.setPosition(100, 500);

        pkmn1.setPosition(50, 180);
        pkmn2.setPosition(275, 180);
        pkmn3.setPosition(500, 180);
        pkmn1.setScale(2.7f, 2.7f);
        pkmn2.setScale(2.7f, 2.7f);
        pkmn3.setScale(2.7f, 2.7f);
    }

    std::vector<PlayerData> players;
    int numberOfPlayers;

    void readFromHOFFile() {
            std::ifstream inputFile;
            std::string fileName = "hall-of-fame-database.txt";
            inputFile.open(fileName);
            if (inputFile.fail())
            {
                std::cout << "File not opened." << std::endl;
            }

            int currentLine = 0;

            while (!inputFile.eof())
            {
                PlayerData player;

                currentLine++;
                inputFile >> player.playerName;

                currentLine++;
                inputFile >> player.genderNumber;

                for (int i = 0; i < 3; i++) {
                    currentLine++;
                    inputFile >> player.usedPokemon[i];
                }

                players.push_back(player);
            }

            numberOfPlayers = currentLine / 5;
        }

    void updateTextColor(sf::Text& text, int mouseX, int mouseY)
    {
        if (text.getGlobalBounds().contains(mouseX, mouseY))
        {
            text.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(4, 136, 162));
        }
    }

    void handleInput(sf::Event event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            updateTextColor(next, event.mouseMove.x, event.mouseMove.y);
            updateTextColor(exit, event.mouseMove.x, event.mouseMove.y);
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (currentIndex < numberOfPlayers-1 && next.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                      currentIndex++;
                }
                else if (exit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    hofmusic.stop();
                    music.play();
                    runDone = 1;
                }
            }
        }
    }


    void display()
    {
        if(currentIndex == 0){
        hofmusic.openFromFile("./Sounds/hof.ogg");
        hofmusic.setVolume(70);
        hofmusic.setLoop(true);
        hofmusic.play();
        }

        std::cout << currentIndex ;


        readFromHOFFile();

        while (window.isOpen() && runDone == 0)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                handleInput(event);
            }

            window.clear();
            window.draw(backgroundSprite);

            if (numberOfPlayers != 0){
                playerName.setString(players[currentIndex].playerName);
            }

            window.draw(playerName);

            if (numberOfPlayers == 0){
                window.draw(gender);
            }
            else{
                if (players[currentIndex].genderNumber == 0){
                    window.draw(Boy);
                }
                else if (players[currentIndex].genderNumber == 1){
                    window.draw(Girl);
                }

                pkmn1texture.loadFromFile(listOfPokemon[players[currentIndex].usedPokemon[0]].FrontSprite);
                pkmn2texture.loadFromFile(listOfPokemon[players[currentIndex].usedPokemon[1]].FrontSprite);
                pkmn3texture.loadFromFile(listOfPokemon[players[currentIndex].usedPokemon[2]].FrontSprite);
                pkmn1.setTexture(pkmn1texture);
                pkmn2.setTexture(pkmn2texture);
                pkmn3.setTexture(pkmn3texture);
            }

            window.draw(pkmn1);
            window.draw(pkmn2);
            window.draw(pkmn3);
            window.draw(next);
            window.draw(exit);

            window.display();
        }
    }

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture boySprite;
    sf::Texture girlSprite;
    sf::Texture pkmn1texture;
    sf::Music hofmusic;
    sf::Texture pkmn2texture;
    sf::Texture pkmn3texture;
    sf::Sprite Boy;
    sf::Sprite Girl;
    sf::Sprite pkmn1;
    sf::Sprite pkmn2;
    sf::Sprite pkmn3;
    sf::Font font;
    sf::Text playerName;
    sf::Text gender;
    sf::Text pokemonused;
    sf::Text next;
    sf::Text exit;
    sf::Music& music;
    std::string nameOfPlayer;
    int index;
    int runDone;
    int currentIndex;
};

class StartingMenu
{
public:
     StartingMenu(sf::RenderWindow& window, sf::Music& music)
        : window(window), music(music)
    {
        backgroundTexture.loadFromFile("menu.png");
        backgroundSprite.setTexture(backgroundTexture);
        alpha = 1;
        backgroundSprite.setColor(sf::Color(255, 255, 255, alpha));
        fadeSpeed = 0.5;
        font.loadFromFile("PKMN RBYGSC.ttf");
        NewGame.setFont(font);
        NewGame.setString("NEW GAME");
        NewGame.setCharacterSize(30);
        NewGame.setFillColor(sf::Color(72,72,72));
        NewGame.setPosition(100, 133);
        Continue.setFont(font);
        Continue.setString("CONTINUE");
        Continue.setCharacterSize(30);
        Continue.setFillColor(sf::Color(72,72,72));
        Continue.setPosition(100, 185);
        HallofFame.setFont(font);
        HallofFame.setString("HALL OF FAME");
        HallofFame.setCharacterSize(30);
        HallofFame.setFillColor(sf::Color(72,72,72));
        HallofFame.setPosition(100, 235);
        Exit.setFont(font);
        Exit.setString("EXIT");
        Exit.setCharacterSize(30);
        Exit.setFillColor(sf::Color(72,72,72));
        Exit.setPosition(100, 287);
    }

    void update()
    {
        if (alpha < 255)
        {
            alpha += fadeSpeed;
            if (alpha > 255)
                alpha = 255;
            backgroundSprite.setColor(sf::Color(255, 255, 255, alpha));
        }
    }

    int handleInput(sf::Event event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            updateTextColor(NewGame, event.mouseMove.x, event.mouseMove.y);
            updateTextColor(Continue, event.mouseMove.x, event.mouseMove.y);
            updateTextColor(HallofFame, event.mouseMove.x, event.mouseMove.y);
            updateTextColor(Exit, event.mouseMove.x, event.mouseMove.y);
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
              if (NewGame.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {

                    window.setActive(false);
                    return 1;
                    window.setActive(true);
                }
              else if (Continue.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.stop();
                    window.setActive(false);
                    return 2;
                    window.setActive(true);
                }
                else if (HallofFame.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.stop();
                    window.setActive(false);
                    int currentOpponent = 0;
                    HallOfFame hallOfFame(window, music, currentOpponent);
                    hallOfFame.display();
                    window.setActive(true);
                }

            }
        }
        return 0;
    }

    void updateTextColor(sf::Text& text, int mouseX, int mouseY)
    {
        if (text.getGlobalBounds().contains(mouseX, mouseY))
        {
            text.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(72, 72, 72));
        }
    }

    int display()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else {
                    menuChoice = handleInput(event);
                }
            }

            if (menuChoice != 0)
                break;

            update();
            window.clear();
            window.draw(backgroundSprite);
            if(alpha == 255){
                window.draw(NewGame);
                window.draw(Continue);
                window.draw(HallofFame);
                window.draw(Exit);
            }
            window.display();
        }

        return menuChoice;
    }

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text NewGame;
    sf::Text Continue;
    sf::Text HallofFame;
    sf::Text Exit;
    sf::Music& music;
    Pokemon listOfPokemon[30];
    int menuChoice = 0;
    float alpha;
    float fadeSpeed;
};

class TitleScreen
{
public:
    TitleScreen(sf::RenderWindow& window, sf::Music& music)
        : window(window), music(music)
    {
        texture.loadFromFile("titlescreen.png");
        sprite.setTexture(texture);
        font.loadFromFile("zektondo.ttf");
        text.setFont(font);
        text.setString("PRESS START");
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        text.setPosition(200, 350);
        flickerTime = sf::Time::Zero;
        flickerDuration = sf::seconds(0.6f);
        isTextVisible = true;
    }

     void handleInput(sf::Event event)
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
        {
            window.setActive(false);
            runDone = 1;
            window.setActive(true);
        }
    }

    void updateFlicker(sf::Time deltaTime)
    {
        flickerTime += deltaTime;

        if (flickerTime >= flickerDuration)
        {
            isTextVisible = !isTextVisible;
            flickerTime = sf::Time::Zero;
        }
    }

     void display()
    {
        sf::Clock clock;

        while (window.isOpen() && runDone == 0)
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                handleInput(event);
                if (event.type == sf::Event::Closed)
                    window.close();

            }

            sf::Time deltaTime = clock.restart();

            updateFlicker(deltaTime);

            window.clear();

            window.draw(sprite);

            if (isTextVisible)
                window.draw(text);

            window.display();
        }
    }

private:
    sf::RenderWindow& window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
    sf::Time flickerTime;
    sf::Time flickerDuration;
    bool isTextVisible;
    sf::Music& music;
    Pokemon listOfPokemon[30];
    int runDone = 0;
};

class maingame {
    private:
        sf::RenderWindow& window;
        sf::Music& music;
        std::string playerName;
        int gender;
        int menuChoice = 0;

        TitleScreen titleScreen;
        StartingMenu startingMenu;
        Game characterID;
        Game2 pokemonSelection;
        Game3 gamebattle;

    public:
        maingame(sf::RenderWindow& window, sf::Music& music) :
            window(window),
            music(music),
            titleScreen(window, music),
            startingMenu(window, music),
            characterID(window, playerName, gender,music),
            pokemonSelection(window, playerName, gender),
            gamebattle(window,playerName,gender) {}

        void loadFile(std::string filename,
                      std::string& playerName,
                      int& gender,
                      int usedPokemonIndices[],
                      int& usedPokemonSize,
                      int& currentOpponent) {

            std::ifstream inputFile(filename);

            if (inputFile.is_open()) {
                getline(inputFile, playerName);
                inputFile >> gender;
                inputFile >> usedPokemonSize;
                inputFile >> currentOpponent;
                currentOpponent++;

                for(int i = 0; i < usedPokemonSize; i++){
                    inputFile >> usedPokemonIndices[i];
                }

                inputFile.close();
            } else {
                std::cout << "Failed to open file: " << filename << std::endl;
            }
        }

        void display() {
            titleScreen.display();
            menuChoice = startingMenu.display();
            if (menuChoice == 1){
                characterID.display();
            }
            if (menuChoice == 2){
                loadFile("Save.txt", playerName, gender, UsedPokemonIndices, UsedPokemonSize, currentOpponent);
            }

            while(currentOpponent < 5){
                pokemonSelection.run();
                gamebattle.run();
            }
        }
};


int main()
{

    int UsedPokemonIndices[30];
    int PokemonChoicesIndices[6];
    int PlayerPokemonIndices[3];
    Pokemon listOfPokemon[30];
    allPokemon(listOfPokemon);
    CollegeOpponents[0] = defineOpponent(65,
                                    "COS REP. TONA",
                                    "./Trainers-Sprite/COS.png",
                                    "COS REP. TONA: There's a limit to how far I could get studying by myself, so I \nstarted taking battle lessons.",
                                    "COS REP. TONA: It seems that my studies have paid off. Could this be my actual \nability level?",
                                    "COS REP. TONA: All I learn in my lessons is the conventional way of battling, \nwhich doesn't seem useful in actual battles.",
                                    "./battlebg/adminfield_1.png",
                                    "./battlebg/adminfield_2.png",
                                    "./battlebg/adminfield_3.png",
                                    "./battlebg/adminfield_4.png"
                                    );
    CollegeOpponents[1] = defineOpponent(50,
                                    "CCAD REP. RINA",
                                    "./Trainers-Sprite/CCAD.png",
                                    "CCAD REP. RINA: My paintbrush is made of secret materials.",
                                    "CCAD REP. RINA: I'll do a sketch of you as you are now frustrated by failure. \nPlease hold still.",
                                    "CCAD REP. RINA: Hmmph... I won't tell you the secret of my paintbrush.",
                                    "./battlebg/joya_1.png",
                                    "./battlebg/joya_2.png",
                                    "./battlebg/joya_3.png",
                                    "./battlebg/joya_4.png"
                                );
    CollegeOpponents[2] = defineOpponent(40,
                                    "CSS REP. JOMAR",
                                    "./Trainers-Sprite/CSS.png",
                                    "CSS REP. JOMAR: I've studied the intricate dynamics of society. Prepare to \nface the power of social analysis!",
                                    "CSS REP. JOMAR: Behold! The forces of society were laid bare in our battle. \nIt's a fascinating case study!",
                                    "CSS REP. JOMAR: Hmm, this outcome calls for further research. I'll need to \nanalyze our battle from a different perspective.",
                                    "./battlebg/asx_1.png",
                                    "./battlebg/asx_2.png",
                                    "./battlebg/asx_3.png",
                                    "./battlebg/asx_4.png"
                                    );
    CollegeOpponents[3] = defineOpponent(30,
                                    "SOM REP. VENN",
                                    "./Trainers-Sprite/SOM.png",
                                    "SOM REP. VENN: Huehuehue... if it's cash you want, I've got some. How about \nyou go and lose this battle for me?",
                                    "SOM REP. VENN: I may have said I had cash, but I haven't said anything about \ngiving you any!",
                                    "SOM REP. VENN: I couldn't fool you, could I? You do quite well, don't you?",
                                    "./battlebg/bball_1.png",
                                    "./battlebg/bball_2.png",
                                    "./battlebg/bball_3.png",
                                    "./battlebg/bball_4.png"
                                    );
    CollegeOpponents[4] = defineOpponent(18,
                                    "CHANCELLOR MAGALAR",
                                    "./Trainers-Sprite/CHANCY.png",
                                    "CHANCELLOR MAGALAR: You've come this far, but I won't back down either!",
                                    "CHANCELLOR MAGALAR: Your training and experiences were not in vain. Still, I \nrecommend you train harder. I will be waiting for your return.",
                                    "CHANCELLOR MAGALAR: Excellent. I knew you had the potential from the start.",
                                    "./battlebg/oble_1.png",
                                    "./battlebg/oble_2.png",
                                    "./battlebg/oble_3.png",
                                    "./battlebg/oble_4.png"
                                    );
    ListOfItems[0] = {"Revive", 5};
    ListOfItems[1] = {"Hyper Potion", 5};
    sf::RenderWindow app(sf::VideoMode(1024, 576), "UPokemon");
    sf::Music music;
    music.openFromFile("backgroundmusic.flac");
    music.setLoop(true);
    music.play();
    maingame maingame1(app, music);
    maingame1.display();


    return EXIT_SUCCESS;
}
