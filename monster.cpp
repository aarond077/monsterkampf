
#include "monster.h"


unsigned monster::get_AP() const {return AP;}

int monster::get_currentLP() const {return current_LP;}

unsigned monster::get_maxLP() const {return max_LP;}

std::string monster::get_name() const {return name;}

void monster::subtract_currentLP(const uint32_t &val) {
    int x = current_LP - val; //x = compare value
    if (x < 0) {        //LP cant be negative
        set_current_LP(0);
    }
    else{current_LP -= val;} //else subtract normally
}

void monster::set_current_LP(const unsigned int &val) { current_LP = val;}

void monster::add_AP() {++AP;}

void monster::heal_LP() {
    unsigned x = current_LP + (max_LP / 2);
    if(x > max_LP){current_LP = max_LP;}
    else{current_LP += (max_LP / 2);}
}

const monster& monster::operator=(const monster &other) {
    AP = other.get_AP();
    current_LP = other.current_LP;
    max_LP = other.max_LP;
    name = other.name;
    return other;
}

monster::monster() {
    name = ' ';
    AP = 0;
    current_LP = 0;
    max_LP = 0;
}

monster::monster(std::string str) {
    if(str == "FeuerEchse"){
        name = str;
        AP = 5;
        current_LP = 20;
        max_LP = 20;
    }
    else if(str == "DonnerRatte"){
        name = str;
        max_LP = 16;
        current_LP = 16;
        AP = 5;
    }
    else if (str == "BaumBaum"){
        name = str;
        max_LP = 7;
        current_LP = 7;
        AP = 5;
    }
    else if (str == "WasserKroete"){
        name = str;
        max_LP = 10;
        current_LP = 10;
        AP = 3;
    }
    else if (str == "SuperTaube"){
        name = str;
        max_LP = 10;
        current_LP = 10;
        AP = 3;
    }
    else if (str == "SteinWurm"){
        name = str;
        max_LP = 35;
        current_LP = 30;
        AP = 7;
    }
    else if(str == "FelsenKugel"){
        name = str;
        max_LP = 25;
        current_LP = 25;
        AP = 4;
    }
}

void monster::add_max_LP() {max_LP += 5;}
