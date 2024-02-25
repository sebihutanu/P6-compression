#include "header.h"

TNode* alocaArbore(){
    TNode* arbore = (TNode*)malloc(sizeof(TNode));
    arbore->grid.blue = 0;
    arbore->grid.green = 0;
    arbore->grid.red = 0;
    arbore->type = 0;
    arbore->lower_left = NULL;
    arbore->lower_right = NULL;
    arbore->upper_left = NULL;
    arbore->upper_right = NULL;
    return arbore;
}

TNode* alocaNod() {
    TNode* nod = (TNode*)malloc(sizeof(TNode));
    nod->grid.blue = 0;
    nod->grid.green = 0;
    nod->grid.red = 0;
    nod->type = 0;
    nod->lower_left = NULL;
    nod->lower_right = NULL;
    nod->upper_left = NULL;
    nod->upper_right = NULL;
    return nod;
}

TNode* alocaNodIntern(){
    TNode* nod_intern = (TNode*)malloc(sizeof(TNode));
    nod_intern->grid.blue = 0;
    nod_intern->grid.green = 0;
    nod_intern->grid.red = 0;
    nod_intern->type = 0;
    nod_intern->lower_left = NULL;
    nod_intern->lower_right = NULL;
    nod_intern->upper_left = NULL;
    nod_intern->upper_right = NULL;
    return nod_intern;
}

TNode* alocaFrunza(unsigned char red, unsigned char green, unsigned char blue) {
    TNode* frunza = (TNode*)malloc(sizeof(TNode));
    frunza->grid.red = red;
    frunza->grid.green = green;
    frunza->grid.blue = blue;
    frunza->type = 1;
    frunza->lower_left = NULL;
    frunza->lower_right = NULL;
    frunza->upper_left = NULL;
    frunza->upper_right = NULL;
    return frunza;
}

TGrid** readFile(FILE* file, unsigned int* size) {
    char img_type[3];
    unsigned int useless;
    fscanf(file, "%s\n", img_type);
    img_type[2] = '\0';
    fscanf(file, "%u %u\n", size, &useless);
    fscanf(file, "%u\n", &useless);
    TGrid** matrix = (TGrid**)malloc(sizeof(TGrid*) * *(size));
    for(int i = 0; i < *(size); i++) {
        matrix[i] = malloc(sizeof(TGrid) * *(size));
    }
    if(matrix == NULL) exit(-1);
    for(int i = 0; i < *(size); i++) {
        for(int j = 0; j < *(size); j++) {
            fread(&matrix[i][j].red, sizeof(unsigned char), 1, file);
            fread(&matrix[i][j].green, sizeof(unsigned char), 1, file);
            fread(&matrix[i][j].blue, sizeof(unsigned char), 1, file);
        }
    }
    return matrix;
}

void freeMatrix(TGrid** matrix, unsigned int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(TGrid** matrix, unsigned int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("{%u %u %u} ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
        }
        printf("\n");
    }
}

long long int calculateRED(int line, int column, int size, TGrid** matrix) {
    long long int red = 0;
    for(int i = line; i < line + size; i++) {
        for(int j = column; j < column + size; j++) {
            red = red + matrix[i][j].red;
        }
    }
    red =  red / (size * size);
    return red;
}

long long int calculateGREEN(int line, int column, int size, TGrid** matrix) {
    long long int green = 0;
    for(int i = line; i < line + size; i++) {
        for(int j = column; j < column + size; j++) {
            green = green + matrix[i][j].green;
        }
    }
    green = green / (size * size);
    return green;
}

long long int calculateBLUE(int line, int column, int size, TGrid** matrix) {
    long long int blue = 0;
    for(int i = line; i < line + size; i++) {
        for(int j = column; j < column + size; j++) {
            blue = blue + matrix[i][j].blue;
        }
    }
    blue = blue / (size * size);
    return blue;
}

long long int calculateMEAN(int line, int column, int size, TGrid** matrix) {
    long long int red = calculateRED(line, column, size, matrix);
    long long int green = calculateGREEN(line, column, size, matrix);
    long long int blue = calculateBLUE(line, column, size, matrix);
    long long int mean = 0;
    for(int i = line; i < line + size; i++) {
        for(int j = column; j < column + size; j++) {
            mean = mean +
                   (red - (long long int)matrix[i][j].red) * (red - (long long int)matrix[i][j].red) +
                   (green - (long long int)matrix[i][j].green) * (green - (long long int)matrix[i][j].green) + 
                   (blue - (long long int)matrix[i][j].blue) * (blue - (long long int)matrix[i][j].blue);
        }
    }
    mean = mean / (3 * size * size);
    return mean;
}

void createCompressionTree(TGrid** matrix, int size, long long int meanFactor, TArb compression_tree, int line, int column, int *aux, int *aux2) {
    long long int mean = calculateMEAN(line, column, size, matrix);

    if (size == 1) {
        compression_tree->grid.red = matrix[line][column].red;
        compression_tree->grid.green = matrix[line][column].green;
        compression_tree->grid.blue = matrix[line][column].blue;
        compression_tree->type = 1;
        compression_tree->lower_left = NULL;
        compression_tree->lower_right = NULL;
        compression_tree->upper_left = NULL;
        compression_tree->upper_right = NULL;
        (*aux)++;
        if(size > (*aux2)) (*aux2) = size;
    } else if (mean <= meanFactor) {
        if(size > (*aux2)) (*aux2) = size;
        (*aux)++;
        compression_tree->grid.red = (unsigned char)calculateRED(line, column, size, matrix);
        compression_tree->grid.green = (unsigned char)calculateGREEN(line, column, size, matrix);
        compression_tree->grid.blue = (unsigned char)calculateBLUE(line, column, size, matrix);
        compression_tree->type = 1;
        compression_tree->lower_left = NULL;
        compression_tree->lower_right = NULL;
        compression_tree->upper_left = NULL;
        compression_tree->upper_right = NULL;
    } else {
        compression_tree->lower_left = alocaNod();
        compression_tree->lower_right = alocaNod();
        compression_tree->upper_left = alocaNod();
        compression_tree->upper_right = alocaNod();
        createCompressionTree(matrix, size / 2, meanFactor, compression_tree->upper_left, line, column, aux, aux2);
        createCompressionTree(matrix, size / 2, meanFactor, compression_tree->upper_right, line, column + size / 2, aux, aux2);
        createCompressionTree(matrix, size / 2, meanFactor, compression_tree->lower_right, line + size / 2, column + size / 2, aux, aux2);
        createCompressionTree(matrix, size / 2, meanFactor, compression_tree->lower_left, line + size / 2, column, aux, aux2);
    }
}

int nrNiveluri(TArb compression_tree) {
    if(!compression_tree) return 0;
    int max = 0;
    int aux = 0;
    aux = nrNiveluri(compression_tree->upper_left);
    if(aux > max) max = aux;
    aux = nrNiveluri(compression_tree->upper_right);
    if(aux > max) max = aux;
    aux = nrNiveluri(compression_tree->lower_left);
    if(aux > max) max = aux;
    aux = nrNiveluri(compression_tree->lower_right);
    if(aux > max) max = aux;
    return max + 1;
}

void freeCompressionTree(TArb compression_tree) {
    if (compression_tree == NULL) {
        return;
    }
    
    freeCompressionTree(compression_tree->upper_left);
    freeCompressionTree(compression_tree->upper_right);
    freeCompressionTree(compression_tree->lower_left);
    freeCompressionTree(compression_tree->lower_right);
    
    free(compression_tree);
}

void task1(char* input, char* output, long long int mean) {
    long long int meanFactor = mean;
    FILE* in = fopen(input, "rb");
    FILE* out = fopen(output, "wb");
    unsigned int size = 30;
    int nrBlocuriCol = 0;
    int aux2 = 1;
    TGrid** matrix = readFile(in, &size);
    TArb compression_tree = alocaArbore();
    createCompressionTree(matrix, size, meanFactor, compression_tree, 0, 0, &nrBlocuriCol, &aux2);
    freeMatrix(matrix, size);
    int nrNivel = nrNiveluri(compression_tree);
    fprintf(out, "%d\n%d\n%d\n", nrNivel, nrBlocuriCol, aux2);
    freeCompressionTree(compression_tree);
    fclose(out);
    fclose(in);
}

void enqueue(Queue* q, TArb data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

void enqueueAdressNodes(NodeAdressQueue* q, TArb* data) {
    NodeAdressQueueNode* newNode = (NodeAdressQueueNode*)malloc(sizeof(NodeAdressQueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

TArb dequeue(Queue* q) {
    if (q->front == NULL)
        return NULL;

    TArb data = q->front->data;
    QueueNode* temp = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return data;
}

TArb* dequeueAdressNodes(NodeAdressQueue* q) {
    if(q->front == NULL) return NULL;

    TArb* data = q->front->data;
    NodeAdressQueueNode* temp = q->front;

    q->front = q->front->next;

    if(q->front == NULL) q->rear = NULL;
    
    free(temp);
    return data;
}

void printBFS(TArb root, FILE* out) {
    if (root == NULL)
        return;

    Queue queue;
    queue.front = queue.rear = NULL;
    enqueue(&queue, root);

    while (queue.front != NULL) {
        TArb node = dequeue(&queue);
        if(node->type == 1) {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
            fwrite(&node->grid.red, sizeof(unsigned char), 1, out);
            fwrite(&node->grid.green, sizeof(unsigned char), 1, out);
            fwrite(&node->grid.blue, sizeof(unsigned char), 1, out);
        } else if(node->type == 0) {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
        }
        if (node->upper_left != NULL)
            enqueue(&queue, node->upper_left);
        if (node->upper_right != NULL)
            enqueue(&queue, node->upper_right);
        if (node->lower_left != NULL)
            enqueue(&queue, node->lower_right);
        if (node->lower_right != NULL)
            enqueue(&queue, node->lower_left);
    }
}



void task2(char* input, char* output2, long long int mean) {
    long long int meanFactor = mean;
    FILE* in = fopen(input, "rb");
    FILE* out2 = fopen(output2, "wb");
    unsigned int size = 30;
    int nrBlocuriCol = 0;
    int aux2 = 1;
    TGrid** matrix = readFile(in, &size);
    TArb compression_tree = alocaArbore();
    createCompressionTree(matrix, size, meanFactor, compression_tree, 0, 0, &nrBlocuriCol, &aux2);
    freeMatrix(matrix, size);
    fwrite(&size, sizeof(unsigned int), 1, out2);
    printBFS(compression_tree, out2);
    freeCompressionTree(compression_tree);
    fclose(out2);
    fclose(in);
}

TGrid** decompress(TArb compression_tree, TGrid** matrix, unsigned int size, int line, int column) {
    if(compression_tree->type == 1) {
        for(int i = line; i < line + size; i++) {
            for(int j = column; j < column + size; j++) {
                matrix[i][j].red = compression_tree->grid.red;
                matrix[i][j].green = compression_tree->grid.green;
                matrix[i][j].blue = compression_tree->grid.blue;
            }
        }
    } else {
        decompress(compression_tree->upper_left, matrix, size / 2, line, column);
        decompress(compression_tree->upper_right, matrix, size / 2, line, column + size / 2);
        decompress(compression_tree->lower_right, matrix, size / 2, line + size / 2, column + size / 2);
        decompress(compression_tree->lower_left, matrix, size / 2, line + size / 2, column);
    }
    return matrix;
}

void printLevelOrder(TArb root) {
    if (root == NULL) {
        return;
    }

    Queue queue;
    queue.front = queue.rear = NULL;
    enqueue(&queue, root);

    while (queue.front != NULL && queue.rear != NULL) {
        TArb node = dequeue(&queue);

        if(node->type == 0) printf("0\n");
        else printf("%u (%u, %u, %u)\n", node->type, node->grid.red, node->grid.green, node->grid.blue);

        if (node->upper_left != NULL) {
            enqueue(&queue, node->upper_left);
        }
        if (node->upper_right != NULL) {
            enqueue(&queue, node->upper_right);
        }
        if (node->lower_left != NULL) {
            enqueue(&queue, node->lower_left);
        }
        if (node->lower_right != NULL) {
            enqueue(&queue, node->lower_right);
        }
    }
}

void task3(char* input, char* output){
    FILE* in = fopen(input, "rb");
    FILE* out = fopen(output, "wb");
    unsigned int size = 0;
    fread(&size, sizeof(unsigned int), 1, in);
    fprintf(out, "P6\n");
    fprintf(out, "%u %u\n", size, size);
    fprintf(out, "255\n");
    unsigned char aux;
    fread(&aux, sizeof(unsigned char), 1, in);
    TArb compression_tree = alocaArbore();
    if(aux == 1) {
        fread(&compression_tree->grid.red, sizeof(unsigned char), 1, in);
        fread(&compression_tree->grid.green, sizeof(unsigned char), 1, in);
        fread(&compression_tree->grid.blue, sizeof(unsigned char), 1, in);
        compression_tree->type = aux;
        compression_tree->lower_left = NULL;
        compression_tree->lower_right = NULL;
        compression_tree->upper_left = NULL;
        compression_tree->upper_right = NULL;
    } else {
        NodeAdressQueue queue;
        queue.front = queue.rear = NULL;
        enqueueAdressNodes(&queue, &compression_tree);
        while(queue.front != NULL) {
            TArb* adress = dequeueAdressNodes(&queue);
            fread(&aux, sizeof(unsigned char), 1, in);
            if(aux == 0) {
                TNode* node = alocaNodIntern();
                (*adress)->upper_left = node;
                enqueueAdressNodes(&queue, &((*adress)->upper_left));
            } else {
                TNode* node = alocaNodIntern();
                node->type = 1;
                node->lower_left = NULL;
                node->lower_right = NULL;
                node->upper_left = NULL;
                node->upper_right = NULL;
                (*adress)->upper_left = node;
                fread(&(*adress)->upper_left->grid.red, sizeof(unsigned char), 1, in);
                fread(&(*adress)->upper_left->grid.green, sizeof(unsigned char), 1, in);
                fread(&(*adress)->upper_left->grid.blue, sizeof(unsigned char), 1, in);
            }
            fread(&aux, sizeof(unsigned char), 1, in);
            if(aux == 0) {
                TNode* node = alocaNodIntern();
                (*adress)->upper_right = node;
                enqueueAdressNodes(&queue, &((*adress)->upper_right));
            } else {
                TNode* node = alocaNodIntern();
                node->type = 1;
                node->lower_left = NULL;
                node->lower_right = NULL;
                node->upper_left = NULL;
                node->upper_right = NULL;
                (*adress)->upper_right = node;
                fread(&(*adress)->upper_right->grid.red, sizeof(unsigned char), 1, in);
                fread(&(*adress)->upper_right->grid.green, sizeof(unsigned char), 1, in);
                fread(&(*adress)->upper_right->grid.blue, sizeof(unsigned char), 1, in);
            }
            fread(&aux, sizeof(unsigned char), 1, in);
            if(aux == 0) {
                TNode* node = alocaNodIntern();
                (*adress)->lower_right = node;
                enqueueAdressNodes(&queue, &((*adress)->lower_right));
            } else {
                TNode* node = alocaNodIntern();
                node->type = 1;
                node->lower_left = NULL;
                node->lower_right = NULL;
                node->upper_left = NULL;
                node->upper_right = NULL;
                (*adress)->lower_right = node;
                fread(&(*adress)->lower_right->grid.red, sizeof(unsigned char), 1, in);
                fread(&(*adress)->lower_right->grid.green, sizeof(unsigned char), 1, in);
                fread(&(*adress)->lower_right->grid.blue, sizeof(unsigned char), 1, in);
            }
            fread(&aux, sizeof(unsigned char), 1, in);
            if(aux == 0) {
                TNode* node = alocaNodIntern();
                (*adress)->lower_left = node;
                enqueueAdressNodes(&queue, &((*adress)->lower_left));
            } else {
                TNode* node = alocaNodIntern();
                node->type = 1;
                node->lower_left = NULL;
                node->lower_right = NULL;
                node->upper_left = NULL;
                node->upper_right = NULL;
                (*adress)->lower_left = node;
                fread(&(*adress)->lower_left->grid.red, sizeof(unsigned char), 1, in);
                fread(&(*adress)->lower_left->grid.green, sizeof(unsigned char), 1, in);
                fread(&(*adress)->lower_left->grid.blue, sizeof(unsigned char), 1, in);
            }
        }
    }
    TGrid** matrix = (TGrid**)malloc(sizeof(TGrid*) * size);
    for(int i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(TGrid) * size);
    }
    matrix = decompress(compression_tree, matrix, size, 0, 0);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            fwrite(&matrix[i][j].red, sizeof(unsigned char), 1, out);
            fwrite(&matrix[i][j].green, sizeof(unsigned char), 1, out);
            fwrite(&matrix[i][j].blue, sizeof(unsigned char), 1, out);
        }
    }
    freeMatrix(matrix, size);
    freeCompressionTree(compression_tree);
    fclose(out);
    fclose(in);
}
