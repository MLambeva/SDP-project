#include "Tree.h"

void Tree::clearHelper(Node* curr)
{
    if(!curr)
    {
        return;
    }
    clearHelper(curr->north);
    clearHelper(curr->east);
    clearHelper(curr->south);
    clearHelper(curr->west);
    clearHelper(curr->paint);
    delete curr;    
}

//According to direction symbol, function returns a pointer to next direction
Tree::Node*& Tree::findNextPosition(char x, Node*& curr) 
{
    if(curr)
    {
        switch(x)
        {
            case 'N':return curr->north;
            case 'E':return curr->east;
            case 'S':return curr->south;
            case 'W':return curr->west;
            case 'P':return curr->paint;
            default:throw std::invalid_argument("Invalid command");
        }
    }  
    else
    {
        throw std::runtime_error ("Cannot be nullptr!");
    }      
}

//Creates next part of tree
void Tree::createNextNode(char x, std::string path, Node*& curr)
{  
    if(path.front() == x)
    {
        Node*& next = findNextPosition(x, curr);
        if(!next)
        {
            next = new Node{x};
        }
        curr = next;
    }
    
}

bool Tree::isCorrectChar(char x) const
{
    return x == 'N' || x == 'E' || x == 'S' || x == 'W' || x == 'P';
}

//Creates the tail of tree
void Tree::createTailTree(std::string& path)
{
    Node* curr = start;
    while(path.size() > 0)
    {
        if(isCorrectChar(path.front()))
        {
            createNextNode('N', path, curr);
            createNextNode('E', path, curr);
            createNextNode('S', path, curr);
            createNextNode('W', path, curr);
            createNextNode('P', path, curr);
        }
        else
        {
            throw std::invalid_argument ("Invalid symbol!");
        }
        path.erase(path.begin());
    }
}

//Creates tree from one string
void Tree::addOnePath(std::string path)
{
    if(!start)
    {
        start = new Node{' '};
    }
    try
    {
        createTailTree(path);   
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what() << '\n';
    }   
}

void Tree::makeLegend(std::ostream& out) const
{
    out << "rankdir=TB \nsubgraph cluster_01 \n { \n node [shape=plaintext] \n label=<<B>Legend:</B>>;\n { \n rankdir = LR \n rank = same\n"
        "key [label=<<table  border=\"0\" cellpadding=\"2\" cellspacing=\"0\" cellborder=\"0\">\n"
            "<tr><td align=\"right\" port=\"north\">North</td></tr>\n"
            "<tr><td align=\"right\" port=\"east\">East</td></tr>\n"
            "<tr><td align=\"right\" port=\"south\">South</td></tr>\n"
            "<tr><td align=\"right\" port=\"west\">West</td></tr>\n"
            "<tr><td align=\"right\" port=\"paint\">Paint</td></tr>\n"
            "</table>>]\n"
        "key2 [label=<<table  border=\"0\" cellpadding=\"2\" cellspacing=\"0\" cellborder=\"0\">\n"
            "<tr><td port=\"north\">&nbsp;</td></tr>\n"
            "<tr><td port=\"east\">&nbsp;</td></tr>\n"
            "<tr><td port=\"south\">&nbsp;</td></tr>\n"
            "<tr><td port=\"west\">&nbsp;</td></tr>\n"
            "<tr><td port=\"paint\">&nbsp;</td></tr>\n"
            "</table>>]\n"
        "key:north:e -> key2:north:w [color=red]\n"
        "key:east:e -> key2:east:w [color=orange]\n"
        "key:south:e -> key2:south:w [color=green]\n"
        "key:west:e -> key2:west:w [color=blue]\n"
        "key:paint:e -> key2:paint:w [color=black]\n" 
    "}\n}\n";
}

//Remove repeats for visualizing tree
void Tree::removeRepeats (std::ostream& out, Node* pos, Node* direction, std::string color) const
{
    if (direction)
    {
        out << (long)pos << "->" << (long)direction << "[color=" << color << "];\n";
    }   
}

//Tree visualization
void Tree::toGvHelper (std::ostream& out, Node *curr) const
{
    if (curr)
    {     
        if (curr == start)
        {
            out << (long)curr << "[label=<<B>Start</B>>];\n";
        }
        else
        {
            out << (long)curr << "[label=<<B>" << curr->data << "</B>>";
            if (isLeaf(curr))
            {
                out << ", xlabel=<<B><font color = \"#416D49\">" << curr->idLeaf << "</font></B>>";
            }
            out << "];\n";
        }     
        
        removeRepeats(out, curr, curr->north, "red");
        removeRepeats(out, curr, curr->east, "orange");
        removeRepeats(out, curr, curr->south, "green");
        removeRepeats(out, curr, curr->west, "blue");
        removeRepeats(out, curr, curr->paint, "black");
    
        toGvHelper (out, curr->north);
        toGvHelper (out, curr->east);
        toGvHelper (out, curr->south);
        toGvHelper (out, curr->west);
        toGvHelper (out, curr->paint);
    }
}

//Checks if the pointer points to leaf
bool Tree::isLeaf(Node* curr) const
{
    return !curr->north && !curr->east && !curr->south && !curr->west && !curr->paint;
}

//Counts the leaves
int Tree::countLeavesHelper(Node *curr) const
{
    if(!curr)
    {
        return 0;
    }
    if(isLeaf(curr))
    {
        return 1;
    }
    return countLeavesHelper(curr->north) + countLeavesHelper(curr->east) +
           countLeavesHelper(curr->south) + countLeavesHelper(curr->west) + countLeavesHelper(curr->paint);
}

//Each leaf has an identifier starting from 0 and each node that is not a leaf takes a value -1
void Tree::createIdToLeavesHelper(Node* curr, int& id)
{
   if(!curr)
   {
      return;
   }
   if(isLeaf(curr))
   {
       id++;
       curr->idLeaf = id;
   }
   createIdToLeavesHelper(curr->north, id);
   createIdToLeavesHelper(curr->east, id);
   createIdToLeavesHelper(curr->south, id);
   createIdToLeavesHelper(curr->west, id);
   createIdToLeavesHelper(curr->paint, id);
}

//Helper function to add node to queue
void Tree::addNodeToQueue(Node* direction, std::queue<Node*>& q)
{
    if(direction)
    {
        q.push(direction);
    }
}

//We need to know if there is leaf with identifier 'id' in the subtree with root 'curr'
bool Tree::isLeafWithIdInSubtree(Node* curr, const int& id) 
{
    if(!curr)
    {
        return false;
    }
    std::queue<Node*> q;
    q.push(curr);
    while(!q.empty())
    {
        Node* saver = q.front();
        q.pop();
        if(isLeaf(saver) && saver->idLeaf == id)
        {
            return true;
        }
        addNodeToQueue(saver->north, q);
        addNodeToQueue(saver->east, q);
        addNodeToQueue(saver->south, q);
        addNodeToQueue(saver->west, q);
        addNodeToQueue(saver->paint, q);
    }
    return false;
}

//According to 'id', function create path from root to leaf with this id
void Tree::findPathOnLeafWithIdHelper(Node* curr, const int& id, std::string& path) 
{
    if(!curr || (isLeaf(curr) && curr->idLeaf != id) || !isLeafWithIdInSubtree(curr, id))
    {
        return;
    }
    if(curr->idLeaf == id)
    {
        path.push_back(curr->data);
        return;
    }    
    if(isLeafWithIdInSubtree(curr, id) && curr->data != ' ')
    {
        path.push_back(curr->data);
    }   
    findPathOnLeafWithIdHelper(curr->north, id, path);
    findPathOnLeafWithIdHelper(curr->east, id, path);
    findPathOnLeafWithIdHelper(curr->south, id, path);
    findPathOnLeafWithIdHelper(curr->west, id, path);
    findPathOnLeafWithIdHelper(curr->paint, id, path);
}

Tree::Tree():start(nullptr){}

Tree::~Tree()
{
    clearHelper(start);
}

//Creates tree from all paths
void Tree::addAllPaths(std::vector<std::string> paths)
{
    for(std::string path : paths)
    {
        addOnePath(path);
    }
}

//Tree visualization
void Tree::toGv(std::ostream& out)
{
    out << "digraph G{\n";
    makeLegend(out);
    toGvHelper(out, start);     
    out << "}";
}

//Counts the leaves
int Tree::countLeaves()const
{
    return countLeavesHelper(start);
}

//Creates identifier to each leaf
void Tree::createIdToLeaves()
{
    int x = -1;
    createIdToLeavesHelper(start, x);
}

//According to a given identifier 'id', function returns string that is path from root to a leaf with this 'id'
std::string Tree::findPathOnLeafWithId(const int& id)
{
    std::string path;
    findPathOnLeafWithIdHelper(start, id, path);
    return path;
}
