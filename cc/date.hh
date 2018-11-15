#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include "string.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        class Date
        {
         public:
           Date()
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
                        if (year_ < 2000 || year_ > static_cast<size_t>(now_.tm_year))
                            errors_.push_back("invalid year: " + year);
                    }
                    catch (std::exception&) {
                        errors_.push_back("invalid year: " + year);
                    }
                }

            std::vector<std::string> validate() const
                {
                    if (errors_.empty()) {
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
                    }
                    return errors_;
                }

            std::string to_string() const
                {
                    std::string result(20, ' ');
                    result.resize(static_cast<size_t>(std::snprintf(result.data(), result.size(), "%04lu-%02lu-%02lu", year_, month_, day_)));
                    return result;
                }

         private:
            mutable std::vector<std::string> errors_;
            size_t day_ = 0, month_ = 0, year_ = 0;
            std::tm now_;
        };
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
