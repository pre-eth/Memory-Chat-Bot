#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>

#include "chatbot.h"


// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE

    // data handles (owned)
    std::vector<std::unique_ptr<GraphEdge>> childEdges;  // edges to subsequent nodes

    // data handles (not owned)
    std::vector<GraphEdge *> parentEdges; // edges to preceding nodes 
    ChatBot *chatBot;

    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    std::vector<std::string> answers;

public:
    // constructor / destructor
    GraphNode(int id) : _id(id) { chatBot = nullptr; };

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return answers; }
    int GetNumberOfParents() { return parentEdges.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge);

    //// STUDENT CODE
    ////

    void MoveChatbotHere(ChatBot *chatbot);

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */