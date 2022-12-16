#include "graphedge.h"
#include "graphnode.h"

void GraphNode::AddToken(std::string token) {
    answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
    parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
    childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot) {
    chatBot = chatbot;
    chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(chatBot);
    chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge* GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    return childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}