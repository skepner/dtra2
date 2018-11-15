#pragma once

// https://infektor.net/posts/2017-03-31-range-based-enumerate.html

#include <iterator>
#include <utility>

// ----------------------------------------------------------------------

namespace acmacs
{
    namespace _enumerate_internal
    {
        template <typename Iterator, typename index_type> struct enumerate_iterator
        {
            using iterator = Iterator;
              //using index_type = typename std::iterator_traits<iterator>::difference_type;
            using reference = typename std::iterator_traits<iterator>::reference;

            inline enumerate_iterator(index_type aIndex, iterator aIterator) : index(aIndex), iter(aIterator) {}
            inline enumerate_iterator& operator++() { ++index; ++iter; return *this; }
            inline bool operator!=(const enumerate_iterator &other) const { return iter != other.iter; }
            inline std::pair<index_type&, reference> operator*() { return {index, *iter}; }

         private:
            index_type index;
            iterator iter;
        };

          // ----------------------------------------------------------------------

        template <typename Iterator, typename index_type> struct enumerate_range
        {
              // using index_type = typename std::iterator_traits<Iterator>::difference_type;
            using iterator = enumerate_iterator<Iterator, index_type>;

            inline enumerate_range(Iterator aFirst, Iterator aLast, index_type aInitial) : first(aFirst), last(aLast), initial(aInitial) {}
            inline iterator begin() const { return iterator(initial, first); }
            inline iterator end() const { return iterator(0, last); }

         private:
            Iterator first;
            Iterator last;
            index_type initial;
        };

    } // namespace _enumerate_internal

// ----------------------------------------------------------------------

    template <typename Iterator, typename index_type> inline auto enumerate(Iterator first, Iterator last, index_type initial = 0)
    {
        return _enumerate_internal::enumerate_range<Iterator, index_type>(first, last, initial);
    }

    template <typename Container> inline auto enumerate(Container& content, size_t initial = 0)
    {
        using iter_type = decltype(std::begin(content));
        return _enumerate_internal::enumerate_range<iter_type, size_t>(std::begin(content), std::end(content), initial);
    }

    template <typename Container> inline auto enumerate(const Container& content, size_t initial = 0)
    {
        using iter_type = decltype(std::begin(content));
        return _enumerate_internal::enumerate_range<iter_type, size_t>(std::begin(content), std::end(content), initial);
    }

} // namespace acmacs

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
