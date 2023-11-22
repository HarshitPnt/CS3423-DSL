#include "../../includes/fsm.hh"
#include <iostream>

using namespace std;

int main()
{
    // Test for o_set
    fsm::o_set<int> ord_s;
    // Test 1: Insertion
    ord_s.insert(2);
    ord_s.insert(3);
    ord_s.insert(4);
    ord_s.insert(5);
    ord_s.out();
    try
    {
        std::cout << ord_s[10] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // Test 2: Removal
    ord_s.remove(3);
    ord_s.out();
    ord_s.del();
    ord_s.out();

    // // Test 3: Find
    cout << ord_s.find(1) << "\n";
    ord_s.insert(1);
    cout << ord_s.find(1) << "\n";

    // // Test 4: Empty
    cout << ord_s.empty() << "\n";
    ord_s.remove(1);
    cout << ord_s.empty() << "\n";

    // // Test 5: Size
    cout << ord_s.size() << "\n";
    ord_s.insert(1);
    ord_s.insert(2);
    ord_s.insert(6);
    cout << ord_s.size() << "\n";

    // // Test for u_set
    fsm::u_set<int> unord_s;
    // // Test 1: Insertion
    unord_s.insert(2);
    unord_s.insert(1);
    unord_s.insert(4);
    unord_s.insert(3);
    unord_s.insert(5);
    unord_s.out();
    // // Test 2: Removal
    unord_s.remove(3);
    unord_s.out();
    unord_s.del();
    unord_s.out();

    // // Test 3: Find
    cout << unord_s.find(1) << "\n";
    unord_s.insert(1);
    cout << unord_s.find(1) << "\n";

    // // Test 4: Empty
    cout << unord_s.empty() << "\n";
    unord_s.remove(1);
    cout << unord_s.empty() << "\n";

    // // Test 5: Size
    cout << unord_s.size() << "\n";
    unord_s.insert(1);
    unord_s.insert(2);
    unord_s.insert(6);
    cout << unord_s.size() << "\n";

    return 0;
}