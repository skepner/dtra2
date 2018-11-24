#pragma once

#include "rjson.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        class Directory
        {
         public:
            Directory(std::string filename);

            const rjson::value& find(std::string key) const { return data_[key]; }
            std::string find(const char* subtree, std::string key) const;

         private:
            rjson::value data_;
        };
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
