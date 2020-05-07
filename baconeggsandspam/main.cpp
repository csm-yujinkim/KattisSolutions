#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

int main()
{
    for (;;)
    {
        map<string, set<string>> items_per_customer;
        size_t n_customers;
        std::cin >> n_customers;
        if (!n_customers)
        {
            break;
        }
        string line;
        cin.ignore(1, '\n');
        for (size_t c = 0; c < n_customers; ++c)
        {
            getline(cin, line);
            stringstream in_line(line);
            string customer;
            in_line >> customer;
            for (string item; in_line >> item;)
            {
                items_per_customer[item].insert(customer);
            }
        }
        for (const auto &it : items_per_customer)
        {
            cout << it.first;
            for (const string &customer : it.second)
            {
                cout << ' ' << customer;
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}