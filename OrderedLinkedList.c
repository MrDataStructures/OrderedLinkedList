#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    long x;
    struct node* next;
}node;

node* delete(node* head, long num){
    node* current = head;
    if(head == NULL)
        return head;
    if(head->x == num){
        node * new_head = head->next;
        free(head);
        return new_head;
    }
    while(current->next != NULL && current->next->x != num)
        current = current->next;

    if(current->next == NULL)
        return head;
    else{
        node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    return head;
}

node * insert(node* head, long num){
    if(head != NULL && head->x == num) return head;
    node* new_node = malloc(sizeof(node));
    new_node->x = num;
    new_node->next = NULL;
    
    if(head == NULL || head->x > num) {
        new_node->next = head;
        head = new_node;
        return head;
    }
    node* current = head;
    while(current->next != NULL && current->next->x < num)
        current = current->next;
    if(current->next != NULL && current->next->x == num){
        free(new_node);
        return head;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    return head;
}

void traverse(node* root){ // traverse through the linked list and print out each long
    if(root != NULL){
        for(node* printing = root; printing != NULL; printing = printing->next)
            printf("%li ", printing->x);
    }
    else printf("EMPTY");
    printf("\n");
}

char INSERT[] = "INSERT";

int main(int argc, char* argv[argc+1]){
    long num;
    char word[7];
    
    FILE * fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("error\n");
        return 1;
    }
    else{ 
        node* first = NULL;
        while(fscanf(fp, "%s%li\n", word, &num) != EOF){
            if(strcmp(word, INSERT) == 0)
                first = insert(first, num);
            else
                first = delete(first, num);
            traverse(first);
        }
        node* next = NULL;
        while(first != NULL){
            next = first->next;
            free(first);
	        first = next;
        }
        fclose(fp);
    }
    return 0;
}
