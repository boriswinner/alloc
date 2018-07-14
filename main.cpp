#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include <limits>
#include <iostream>
#include <vector>
#include <vector>
#include <cstdlib> // for rand

namespace pretty_allocator {
    template<class T>
    class allocator {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        template<class U>
        struct rebind {
            typedef allocator<U> other;
        };

        pointer address(reference value) const {
            return &value;
        }

        const_pointer address(const_reference value) const {
            return &value;
        }

        allocator() noexcept {
        }

        allocator(const allocator &) noexcept {
        }

        template<class U>
        allocator(const allocator<U> &) noexcept {
        }

        ~allocator() noexcept {
        }

        size_type max_size() const noexcept {
            return std::numeric_limits<std::size_t>::max() / sizeof(T);
        }

        pointer allocate(size_type num, const void * = 0) {
            pointer p = (pointer) (::operator new(num * sizeof(T)));
            return p;
        }

        void construct(pointer p, const T &value) {
            new((void *) p)T(value);
        }

        void destroy(pointer p) {
            p->~T();
        }

        void deallocate(pointer p, size_type num) {
            ::operator delete((void *) p);
        }
    };

    template<class T1, class T2>
    bool operator==(const allocator<T1> &,
                    const allocator<T2> &) throw() {
        return true;
    }

    template<class T1, class T2>
    bool operator!=(const allocator<T1> &,
                    const allocator<T2> &) throw() {
        return false;
    }
}

static void std_push_back(picobench::state &s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.push_back(rand());
    }
}
PICOBENCH(std_push_back);

static void my_push_back(picobench::state &s)
{
    std::vector<int,pretty_allocator::allocator<int> > v;
    for (auto _ : s)
    {
        v.push_back(rand());
    }
}
PICOBENCH(my_push_back);

static void std_reserve(picobench::state &s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.reserve(100000);
    }
}
PICOBENCH(std_reserve);

static void my_reserve(picobench::state &s)
{
    std::vector<int,pretty_allocator::allocator<int> > v;
    for (auto _ : s)
    {
        v.reserve(100000);
    }
}
PICOBENCH(my_reserve);

static void std_reserve_big(picobench::state &s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.reserve(10000000);
    }
}
PICOBENCH(std_reserve_big);

static void my_reserve_big(picobench::state &s)
{
    std::vector<int,pretty_allocator::allocator<int> > v;
    for (auto _ : s)
    {
        v.reserve(10000000);
    }
}
PICOBENCH(my_reserve_big);

static void std_clear(picobench::state &s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.insert(v.begin(),10000,1);
        v.clear();
    }
}
PICOBENCH(std_clear);

static void my_clear(picobench::state &s)
{
    std::vector<int,pretty_allocator::allocator<int> > v;
    for (auto _ : s)
    {
        v.insert(v.begin(),10000,1);
        v.clear();
    }
}
PICOBENCH(my_clear);

static void std_erase(picobench::state &s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.insert(v.begin(),100,1);
        for (auto it = v.begin(); it < v.end(); ++it){
            v.erase(it);
        }
    }
}

PICOBENCH(std_erase);

static void my_erase(picobench::state &s)
{
    std::vector<int,pretty_allocator::allocator<int> > v;
    for (auto _ : s)
    {
        v.insert(v.begin(),100,1);
        for (auto it = v.begin(); it < v.end(); ++it){
            v.erase(it);
        }
    }
}
PICOBENCH(my_erase);