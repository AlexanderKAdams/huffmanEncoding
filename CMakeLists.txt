cmake_minimum_required(VERSION 3.20)
project(huffmanEncoding C)

set(CMAKE_C_STANDARD 90)

add_executable(huffmanEncode huffencode.c huffman.h treeNode.h listNode.h linkedList.c huffTree.c)
add_executable(huffmanDecode huffdecode.c huffman.h treeNode.h listNode.h linkedList.c huffTree.c)