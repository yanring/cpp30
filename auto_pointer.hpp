//
// Created by 颜子杰 on 2021/10/6.
//

#ifndef C__30_AUTO_POINTER_HPP
#define C__30_AUTO_POINTER_HPP

#include <stdio.h>
#include <iostream>

class shape {
public:
    int a = 1;

    virtual ~shape() {
        puts("~shape");
    }
};

class circle : public shape {
public:
    ~circle() {
        puts("~circle");
    }
};

template<typename T>
class unique_pointer {
public:
    explicit unique_pointer(T *ptr = nullptr) : ptr_(ptr) {}

    ~unique_pointer() { delete ptr_; }

    T *get() const { return ptr_; }

    // 运算符与指针对齐
    T &operator*() const { return *ptr_; }

    T *operator->() const { return ptr_; }

    operator bool() const { return ptr_; }

    // copy and assign
    unique_pointer &operator=(unique_pointer rvalue) {
        // 可以思考一下这里为什么这么写
        // operator=()的参数在接收参数的时候，会调用构造函数，如果调用的是拷贝构造，那赋值操作就是拷贝，如果调用的是移动构造，那么赋值操作就是移动。
        rvalue.swap(*this);
        return *this;
    }

    unique_pointer(unique_pointer &&rvalue) {
        ptr_ = rvalue.release();
    }

    unique_pointer(unique_pointer &rvalue) = delete;

    template<typename U>
    unique_pointer(unique_pointer<U> &&rvalue) {
        ptr_ = rvalue.ptr_;
    }

    T *release() {
        T *tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void swap(unique_pointer &rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

private:
    T *ptr_;
};

class shared_count {
private:
    long count_;
public:
    shared_count(int cnt) : count_(cnt) {}

    shared_count() : count_(1) {}

    void add_count() { count_++; }

    long reduce_count() {
        return --count_;
    };

    long get_count() const {
        return count_;
    }
};

template<typename T>
class shared_pointer {
private:
    T *ptr_;
    shared_count *count_ptr{};
public:
    explicit shared_pointer(T *ptr = nullptr) : ptr_(ptr) {
        if (ptr) count_ptr = new shared_count;
    }

    ~shared_pointer() {
        if (ptr_ && count_ptr->reduce_count()) {
            delete ptr_;
            delete count_ptr;
        }
    }

    T *get() const { return ptr_; }

    // 运算符与指针对齐
    T &operator*() const { return *ptr_; }

    T *operator->() const { return ptr_; }

    operator bool() const { return ptr_; }

    // copy and assign
    // template move construct
    template<typename U>
    shared_pointer(shared_pointer<U> &&rvalue)  noexcept {
        ptr_ = rvalue.ptr_;
        if (ptr_) {
            count_ptr = rvalue.count_ptr;
            rvalue.ptr_ = nullptr;
        }
    }

    // copy construct
    // 必须要写一个非模板的copy construct, 不然编译器会生成默认的
    shared_pointer(const shared_pointer &rvalue) {
        ptr_ = rvalue.ptr_;
        if (ptr_) {
            this->count_ptr = rvalue.count_ptr;
            this->count.add_count();
        }
    };

    // template copy construct
    template<typename U>
    shared_pointer(shared_pointer<U> &rvalue) {
        ptr_ = rvalue.ptr_;
        if (ptr_) {
            this->count_ptr = rvalue.count_ptr;
            this->count_ptr->add_count();
        }
    }

    // assign
    shared_pointer &operator=(shared_pointer rvalue) {
        rvalue.swap(*this);
        return *this;
    }

    void swap(shared_pointer &rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(count_ptr, rhs.count_ptr);
    }

    long use_count() const { if (ptr_) { return count_ptr->get_count(); } else { return 0; }}

    // type conversion


};

int auto_pointer() {
    unique_pointer<shape> ptr(new circle());
    unique_pointer<shape> ptr2(new circle());
    std::cout << &(ptr->a) << std::endl;
    std::cout << &(ptr2->a) << std::endl;
    ptr = std::move(ptr2);
    std::cout << &(ptr->a) << std::endl;
    std::cout << &(ptr2->a) << std::endl;

    shared_pointer<circle> ptr3(new circle());
    printf("use count of ptr1 is %ld\n", ptr3.use_count());
    shared_pointer<circle> ptr4;
    printf("use count of ptr2 was %ld\n", ptr4.use_count());
    ptr4 = ptr3;
    printf("use count of ptr2 is now %ld\n", ptr4.use_count());
    if (ptr3) { puts("ptr1 is not empty"); }
    return 0;
}


#endif //C__30_AUTO_POINTER_HPP
