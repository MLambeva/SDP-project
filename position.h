#ifndef COORDINATES_H
#define COORDINATES_H
#include<iostream>
#include<fstream>

struct Position
{
    int x;
    int y;

    Position() = default;

    Position north()const;
    Position south()const;
    Position east()const;
    Position west()const;  

    bool operator==(const Position& other);
    bool operator!=(const Position& other);

    void read(std::ifstream& input);

};

#endif
