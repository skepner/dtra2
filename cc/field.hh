#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <optional>

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
                Uppercase(const char* validation_regex, const char* error_message, can_be_empty cbe = can_be_empty::yes)
                    : Text(cbe), re_validator_{validation_regex}, error_message_{error_message} {}
                using Text::operator=;

                std::vector<std::string> validate() const;

             protected:
                virtual void fix_on_assign() { std::transform(begin(), end(), begin(), [](unsigned char src) { return std::toupper(src); }); }

             private:
                const std::optional<std::regex> re_validator_;
                const std::string error_message_;
            };

        } // namespace field

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
