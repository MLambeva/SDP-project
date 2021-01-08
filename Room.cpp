#include"Room.h"

//Function that checks if we can place Tom, Jerry or furniture in the position set by the text file 
bool Room::canBeLocated(const Position& other) const
{
    return other.x >= 0 && other.x < room.size()&&
           other.y >= 0 && other.y < room[0].size() &&
           isCorrectSymbol(other, '0');
}

void Room::resizeRoom(std::ifstream& input)
{
    int width;
    input>>width;

    int length;
    input>>length;
    //width - Ox(north->south)
    //length - Oy(west->east)
    room.resize(width, std::vector<char>(length));
    
    for (int i = 0; i < room.size(); i++)
    {
        for (int j = 0; j < room[i].size(); j++)
        {
            room[i][j] = '0';
        }    
    }
}

//Function that sets position of Tom and Jerry
void Room::putCharactersPosition(Position& other, char x, const std::string& error, std::ifstream& input)
{
    Position saver;
    saver.read(input);
    if(canBeLocated(saver))
    {
        other = saver;
        setElemInCurrPosition(other, x);
    }
    else
    {
        throw std::runtime_error (error);
    }    
}

void Room::putJerryPosition(std::ifstream& input)
{
    putCharactersPosition(Jerry, 'F', "Invalid position of Jerry in text file!", input);  
}

void Room::putTomPosition(std::ifstream& input)
{
    putCharactersPosition(Tom, 'S', "Invalid position of Tom in text file!", input);  
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
        if((isCorrectSymbol({x,y}, 'F') || isCorrectSymbol({x,y}, 'S') && elem == '1'))
        {
            throw std::runtime_error ("Furniture cannot be outside the room or on Tom or Jerry!");
        }
        
        while(elem != '=')
        {
            if(canBeLocated({x,y}) || ((isCorrectSymbol({x,y}, 'F') || isCorrectSymbol({x,y}, 'S')) && elem == ' '))
            {
                if(elem == '1')        
                {
                    setElemInCurrPosition({x,y}, '1');                  
                    y++;                   
                }
                else if(elem == ' ')
                {
                    y++;
                }
                else
                {
                    throw std::runtime_error("Invalid symbol in the definition of furniture!");
                }
                elem = input.get();
                if(elem == '\n')
                {
                    x++;
                    y = furn.y;
                    elem = input.get();
                }
            }
            else
            {
                throw std::runtime_error ("Furniture cannot be outside the room or on Tom or Jerry!");
            }           
        }
        if(input.get() != '=' || input.get() != '=')
        {
            throw std::runtime_error("Invalid end of furniture!");
        }
    }
}

void Room::placesForPaintSpill(int L, std::ifstream& input)
{
    for(int i = 0; i < L; i++)
    {
        Position help;
        help.read(input);
        if(canBeLocated(help))
        {
            setElemInCurrPosition(help, 'P');
        }
        else
        {
            throw std::runtime_error ("Cannot spill paint on that position!");
        }        
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
    return other.x >= 0 && other.x < room.size()&&
           other.y >= 0 && other.y < room[0].size() &&
           (isCorrectSymbol(other, '0') ||
            isCorrectSymbol(other, 'P') ||
            isCorrectSymbol(other, 'S') ||
            isCorrectSymbol(other, 'F')) &&
            !isCorrectSymbol(other, 'V');
}

void Room::actionAfterCanStepOn(const Position& curr, char x, std::string path)
{
    if(canStepOn(curr))
    {
        path.push_back(x);
        createPossiblePathsHelper(curr, path);
        path.pop_back();
    }
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
    
    actionAfterCanStepOn(curr.north(), 'N', path);
    actionAfterCanStepOn(curr.east(), 'E', path);
    actionAfterCanStepOn(curr.south(), 'S', path);
    actionAfterCanStepOn(curr.west(), 'W', path);

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
    for(char elem : path)
    {
        if(elem != 'P')
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
        for(std::string posPath : possiblePaths)
        {
            if(lengthPath(posPath) < helper)
            {
                helper = lengthPath(posPath);
            }
        }
    }
    return helper;
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
		throw std::runtime_error ("The read file failed!");
	}
    resizeRoom(input);
    putJerryPosition(input);
    putTomPosition(input); 
    if(Jerry == Tom)
    {
        setElemInCurrPosition(Tom, 'F');
    }
    int K;//number of furniture
    input >> K;
    int L;//number of paint spill positions
    input >> L;
    putFurniture(K, input);
    placesForPaintSpill(L, input);   
    printRoom();
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
    for(std::string posPath : possiblePaths)
    {
        if(lengthPath(posPath) == length)
        {
            shortestPosPaths.push_back(posPath);
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
    std::cout << std::endl;
}
