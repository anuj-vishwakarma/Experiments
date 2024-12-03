#include <stdio.h>
#include <stdint.h> // for uintptr_t


struct Node {
    int packedData;  // This integer will store both data (in the lower 3 bits) and the pointer (in the upper 29 bits)
};
void traverseList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        int data = current->packedData & 0b111;  
        struct Node* nextNode = (struct Node*)(current->packedData >> 3);
        
        printf("Data: %d, Next Node Address: %p\n", data, nextNode);
        current = nextNode;
    }
}
int main() {
    // Defining three Node variables to simulate a 3-node linked list
    struct Node node1, node2, node3;  

    // Encoding data '1' and pointer to node2 into packedData of node1 as:
    // (1 & 0b111) this is '1' in binary, now
    // (uintptr_t)(&node2) address of the node
    // to create space to store data and variable both we'll shift it by 3(because for now our data could atmost 7)
    // (uintptr_t)(&node2) << 3 

    // 0 0 0 0 0  <0 0 1>  
    // <1 0 1 1 0> 0 0 0 
    // Now we need to take bitwise OR to store it in single variable: 
    // so, (1 & 0b111) | ((uintptr_t)&node2 << 3) and store it back to node1.packedData

    node1.packedData = (1 & 0b111) | ((uintptr_t)&node2 << 3); 
    node2.packedData = (2 & 0b111) | ((uintptr_t)&node3 << 3); 
    node3.packedData = (3 & 0b111) | ((uintptr_t)NULL << 3);    

    // Step 3: Print the data and pointer information for each node
    // Decode and print the data and pointer from node1

    // printf("Node 1 - Data: %d, Next Node Address: %p\n", node1.packedData & 0b111, (struct Node*)(node1.packedData >> 3));

    // // Decode and print the data and pointer from node2
    // printf("Node 2 - Data: %d, Next Node Address: %p\n", node2.packedData & 0b111, (struct Node*)(node2.packedData >> 3));

    // // Decode and print the data and pointer from node3
    // printf("Node 3 - Data: %d, Next Node Address: %p\n", node3.packedData & 0b111, (struct Node*)(node3.packedData >> 3));

    traverseList(&node1);
   

    // printf("%d", sizeof(uintptr_t));
    // printf("%d", sizeof(int));
    return 0;
}

