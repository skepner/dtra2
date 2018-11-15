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

         private:
            std::vector<Record> records_;
        };
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
