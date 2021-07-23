

#ifndef MONSTERKAMPF_ENEMY_H
#define MONSTERKAMPF_ENEMY_H
#include "monster.h"
#include "position.h"

class enemy { //enemy class
protected:
    monster mons; //every enemy has 1 monster
    monster snd_mons; //only access for rocko;
    position pos;
    bool beaten = false;
public:
    //constructor
    enemy();
    //deconstructor is empty because enemy has no pointers
    ~enemy(){}

    //getter/setter functions
    monster get_mons() const;
    position get_pos() const;
    bool is_beaten() const;
    void set_beaten(const bool &b);
    void set_mons(const monster &other);
    void set_mons_curr_LP(const unsigned &val);
    void set_pos(const position&p);

    //decreases enemys monsters LP
    void monster_got_hit(const unsigned &val);

    //operator
    const enemy& operator=(const enemy &other);
};


//status quo: Not implemented yet
class leader : public enemy{
    bool last_monster;
public:
    leader();
    ~leader(){}
    bool is_last_monster() const;
    void set_last_monster(const bool &b);

    void next_monster(); // exception of 1 monster rule: leader can "create" a new monster out of nothing so he can have multiple monsters
};


#endif //MONSTERKAMPF_ENEMY_H
