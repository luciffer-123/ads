
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define N 26

    typedef struct TrieNode TrieNode;

struct TrieNode
{

    char data;

    TrieNode *children[N];

    int is_leaf;
};

TrieNode *make_trie_node(char data)
{

    TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));

    for (int i = 0; i < N; i++)

        node->children[i] = NULL;

    node->is_leaf = 0;

    node->data = data;

    return node;
}

void free_trie_node(TrieNode *node)
{

    for (int i = 0; i < N; i++)
    {

        if (node->children[i] != NULL)
        {

            free_trie_node(node->children[i]);
        }
    }

    free(node);
}

TrieNode *insert_trie(TrieNode *root, char *word)
{

    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {

        int idx = (int)word[i] - 'a';

        if (temp->children[idx] == NULL)
        {

            temp->children[idx] = make_trie_node(word[i]);
        }

        temp = temp->children[idx];
    }

    temp->is_leaf = 1;

    return root;
}

int search_trie(TrieNode *root, char *word)
{

    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {

        int position = word[i] - 'a';

        if (temp->children[position] == NULL)

            return 0;

        temp = temp->children[position];
    }

    if (temp != NULL && temp->is_leaf == 1)

        return 1;

    return 0;
}

void delete_helper(TrieNode *node)
{

    if (node == NULL)

        return;

    for (int i = 0; i < N; i++)
    {

        delete_helper(node->children[i]);
    }

    free_trie_node(node);
}

TrieNode *delete_trie(TrieNode *root, char *word)
{

    TrieNode *temp = root;

    TrieNode *parent = NULL;

    int idx;

    for (int i = 0; word[i] != '\0'; i++)
    {

        idx = (int)word[i] - 'a';

        if (temp->children[idx] == NULL)
        {

            printf("%s does not exist in the Trie. Cannot delete.\n", word);

            return root;
        }

        parent = temp;

        temp = temp->children[idx];
    }

    temp->is_leaf = 0;

    int hasChildren = 0;

    for (int i = 0; i < N; i++)
    {

        if (temp->children[i] != NULL)
        {

            hasChildren = 1;

            break;
        }
    }

    if (!hasChildren)
    {

        for (int i = 0; word[i] != '\0'; i++)
        {

            idx = (int)word[i] - 'a';

            parent->children[idx] = NULL;

            int parentHasChildren = 0;

            for (int j = 0; j < N; j++)
            {

                if (parent->children[j] != NULL)
                {

                    parentHasChildren = 1;

                    break;
                }
            }

            if (parent->is_leaf || parentHasChildren)
            {

                break;
            }

            TrieNode *toDelete = parent;

            parent = NULL;

            temp = toDelete;
        }
    }

    printf("%s deleted from the Trie.\n", word);

    return root;
}

void print_trie(TrieNode *root)
{

    if (!root)

        return;

    TrieNode *temp = root;

    printf("%c -> ", temp->data);

    for (int i = 0; i < N; i++)
    {

        print_trie(temp->children[i]);
    }
}

void print_search(TrieNode *root, char *word)
{

    printf("Searching for %s: ", word);

    if (search_trie(root, word) == 0)

        printf("Not Found\n");

    else

        printf("Found!\n");
}

int main()
{

    TrieNode *root = make_trie_node('\0');

    int choice = 3;

    char str[25];

    while (1)
    {

        printf("Enter 1 to insert\nEnter 2 to search\nEnter 3 to delete\nEnter 0 to exit\n");

        scanf("%d", &choice);

        while (getchar() != '\n')

            ;

        switch (choice)
        {

        case 0:

            goto exit;

            break;

        case 1:

            printf("Enter word to insert\n");

            fgets(str, sizeof(str), stdin);

            str[strcspn(str, "\n")] = '\0';

            root = insert_trie(root, str);

            break;

        case 2:

            printf("Enter word to search\n");

            fgets(str, sizeof(str), stdin);

            str[strcspn(str, "\n")] = '\0';

            print_search(root, str);

            break;

        case 3:

            printf("Enter word to delete\n");

            fgets(str, sizeof(str), stdin);

            str[strcspn(str, "\n")] = '\0';

            root = delete_trie(root, str);

            break;
        }
    }

exit:

    printf("Trie after operations:\n");

    print_trie(root);

    printf("\n");

    free_trie_node(root);

    return 0;
}