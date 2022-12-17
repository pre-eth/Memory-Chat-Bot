#include "graphnode.h"
#include "graphedge.h"

void GraphNode::AddToken(std::string token) {
    answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
    parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
    childEdges.push_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot cbot) {
    chatBot = std::move(cbot);
    chatBot.SetCurrentNode(this);
}
