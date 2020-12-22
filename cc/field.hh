#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <optional>
#include "float.hh"

// ----------------------------------------------------------------------

namespace xlnt { class cell; }

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        namespace field
        {
            enum class can_be_empty { no, yes };

            class Field
            {
             public:
                Field(can_be_empty cbe = can_be_empty::yes) : can_be_empty_{cbe} {}
                Field(const Field&) = default;
                virtual ~Field() = default;
                Field& operator=(const Field&) = default;

                virtual std::string csv_value() const = 0;
                virtual void from_cell(const xlnt::cell& cell) = 0;
                virtual void to_cell(xlnt::cell& cell) const = 0;

             protected:
                bool can_be_empty() const { return can_be_empty_ == can_be_empty::yes; }

             private:
                enum can_be_empty can_be_empty_;
            };

            class Text : public Field
            {
              public:
                Text(enum can_be_empty cbe = can_be_empty::yes) : Field(cbe) {}
                Text(const Text&) = default;
                Text(Text&&) = default;
                Text& operator=(std::string_view source)
                {
                    value_ = source;
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(const std::string& source)
                {
                    value_ = source;
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(std::string&& source)
                {
                    value_ = std::move(source);
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(const char* source)
                {
                    value_ = source;
                    fix_on_assign();
                    return *this;
                }
                Text& operator=(const Text& source) = default;

                operator std::string() const { return value_; }
                auto value() const { return value_; }
                std::string to_string() const { return value_; }
                std::string lower() const { return string::lower(value_); }
                bool empty() const { return value_.empty(); }
                void clear() { return value_.clear(); }
                bool contains(const char *text) const { return value_.find(text) != std::string::npos; }

                bool operator==(std::string_view rhs) const { return std::string_view(value_) == rhs; }
                // bool operator!=(std::string_view rhs) const { return !operator==(rhs); }
                bool operator==(std::string rhs) const { return value_ == rhs; }
                // bool operator!=(std::string rhs) const { return !operator==(rhs); }
                bool operator==(const char* rhs) const { return operator==(std::string_view(rhs)); }
                // bool operator!=(const char* rhs) const { return !operator==(rhs); }

                std::string csv_value() const override { return value_; }
                void from_cell(const xlnt::cell& cell) override;
                void to_cell(xlnt::cell& cell) const override;

                std::vector<std::string> validate() const;

              protected:
                virtual void fix_on_assign() { string::strip_in_place(value_); }
                auto begin() { return value_.begin(); }
                auto end() { return value_.end(); }

             private:
                std::string value_;
            };

              // ----------------------------------------------------------------------

            class Uppercase : public Text
            {
              public:
                using Text::Text;
                Uppercase(const char* validation_regex, const char* error_message, enum can_be_empty cbe = can_be_empty::yes)
                    : Text(cbe), re_validator_{validation_regex}, error_message_{error_message} {}
                Uppercase(const Uppercase&) = default;
                using Text::operator=;
                Uppercase& operator=(const Uppercase& source)
                {
                    Text::operator=(source);
                    return *this;
                }

                std::vector<std::string> validate() const;

             protected:
               void fix_on_assign() override
               {
                   Text::fix_on_assign();
                   std::transform(begin(), end(), begin(), [](unsigned char src) { return std::toupper(src); });
               }

             private:
                const std::optional<std::regex> re_validator_;
                const std::string error_message_;
            };

              // ----------------------------------------------------------------------

            class Float : public Field
            {
             public:
                Float() = default;
                Float(const Float&) = default;
                Float(double min, double max) : min_{min}, max_{max} {}
                Float& operator=(const std::string& source);
                Float& operator=(double source);
                Float& operator=(const Float& source) { value_ = source.value_; return *this; }
                bool operator==(const Float& rhs) const { return bool(value_) == bool(rhs.value_) && (!value_ || float_equal(*value_, *rhs.value_)); }
                bool operator!=(const Float& rhs) const { return !operator==(rhs); }

                bool empty() const { return !value_; }
                operator double() const { return *value_; }
                std::string to_string() const;

                std::string csv_value() const override { return to_string(); }
                void from_cell(const xlnt::cell& cell) override;
                void to_cell(xlnt::cell& cell) const override;

                std::vector<std::string> validate() const;

             private:
                std::optional<double> value_;
                std::optional<double> min_, max_;
                mutable std::vector<std::string> errors_;
            };

            inline std::string to_string(const Text& field) { return field.to_string(); }
            inline std::string to_string(const Float& field) { return field.to_string(); }

        } // namespace field

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
