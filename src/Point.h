#ifndef __POINT_H__
#define __POINT_H__
#include <string>
using namespace std;

struct Point{
    int y, x;

    Point operator +(Point other) {
        return Point{y+other.y, x+other.x};
    }

    Point operator *(int other) {
        return Point{y*other, x*other};
    }

    bool operator ==(Point other) {
        return (y==other.y) && (x==other.x);
    }
    
    bool outOfBounds(Point up, Point right, Point botLeft) {
        // TO DO: also doesn't work for players 3 and 4
        //          they have their x and y swapped essentially
        int y = botLeft.y * up.y;
        int x = botLeft.x * right.x;
        if (x < botLeft.x * right.x || 
            x > (7-botLeft.x)*right.x || 
            y < botLeft.y * up.y) {
            return true;
        }
        return false;
    }

    bool inDownloadZone(Point up, Point right, Point botLeft){
        // TO DO: also doesn't work for players 3 and 4
        //          they have their x and y swapped essentially
        int y = botLeft.y * up.y;
        int x = botLeft.x * right.x;
        if (y > (7-botLeft.y) * up.y) {
            return true;
        }
        return false;
    }

    static Point translate(string dir) {
        if (dir == "up") {
            return Point{1, 0};
        }
        else if (dir == "right") {
            return Point{0, 1};
        }
        else if (dir == "down") {
            return Point{-1, 0};
        }
        else if (dir == "left") {
            return Point{0, -1};
        }
    }

    friend ostream &operator<<(ostream &out, const Point &p) {
        out << "(" << p.y << ", " << p.x << ")";
        return out;
    }
};

#endif
