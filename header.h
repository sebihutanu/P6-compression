#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grid{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}TGrid;

typedef struct node{
    TGrid grid;
    unsigned char type;
    struct node *upper_left, *upper_right, *lower_left, *lower_right;
}TNode, *TArb;

typedef struct queue_node {
    TArb data;
    struct queue_node* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct node_adress_queue_node {
    TArb* data;
    struct node_adress_queue_node* next;
}NodeAdressQueueNode;

typedef struct{
    NodeAdressQueueNode* front;
    NodeAdressQueueNode* rear;
}NodeAdressQueue;

TGrid** readFile(FILE* file, unsigned int* size);
void freeMatrix(TGrid** matrix, unsigned int size);
void printMatrix(TGrid** matrix, unsigned int size);
long long int calculateRED(int line, int column, int size, TGrid** matrix);
long long int calculateGREEN(int line, int column, int size, TGrid** matrix);
long long int calculateBLUE(int line, int column, int size, TGrid** matrix);
long long int calculateMEAN(int line, int column, int size, TGrid** matrix);
void createCompressionTree(TGrid** matrix, int size, long long int meanFactor, TArb compression_tree, int line, int column, int* aux, int *aux2);
TNode* alocaArbore();
TNode* alocaNod();
int nrNiveluri(TArb arbore);
void freeCompressionTree(TArb compression_tree);
void enqueue(Queue* q, TArb data);
TArb dequeue(Queue* q);
void enqueueAdressNodes(NodeAdressQueue* q, TArb* data);
TArb* dequeueAdressNodes(NodeAdressQueue* q);
void printBFS(TArb root, FILE* out);
TGrid** decompress(TArb compression_tree, TGrid** matrix, unsigned int size, int line, int column);
void task1(char* input, char* output, long long int mean);
void task2(char* input, char* output2, long long int mean);
void task3(char* input, char* output);
void printLevelOrder(TArb root);
