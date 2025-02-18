#include "Huffman.h"
#include <iostream>
bool comp(NODE* a, NODE* b) {
    return a->freq < b->freq;
}