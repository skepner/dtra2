#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "xlnt.hh"

// ----------------------------------------------------------------------

inline std::string format(std::chrono::nanoseconds duration)
{
    std::stringstream result;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
    if (hours > 24) {
        result << (hours / 24) << "d:";
        hours %= 24;
    }
    auto format_val = [](auto& target, auto val, char terminator) {
                          if (val || target.tellg())
                              target << std::setw(2) << std::setfill('0') << val << terminator;
                      };
    format_val(result, hours, ':');
    const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1)).count();
    format_val(result, minutes, ':');
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1)).count();
    result << std::setw(2) << std::setfill('0') << seconds << '.';
    const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration % std::chrono::seconds(1)).count();
    result << std::setw(6) << std::setfill('0') << microseconds;
    return result.str();
}

// ----------------------------------------------------------------------

int main(int /*argc*/, char* const argv[])
{
    try {
        xlnt::workbook wb;
        auto start = std::chrono::high_resolution_clock::now();
        wb.load(argv[1]);
        std::cerr << "TIME: load: " << format(std::chrono::high_resolution_clock::now() - start) << '\n';
        const auto ws = wb.active_sheet();
        std::cerr << "DEBUG: title: " << ws.title() << '\n';
        std::cerr << "DEBUG: cell-A1: " << ws.cell(1, 1).value<std::string>() << '\n';
        std::cerr << "DEBUG: rows:" << ws.highest_row() << " columns:" << ws.highest_column().column_string() << '\n';
        start = std::chrono::high_resolution_clock::now();
        for (const auto row : ws.rows()) {
            for (const auto cell : row) {
                cell.reference().to_string();
                  // std::cerr << "DEBUG: cell " << cell.reference().to_string() << '\n';
            }
        }
        std::cerr << "TIME: iteratate: " << format(std::chrono::high_resolution_clock::now() - start) << '\n';
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
