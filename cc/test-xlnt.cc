#include <iostream>

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wdocumentation-unknown-command"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wnewline-eof"
#endif
#include "xlnt/xlnt.hpp"
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------

int main(int argc, char* const argv[])
{
    try {
        xlnt::workbook wb;
        wb.load(argv[1]);
        const auto ws = wb.active_sheet();
        std::cerr << "DEBUG: title: " << ws.title() << '\n';
        std::cerr << "DEBUG: cell-A1: " << ws.cell(1, 1).value<std::string>() << '\n';
          // std::cerr << "DEBUG: rows:" << ws.highest_row() << " columns:" << ws.highest_column().column_string() << '\n';
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
