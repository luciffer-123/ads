#include<iostream>
#include<vector>
using namespace std;
void display(vector<int> v)
{
    for (int i = 3 ; i >= 0; i--)
    {
        cout << v[i] << " ";
    }
}
int increment(vector<int> &binary)
{
    int i = 0;
    int no_of_flips = 0;
    while (i < binary.size() && binary[i] == 1)
    {
        binary[i] = 0;
        no_of_flips++;
        i++;
    }
    if (i < binary.size())
    {
        binary[i] = 1;
        no_of_flips++;
    }
    return no_of_flips;
}
vector<int> convert(int n)
{
    vector<int> binary(4, 0);
    int rem = 0;
    int i = 0;
    while (n > 0)
    {
        rem = n % 2;
        binary[i] = rem;
        i++;
        n /= 2;
    }
    return binary;
}
void binary_counter(int n, int k)
{
    vector<int> binary = convert(n);
    cout << "Original Number : ";
    display(binary);
    cout << endl;
    int count = 0;
    while (count < k)
    {
        int tc = increment(binary);
        display(binary);
        cout << "Total Cost : " << tc;
        cout << endl;
        count++;
    }
}
int main()
{
    cout << "Enter starting number : ";
    int n;
    cin >> n;
    cout << "Enter number of times to increment : ";
    int a;
    cin >> a;
    binary_counter(n, a);
    return 0;
}
