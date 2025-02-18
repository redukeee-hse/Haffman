#ifndef HUFFMAN_H
#define HUFFMAN_H


#define CODE_SIZE   8
typedef struct Node
{
    bool isSymbol;
	char symbol;
    char code[CODE_SIZE];
	int freq;
	struct Node* left;
    struct Node* right;
    struct Node* parent;

}NODE;



#endif // HUFFMAN_H