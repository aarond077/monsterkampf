
#ifndef EISBLATT7_CAR_SIM_POSITION_H
#define EISBLATT7_CAR_SIM_POSITION_H

#include <cstdint>


class position { //source: my own movement_simulation (wurde nicht hochgeladen) (or Übungsblatt 05, pair class umgeschrieben)
    int x;
    int y;
public:
    position();
    position(int x, int y);

    int get_x() const;
    int get_y() const;
    void set_x(const int &x);
    void set_y(const int &y);

    void swap(const position &other);

    const position& operator=(const position &other);
    const bool operator==(const position &other) const;
    const bool operator!=(const position &other) const;
    position calc_vec(const position &b);
    uint64_t length();

};

class vec : public position{};


#endif //EISBLATT7_CAR_SIM_POSITION_H
