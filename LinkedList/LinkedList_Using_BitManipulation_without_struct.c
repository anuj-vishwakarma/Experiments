#include <stdio.h>
#include <stdint.h> // for uintptr_t

int main() {
    int node1_packedData, node2_packedData, node3_packedData;

    // Node1: We store data '1' and pointer to node2 in packedData of node1
    // (1 & 0b111) is '1' in binary, this gives us the lower 3 bits for data
    // ((uintptr_t)&node2 << 3) shifts the address of node2 by 3 bits to create space
    // for the data (since the data can be at most 7, which requires 3 bits)
    node1_packedData = (1 & 0b111) | ((uintptr_t)&node2_packedData << 3); 
    
    // Node2: We store data '2' and pointer to node3 in packedData of node2
    node2_packedData = (2 & 0b111) | ((uintptr_t)&node3_packedData << 3); 
    
    // Node3: We store data '3' and pointer NULL (0) in packedData of node3
    node3_packedData = (3 & 0b111) | ((uintptr_t)NULL << 3);    
    
    int* current = &node1_packedData;

    while (current != NULL) {
        int data = *current & 0b111;
        int* nextNode = (int*)((*current) >> 3);
        printf("Data: %d, Next Node Address: %p\n", data, nextNode);
        current = nextNode; 
    }

    return 0;
}
