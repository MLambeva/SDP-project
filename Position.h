#ifndef POSITION_H
#define POSITION_H
#include<iostream>
#include<fstream>
#include<exception>

struct Position
{
    int x;
    int y;

    Position() = default;

    Position north()const;
    Position south()const;
    Position east()const;
    Position west()const;  

    bool operator==(const Position& other) const;
    Position& operator=(const Position& other);
    Position& changePos(int _x, int _y);

    void read(std::ifstream& input);
};

#endif
