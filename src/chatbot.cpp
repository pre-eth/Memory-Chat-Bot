#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include "chatlogic.h"
#include "graphnode.h"
#include "graphedge.h"
#include "chatbot.h"

// constructor WITH memory allocation
ChatBot::ChatBot(std::string filename) {
    std::cout << "ChatBot Constructor\n";

    // load image into heap memory
    image = new wxBitmap(filename, wxBITMAP_TYPE_PNG);
}

ChatBot::~ChatBot() {
    std::cout << "ChatBot Destructor\n";

    if (image != NULL) 
        delete image;    
}

ChatBot::ChatBot(const ChatBot& src) : 
currentNode(src.currentNode), chatLogic(src.chatLogic), rootNode(src.rootNode) {
    std::cout << "ChatBot Copy Constructor\n";

    image = new wxBitmap(*src.image);
}

ChatBot& ChatBot::operator=(const ChatBot& src) {
    std::cout << "Chatbot Copy Assignment Constructor\n";
    std::cout << "Assigning content from from ChatBot " << &src << " to ChatBot " << this << "\n";

    if (this == &src)
        return *this;
    
    currentNode = src.currentNode;
    chatLogic = src.chatLogic;
    rootNode = src.rootNode;

    delete image;
    image = new wxBitmap(*src.image);

    return *this;
}

ChatBot::ChatBot(ChatBot&& src) :
currentNode(src.currentNode), chatLogic(src.chatLogic), rootNode(src.rootNode), image(src.image) {
    std::cout << "Chatbot Move Constructor\n";
    std::cout << "Moving content from from ChatBot " << &src << " to ChatBot " << this << "\n";

    src.currentNode = nullptr;
    src.chatLogic = nullptr;
    src.rootNode = nullptr;
    src.image = NULL;   // since wxBitmap uses NULL
}

ChatBot& ChatBot::operator=(ChatBot&& src)  {
    std::cout << "Chatbot Move Assignment Constructor\n";
    std::cout << "Moving and assigning content from from ChatBot " << &src << " to ChatBot " << this << "\n";
    
    if (this == &src)
        return *this;

    currentNode = src.currentNode;
    chatLogic = src.chatLogic;
    rootNode = src.rootNode;

    delete image;
    image = src.image;

    src.currentNode = nullptr;
    src.chatLogic = nullptr;
    src.rootNode = nullptr;
    src.image = NULL;   

    return *this;
}

void ChatBot::ReceiveMessageFromUser(std::string message) {
    // loop over all edges and keywords and compute Levenshtein distance to query
    typedef std::pair<GraphEdge *, int> EdgeDist;
    std::vector<EdgeDist> levDists; // format is <ptr,levDist>

    for (size_t i = 0; i < currentNode->GetNumberOfChildEdges(); ++i) {
        GraphEdge *edge = currentNode->GetChildEdgeAtIndex(i);
        for (auto keyword : edge->GetKeywords()) {
            EdgeDist ed{edge, ComputeLevenshteinDistance(keyword, message)};
            levDists.push_back(ed);
        }
    }

    // select best fitting edge to proceed along
    GraphNode *newNode;
    if (levDists.size() > 0) {
        // sort in ascending order of Levenshtein distance (best fit is at the top)
        std::sort(
            levDists.begin(), levDists.end(), 
            [](const EdgeDist &a, const EdgeDist &b) { return a.second < b.second; }
        );

        // after sorting the best edge is at first position
        newNode = levDists.at(0).first->GetChildNode(); 
    }
    else
        // go back to root node
        newNode = rootNode;

    // tell current node to move chatbot to new node
    currentNode->MoveChatbotToNewNode(newNode);
}

void ChatBot::SetCurrentNode(GraphNode *node) {
    // update pointer to current node
    currentNode = node;

    // select a random node answer (if several answers should exist)
    std::vector<std::string> answers = currentNode->GetAnswers();
    std::mt19937 generator(int(std::time(0)));
    std::uniform_int_distribution<int> dis(0, answers.size() - 1);
    std::string answer = answers.at(dis(generator));

    // send selected node answer to user
    chatLogic->SendMessageToUser(answer);
}

int ChatBot::ComputeLevenshteinDistance(std::string s1, std::string s2) {
    // convert both strings to upper-case before comparing
    std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    // compute Levenshtein distance measure between both strings
    const size_t m(s1.size());
    const size_t n(s2.size());

    if (m == 0)
        return n;
    if (n == 0)
        return m;

    size_t *costs = new size_t[n + 1];

    for (size_t k = 0; k <= n; k++)
        costs[k] = k;

    size_t i = 0;
    for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
        costs[0] = i + 1;
        size_t corner = i;

        size_t j = 0;
        for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
            size_t upper = costs[j + 1];
            if (*it1 == *it2)
                costs[j + 1] = corner;
            else {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }

            corner = upper;
        }
    }

    int result = costs[n];
    delete[] costs;

    return result;
}