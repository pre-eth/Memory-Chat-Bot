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
    // data handles (owned)
    std::vector<std::unique_ptr<GraphEdge>> childEdges;  // edges to subsequent nodes

    // data handles (not owned)
    std::vector<GraphEdge*> parentEdges; // edges to preceding nodes 
    ChatBot chatBot;

    // proprietary members
    int _id;
    std::vector<std::string> answers;

public:
    // constructor / destructor
    GraphNode(int id) : _id(id) {};

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index)
        { return childEdges[index].get(); };
    std::vector<std::string> GetAnswers() { return answers; }
    int GetNumberOfParents() { return parentEdges.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge);
    void MoveChatbotHere(ChatBot cbot);
    void MoveChatbotToNewNode(GraphNode *newNode)
        { newNode->MoveChatbotHere(std::move(chatBot)); };
};

#endif /* GRAPHNODE_H_ */