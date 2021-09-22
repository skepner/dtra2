#pragma once

#include <vector>
#include <variant>

#include "xlnt.hh"
#include "record.hh"

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        class Directory;
        class Accessor;

        class Sheet
        {
          public:
            Sheet(const Directory& locations, const Directory& birds, const char* filename, bool allow_zero_date = false)
                : locations_{locations}, birds_{birds}, allow_zero_date_{allow_zero_date} { read(filename); }

            void read(const char* filename);
            void write(const char* filename) const;
            void write_csv(const char* filename) const;
            void write_ceirs(const char* filename, std::string first_date, std::string last_date) const;
            void merge(const Sheet& merge_in, bool resolve_conflict_with_merge_in);
            std::string report() const { return report_; }
            bool unresolved_conflicts() const { return unresolved_conflicts_; }

          private:
            mutable xlnt::workbook workbook_;
            std::vector<Record> records_;
            std::string report_; // empty, if there are no errors
            const Directory& locations_;
            const Directory& birds_;
            const bool allow_zero_date_;
            std::unordered_map<unsigned, const dtra::Accessor*> accessors_;
            bool unresolved_conflicts_{false};

            Record* find(const field::Uppercase& sample_id);
            void make_index(const xlnt::worksheet& worksheet);

        };

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
