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

    void read(std::ifstream& input);
};

#endif
