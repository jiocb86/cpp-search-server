#pragma once
#include <vector>

template<class Iterator>
class IteratorRange {
private:
    Iterator begin_;
    Iterator end_;
    size_t size_;
public:
    IteratorRange(Iterator begin, Iterator end) 
    {
        begin_ = begin;
        end_ = end;
        size_ = distance(begin_, end_);
    }

    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

    size_t size() const {
        return size_;
    }
};

template<class Iterator>
class Paginator {
private:
    size_t size_;
    std::vector<IteratorRange<Iterator>> pages_;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        size_t len = distance(begin, end);
        for (auto it = begin; it < end; it += page_size){
            const size_t current_page_size = std::min(page_size, static_cast<size_t>(len));
            Iterator page_begin = it;
            Iterator page_end = next(it, current_page_size);
            pages_.push_back(IteratorRange(page_begin, page_end));
        } 
    }

    size_t size() const {
        return size_;
    }

    auto begin() const {
        return pages_.begin();
    }

    auto end() const {
        return pages_.end();
    }
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& out, const IteratorRange<Iterator>& range) {
    for (auto it = range.begin(); it != range.end(); ++it){
        out << *it;
    }
    return out;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}
