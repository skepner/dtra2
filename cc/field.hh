#pragma once

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
                Text& operator=(const std::string& source)
                {
                    std::string::operator=(source);
                    return *this;
                }
                Text& operator=(std::string&& source)
                {
                    std::string::operator=(std::move(source));
                    return *this;
                }
                Text& operator=(const char* source)
                {
                    std::string::operator=(source);
                    return *this;
                }

                std::vector<std::string> validate() const { return {}; }

              private:
                const can_be_empty can_be_empty_ = can_be_empty::yes;
            };
        } // namespace field

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
