#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"
#include "myutils.h"


int main(){

    BTree* tree = create_btree();

    insert(tree, 10, "Pratham");
    insert(tree, 5, "Ridin");
    insert(tree, 20, "Rahul");
    insert(tree, 2, "Hardik");
    insert(tree, 3, "Burhan");
    insert(tree, 12, "Yash");
    insert(tree, 17, "Divyansh");
    insert(tree, 30, "Shivam");

    printf("Hello, ewlcome to B Tree!\n");
    printf("What operation would you like to perform?\n");
    int choice;
    while (true) {
        printf("Enter your choice: \n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Traversal\n");
        printf("5. Exit\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Insert operation selected.\n");
                int x;
                char s[100];
                printf("Enter key: ");
                scanf("%d", &x);
                printf("\nEnter name: ");
                scanf("%s", s);
                insert(tree, x, s);
                level_order_traversal(tree->root);
                break;
            case 2:
                printf("enter the key you want to delete: ");
                int del;
                scanf("%d", &del);
                delete_key(tree->root, del);
                level_order_traversal(tree->root);
                break;
            case 3:
                printf("enter a key to search: ");
                int key;
                scanf("%d", &key);
                printf("Found: %s\n", search(tree, key));
                break;
            case 4:
                printf("Level order traversal:\n");
                level_order_traversal(tree->root);
                break;
            case 5:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}