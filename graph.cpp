/*
* File:          Game.cpp
* Project:       CMSC 341 Project 1, Fall 2021
* Author:        Johnson Xie
*
* Description:   This file contains the graph.cpp
*               
*
*/

#include "graph.h"

//default constructor
Graph::Graph()
{
    m_numNodes = 0;
    m_head = nullptr;
    m_dataFile = "something";
}

//overloaded constructor that loads in data file 
Graph::Graph(string dataFile)
{
    m_dataFile = dataFile;
    m_head = nullptr;
    m_numNodes = 0;
    loadData();
}

//desctructor 
Graph::~Graph()
{
    Node *curr = m_head;

    while(curr != nullptr)
    {
        m_head = curr;
        curr = curr->m_next;
        delete m_head;
    }

    m_head = nullptr;
    m_dataFile = "";
    m_numNodes = 0;
}

//loads data from file 
void Graph::loadData()
{
    int numNodes;
    int node, n, e, s, w;
    ifstream dataFile;

    dataFile.open(m_dataFile);
    if (dataFile.is_open()) 
    {
        dataFile >> numNodes;
        m_numNodes = numNodes;

        for (int i = 0; i < numNodes; i++) 
        {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}


//creates nodes and inserts them into linked list 
void Graph::insert(int node, int n, int e, int s, int w) 
{
    bool notEmpty = true;

    // if the LL is empty
    if (m_head == nullptr) 
    {
        notEmpty = false;

        Node *theNode = new Node(node);
        m_head = theNode;

        //-1 means no path in that direction 
        if (n != -1)
        {
            Node *someNode = new Node(n);
            insertAtHead(someNode);
            theNode->setNorth(someNode);
        }

        if (e != -1)
        {
            Node *eastNode = new Node(e);
            insertAtHead(eastNode);
            theNode->setEast(eastNode);
        }

        if (s != -1) 
        {
            Node *someNode = new Node(s);
            insertAtHead(someNode);
            theNode->setSouth(someNode);
        }

        if (w != -1) 
        {
            Node *someNode = new Node(w);
            insertAtHead(someNode);
            theNode->setWest(someNode);
        }
    }

    // if LL has at least one element
    if (notEmpty == true) 
    {

        Node *nodeToAdd = findNode(node);

        // if node doesnt exist in LL
        if (nodeToAdd == nullptr)
        {
            Node *someNode = new Node(node);
            insertAtHead(someNode);
            nodeToAdd = someNode;
        }

        if (n != -1)
        {
            Node *northNode = findNode(n);

            // if north node not in LL
            if (northNode == nullptr)
            {
                Node *someNode = new Node(n);
                insertAtHead(someNode);
                nodeToAdd->setNorth(someNode);
            }else 
            {
                nodeToAdd->setNorth(northNode);
            }
        }
        if (e != -1)

            {
                Node *eastNode = findNode(e);

                if (eastNode == nullptr) 
                {
                    Node *someNode = new Node(e);
                    insertAtHead(someNode);
                    nodeToAdd->setEast(someNode);
                } else {
                    nodeToAdd->setEast(eastNode);
                }
            }

            if (s != -1) {
                Node *southNode = findNode(s);

                if (southNode == nullptr) 
                {
                    Node *someNode = new Node(s);
                    insertAtHead(someNode);
                    nodeToAdd->setSouth(someNode);

                } else {
                    nodeToAdd->setSouth(southNode);
                }
            }

            if (w != -1)
            {
                Node *westNode = findNode(w);

                if (westNode == nullptr)
                {
                    Node *someNode = new Node(w);
                    insertAtHead(someNode);
                    nodeToAdd->setWest(someNode);

                } else{
                    nodeToAdd->setWest(westNode);
                }
            }
    }
}

//inserts node at the head of linked list and updates pointers 
void Graph::insertAtHead(Node * aNode)
{
    aNode->m_next = m_head;
    m_head = aNode;
}

//function that traverses the linked list and find node with nodeValue
Node * Graph::findNode(int nodeValue)
{
    Node *temp = m_head;

    //if linked list only has 1 node
    if(temp->m_next == nullptr)
    {
        if(temp->m_value == nodeValue)
            return temp;
    }

    else
    {
        while(temp != nullptr)
        {
            if(temp->getValue() == nodeValue)
                return temp;

            temp = temp->m_next;
        }
    }
    return nullptr;
}


//function that finds a path from start node to end node.
bool Graph::findPath(int start, int end)
{
    Node *startNode = findNode(start);
    if(startNode == nullptr)
        return false;

    return findPath(startNode, end);

}

//helper function that recursively traverses the nodes.
bool Graph::findPath(Node* aNode, int end){
    if(aNode->getVisited() == false)
    {
        m_path.push(aNode->getValue());
        aNode->setVisited(true);
    }
    else
    {
        return false;
    }

    if(aNode->m_value == end)
        return true;
    else
    {
        if(aNode->getNorth() != nullptr)
        {
            if(aNode->getNorth()->m_value == end)
                return true;
            else
            {
                if(findPath(aNode->getNorth(), end) == true)
                {
                    return true;
                }
                else
                {
                    m_path.pop();
                }
            }
        }
        if(aNode->getEast() != nullptr)
        {
            if(aNode->getEast()->m_value == end)
                return true;
            else{

                if(findPath(aNode->getEast(), end) == true)
                {
                    return true;
                }
                else
                {
                    m_path.pop();
                }
            }
        }

        if(aNode->getSouth() != nullptr)
        {
            if(aNode->getSouth()->m_value == end)
                return true;
            else{

                if(findPath(aNode->getSouth(), end) == true)
                {
                    return true;
                }
                else
                {
                    m_path.pop();
                }
            }
        }

        if(aNode->getWest() != nullptr)
        {
            if(aNode->getWest()->m_value == end)
                return true;
            else{

                if(findPath(aNode->getWest(), end) == true)
                {
                    return true;
                }
                else
                {
                    m_path.pop();
                }
            }
        }

        return false;
    }
}

//function that prints out the path to output
void Graph::dump()
{
    stack<int> tempPath;

    while(!m_path.empty())
    {
        tempPath.push(m_path.top());
        m_path.pop();
    }

    while(!tempPath.empty())
    {
        int path = tempPath.top();
        cout << path <<"-->";
        tempPath.pop();

        //repopulates the original stack
        m_path.push(path);
    }
    cout << "END" << endl;
}

//function that clears the path found 
void Graph::clearResult()
{
    if(m_path.empty())
        cout << "path is empty" << endl;
    else
    {
        while(!m_path.empty())
        {
            m_path.pop();
        }
    }
}

//function that resets visted flag for all nodes
void Graph::clearVisited()
{
    Node* temp = m_head;
    while(temp->m_next != nullptr)
    {
        temp->setVisited(false);
        temp = temp->m_next;
    }
}

//function that builds graph using info in file
void Graph::buildGraph(string file)
{
    clearGraph();
    m_dataFile = file;
    loadData();
}

//function that deallocates all memory and reintializes all member variables 
void Graph::clearGraph(){
    cout << "Clear graph called" << endl;
    Node *curr = m_head;
    while(curr != nullptr)
    {
        m_head = curr;
        curr = curr->m_next;
        delete m_head;
    }

    m_head = nullptr;
    m_dataFile = "";
    m_numNodes = 0;
}

//creates deep copy of rhs
const Graph & Graph::operator=(const Graph & rhs){
    if(this != &rhs)
    {
        m_head = nullptr;
        m_numNodes = rhs.m_numNodes;
        m_path = rhs.m_path;

        Node *temp = m_head;
        Node *other = rhs.m_head;

        while(other != nullptr)
        {
            other = other->m_next;
        }
    }
    return *this;
}

bool Graph::empty() const		// is the list empty?
{ return m_head == nullptr; }
