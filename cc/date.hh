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
            class Date
            {
              public:
                Date(can_be_empty cbe = can_be_empty::yes) : can_be_empty_{cbe}
                {
                    const auto now = std::chrono::system_clock::now();
                    const auto now_c = std::chrono::system_clock::to_time_t(now);
                    now_ = *std::localtime(&now_c);
                }

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
                std::string year() const;
                std::string month() const;
                std::string day() const;

              private:
                const can_be_empty can_be_empty_ = can_be_empty::yes;
                size_t day_ = 0, month_ = 0, year_ = 0;
                std::tm now_;
                mutable std::vector<std::string> errors_;
            };
        } // namespace field
    }     // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
