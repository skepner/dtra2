#pragma once

#include <vector>

#include "record.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        class Sheet
        {
         public:
            Sheet(const char* filename) { read(filename); }

            void read(const char* filename);
            std::string report() const { return report_; }

         private:
            std::vector<Record> records_;
            std::string report_; // empty, if there are no errors
        };
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
