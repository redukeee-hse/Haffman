#include "Huffman.h"
#include <iostream>


long int getFileLength(FILE* file)  
{  
    if (!file)   
    {  
        std::cout << "File can't be opened" << std::endl;  
        return -1; 
    }  

    fseek(file, 0, SEEK_END); // Перемещаем указатель в конец файла  
    long int length = ftell(file); // Получаем длину файла  
    fseek(file, 0, SEEK_SET); // Возвращаем указатель обратно на начало  

    return length;  
}  


bool comp(NODE* a, NODE* b) 
{
    return a->freq < b->freq;
}

