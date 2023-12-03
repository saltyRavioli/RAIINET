#ifndef __SCAN_H__
#define __SCAN_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class Scan : public Ability {
    Link *link;
    
    public:
        Scan(int id, Player *player);
        void setLink(Link *l);
        void useAbility() override; 
};

#endif