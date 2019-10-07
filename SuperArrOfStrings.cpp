#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::pair, std::make_pair, std::vector;

struct Node {
    int sizeOfTree;
    int priority;
    string value;
    Node* left, *right;
    Node(const string& value);
    void CountSize();
    void Clear();
};

Node::Node(const string& val) {
    value = val;
    priority = rand();
    left = nullptr;
    right = nullptr;
    sizeOfTree = 1;
}


void Node::CountSize() {
    sizeOfTree = 1;
    if (left) {
        sizeOfTree += left->sizeOfTree;
    }
    if (right) {
        sizeOfTree += right->sizeOfTree;
    }
}

/*void Node::Clear() {
    if (this == nullptr) {
        return;
    }
    left->Clear();
    right->Clear();
    delete this;
}*/

class SuperStringArray {
private:
    Node* root;
public:
    SuperStringArray();
    ~SuperStringArray();
    void InsertAt(int position, const string &value);
    void DeleteAt(int position);
    string GetAt(int position) const;
    pair<Node*, Node*> Split(Node *node, int position);
    Node* Merge(Node *leftNode, Node *rightNode);
    void DelNode(Node* node);
};

void SuperStringArray::DelNode(Node *node) {
    if (node == nullptr) {
        return;
    }
    DelNode(node->left);
    DelNode(node->right);
    delete(node);
}

SuperStringArray::SuperStringArray() {
    root = nullptr;
}

SuperStringArray::~SuperStringArray() {
    DelNode(root);
}

void SuperStringArray::InsertAt(int position, const string& value) {
    Node* current = new Node(value);
    pair<Node*, Node*> ans = Split(root, position);
    Node* right = Merge(current, ans.second);
    root = Merge(ans.first, right);
};

void SuperStringArray::DeleteAt(int position) {
    pair<Node*, Node*> pair1 = Split(root, position);
    pair<Node*, Node*> pair2 = Split(pair1.second, 1);
    delete pair2.first;
    root = Merge(pair1.first, pair2.second);
}

string SuperStringArray::GetAt(int position) const {
    Node* node = root;
    while(node) {
    	int l = 0;
    	if (node->left) {
    		l = node->left->sizeOfTree;
        }
        if (l == position) break;
        if (position > l) { position -= l + 1; node = node->right; }
        else node = node->left;
    }
    return node->value;
};

pair<Node*, Node*> SuperStringArray::Split(Node *node, int position) {
    if (!node) {
        return make_pair(nullptr, nullptr);
    }
    int l = 0;
    if (node->left) {
        l = node->left->sizeOfTree;
    }
    pair<Node*, Node*> splittedPlace;
    if (l >= position) {
        splittedPlace = Split(node->left, position);
        node->left = splittedPlace.second;
        node->CountSize();
        return make_pair(splittedPlace.first, node);
    }
    else {
        int pos = position - l - 1;
        splittedPlace = Split(node->right, pos);
        node->right = splittedPlace.first;
        node->CountSize();
        return make_pair(node, splittedPlace.second);
    }
}

Node* SuperStringArray::Merge(Node *leftNode, Node *rightNode) {
    if (!rightNode) {
        return leftNode;
    }
    if (!leftNode) {
        return rightNode;
    }
    if (leftNode->priority > rightNode->priority) {
        leftNode->right = Merge(leftNode->right, rightNode);
        leftNode->CountSize();
        return leftNode;
    }
    else {
        rightNode->left = Merge(leftNode, rightNode->left);
        rightNode->CountSize();
        return rightNode;
    }
}

int main() {
    int amountOfCommands;
    cin >> amountOfCommands;
    SuperStringArray arrOfStrings;
    vector<string> output(amountOfCommands);
    for (int i = 0; i < amountOfCommands; ++i) {
        char command;
        cin >> command;
        switch(command) {
            case '?': {
                int position;
                cin >> position;
                output.push_back(arrOfStrings.GetAt(position));
                break;
            }
            case '-': {
                int position1, position2;
                cin >> position1 >> position2;
                for(int j = 0; j < position2 - position1 + 1; ++j) {
                    arrOfStrings.DeleteAt(position1);
                }
                break;
            }
            default: {
                int position;
                string val;
                cin >> position >> val;
                arrOfStrings.InsertAt(position, val);
                break;
            }
        }
    }
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << endl;
    }
    return 0; //
}
