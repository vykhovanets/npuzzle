#pragma once

#include <queue>
#include <vector>

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>>
class MyPriorQueue : public std::priority_queue<T, Container, Compare> {
    public:
        typedef typename
            std::priority_queue<
            T,
            Container,
            Compare>::container_type::const_iterator const_iterator;

        using std::priority_queue<T, Container, Compare>::priority_queue;

        template<class Comparator>
        const_iterator find_if(const Comparator comp) const
        {
            auto first = this->c.cbegin();
            auto last = this->c.cend();
            while (first!=last) {
                if (comp(*first)) return first;
                ++first;
            }
            return last;
        }

        const_iterator end() const {
            return this->c.cend();
        }
};

