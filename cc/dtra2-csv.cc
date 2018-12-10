#include <iostream>

#include "filesystem.hh"
#include "sheet.hh"
#include "directories.hh"

// ----------------------------------------------------------------------

int main(int argc, char* const argv[])
{
    try {
        if (argc < 3)
            throw std::runtime_error("Usage: dtra2 [--allow-zero-date] <source.xlsx> <output.csv>");
        const auto data_dir = fs::path(argv[0]).parent_path() / "../data/";
        const dtra::Directory locations(data_dir / "locations.json");
        const dtra::Directory birds(data_dir / "bird-list.json");
        int source_arg_no = 1, output_arg_no = 2;
        bool allow_zero_date = false;
        if (std::string_view(argv[1]) == "--allow-zero-date") {
            allow_zero_date = true;
            source_arg_no = 2;
            output_arg_no = 3;
        }
        dtra::Sheet sheet1(locations, birds, argv[source_arg_no], allow_zero_date);
        if (const auto report1 = sheet1.report(); !report1.empty()) {
            std::cerr << report1 << '\n';
            throw std::runtime_error{string::concat("errors in reading ", argv[source_arg_no])};
        }
        sheet1.write_csv(argv[output_arg_no]);
        return 0;
    }
    catch (std::exception& err) {
        std::cerr << "ERROR: " << err.what() << '\n';
        return 1;
    }
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
