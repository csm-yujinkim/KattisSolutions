#include <map>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    for (size_t n_customers; cin >> n_customers, n_customers;)
    {
        // unprocessed \n, discard
        cin.get();

        map<string, set<string>> assoc;

        for (size_t c = 0; c < n_customers; ++c)
        {
            string customer;
            cin >> customer;
            // unprocessed \n, discard
            cin.get();
            string line_items;
            getline(cin, line_items);
            istringstream make_toks(line_items);
            for (string item; make_toks >> item;)
            {
                assoc[item].insert(customer);
            }
        }

        for (auto const &[customer, items] : assoc)
        {
            cout << customer;
            for (string const &item : items)
            {
                cout << ' ' << item;
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
