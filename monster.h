

#ifndef MONSTERKAMPF_MONSTER_H
#define MONSTERKAMPF_MONSTER_H

#include <QString>


class monster {
protected:
    std::string name; //name
    unsigned max_LP; //maximum LP
    int current_LP; //current LP
    unsigned AP; //Attack Points
    std::string type; //type: not implemented yet
public:
    //constructor
    monster();
    monster(std::string str);

    //deconstructor is empty
    ~monster() {}

    //getter/setter methods
    std::string get_name() const;

    std::string get_type() const;

    unsigned get_maxLP() const;

    int get_currentLP() const;

    unsigned get_AP() const;

    void set_current_LP(const unsigned &val);

    //subtracts the LP of the monster, if its below zero it will change to zero
    void subtract_currentLP(const uint32_t &val);

    void add_max_LP();

    void add_AP();

    //heals the LP of the monster (adds Max_LP/2 to the current_LP, cant go over max_LP value)
    void heal_LP();

    const monster &operator=(const monster &other);


};


#endif //MONSTERKAMPF_MONSTER_H