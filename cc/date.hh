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

                void set_day(std::string day)
                {
                    try {
                        day_ = std::stoul(day);
                        if (day_ < 1 || day_ > 31)
                            errors_.push_back("invalid day: " + day);
                    }
                    catch (std::exception&) {
                        errors_.push_back("invalid day: " + day);
                    }
                }

                void set_month(std::string month)
                {
                    try {
                        month_ = std::stoul(month);
                        if (month_ < 1 || month_ > 12)
                            errors_.push_back("invalid month: " + month);
                    }
                    catch (std::exception&) {
                        errors_.push_back("invalid month: " + month);
                    }
                }

                void set_year(std::string year)
                {
                    try {
                        year_ = std::stoul(year);
                        if (year_ < 2000 || year_ > static_cast<size_t>(now_.tm_year + 1900))
                            errors_.push_back("invalid year: " + year);
                    }
                    catch (std::exception&) {
                        errors_.push_back("invalid year: " + year);
                    }
                }

                std::vector<std::string> validate() const;

                std::string to_string() const
                {
                    std::string result(20, ' ');
                    result.resize(static_cast<size_t>(std::snprintf(result.data(), result.size(), "%04lu-%02lu-%02lu", year_, month_, day_)));
                    return result;
                }

                std::string year() const
                {
                    if (!year_)
                        return {};
                    std::string result(4, ' ');
                    std::snprintf(result.data(), result.size(), "%04lu", year_);
                    return result;
                }

                std::string month() const
                {
                    if (!month_)
                        return {};
                    std::string result(4, ' ');
                    std::snprintf(result.data(), result.size(), "%02lu", month_);
                    return result;
                }

                std::string day() const
                {
                    if (!day_)
                        return {};
                    std::string result(4, ' ');
                    std::snprintf(result.data(), result.size(), "%02lu", day_);
                    return result;
                }

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
