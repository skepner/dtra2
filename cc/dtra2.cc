#include <iostream>

#include "filesystem.hh"
#include "sheet.hh"
#include "directories.hh"

// ----------------------------------------------------------------------

int main(int argc, char* const argv[])
{
    try {
        if (argc < 2 || argc > 4)
            throw std::runtime_error("Usage: dtra2 <master.xlsx> [<merge-in.xlsx> [<output.xlsx>]]");
        const auto data_dir = fs::path(argv[0]).parent_path() / "../data/";
        const dtra::Directory locations(data_dir / "locations.json");
        const dtra::Directory birds(data_dir / "bird-list.json");
        dtra::Sheet sheet1(locations, birds, argv[1]);
        if (const auto report1 = sheet1.report(); !report1.empty()) {
            std::cerr << report1 << '\n';
            throw std::runtime_error{string::concat("errors in reading ", argv[1])};
        }
        if (argc > 2) {
            dtra::Sheet sheet2(locations, birds, argv[2]);
            if (const auto report2 = sheet2.report(); !report2.empty()) {
                std::cerr << report2 << '\n';
                throw std::runtime_error{string::concat("errors in reading ", argv[2])};
            }
        }
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
