#include <iostream>

#include "string.hh"
#include "field.hh"
#include "xlnt.hh"

// ----------------------------------------------------------------------

void dtra::v2::field::Text::from_cell(const xlnt::cell& cell)
{
    value_ = cell.to_string();

} // dtra::v2::field::Text::from_cell

// ----------------------------------------------------------------------

void dtra::v2::field::Text::to_cell(xlnt::cell& cell) const
{
    cell.value(value_);

} // dtra::v2::field::Text::to_cell

// ----------------------------------------------------------------------

std::vector<std::string> dtra::v2::field::Text::validate() const
{
    std::vector<std::string> errors;
    if (!can_be_empty() && empty())
        errors.push_back("cannot be empty");
    return errors;

} // dtra::v2::field::Text::validate

// ----------------------------------------------------------------------

std::vector<std::string> dtra::v2::field::Uppercase::validate() const
{
    auto errors = Text::validate();
    if (errors.empty() && !empty() && re_validator_) {
        if (!std::regex_match(value(), *re_validator_))
            errors.push_back(error_message_);
    }
    return errors;

} // dtra::v2::field::Uppercase::validate

// ----------------------------------------------------------------------

dtra::v2::field::Float& dtra::v2::field::Float::operator=(double source)
{
    value_ = source;
    return *this;

} // dtra::v2::field::Float::operator=

// ----------------------------------------------------------------------

dtra::v2::field::Float& dtra::v2::field::Float::operator=(const std::string& source)
{
    const auto stripped = string::strip(source);
    // std::cerr << "DEBUG: float " << stripped << ' ' << stripped.empty() << '\n';
    if (!stripped.empty()) {
        size_t end;
        try {
            value_ = std::stod(stripped, &end);
            if (end != stripped.size())
                errors_.push_back("number expected");
        }
        catch (std::exception& /*err*/) {
            errors_.push_back("number expected");
        }
    }
    else
        value_.reset();
    return *this;

} // dtra::v2::field::Float::operator=

// ----------------------------------------------------------------------

std::vector<std::string> dtra::v2::field::Float::validate() const
{
    if (errors_.empty()) {
        if (min_ && value_ && value_ < min_)
            errors_.push_back("number out of range");
        else if (max_ && value_ && value_ > max_)
            errors_.push_back("number out of range");
    }
    return errors_;

} // dtra::v2::field::Float::validate

// ----------------------------------------------------------------------

void dtra::v2::field::Float::from_cell(const xlnt::cell& cell)
{
    value_ = cell.value<double>();

} // dtra::v2::field::Float::from_cell

// ----------------------------------------------------------------------

void dtra::v2::field::Float::to_cell(xlnt::cell& cell) const
{
    if (!empty())
        cell.value(*value_);
    else
        cell.clear_value();

} // dtra::v2::field::Float::to_cell

// ----------------------------------------------------------------------

std::string dtra::v2::field::Float::to_string() const
{
    if (empty())
        return {};
    auto result = std::to_string(*value_);
    if (result.find('.') != std::string::npos) { // remove trailing 0's
        while (result.size() > 2 && result.back() == '0' && result[result.size() - 2] != '.')
            result.resize(result.size() - 1 );
    }
    return result;
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
