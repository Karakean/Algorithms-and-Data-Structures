#include "Node.h"
Node::Node() {
        for(int i=0; i<ALPHABET_LENGTH; i++)
                this->children[i] = nullptr;
        this->translation = "";
        this->isWord = false;
}
void Node::addWord(std::string word, std::string _translation) {
        unsigned int i = 0;
        Node* node = this;
        while (i < word.length()) {
                int j = word[i] - 97;
                if (node->children[j] == nullptr)
                        node->children[j] = new Node();
                node = node->children[j];
                ++i;
        }
        node->isWord = true;
        node->translation = _translation;
}
Node* Node::search(std::string word) {
        Node *ntr = this; //Node to return
        unsigned int i = 0;
        while (i < word.length()) {
                int j = word[i] - 97;
                if (ntr->children[j] == nullptr)
                        return nullptr;
                ntr = ntr->children[j];
                ++i;
        }
        if (ntr->isWord)
                return ntr;
        else 
                return nullptr;
}
std::string Node::getTranslation() const{
        return this->translation;
}
void Node::traverse() {
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
                if (this->children[i] != nullptr) {
                        if (this->children[i]->isWord)
                                std::cout << this->children[i]->translation << "\n";
                        this->children[i]->traverse();
                }
        }
}
void Node::printWords(std::string prefix) {
        unsigned int i = 0;
        Node* node = this;
        while (i < prefix.length()) {
                int j = prefix[i] - 97;
                if (node->children[j] == nullptr) {
                        printf("-\n");
                        return;
                }
                node = node->children[j];
                ++i;
        }
        if ((i == prefix.length()) && (node->isWord))
                std::cout << node->translation << "\n";
        node->traverse();
}
void Node::deleteChildren() {
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
                if (this->children[i] != nullptr) {
                        this->children[i]->deleteChildren();
                }
                delete this->children[i];
                this->children[i] = nullptr;
        }
}
Node::~Node() {
        this->deleteChildren();
}