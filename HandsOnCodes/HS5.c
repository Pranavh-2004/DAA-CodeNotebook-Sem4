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
// Temporary capacity for keys while spiltting
#define TEMP_KEYS 3

typedef struct BTreeNode
{
    int keys[TEMP_KEYS];
    struct BTreeNode *children[TEMP_KEYS + 1];
    int num_keys;
    int leaf;
} BTreeNode;

typedef struct
{
    BTreeNode *root;
} BTree;

BTreeNode *createNode(int leaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->num_keys = 0;

    for (int i = 0; i < TEMP_KEYS + 1; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

int insertInternal(BTreeNode *node, int key, int *upKey, BTreeNode **newRight)
{
    int pos = 0;
    while (pos < node->num_keys && key > node->keys[pos])
        pos++;

    if (node->leaf)
    {
        for (int j = node->num_keys; j > pos; j--)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[pos] = key;
        node->num_keys++;

        if (node->num_keys <= MAX_KEYS)
            return 0;

        *upKey = node->keys[1];

        BTreeNode *rightNode = createNode(1);
        rightNode->keys[0] = node->keys[2];
        rightNode->num_keys = 1;

        node->num_keys = 1;

        *newRight = rightNode;
        return 1;
    }
    else
    {
        int splitChild = insertInternal(node->children[pos], key, upKey, newRight);
        if (!splitChild)
            return 0;

        for (int j = node->num_keys; j > pos; j--)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[pos] = *upKey;

        for (int j = node->num_keys + 1; j > pos + 1; j--)
        {
            node->children[j] = node->children[j - 1];
        }
        node->children[pos + 1] = *newRight;
        node->num_keys++;

        if (node->num_keys <= MAX_KEYS)
            return 0;

        *upKey = node->keys[1];

        BTreeNode *rightNode = createNode(0);

        rightNode->keys[0] = node->keys[2];
        rightNode->num_keys = 1;

        rightNode->children[0] = node->children[2];
        rightNode->children[1] = node->children[3];

        node->num_keys = 1;

        *newRight = rightNode;
        return 1;
    }
}

void insert(BTree *tree, int key)
{
    int upKey;
    BTreeNode *newRight = NULL;
    int split = insertInternal(tree->root, key, &upKey, &newRight);
    if (split)
    {
        BTreeNode *newRoot = createNode(0);
        newRoot->keys[0] = upKey;
        newRoot->children[0] = tree->root;
        newRoot->children[1] = newRight;
        newRoot->num_keys = 1;
        tree->root = newRoot;
    }
}

int search(BTreeNode *node, int key)
{
    int i = 0;
    while (i < node->num_keys && key > node->keys[i])
        i++;
    if (i < node->num_keys && key == node->keys[i])
        return 1;
    if (node->leaf)
        return 0;
    return search(node->children[i], key);
}

void inorderTraversal(BTreeNode *node)
{
    if (node->leaf)
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
            inorderTraversal(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        inorderTraversal(node->children[node->num_keys]);
    }
}

void display(BTreeNode *node, int level)
{
    if (node == NULL)
        return;
    for (int i = 0; i < level; i++)
        printf("   ");
    printf("Level %d: ", level);
    for (int i = 0; i < node->num_keys; i++)
        printf("%d ", node->keys[i]);
    printf("\n");
    if (!node->leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            display(node->children[i], level + 1);
        }
    }
}

int main()
{
    int N;

    printf("Enter the number of records: ");
    if (scanf("%d", &N) != 1)
    {
        printf("Error reading number of records.\n");
        return 1;
    }

    BTree tree;
    tree.root = createNode(1);

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

    printf("\nArchive structure:\n");
    display(tree.root, 0);

    printf("\nIn-order traversal (sorted records): ");
    inorderTraversal(tree.root);
    printf("\n");

    if (search(tree.root, search_id))
        printf("\nRecord %d found: true\n", search_id);
    else
        printf("\nRecord %d not found: false\n", search_id);

    return 0;
}