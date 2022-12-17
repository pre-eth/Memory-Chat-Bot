#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <vector>
#include <string>
#include <memory>
#include "chatgui.h"

// forward declarations
class ChatBot;
class GraphEdge;
class GraphNode;

class ChatLogic
{
    private:
        // data handles (owned)
        std::vector<std::unique_ptr<GraphNode>> nodes;

        // data handles (not owned)
        GraphNode *currentNode;
        ChatBot *chatBot;
        ChatBotPanelDialog *panelDialog;

        // proprietary type definitions
        typedef std::vector<std::pair<std::string, std::string>> tokenlist;

        // proprietary functions
        template <typename T>
            void AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element);

    public:
        ChatLogic() {};
        // getter / setter
        void SetPanelDialogHandle(ChatBotPanelDialog* pd);
        void SetChatbotHandle(ChatBot* chatbot);

        // proprietary functions
        void LoadAnswerGraphFromFile(std::string filename);
        void SendMessageToChatbot(std::string message);
        void SendMessageToUser(std::string message);
        wxBitmap *GetImageFromChatbot();
};
#endif /* CHATLOGIC_H_ */