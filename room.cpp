#include"room.h"
#include<stack>

Room::Room(){}

std::vector<std::vector<char>> Room::getRoom() const
{
    return this->room;
}

Position Room::getJerry() const
{
    return this->Jerry;
}

Position Room::getTom() const
{
    return this->Tom;
}

std::vector<std::string> Room::getPossiblePaths() const
{
    return this->possiblePaths;
}

void Room::resizeRoom(std::ifstream& input)
{
    int width;
    input>>width;

    int length;
    input>>length;

    this->room.resize(length, std::vector<char>(width));
    
    for (int i = 0; i < this->room.size(); i++)
    {
        for (int j = 0; j < this->room[i].size(); j++)
        {
            this->room[i][j] = '0';
        }    
    }
}

void Room::putJerryPosition(std::ifstream& input)
{
    Jerry.read(input);
    room[Jerry.x][Jerry.y] = 'F';
}

void Room::putTomPosition(std::ifstream& input)
{
    Tom.read(input);
    room[Tom.x][Tom.y] = 'S';
}

void Room::putFurniture(int K, std::ifstream& input)
{
    for(int i = 0; i < K; i++)
    {
        Position furn;
        furn.read(input);
        input.get();
        int x = furn.x;
        int y = furn.y;
        char elem = input.get();
        while(elem != '=')
        {
            if(elem == '1')        
            {
                this->room[x][y] = '1';
                y++;
            }
            else if(elem == '\n')
            {
                x++;
                y = furn.y;
            }
            else if(elem == ' ')
            {
                y++;
            }
            else
            {
                throw std::runtime_error("Invalid symbol!");
            }
            elem = input.get();   
        } 
        input.get();
        input.get();
    }
}

void Room::placesForPaintSpill(int L, std::ifstream& input)
{
    for(int i = 0; i < L; i++)
    {
        Position help;
        help.read(input);
        this->room[help.x][help.y] = 'P';
    }
}

void Room::printRoom() {
    std::cout<<'\n';
    for (std::vector<char> v : room) {
        for (char c : v) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<'\n';
}

void Room::createRoom(std::string filePath)
{
    std::ifstream input(filePath.c_str());
    if (input.fail())
	{
		std::cout << "Error!\n";
	}
    resizeRoom(input);
     
    putJerryPosition(input);
    putTomPosition(input); 
    if(Jerry == Tom)
    {
        this->room[Tom.x][Tom.y] = 'F';
    }
    
    int K;
    input >> K;

    int L;
    input >> L;

    putFurniture(K, input);
    placesForPaintSpill(L, input);   

    input.close(); 
}

bool Room::canStepOn(const Position& other)
{
    return other.x >= 0 && other.x < this->room[0].size()&&
           other.y >= 0 && other.y < this->room.size() &&
           (this->room[other.x][other.y] == '0' ||
            this->room[other.x][other.y] == 'P' ||
            this->room[other.x][other.y] == 'S' ||
            this->room[other.x][other.y] == 'F') &&
            this->room[other.x][other.y] != 'V';
}

void Room::createPossiblePathsHelper(const Position& curr, std::string& path)
{    
    bool isP = false;
    if(!canStepOn(curr))
    {
        return;
    }
    if(room[curr.x][curr.y] == 'F')
    {
        possiblePaths.push_back(path);
        return;
    }
    if(room[curr.x][curr.y] == 'P')
    {
        path.push_back('P');
        isP = true;
    }

    room[curr.x][curr.y] = 'V';   
    
    if(canStepOn(curr.north()))
    {
        path.push_back('N');
        createPossiblePathsHelper(curr.north(), path);
        path.pop_back();
    }

    if(canStepOn(curr.east()))
    {
        path.push_back('E');
        createPossiblePathsHelper(curr.east(), path);
        path.pop_back();
    }

    if(canStepOn(curr.south()))
    {
        path.push_back('S');
        createPossiblePathsHelper(curr.south(), path);
        path.pop_back();
    }   

    if(canStepOn(curr.west()))
    {
        path.push_back('W');
        createPossiblePathsHelper(curr.west(), path);
        path.pop_back();
    }

    if (isP) 
    {
        path.pop_back();
        room[curr.x][curr.y] = 'P';
    }
    else 
    {
        room[curr.x][curr.y] = '0';    
    }
}

void Room::createPossiblePaths(const Position& curr)
{
    std::string path;
    createPossiblePathsHelper(curr, path);
}

std::vector<std::string> Room::allPossPathsInRoom(std::string filePath)
{
    createRoom(filePath);
    createPossiblePaths(Tom);
    return possiblePaths;
}

int Room::sizeWithoutPaintSpill(std::string path)
{
    int min = 0;
    for(int i =0; i < path.size(); i++)
    {
        if(path[i] != 'P')
        {
            min++;
        }
    }
    return min;
}

int Room::minLengthPaths(std::vector<std::string> paths)
{
    std::string min = paths[0];
    for(int i = 1; i < paths.size(); i++)
    {
        if(sizeWithoutPaintSpill(paths[i]) < sizeWithoutPaintSpill(min))
        {
            min = paths[i];
        }
    }
    return sizeWithoutPaintSpill(min);
}

std::string Room::findPathWithoutPaintSpill(std::string path)
{
    std::string saver;
    for(int i =0; i < path.size(); i++)
    {
        if(path[i] != 'P')
        {
            saver.push_back(path[i]);
        }
    }
    return saver;
}

std::vector<std::string> Room::shortestPathsInRoom(std::string filePath)
{
    std::vector<std::string> allPaths = allPossPathsInRoom(filePath);
    possiblePaths.clear();
    int len = minLengthPaths(allPaths);
    for(int i = 0; i < allPaths.size(); i++)
    {
        if(sizeWithoutPaintSpill(allPaths[i]) == len)
        {
            possiblePaths.push_back(allPaths[i]);
        }
    }
    return possiblePaths;
}