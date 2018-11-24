#include "directories.hh"

// ----------------------------------------------------------------------

dtra::v2::Directory::Directory(std::string filename)
    : data_{rjson::parse_file(filename)}
{

} // dtra::v2::Directory::Directory

// ----------------------------------------------------------------------

std::string dtra::v2::Directory::find(const char* subtree, std::string key) const
{
    if (const auto& root = data_[subtree]; !root.is_null()) {
        return root[key].get_or_default("");
    }
    return {};

} // dtra::v2::Directory::find

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
