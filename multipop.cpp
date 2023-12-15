#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of elements in stack : ";
    cin >> n;
    int arr[n];
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 5 + 2;
        printf("%d ", arr[i]);
    }
    printf("--------------------\n");
    int cost = 0;
    int accountingcost = 0;
    int potentialcost = 0;
    stack<int> stk;
    for (int i = 0; i < n; i++)
    {
        // printf("rand: %d, k: ", srand());
        int k = rand() % 3;
        printf("%d ", k);
        if (k == 0)
        {
            stk.push(arr[i]);
            cost += 1;
            accountingcost += 1;
            cout << stk.top() << " push accounting cost : "
                 << "1" << endl;
            potentialcost += 1;
        }
        else if (k == 1)
        {
            if (stk.size() >= 1)
            {
                cout << stk.top() << " pop accounting cost : "
                     << "-1" << endl;
                stk.pop();
                cost += 1;
                accountingcost -= 1;
                potentialcost -= 1;
            }
        }
        else
        {
            int k = rand() % 5;
            int s = stk.size();
            int minimum = min(k, s);
            for (int i = 0; i < minimum; i++)
            {
                cout << stk.top() << " multipop accounting cost : "
                     << "-1" << endl;
                stk.pop();
                accountingcost -= 1;
                cost += 1;
                potentialcost -= 1;
            }
        }
    }
    cout << "Cost: " << cost << endl;
    cout << "Aggregate cost: " << (float)cost / n << endl;
    cout << "Accounting: " << accountingcost << endl;
    cout << "Potential or Excess: " << potentialcost << endl;
    cout << "Final stack size: " << stk.size();
    return 0;
}
