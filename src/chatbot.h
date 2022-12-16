#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *image{NULL}; // avatar image

    // data handles (not owned)
    GraphNode *currentNode{nullptr};
    GraphNode *rootNode{nullptr};
    ChatLogic *chatLogic{nullptr};

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    ChatBot(const ChatBot& src);                // COPY CTOR
    ChatBot& operator=(const ChatBot& src);     // COPY ASSIGN CTOR 
    ChatBot(ChatBot&& src);                     // MOVE CTOR
    ChatBot& operator=(ChatBot&& src);          // MOVE ASSIGN

    //// STUDENT CODE
    ////

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rNode) { rootNode = rNode; }
    void SetChatLogicHandle(ChatLogic *cLogic) { chatLogic = cLogic; }
    wxBitmap *GetImageHandle() { return image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
