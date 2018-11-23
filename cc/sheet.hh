#pragma once

#include <vector>

#include "record.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        class Directory;

        class Sheet
        {
         public:
            Sheet(const Directory& locations, const Directory& birds, const char* filename) : locations_{locations}, birds_{birds} { read(filename); }

            void read(const char* filename);
            std::string report() const { return report_; }

         private:
            std::vector<Record> records_;
            std::string report_; // empty, if there are no errors
            const Directory& locations_;
            const Directory& birds_;
        };
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
