#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct Node {
    char symbol;
    int frequency;
    std::string code;
    Node* left;
    Node* right;

    Node(char s, int freq) : symbol(s), frequency(freq), left(nullptr), right(nullptr) {}
};

std::vector<Node*> buildHuffmanTree(std::vector<Node*>& nodes);

void generateHuffmanCodes(Node* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes);

std::vector<Node*> readFileAndCreateNodes(const std::string& filename);

#endif // HUFFMAN_H
