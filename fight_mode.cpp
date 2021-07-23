
#include "fight_mode.h"

fight_mode::~fight_mode() {}

fight_mode::fight_mode() {
    opponent = enemy();
    healed = false;
}

enemy  fight_mode::get_opponent() const {return opponent;}

bool  fight_mode::is_healed() const {return healed;}

void fight_mode::set_heal(const bool &b) {healed = b;}

void fight_mode::set_opponent(const enemy &other) {opponent = other;}

void fight_mode::opponent_mons_got_hit(const unsigned int &val) {
    opponent.monster_got_hit(val);
}

void fight_mode::set_opponent_mons_LP(const unsigned int &val) {
    opponent.set_mons_curr_LP(val);
}