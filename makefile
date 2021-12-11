all: huffencode huffdecode

clean:
	rm huffencode huffdecode

huffencode: huffencode.c huffman.h treeNode.h treeListNode.h treeList.c huffTree.c
	gcc -Wall -ansi -pedantic -o huffencode huffencode.c huffman.h treeNode.h treeListNode.h treeList.c huffTree.c

huffdecode: huffdecode.c huffman.h treeNode.h treeListNode.h treeList.c huffTree.c
	gcc -Wall -ansi -pedantic -o huffdecode huffdecode.c huffman.h treeNode.h treeListNode.h treeList.c huffTree.c

