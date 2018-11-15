#pragma once

#include <iterator>

// ----------------------------------------------------------------------
// polyfill for std::ostream_joiner of c++17

// #if __cplusplus <= 201500

// clang 8.1 on macOS 10.12
namespace polyfill
{
    template <typename Stream, typename _DelimT/* , typename _CharT = char, typename _Traits = char_traits<_CharT> */> class ostream_joiner
    {
     public:
        using char_type = typename Stream::char_type; // _CharT;
        using traits_type = typename Stream::traits_type; //_Traits;
        using iterator_category = std::output_iterator_tag;

        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;

        inline ostream_joiner(Stream& __os, const _DelimT& __delimiter)
              // noexcept(is_nothrow_copy_constructible_v<_DelimT>)
            : _M_out(std::addressof(__os)), _M_delim(__delimiter)
            { }

        inline ostream_joiner(Stream& __os, _DelimT&& __delimiter)
              // noexcept(is_nothrow_move_constructible_v<_DelimT>)
            : _M_out(std::addressof(__os)), _M_delim(std::move(__delimiter))
            { }

        template <typename _Tp> inline ostream_joiner& operator=(const _Tp& __value)
            {
                if (!_M_first)
                    *_M_out << _M_delim;
                _M_first = false;
                *_M_out << __value;
                return *this;
            }

        ostream_joiner& operator*() noexcept { return *this; }
        ostream_joiner& operator++() noexcept { return *this; }
        ostream_joiner& operator++(int) noexcept { return *this; }

     private:
        Stream* _M_out;
        _DelimT _M_delim;
        bool _M_first = true;
    };

    template <typename Stream, typename _DelimT/* , typename _CharT = char, typename _Traits = char_traits<_CharT> */> inline ostream_joiner<Stream, std::decay_t<_DelimT>> make_ostream_joiner(Stream& __os, _DelimT&& __delimiter)
    {
        return { __os, std::forward<_DelimT>(__delimiter) };
    }

} // namespace polyfill

// #else
// // gcc 6.2+
// #include <experimental/iterator>
// namespace std
// {
//     template<typename _DelimT> using ostream_joiner = experimental::fundamentals_v2::ostream_joiner<_DelimT>;
// }
// #endif

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
