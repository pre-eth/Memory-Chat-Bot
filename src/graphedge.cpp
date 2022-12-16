#include "graphnode.h"
#include "graphedge.h"

void GraphEdge::SetChildNode(GraphNode* childNode) {
    _childNode = childNode;
}

void GraphEdge::SetParentNode(GraphNode* parentNode) {
    _parentNode = parentNode;
}

void GraphEdge::AddToken(std::string token) {
    _keywords.push_back(token);
}