#include "field.hh"

std::vector<std::string> dtra::v2::field::Text::validate() const
{
    std::vector<std::string> errors;
    if (can_be_empty_ == can_be_empty::no && empty())
        errors.push_back("cannot be empty");
    return errors;

} // dtra::v2::field::Text::validate

// ----------------------------------------------------------------------

std::vector<std::string> dtra::v2::field::Uppercase::validate() const
{
    auto errors = Text::validate();
    if (errors.empty() && !empty() && re_validator_) {
        if (!std::regex_match(*this, *re_validator_))
            errors.push_back(error_message_);
    }
    return errors;

} // dtra::v2::field::Uppercase::validate


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
