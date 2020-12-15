#include "tree.h"

Tree::Tree():start(nullptr){}

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
            default:throw std::runtime_error("Invalid command");
        }
    }    
}

void Tree::helper(std::string x, Node*& curr)
{  
    Node*& next = findNextPosition(x.front(), curr);
    if(!next)
    {
        next = new Node{x};
    }
    curr = next;
}

void Tree::createTailTree(std::string& path)
{
    Node* curr = start;
    while(path.size() > 0)
    {
        if(path.front() == 'N')
        {
            helper("N", curr);
        }
        else if(path.front() == 'E')
        {
            helper("E", curr);
        }
        else if(path.front() == 'S')
        {
            helper("S", curr);
        }
        else if(path.front() == 'W')
        {
            helper("W", curr);
        }
        else if(path.front() == 'P')
        {
            helper("P", curr);
        }
        else
        {
            throw std::runtime_error ("Invalid symbol!");
        }
        path.erase(path.begin());
    }
}

void Tree::add(std::string path)
{
    if(!start)
    {
        start = new Node{"Start"};
    }
    try
    {
        createTailTree(path);   
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }   
}

void Tree::toGv(std::ostream& out)
{
    out << "digraph G{\n";
    toGvHelp(out, start);     
    out << "}";
}

void Tree::toGvHelp (std::ostream& out, Node *curr)
{
    if (curr)
    {     
        out << (long)curr << "[label=\"" << curr->data << "\"];\n";

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
    
        toGvHelp (out, curr->north);
        toGvHelp (out, curr->east);
        toGvHelp (out, curr->south);
        toGvHelp (out, curr->west);
        toGvHelp (out, curr->paint);
    }
}

void Tree::createTree(std::vector<std::string> paths)
{
    for(int i=0;i<paths.size();i++)
    {
        add(paths[i]);
    }
}
