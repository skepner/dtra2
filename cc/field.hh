#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        namespace field
        {
            enum class can_be_empty { no, yes };

            class Text : public std::string
            {
              public:
                Text(can_be_empty cbe = can_be_empty::yes) : can_be_empty_{cbe} {}
                Text(const Text&) = default;
                Text(Text&&) = default;
                virtual ~Text() = default;
                Text& operator=(const std::string& source)
                {
                    std::string::operator=(source);
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(std::string&& source)
                {
                    std::string::operator=(std::move(source));
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(const char* source)
                {
                    std::string::operator=(source);
                    fix_on_assign();
                    return *this;
                }

                std::vector<std::string> validate() const;

              protected:
                virtual void fix_on_assign() {}

              private:
                const can_be_empty can_be_empty_ = can_be_empty::yes;
            };

            class Uppercase : public Text
            {
              public:
                using Text::Text;
                using Text::operator=;

             protected:
                virtual void fix_on_assign() { std::transform(begin(), end(), begin(), [](unsigned char src) { return std::toupper(src); }); }
            };

            class SampleId : public Uppercase
            {
              public:
                using Uppercase::Uppercase;
                using Uppercase::operator=;

                std::vector<std::string> validate() const;

             private:
                static const std::regex re_validator_;
            };

        } // namespace field

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
