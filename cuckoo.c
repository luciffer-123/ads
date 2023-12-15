#include <stdio.h>
#include <stdlib.h>

#define MAXN 11
#define VER 2

int hashtable[VER][MAXN];
int pos[VER];

void init_table()
{
    for (int i = 0; i < VER; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            hashtable[i][j] = -1;
        }
    }
}

int hash(int function, int key)
{
    if (function == 1)
        return key % MAXN;
    else if (function == 2)
        return (key / MAXN) % MAXN;
}

void place(int key, int table_id, int cnt, int n)
{
    if (cnt == n)
    {
        printf("%d unpositioned\n", key);
        printf("Cycle present. REHASH.\n");
        return;
    }

    for (int i = 0; i < VER; i++)
    {
        pos[i] = hash(i + 1, key);
        if (hashtable[i][pos[i]] == key)
            return;
    }

    if (hashtable[table_id][pos[table_id]] != -1)
    {
        int dis = hashtable[table_id][pos[table_id]];
        hashtable[table_id][pos[table_id]] = key;
        place(dis, (table_id + 1) % VER, cnt + 1, n);
    }
    else
    {
        hashtable[table_id][pos[table_id]] = key;
    }
}

void print_table()
{
    printf("Final hash tables:\n");
    for (int i = 0; i < VER; i++)
    {
        printf("\n");
        for (int j = 0; j < MAXN; j++)
        {
            if (hashtable[i][j] == -1)
                printf("- ");
            else
                printf("%d ", hashtable[i][j]);
        }
    }
    printf("\n");
}

void cuckoo(int keys[], int n)
{
    init_table();

    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        place(keys[i], 0, cnt, n);
    }

    print_table();
}

int main()
{
    int n;

    printf("Enter the number of keys: ");
    scanf("%d", &n);

    int keys[n];

    printf("Enter the keys: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &keys[i]);
    }

    cuckoo(keys, n);

    return 0;
}