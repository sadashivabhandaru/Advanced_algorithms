#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& freqs) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto& pair : freqs) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* merged = new Node('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    return minHeap.top();
}

void generateCodes(Node* root, const string& code, unordered_map<char, string>& codes) {
    if (root == nullptr) return;

    if (root->character != '\0') {
        codes[root->character] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

string encodeMessage(const string& message, const unordered_map<char, string>& codes) {
    string encodedMessage = "";
    for (char ch : message) {
        encodedMessage += codes.at(ch);
    }
    return encodedMessage;
}

string decodeMessage(const string& encodedMessage, Node* root) {
    string decodedMessage = "";
    Node* currentNode = root;

    for (char bit : encodedMessage) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (currentNode->character != '\0') {
            decodedMessage += currentNode->character;
            currentNode = root;
        }
    }

    return decodedMessage;
}

int main() {
    int numChars;
    cout << "Enter number of unique characters: ";
    cin >> numChars;

    unordered_map<char, int> freqs;
    for (int i = 0; i < numChars; ++i) {
        char ch;
        int freq;
        cout << "Character: ";
        cin >> ch;
        cout << "Frequency: ";
        cin >> freq;
        freqs[ch] = freq;
    }

    Node* root = buildHuffmanTree(freqs);
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Huffman Codes:" << endl;
    for (auto& pair : codes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    string message;
    cout << "Enter the message to encode: ";
    cin >> message;
    string encodedMessage = encodeMessage(message, codes);
    cout << "Encoded Message: " << encodedMessage << endl;

    string encodedMessageToDecode;
    cout << "Enter encoded message to decode: ";
    cin >> encodedMessageToDecode;
    string decodedMessage = decodeMessage(encodedMessageToDecode, root);
    cout << "Decoded Message: " << decodedMessage << endl;

    return 0;
}
