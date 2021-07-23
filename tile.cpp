
#include "tile.h"

position tile::get_pos() const {return pos;}

void tile::set_pos(const position &other) {this->pos = other;}


power::power() {
    used = false;
    pos = position(0, 0);
}

bool power::is_used() const {return used;}

void power::set_used(const bool &b) {used = b;}