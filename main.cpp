#include "Huffman.h"
#include <iostream>
#include <unordered_map>

int main() {
    system("chcp 65001");
    std::string inputFilename;
    std::cout << "Типочек, ну ка файлик дай:  ";
    std::cin >> inputFilename;

    std::vector<Node *> nodes = readFileAndCreateNodes(inputFilename);

    auto huffmanTree = buildHuffmanTree(nodes);
    std::unordered_map<char, std::string> huffmanCodes;

    if (!huffmanTree.empty()) {
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes);
    }

    std::cout << "\nКоды из хеш-таблицы:\n";
    for (const auto &pair: huffmanCodes) {
        std::cout << "Символ:" << pair.first << " его код: " << pair.second << std::endl;
    }


    for (Node *node: nodes) {
        delete node;
    }

    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    return 0;
}
