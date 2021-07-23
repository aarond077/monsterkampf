
#include "enemy.h"
#include <random>

enemy::enemy() {
    pos = position(0, 0);
    mons = monster();
}

position enemy::get_pos() const {return pos;}

monster enemy::get_mons() const {return mons;}

void enemy::set_pos(const position &p) {pos = p;}

bool enemy::is_beaten() const {return beaten;}

void enemy::set_beaten(const bool &b) {beaten = b;}

void enemy::set_mons_curr_LP(const unsigned int &val) {
    mons.set_current_LP(val);
}

void enemy::monster_got_hit(const unsigned &val) {
    mons.subtract_currentLP(val);
}

void enemy::set_mons(const monster &other) {mons = other;}

const enemy& enemy::operator=(const enemy &other) {
    pos = other.pos;
    mons = other.get_mons();
    return other;

}

leader::leader(){
    pos = position(0, 0);
    mons = monster("FelsenKugel");
    last_monster = false;
}


void leader::next_monster() {
    mons = monster("SteinWurm");
}

bool leader::is_last_monster() const {return last_monster;}

void leader::set_last_monster(const bool &b) {last_monster = b;}


