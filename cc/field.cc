#include "field.hh"

std::vector<std::string> dtra::v2::field::Text::validate() const
{
    std::vector<std::string> errors;
    if (can_be_empty_ == can_be_empty::no && empty())
        errors.push_back("cannot be empty");
    return errors;

} // dtra::v2::field::Text::validate

// ----------------------------------------------------------------------

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif

const std::regex dtra::v2::field::SampleId::re_validator_{"^(217|DT)-[0-9]+$"};

#pragma GCC diagnostic pop

std::vector<std::string> dtra::v2::field::SampleId::validate() const
{
    auto errors = Uppercase::validate();
    if (errors.empty()) {
        if (!std::regex_match(*this, re_validator_))
            errors.push_back("expected: 217-xxxxx, DT-xxxxx");
    }
    return errors;

} // dtra::v2::field::SampleId::validate

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
