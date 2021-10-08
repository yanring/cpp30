//
// Created by 颜子杰 on 2021/10/7.
//

#ifndef C__30_CONTAINER_HPP
#define C__30_CONTAINER_HPP


#include <iostream>
#include <map>
#include <vector>
#include "output_container.h"

using namespace std;

int container()
{
  map<int, int> mp{
    {1, 1}, {2, 4}, {3, 9}};
  cout << mp << endl;
  vector<vector<int>> vv{
    {1, 1}, {2, 4}, {3, 9}};
  cout << vv << endl;
}

#endif //C__30_CONTAINER_HPP
