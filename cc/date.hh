#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include "string.hh"
#include "field.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        namespace field
        {
            class Date : public Field
            {
              public:
                Date(enum can_be_empty cbe = can_be_empty::yes) : Field(cbe)
                {
                    const auto now = std::chrono::system_clock::now();
                    const auto now_c = std::chrono::system_clock::to_time_t(now);
                    now_ = *std::localtime(&now_c);
                }
                Date(const Date& source) = default;
                Date(const std::string source);
                Date& operator=(const Date& source) = default;

                bool operator==(const Date& rhs) const { return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_; }
                bool operator!=(const Date& rhs) const { return !operator==(rhs); }
                bool operator<(const Date& rhs) const { return year_ == rhs.year_ ? (month_ == rhs.month_ ? day_ < rhs.day_ : month_ < rhs.month_) : year_ < rhs.year_; }
                bool operator<=(const Date& rhs) const { return operator<(rhs) || operator==(rhs); }
                bool operator>(const Date& rhs) const { return !operator<(rhs) && !operator==(rhs); }
                bool operator>=(const Date& rhs) const { return !operator<(rhs); }

                bool empty() const { return !year_ && !month_ && !day_; }

                void set_day(std::string day);
                void set_month(std::string month);
                void set_year(std::string year);

                std::vector<std::string> validate() const;

                std::string to_string() const;
                int year() const { return static_cast<int>(year_); }
                int month() const { return static_cast<int>(month_); }
                int day() const { return static_cast<int>(day_); }

                std::string csv_value() const override { return to_string(); }
                void from_cell(const xlnt::cell& /*cell*/) override {}
                void to_cell(xlnt::cell& /*cell*/) const override {}

                void allow_zero_date(bool allow_zero_date) { allow_zero_date_ = allow_zero_date; }
                constexpr bool allow_zero_date() const { return allow_zero_date_; }

              private:
                size_t day_ = 0, month_ = 0, year_ = 0;
                std::tm now_;
                bool allow_zero_date_ = false;
                mutable std::vector<std::string> errors_;
            };

            inline std::string to_string(const Date& field) { return field.to_string(); }

        } // namespace field
    }     // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
