#include"Room.h"

//Function for putting position of Tom and Jerry
void Room::putHeroPosition(Position& other, char x, const std::string& error, std::ifstream& input)
{
    Position saver;
    saver.read(input);
    if(canStepOn(saver))
    {
        other = saver;
        setElemInCurrPosition(other, x);
    }
    else
    {
        throw std::runtime_error (error);
    }    
}

void Room::resizeRoom(std::ifstream& input)
{
    int width;
    input>>width;

    int length;
    input>>length;

    room.resize(length, std::vector<char>(width));
    
    for (int i = 0; i < room.size(); i++)
    {
        for (int j = 0; j < room[i].size(); j++)
        {
            room[i][j] = '0';
        }    
    }
}

void Room::putJerryPosition(std::ifstream& input)
{
    putHeroPosition(Jerry, 'F', "Invalid position of Jerry in text file!", input);  
}

void Room::putTomPosition(std::ifstream& input)
{
    putHeroPosition(Tom, 'S', "Invalid position of Tom in text file!", input);  
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

//Places 'x' in the room on position 'curr'
void Room::setElemInCurrPosition(const Position& curr, char x)
{
    room[curr.x][curr.y] = x;
}

//Checks if element 'x' is on position 'curr' in the room
bool Room::isCorrectSymbol(const Position& curr, char x) const
{
    return room[curr.x][curr.y] == x;
}

bool Room::canStepOn(const Position& other) const
{
    return other.x >= 0 && other.x < room[0].size()&&
           other.y >= 0 && other.y < room.size() &&
           (isCorrectSymbol(other, '0') ||
            isCorrectSymbol(other, 'P') ||
            isCorrectSymbol(other, 'S') ||
            isCorrectSymbol(other, 'F')) &&
            !isCorrectSymbol(other, 'V');
}

void Room::createPossiblePathsHelper(const Position& curr, std::string& path)
{    
    bool isP = false;
    if(!canStepOn(curr))
    {
        return;
    }
    if(isCorrectSymbol(curr, 'F'))
    {
        possiblePaths.push_back(path);
        return;
    }
    if(isCorrectSymbol(curr, 'P'))
    {
        path.push_back('P');
        isP = true;
    }
    setElemInCurrPosition(curr, 'V');
    
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
        setElemInCurrPosition(curr, 'P');
    }
    else 
    {
        setElemInCurrPosition(curr, '0');
    }
}

//Returns length of set path
int Room::lengthPath(std::string path) const
{
    int length = 0;
    for(int i=0;i<path.size();i++)
    {
        if(path[i] != 'P')
        {
            length++;
        }
    }
    return length;
}

//Finds length of shortest path
int Room::lengthShortestPath() const
{
    int helper = 0;
    if(!possiblePaths.empty())
    {
        helper = lengthPath(possiblePaths[0]);
        for(int i=1;i<possiblePaths.size();i++)
        {
            if(lengthPath(possiblePaths[i]) < helper)
            {
                helper = lengthPath(possiblePaths[i]);
            }
        }
    }
    return helper;
}

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
    return possiblePaths;
}

//Creates the room with information from a text file 
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

//Returns all possible paths for Tom to reach Jerry
std::vector<std::string> Room::createAllPossiblePaths()
{
    std::string path;
    createPossiblePathsHelper(Tom, path);
    return possiblePaths;
}

//Returns the shortest possible paths for Tom to reach Jerry
std::vector<std::string> Room::createShortestPossiblePaths() const
{
    std::vector<std::string> shortestPosPaths;
    int length = lengthShortestPath();
    for(int i=0;i<possiblePaths.size();i++)
    {
        if(lengthPath(possiblePaths[i]) == length)
        {
            shortestPosPaths.push_back(possiblePaths[i]);
        }
    }
    return shortestPosPaths;
}

void Room::printRoom() const
{
    std::cout<<'\n';
    for (std::vector<char> v : room) 
    {
        for (char c : v) 
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<'\n';
    for(int i=0;i<possiblePaths.size();i++)
    {
        std::cout<<possiblePaths[i]<<"   ";
    }
    std::cout<<'\n';
}
