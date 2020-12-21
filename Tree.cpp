#include "Tree.h"

Tree::Tree():start(nullptr){}

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
void Tree::helper(char x, Node*& curr)
{  
    Node*& next = findNextPosition(x, curr);
    if(!next)
    {
        next = new Node{x};
    }
    curr = next;
}

//Creates the tail of tree
void Tree::createTailTree(std::string& path)
{
    Node* curr = start;
    while(path.size() > 0)
    {
        if(path.front() == 'N')
        {
            helper('N', curr);
        }
        else if(path.front() == 'E')
        {
            helper('E', curr);
        }
        else if(path.front() == 'S')
        {
            helper('S', curr);
        }
        else if(path.front() == 'W')
        {
            helper('W', curr);
        }
        else if(path.front() == 'P')
        {
            helper('P', curr);
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
    out << "rankdir=TB \nsubgraph cluster_01 \n { \n node [shape=plaintext] \n label=\"Legend:\";\n { \n rankdir = LR \n rank = same\n"
        "key [label=<<table  border=\"0\" cellpadding=\"2\" cellspacing=\"0\" cellborder=\"0\">\n"
            "<tr><td align=\"right\" port=\"north\">North</td></tr>\n"
            "<tr><td align=\"right\" port=\"east\">East</td></tr>\n"
            "<tr><td align=\"right\" port=\"south\">South</td></tr>\n"
            "<tr><td align=\"righ\" port=\"west\">West</td></tr>\n"
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
                out << ", xlabel=<<B>" << curr->idLeaf << "</B>>";
            }
            out << "];\n";
        }     
        
        if (curr->north)
        {
            out << (long)curr << "->" << (long)(curr->north) << "[color=red];\n";
        } 
        if (curr->east)
        {
            out << (long)curr << "->" << (long)(curr->east) << "[color=orange];\n";
        }
        if (curr->south)
        {
            out << (long)curr << "->" << (long)(curr->south) << "[color=green];\n";
        } 
        if (curr->west)
        {
            out << (long)curr << "->" << (long)(curr->west) << "[color=blue];\n";
        }
        if (curr->paint)
        {
            out << (long)curr << "->" << (long)(curr->paint) << "[color=black];\n";
        } 
    
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

//We need to know if there is leaf with identifier 'id' in the subtree with root 'curr'
bool Tree::isLeafWithIdInSubtree(Node* curr, const int& id) 
{
    if(!curr)
    {
        return false;
    }
    if(isLeaf(curr) && curr->idLeaf == id)
    {
        return true;
    }
    return isLeafWithIdInSubtree(curr->north, id)
        || isLeafWithIdInSubtree(curr->east, id)
        || isLeafWithIdInSubtree(curr->south, id)
        || isLeafWithIdInSubtree(curr->west, id)
        || isLeafWithIdInSubtree(curr->paint, id);
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
