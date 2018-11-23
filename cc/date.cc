#include "date.hh"

// ----------------------------------------------------------------------

std::vector<std::string> dtra::v2::field::Date::validate() const
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
            errors_.push_back("cannot be empty");
    }
    return errors_;

} // dtra::v2::field::Date::validate

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
