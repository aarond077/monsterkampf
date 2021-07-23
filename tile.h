//
// Created by Aaron Diether on 21.07.2021.
//

#ifndef MONSTERKAMPF_TILE_H
#define MONSTERKAMPF_TILE_H
#include "position.h"

class tile { //tile class (not that important because i did some change in the game structure)
protected:
    position pos;
public:
    position get_pos() const;
    void set_pos(const position&other);
};


class power : public tile{ //muscle symbol on the map
private:
    bool used;
public:
    power();
    bool is_used() const;
    void set_used(const bool &b);
};



#endif //MONSTERKAMPF_TILE_H
