//
// Created by 颜子杰 on 2021/10/7.
//

#ifndef C__30_MOVE_HPP
#define C__30_MOVE_HPP

#include <stdio.h>
#include "iostream"
#include "auto_pointer.hpp"

void foo(const shape &) {
    puts("foo(const shape&)");
}

void foo(shape &&) {
    puts("foo(shape&&)");
}

void bar(const shape &s) {
    puts("bar(const shape&)");
    foo(s);
}

void bar(shape &&s) {
    puts("bar(shape&&)");
    foo(std::forward<shape>(s));
}

int move() {
    bar(circle());
}

#endif //C__30_MOVE_HPP
