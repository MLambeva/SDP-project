#include"position.h"

Position Position::north() const
{
    return Position{x-1, y};
}

Position Position::south() const
{
    return Position{x+1, y};
}

Position Position::east() const
{
    return Position{x, y+1};
}

Position Position::west() const
{
    return Position{x, y-1};
}  

bool Position::operator==(const Position& other) const
{
    return x == other.x && y == other.y;
}

Position& Position::operator=(const Position& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

void Position::read(std::ifstream& input)
{    
    if (input.fail())
    {
	    std::cout << "Error!\n";
    }
    input >> x;
    input >> y;
}
