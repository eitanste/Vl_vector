#include "vl_vector.h"
#include "vl_string.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;


//void print_vec(VLVector<int> &vec) {
//    for (int j : vec) {
//        std::cout << j << ' ' << std::endl;
//    }
//    std::cout << "size is: " << vec.size() << " capacity is: "
//              << vec.capacity() << std::endl;
//}
//
void print_str(VLString<STATIC_CAPACITY> &str) {

    std::cout << "-------------------------------" <<endl;

    for (size_t j = 0; j < str.size(); ++j) {
        std::cout << "'" << str.at(j) << "', " ;
    }
    std::cout << "'" << "/0" << "'" << endl;
    std::cout << "size is: " << str.size() << " capacity is: "
    << str.capacity() << std::endl;
}
//
//void test_creat_vectors() {
//
//    VLVector<int> vec0;
//    VLVector<int, 16> vec1((size_t)4, -1);
//    VLVector<int, 16> vec2(vec1);
//}
//void test_single_erase(VLVector<int> &vec) {
//    int *it4 = vec.data() + 6;
//    int *ret4 = vec.erase(it4);
//    cout << " the return value of 'ret4' from a single erase is: " << *ret4
//    << endl;
//    print_vec(vec);
//}
//
//void test_multy_erase(VLVector<int> &vec) {
//    int *it = vec.data() + 2;
//    int *ret = vec.erase(it, it + 3);
//    cout << " the return value of 'ret4' from a multy erase is: " << *ret
//    << endl;
//    print_vec(vec);
//    int *it2 = vec.data() + 3;
//    int *ret2 = vec.erase(it2, it2 + 3);
//    cout << " the return value of 'ret2' from a multy erase is: " << *ret2
//    << endl;
//    print_vec(vec);
//}
//
//void test_comp_op(VLVector<int> &vec) {
//    auto vec2(vec);
////    bool compare = (vec == vec2);
//    std::cout << "the result from compering to vectors is: " << (vec == vec2) << endl;
//
//    vec2.pop_back();
//    std::cout << "the result from compering to vectors after poping is: " << (vec == vec2) << endl;
//
//}
//
//void TestInsertIteratorInStaticCapacity() {
//    VLVector<int, 16> vec((size_t)0,0);
//    vec.push_back (0);
//
//    std::vector<int> values{1, 2, 3, 4};
//    auto it = vec.begin();
//    ++it;
//    auto begin = values.begin();
//    auto end = values.end();
//    vec.insert(it, begin, end);
//    vec.insert(it, values.begin(), values.end());
//}
//
//
//void test_regular_iterator(){
//    VLVector<int,16> vec1((size_t)6,0);
//    const VLVector<int> vec2((size_t)7,1);
//
//    VLVector<int,16>::iterator it = vec1.begin();
//    VLVector<int,16>::const_iterator it2 = vec1.begin();
//    VLVector<int,16>::const_iterator it3 = vec2.begin();
//
//    VLVector<int,16>::const_iterator it4 = vec1.cbegin();
//    VLVector<int,16>::iterator it1 = vec1.end();
//
//    cout<< "from first iterator: " << endl;
//    while (it!= it1) {
//        cout<< *(it++) << std::endl;
//    }
//    cout<< "from second const iterator: " << endl;
//    while (it2!= it1) {
//        cout<< *(it2++) << std::endl;
//    }
//    cout<< "from third const iterator: " << endl;
//    while (it3!= vec2.end()) {
//        cout<< *(it3++) << std::endl;
//    }
//    cout<< "from forth const iterator: " << endl;
//    while (it4!= it1) {
//        cout<< *(it4++) << std::endl;
//    }
//}
//
//void test_reverse_iterator(){
//    VLVector<int, 16> vec((size_t)0,0);
//    for (int i = 0; i < 10; ++i) {
//        vec.push_back(i);
//    }
////    VLVector<int,16>::reverse_iterator it = vec.rbegin();
//    auto it = vec.rbegin();
//    auto it1 = vec.rend();
//
//    cout<< "from forth const iterator: " << endl;
//    while (it!= it1) {
//        cout<< *(it++) << std::endl;
//    }
//}
//
//void test_iterators() {
//    test_regular_iterator();
//    test_reverse_iterator();
//}
//
//void test_cap() {
//    VLVector<int> vec;
//    for (int i = 0; i < 30; ++i) {
//        vec.push_back(i);
//    }
//    print_vec(vec);
//}
//
//void test_vector() {
//        std::cout << "begin test" << std::endl;
//        VLVector<int, 16> vec1((size_t)4, -1);
//        VLVector<int, 16> vec2(vec1);
//        for (int i = 0; i < 10; ++i) {
//            vec2.push_back(i);
//        }
//
//        std::cout << "----------------------" << std::endl;
//
//        print_vec(vec2);
//        std::cout << "----------------------" << std::endl;
//
//        for (size_t i = 0; i < 10; ++i) {
//            vec2.push_back(i + 10);
//        }
//        for (size_t j = 0; j < vec2.size(); ++j) {
//            std::cout << vec2.at(j) << ' ' << std::endl;
//        }
//        std::cout << "size is: " << vec2.size() << " capacity is: "
//                  << vec2.capacity() << std::endl;
//
//        std::cout << "----------------------" << std::endl;
//
//        vec2.push_back(20);
//        vec2.push_back(21);
//        std::cout << "size is: " << vec2.size() << " capacity is: "
//                  << vec2.capacity() << std::endl;
//
//
//        std::cout << "----------------------" << std::endl;
//        for (size_t i = vec2.size(); i > 4; --i) {
//            vec2.pop_back();
//        }
//        for (size_t j = 0; j < vec2.size(); ++j) {
//            std::cout << vec2.at(j) << ' ' << std::endl;
//        }
//        std::cout << "size is: " << vec2.size() << " capacity is: "
//                  << vec2.capacity() << std::endl;
//
//        std::cout << "----------------------" << std::endl;
//
//        int *it = vec2.data() + 2;
//        int *ret = vec2.insert(it, -20); //
//
//        cout << " the return value of a singl insert is: " << *ret << endl;
//
//        for (size_t j = 0; j < vec2.size(); ++j) {
//            std::cout << vec2.at(j) << ' ' << std::endl;
//        }
//        std::cout << "size is: " << vec2.size() << " capacity is: "
//                  << vec2.capacity() << std::endl;
//
//        std::cout << "----------------------" << std::endl;
//        int *it2 = vec1.data() + 2;
//        int array[3] = {10, 20, 30};
//        int *ret2 = vec1.insert(it2, array, array + 3);
//
//        cout << " the return value of 'ret2' from a singl insert is: " << *ret2
//             << endl;
//
//        for (size_t j = 0; j < vec1.size(); ++j) {
//            std::cout << vec1.at(j) << ' ' << std::endl;
//        }
//        std::cout << "size is: " << vec1.size() << " capacity is: "
//                  << vec1.capacity() << std::endl;
//
//        std::cout << "----------------------" << std::endl;
//        int *it3 = vec1.data() + 6;
//        int array2[4] = {100, 200, 300, 400};
//        int *ret3 = vec1.insert(it3, array2, array2 + 4);
//
//        cout << " the return value of 'ret3' from a multy insert is: " << *ret3
//             << endl;
//
//        for (size_t j = 0; j < vec1.size(); ++j) {
//            std::cout << vec1.at(j) << ' ' << std::endl;
//        }
//        std::cout << "size is: " << vec1.size() << " capacity is: "
//                  << vec1.capacity() << std::endl;
//
//        std::cout << "-----------test_single_erase-----------" << std::endl;
//
//        test_single_erase(vec1);
//
//        std::cout << "------------test_multy_erase----------" << std::endl;
//
//        test_multy_erase(vec1);
//
//        std::cout << "------------test_comp1----------" << std::endl;
//
//        test_comp_op(vec1);
//
//        std::cout << "------------test_iterators----------" << std::endl;
//        test_iterators();
//
//    std::cout << "------------test_cap----------" << std::endl;
//
//    test_cap();
//}
//void test_creat_string() {
//    VLString<STATIC_CAPACITY> str;
//
//    std::cout << "------------test_str_creat----------" << std::endl;
//
//    print_str(str);
//
//    str.push_back('f');
//
//    print_str(str);
//
//    for (int i = 65; i < 91; ++i) {
//        str.push_back(i);
//    }
//
//    print_str(str);
//
//}
//
//void test_contain() {
//    VLString<STATIC_CAPACITY> str = "hello";
//    const char* str1 = "ell";
//    const char* str2 = "goll";
//    std::cout << str.contains(str1) << std::endl;
//    std::cout << str.contains(str2) << std::endl;
//
//}
//
//void test_string() {
////    test_creat_string();
//    test_contain();
//}

int main() {
//    test_vector();
//    test_string();
    VLVector<char,STATIC_CAPACITY> vec((size_t)4,2);
//    vec.insert(vec.begin() , vec.begin(), vec.begin());
//    vec.erase(vec.end()-1);

    VLVector<char,0> vec2((size_t)1,'2');
    vec2.push_back('3');
    vec2.push_back('4');
    vec2.push_back('5');
    vec2.push_back('6');
    VLVector<char,0> vec3((size_t)0,2);
//    vec2.insert(vec2.begin() , vec.begin(), vec.end());
    vec2.erase(vec2.begin());
    return 0;
}
