#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct HuffmanNode {
    char ch;              
    int freq;             
    HuffmanNode* left;    
    HuffmanNode* right;   

    HuffmanNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& entry : freqMap) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top(); 
}

void generateCodes(HuffmanNode* root, const string& currentCode, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = currentCode;
    }

    generateCodes(root->left, currentCode + "0", huffmanCodes);
    generateCodes(root->right, currentCode + "1", huffmanCodes);
}

string encode(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedString;
    for (char ch : text) {
        encodedString += huffmanCodes.at(ch);
    }
    return encodedString;
}

string decode(HuffmanNode* root, const string& encodedString) {
    string decodedString;
    HuffmanNode* current = root;

    for (char bit : encodedString) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedString += current->ch;
            current = root;
        }
    }

    return decodedString;
}

int main() {
    string text = "huffman algorithm example";

    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    HuffmanNode* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "Huffman Codes:\n";
    for (const auto& entry : huffmanCodes) {
        cout << entry.first << ": " << entry.second << "\n";
    }

    string encodedString = encode(text, huffmanCodes);
    cout << "\nEncoded String: " << encodedString << "\n";

    string decodedString = decode(root, encodedString);
    cout << "\nDecoded String: " << decodedString << "\n";

    return 0;
}
