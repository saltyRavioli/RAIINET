#include <iostream>
#include "Link.h"
#include "Point.h"
using namespace std;

Link::Link(char id, Point p, char type, int strength) : id{id}, p{p}, type{type}, strength{strength}, isRevealed{false} {}

Link::~Link() {}

char Link::getType() {
    return type;
}

char Link::getId() {
    return id;
}

int Link::getStrength() {
    return strength;
}

Player* Link::getPlayer() {
    return player;
}

Point Link::getPoint() {
    return p;
}

void Link::move(Point dir) {
    p = p + dir;
}

bool Link::battle(Link *other) { // true if this link wins
    if (other->getStrength() > strength)
    {
        return false;
    }
    return true; // in case of tie, you still win
}

void Link::reveal() {
    isRevealed = true;
}

ostream &operator<<(ostream &out, const Link &l) {
    out << l.id << ": " << l.type << l.strength;
    return out;
}
