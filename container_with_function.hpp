//
// Created by 颜子杰 on 2021/10/7.
//

#ifndef C__30_CONTAINER_WITH_FUNCTION_HPP
#define C__30_CONTAINER_WITH_FUNCTION_HPP


#include <algorithm>   // std::sort
#include <functional>  // std::less/greater/hash
#include <iostream>    // std::cout/endl
#include <string>      // std::string
#include <vector>      // std::vector
#include <queue>
#include <memory>
#include "output_container.h"


using namespace std;

void priority_queue_test() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({1, 1});
    q.push({2, 2});
    q.push({0, 3});
    q.push({0, 4});
    while (!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
}

void sort_and_hash() {
    // 初始数组
    vector<int> v{13, 6, 4, 11, 29};
    cout << v << endl;

    // 从小到大排序
    sort(v.begin(), v.end());
    cout << v << endl;

    // 从大到小排序
    sort(v.begin(), v.end(),
         greater<>());
    cout << v << endl;

    cout << hex;

    auto hp = hash<int *>();
    cout << "hash(nullptr)  = "
         << hp(nullptr) << endl;
    cout << "hash(v.data()) = "
         << hp(v.data()) << endl;
    cout << "v.data()       = "
         << static_cast<void *>(v.data())
         << endl;

    auto hs = hash<string>();
    cout << "hash(\"hello\")  = "
         << hs(string("hello")) << endl;
    cout << "hash(\"hellp\")  = "
         << hs(string("hellp")) << endl;
}

int container_with_function() {
    sort_and_hash();
    priority_queue_test();
}

#endif //C__30_CONTAINER_WITH_FUNCTION_HPP
