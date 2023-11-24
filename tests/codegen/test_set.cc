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

    // Test 6: Addition of two sets
    fsm::o_set<int> ord_s2;
    ord_s2.insert(1);
    ord_s2.insert(2);
    ord_s2.insert(3);
    ord_s2.insert(4);

    fsm::o_set<int> ord_s3 = ord_s + ord_s2;
    ord_s3.out();

    // Test 7: Subtraction of two sets
    fsm::o_set<int> ord_s4 = ord_s - ord_s2;
    ord_s4.out();

    // Test 8: Power set
    fsm::o_set<int> ord_s5;
    ord_s5.insert(1);
    ord_s5.insert(2);
    ord_s5.insert(3);

    fsm::o_set<fsm::o_set<int>> ord_s6 = ord_s5.power_set();
    std::cout << "Printing power set" << std::endl;
    ord_s6.out();

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

    // Test 6: Addition of two sets
    fsm::u_set<int> unord_s2;
    unord_s2.insert(1);
    unord_s2.insert(2);
    unord_s2.insert(3);
    unord_s2.insert(4);

    fsm::u_set<int> unord_s3 = unord_s + unord_s2;
    unord_s3.out();

    // Test 7: Subtraction of two sets
    fsm::u_set<int> unord_s4 = unord_s - unord_s2;
    unord_s4.out();

    // Test 8: Power set
    fsm::u_set<int> unord_s5;
    unord_s5.insert(1);
    unord_s5.insert(2);
    unord_s5.insert(3);

    // fsm::u_set<fsm::u_set<int>> unord_s6 = unord_s5.power_set();
    // unord_s6.out();

    // Test 9: Addition of two sets of different types
    fsm::u_set<int> unord_s7;
    unord_s7.insert(1);
    unord_s7.insert(2);
    unord_s7.insert(3);

    fsm::o_set<int> ord_s7;
    ord_s7.insert(1);
    ord_s7.insert(6);
    ord_s7.insert(2);
    fsm::o_set<int> ord_s8 = ord_s7 + unord_s7;
    ord_s8.out();

    fsm::o_set<int> ord_s9 = unord_s7 + ord_s7;
    ord_s9.out();

    return 0;
}