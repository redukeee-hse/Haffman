#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm>

struct Node {
    char symbol;       // Символ
    int frequency;     // Частота
    Node* left;
    Node* right;

    Node(char s, int freq) : symbol(s), frequency(freq), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева Хаффмана
std::vector<Node*> buildHuffmanTree(std::vector<Node*>& nodes) {
    // Проверяем, есть ли узлы для дальнейшей обработки
    if (nodes.empty()) {
        return {}; // Возврат пустого вектора, если узлы отсутствуют
    }

    // Мы будем работать с узлами, добавляя новые до получения итогового дерева
    std::vector<Node*> huffmanNodes = nodes; // Копируем исходные узлы

    // Продолжать объединять узлы, пока вектора не останутся менее 2
    while (huffmanNodes.size() > 1) {
        // Слияние двух узлов с наименьшей частотой
        Node* left = huffmanNodes[0]; // Наименьший узел
        Node* right = huffmanNodes[1]; // Второй наименьший узел

        // Создаем новый узел, который будет родителем
        Node* newNode = new Node('\0', left->frequency + right->frequency); // Новый узел без символа
        newNode->left = left;
        newNode->right = right;

        // Удаляем объединенные узлы из вектора
        huffmanNodes.erase(huffmanNodes.begin(), huffmanNodes.begin() + 2);

        // Вставляем новый узел в подходящее место, чтобы сохранить сортировку
        auto position = std::lower_bound(huffmanNodes.begin(), huffmanNodes.end(), newNode,
                                         [](Node* a, Node* b) { return a->frequency < b->frequency; });

        huffmanNodes.insert(position, newNode); // Вставляем новый узел в отсортированный вектор
    }

    // Вернем полученный вектор узлов, содержащий только корневой узел Хаффмана
    return huffmanNodes;
}

// Функция для генерации кодов Хаффмана
void generateHuffmanCodes(Node* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root) return;

    // Если узел является листом (символ)
    if (root->symbol != '\0') {
        huffmanCodes[root->symbol] = code; // Сохраняем код в хеш-карту
        std::cout << "Символ: '" << root->symbol << "' имеет код: " << code << std::endl; // Выводим код символа на экран
    }

    // Рекурсивно обрабатываем левое и правое поддеревья
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Функция для чтения содержимого файла и создания узлов
std::vector<Node*> readFileAndCreateNodes(const std::string& filename) {
    std::ifstream file(filename);
    std::unordered_map<char, int> frequencyMap;

    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            for (char ch : line) {
                if (ch != '\n') { // Исключаем символ новой строки
                    frequencyMap[ch]++;
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        exit(1); // Выход при ошибке открытия файла
    }

    // Создаем узлы на основе частот символов
    std::vector<Node*> nodes;
    for (const auto& pair : frequencyMap) {
        nodes.push_back(new Node(pair.first, pair.second)); // Создаем узлы для каждого символа
    }

    // Сортируем узлы по частоте
    std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->frequency < b->frequency;
    });

    return nodes; // Возвращаем вектор узлов
}

int main() {
    system("chcp 65001"); //  Для вывода русских символов
    std::string inputFilename;
    std::cout << "Введите имя файла для чтения: ";
    std::cin >> inputFilename;

    // Считываем содержимое файла и создаем отсортированный вектор узлов
    std::vector<Node*> nodes = readFileAndCreateNodes(inputFilename);


    // Строим дерево Хаффмана
    auto huffmanTree = buildHuffmanTree(nodes);

    // Хеш-карта для хранения кодов символов
    std::unordered_map<char, std::string> huffmanCodes;

    // Генерация и вывод кодов Хаффмана
    if (!huffmanTree.empty()) {
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes); // Используем последний узел как корень
    }

    // Дополнительно выводим коды из хеш-карты
    std::cout << "\nКоды из хеш-карты:\n";
    for (const auto& pair : huffmanCodes) {
        std::cout << "Символ: '" << pair.first << "' имеет код: " << pair.second << std::endl;
    }

    // Освобождение памяти
    for (Node* node : nodes) {
        delete node; // Освобождаем память для узлов
    }

    // Освобождаем память для корневого узла дерева
    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    return 0;
}
