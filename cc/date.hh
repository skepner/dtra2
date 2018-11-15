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

                std::vector<std::string> validate() const
                {
                    if (errors_.empty()) {
                        if (year_ || month_ || day_) {
                            switch (month_) {
                                case 1:
                                case 3:
                                case 5:
                                case 7:
                                case 8:
                                case 10:
                                case 12:
                                    break;
                                case 2:
                                    if (day_ > 28)
                                        errors_.push_back(::string::concat("invalid day ", day_, " in month ", month_));
                                    break;
                                case 4:
                                case 6:
                                case 9:
                                case 11:
                                    if (day_ > 30)
                                        errors_.push_back(::string::concat("invalid day ", day_, " in month ", month_));
                                    break;
                                default:
                                    errors_.push_back(::string::concat("invalid month ", month_));
                                    break;
                            }
                            if (year_ == static_cast<size_t>(now_.tm_year + 1900)) {
                                if (month_ > static_cast<size_t>(now_.tm_mon + 1))
                                    errors_.push_back(::string::concat("invalid month ", month_, " (future date)"));
                                else if (month_ == static_cast<size_t>(now_.tm_mon + 1) && day_ > static_cast<size_t>(now_.tm_mday))
                                    errors_.push_back(::string::concat("invalid day ", day_, " (future date)"));
                            }
                        }
                        else if (can_be_empty_ == can_be_empty::no)
                            errors_.push_back("date cannot be empty");
                    }
                    return errors_;
                }

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
        }
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
