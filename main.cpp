#include "Huffman.h"
#include <chrono>
#include <time.h>

using namespace std;;
using namespace std::chrono;

int main() {
    system("chcp 65001");
    std::string inputFilename;
    std::cout << "Файл для чтения:  ";
    std::cin >> inputFilename;

    clock_t tStart = clock();

    std::vector<Node *> nodes = readFileAndCreateNodes(inputFilename);

    auto huffmanTree = buildHuffmanTree(nodes); // дерево Хаффмана на векторе
    std::unordered_map<char, std::string> huffmanCodes;

    if (!huffmanTree.empty()) {
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes); // символ - код
    }


    std::string compressedFilename = "compressed_output.bin"; // Имя файла для сжатых данных
    writeEncodedFile(inputFilename, huffmanCodes, compressedFilename);
    printf("Time taken to encode: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    std::string decodedOutput = "decoded" + inputFilename.substr(inputFilename.find_last_of('.'));

    printf("Time taken overall: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    decode(decodedOutput, compressedFilename);


    for (auto node: nodes) {
        delete node;
    }

    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    return 0;
}