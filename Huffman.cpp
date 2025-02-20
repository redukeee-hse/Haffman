#include "Huffman.h"
#include <algorithm>
#include <fstream>


std::vector<Node *> buildHuffmanTree(std::vector<Node *> &nodes) {
    if (nodes.empty())
        return {};

    std::vector<Node *> huffmanNodes = nodes;

    while (huffmanNodes.size() > 1) {
        auto left = huffmanNodes[0];
        auto right = huffmanNodes[1];

        Node *newNode = new Node('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        huffmanNodes.erase(huffmanNodes.begin(), huffmanNodes.begin() + 2);

        auto position = lower_bound(huffmanNodes.begin(), huffmanNodes.end(), newNode,
                                    [](Node *a, Node *b) { return a->frequency < b->frequency; });

        huffmanNodes.insert(position, newNode);
    }

    return huffmanNodes;
}

void generateHuffmanCodes(Node *root, const std::string &code, std::unordered_map<char, std::string> &huffmanCodes) {
    if (!root)
        return;

    if (root->symbol != '\0') {
        huffmanCodes[root->symbol] = code;
        root->code = code;
        std::cout << "Символ: " << root->symbol << " его код: " << root->code << std::endl;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

std::vector<Node *> readFileAndCreateNodes(const std::string &filename) {
    std::ifstream file(filename);
    std::unordered_map<char, int> frequencyMap;

    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            for (char ch: line)
                frequencyMap[ch]++;
        }
        file.close();
    } else {
        std::cerr << "файл не открылся, баран... " << filename << std::endl;
        exit(1);
    }

    std::vector<Node *> nodes;
    for (const auto &pair: frequencyMap)
        nodes.push_back(new Node(pair.first, pair.second));
    sort(nodes.begin(), nodes.end(), [](Node *a, Node *b) { return a->frequency < b->frequency; });

    return nodes;
}

