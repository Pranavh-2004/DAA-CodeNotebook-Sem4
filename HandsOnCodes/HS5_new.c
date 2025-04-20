/*
Problem 1 – Job Requests
In the futuristic city of Byteburg, the government maintains a Digital Archive System to store
classified records efficiently. The system follows a B-tree of order 3 to keep the records
structured, ensuring fast insertion, retrieval, and balancing.
However, a recent system failure corrupted the archive, and Chief Engineer Nova needs your
help to restore its functionality.
Your task is to implement the Digital Archive System with the following capabilities:
1. Add a record (insert a key) – Each record is assigned a unique numeric ID (a positive
integer). You must insert these IDs into the archive while maintaining the B-tree
structure.
2. Display the archive structure – Show how records are organized in the B-tree using an
indented format to represent levels in the tree.
3. Search for a record – Given a record ID, determine whether it exists in the archive and
print an appropriate message.
A B-tree of order 3 (B(3) tree) is a balanced search tree with the following properties:
● Each node can store a maximum of 2 keys (since order = 3).
● Each node can have at most 3 children.
● The tree remains balanced—all leaf nodes are at the same level.
● When a node exceeds its limit, it splits, pushing a key to the parent node.
Input Format- An integer N – The number of records to be inserted.
N space-separated integers – The record IDs to insert in order
An integer Q – The record ID to search.

Output Format- N space-separated integers – The record IDs to inserted in order
Boolean true or false - If search ID is found
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 2
#define TEMP_KEYS 3

typedef struct BTreeNode
{
    int keys[TEMP_KEYS];
    struct BTreeNode *children[TEMP_KEYS + 1];
    int num_keys;
    int is_leaf;
} BTreeNode;

typedef struct
{
    BTreeNode *root;
} BTree;

// Function prototypes
BTreeNode *create_node(int is_leaf);
void insert(BTree *tree, int key);
int insert_internal(BTreeNode *node, int key, int *up_key, BTreeNode **new_right);
int search(BTreeNode *node, int key);
void inorder_traversal(BTreeNode *node);
void display_tree(BTreeNode *node, int level);
void free_tree(BTreeNode *node);

BTreeNode *create_node(int is_leaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (!node)
    {
        perror("Failed to create node");
        exit(EXIT_FAILURE);
    }

    node->is_leaf = is_leaf;
    node->num_keys = 0;

    for (int i = 0; i < TEMP_KEYS + 1; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}

void insert(BTree *tree, int key)
{
    int up_key;
    BTreeNode *new_right = NULL;

    int split = insert_internal(tree->root, key, &up_key, &new_right);

    if (split)
    {
        BTreeNode *new_root = create_node(0);
        new_root->keys[0] = up_key;
        new_root->children[0] = tree->root;
        new_root->children[1] = new_right;
        new_root->num_keys = 1;
        tree->root = new_root;
    }
}

int insert_internal(BTreeNode *node, int key, int *up_key, BTreeNode **new_right)
{
    int pos = 0;

    while (pos < node->num_keys && key > node->keys[pos])
    {
        pos++;
    }

    if (node->is_leaf)
    {
        for (int j = node->num_keys; j > pos; j--)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[pos] = key;
        node->num_keys++;

        if (node->num_keys <= MAX_KEYS)
        {
            return 0;
        }

        *up_key = node->keys[1];
        *new_right = create_node(1);
        (*new_right)->keys[0] = node->keys[2];
        (*new_right)->num_keys = 1;

        node->num_keys = 1;
        return 1;
    }
    else
    {
        int split_child = insert_internal(node->children[pos], key, up_key, new_right);
        if (!split_child)
        {
            return 0;
        }

        for (int j = node->num_keys; j > pos; j--)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[pos] = *up_key;

        for (int j = node->num_keys + 1; j > pos + 1; j--)
        {
            node->children[j] = node->children[j - 1];
        }
        node->children[pos + 1] = *new_right;
        node->num_keys++;

        if (node->num_keys <= MAX_KEYS)
        {
            return 0;
        }

        *up_key = node->keys[1];
        *new_right = create_node(0);
        (*new_right)->keys[0] = node->keys[2];
        (*new_right)->num_keys = 1;

        (*new_right)->children[0] = node->children[2];
        (*new_right)->children[1] = node->children[3];

        node->num_keys = 1; // Left node now has one key
        return 1;           // Split occurred
    }
}

// Search for a key in the B-tree
int search(BTreeNode *node, int key)
{
    int i = 0;
    while (i < node->num_keys && key > node->keys[i])
    {
        i++;
    }

    if (i < node->num_keys && key == node->keys[i])
    {
        return 1; // Key found
    }

    if (node->is_leaf)
    {
        return 0; // Key not found
    }

    return search(node->children[i], key); // Recursively search in the child
}

// In-order traversal of the B-tree
void inorder_traversal(BTreeNode *node)
{
    if (node->is_leaf)
    {
        for (int i = 0; i < node->num_keys; i++)
        {
            printf("%d ", node->keys[i]);
        }
    }
    else
    {
        for (int i = 0; i < node->num_keys; i++)
        {
            inorder_traversal(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        inorder_traversal(node->children[node->num_keys]);
    }
}

// Display the B-tree structure
void display_tree(BTreeNode *node, int level)
{
    if (node == NULL)
    {
        return;
    }

    // Print the keys of the current node
    for (int i = 0; i < level; i++)
    {
        printf("    "); // Indent based on the level
    }
    printf("Level %d: ", level);
    for (int i = 0; i < node->num_keys; i++)
    {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    // Recursively display the children
    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            display_tree(node->children[i], level + 1);
        }
    }
}

// Free the memory allocated for the B-tree
void free_tree(BTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            free_tree(node->children[i]);
        }
    }

    free(node);
}

int main()
{
    BTree tree;
    tree.root = create_node(1); // Create an empty B-tree with a leaf root

    int N;
    printf("Enter the number of records: ");
    if (scanf("%d", &N) != 1)
    {
        printf("Error reading number of records.\n");
        return 1;
    }

    printf("Enter %d record IDs (space separated): ", N);
    for (int i = 0; i < N; i++)
    {
        int key;
        scanf("%d", &key);
        insert(&tree, key);
    }

    int search_id;
    printf("Enter the record ID to search: ");
    scanf("%d", &search_id);

    printf("\nB-tree structure:\n");
    display_tree(tree.root, 0);

    printf("\nIn-order traversal (sorted records): ");
    inorder_traversal(tree.root);
    printf("\n");

    if (search(tree.root, search_id))
    {
        printf("\nRecord %d found: true\n", search_id);
    }
    else
    {
        printf("\nRecord %d not found: false\n", search_id);
    }

    // Free the allocated memory
    free_tree(tree.root);

    return 0;
}