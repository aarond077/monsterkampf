

#ifndef MONSTERKAMPF_PLAYER_H
#define MONSTERKAMPF_PLAYER_H
#include "monster.h"
#include "position.h"
#include <vector>

class player {
private:
    QString sym = QString::fromUtf8("\xF0\x9F\x98\x83"); //players symbol
    std::vector<monster*> team; //players monsters
    uint64_t direction; //direction for movement
    position pos; //position for movement
    std::vector<position> last; //puffer vector for clearing the last tile the player was on

public:
    //constructor
    player();
    player(position &p);
    //deconstructor
    ~player();

    //getter/setter methods
    std::vector<monster*> get_team() const;
    QString get_sym() const;
    uint64_t get_direction() const;
    position get_pos() const;
    std::vector<position> get_last() const;
    void set_direction(const uint64_t &direc);
    void set_pos(const position &other);

    //player changes position
    void move(position &p);
    //clears vector "last"
    void clear_vec();
    //appends "team" using push_back
    void append_team(monster *m);
    //gives back index of monster in team
    unsigned & find_monster(const std::string& str) const;
    //overrides data on certain index in team
    void update_team(const unsigned &index, monster *m);
    //AP += 1
    void add_active_mons_AP();
    //heals the active monster (-> monster.h -> heal())
    void heal_active_monster();
    //clears team vector if there is a reset
    void clear_team();


};


#endif //MONSTERKAMPF_PLAYER_H
