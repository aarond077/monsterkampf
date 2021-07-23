

#include "player.h"

player::~player() {
    for(auto i : team){
        delete i;
    }
}

player::player() {
    sym = QString::fromUtf8("\xF0\x9F\x98\x83");
    direction = 0;
    team.push_back(new monster("FeuerEchse"));
}

player::player(position &p) {
    this->pos = pos;
    sym = QString::fromUtf8("\xF0\x9F\x98\x83");
    direction = 0;
}

QString player::get_sym() const {return sym;}

std::vector<monster *> player::get_team() const {return team;}

std::vector<position> player::get_last() const {return last;}

uint64_t player::get_direction() const {return direction;}

position player::get_pos() const {return pos;}

void player::set_direction(const uint64_t &direc) {this->direction = direc;}

void player::set_pos(const position &other) {pos = other;}

void player::move(position &p) {this->last.push_back(this->pos); this->pos = p;}

void player::clear_vec() {this->last.clear();}

void player::append_team(monster *m) {this->team.push_back(m);}


//unsigned int & player::find_monster(const std::string& str) const {for(unsigned i = 0; i < team.size(); ++i){team[i]->get_name() == str? i : -1;}}

void player::update_team(const unsigned int &index, monster *m) {
    team[index] = m;
}

void player::add_active_mons_AP() {team[0]->add_AP();}

void player::heal_active_monster() {team[0]->heal_LP();}

void player::clear_team() {team.clear();}