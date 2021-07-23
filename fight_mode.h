
#ifndef MONSTERKAMPF_FIGHT_MODE_H
#define MONSTERKAMPF_FIGHT_MODE_H
#include "enemy.h"


class fight_mode { //environment for the fight mode
private:
    enemy opponent; //certain enemy which is the opponent
    bool healed = false; //you can only heal once in one fight
public:
    //constructor
    fight_mode();
    //deconstructor is empty
    ~fight_mode();
    //getter/setter functions
    enemy get_opponent() const;
    bool is_healed() const;
    void set_heal(const bool &b);
    void set_opponent(const enemy &other);
    void set_opponent_mons_LP(const unsigned &val);

    //decreases LP
    void opponent_mons_got_hit(const unsigned &val);
};


#endif //MONSTERKAMPF_FIGHT_MODE_H
