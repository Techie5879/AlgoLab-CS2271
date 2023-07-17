#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Define the node structure for the Huffman tree
struct HuffmanNode {
    char symbol;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    // Constructor
    HuffmanNode(char s, int f) {
        symbol = s;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    // Destructor
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Comparator function for the min-heap
struct CompareHuffmanNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(string text) {
    // Create a map to store the frequency of each symbol
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Create a priority queue (min-heap) to store the Huffman nodes
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> pq;
    for (auto& f : freq) {
        pq.push(new HuffmanNode(f.first, f.second));
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        // Extract the two minimum frequency nodes from the priority queue
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Create a new node with the sum of the frequencies of the two nodes
        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // Add the new node to the priority queue
        pq.push(newNode);
    }

    // Return the root node of the Huffman tree
    return pq.top();
}

// Function to encode the text using the Huffman tree
string encodeText(string text, unordered_map<char, string>& code) {
    string encodedText = "";
    for (char c : text) {
        encodedText += code[c];
    }
    return encodedText;
}

// Function to traverse the Huffman tree and assign codes to symbols
void assignHuffmanCodes(HuffmanNode* node, string code, unordered_map<char, string>& huffmanCode) {
    if (node->left == nullptr && node->right == nullptr) {
        huffmanCode[node->symbol] = code;
    }
    else {
        assignHuffmanCodes(node->left, code + "0", huffmanCode);
        assignHuffmanCodes(node->right, code + "1", huffmanCode);
    }
}

// Function to print the Huffman codes for each symbol
void printHuffmanCodes(unordered_map<char, string>& huffmanCode) {
    cout << "Huffman Codes:" << endl;
    for (auto& code : huffmanCode) {
        cout << code.first << ": " << code.second << endl;
    }
}

// Function to decode the text using the Huffman tree
string decodeText(string encodedText, HuffmanNode* root) {
    string decodedText = "";
    HuffmanNode* current = root;
    for (char c : encodedText) {
        if (c == '0') {
            current = current->left;
        }
        else if (c == '1') {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->symbol;
            current = root;
        }
    }
    return decodedText;
}



int main() {
    // Open the input file
    ifstream inputFile("input_text1.txt");
    ofstream outputFile("output_text1.txt");
    if (!inputFile) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    // Read the input text from the file
    string text((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    inputFile.close();

    HuffmanNode* root = buildHuffmanTree(text);

    unordered_map<char, string> huffmanCode;
    assignHuffmanCodes(root, "", huffmanCode);

    // printHuffmanCodes(huffmanCode);

    string encodedText = encodeText(text, huffmanCode);
    // cout << "Input Text: " << text << endl;
    outputFile << encodedText << endl;
    // string decoded = decodeText(encodedText, root);
    // cout << "Decoded Text: " << decoded << endl;
    delete root;
    inputFile.close();
    outputFile.close();
    return 0;
}
