

#include "position.h"
#include <cmath>

position::position() {
    this->set_x(0);
    this->set_y(0);
}

position::position(int x, int y) {
    this->set_x(x);
    this->set_y(y);
}

int position::get_y() const {
    return this->y;
}

int position::get_x() const {
    return this->x;
}

void position::set_y(const int &y) {
    this->y = y;
}

void position::set_x(const int &x) {
    this->x = x;
}

void position::swap(const position &other) {
    this->set_x(other.get_x());
    this->set_y(other.get_y());
}

const position& position::operator=(const position &other) {
    this->set_x(other.get_x());
    this->set_y(other.get_y());
    return other;
}

const bool position::operator==(const position &other) const {
    if((this->get_x() == other.get_x()) && (this->get_y() == other.get_y())){return true;}
    else{return false;}
}

const bool position::operator!=(const position &other) const {
    if((this->get_x() != other.get_x()) || (this->get_y() != other.get_y())){return true;}
    else{return false;}
}

position position::calc_vec(const position &b) {
    position p = position(b.get_x() - this->get_x(), b.get_y() - this->get_y());
    return p;
}

uint64_t position::length() {
    uint64_t res = 0;
    res += ((this->get_x() * this->get_x()) + (this->get_y() * this->get_y()));
    res >> 2;
    return res;} //a² + b² = c²