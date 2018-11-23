#include "field.hh"

std::vector<std::string> dtra::v2::field::Text::validate() const
{
    std::vector<std::string> errors;
    if (can_be_empty_ == can_be_empty::no && empty())
        errors.push_back("cannot be empty");
    return errors;

} // dtra::v2::field::Text::validate

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
