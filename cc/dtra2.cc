#include <iostream>
#include <vector>
#include <map>
#include <regex>

#include "xlnt.hh"

class Record
{
 public:

    void record_id(const xlnt::cell& cell) {}
    void importer_default(const xlnt::cell& cell) {}

};

using DtraData = std::vector<Record>;

static DtraData read_sheet(const char* filename);

// ----------------------------------------------------------------------

int main(int argc, char* const argv[])
{
    try {
        if (argc < 2 || argc > 4)
            throw std::runtime_error("Usage: dtra2 <master.xlsx> [<merge-in.xlsx> [<output.xlsx>]]");
        read_sheet(argv[1]);
        if (argc > 2)
            read_sheet(argv[2]);
        return 0;
    }
    catch (std::exception& err) {
        std::cerr << "ERROR: " << err.what() << '\n';
        return 1;
    }
}

// ----------------------------------------------------------------------

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif

using field_importer_t = void (Record::*)(const xlnt::cell& cell);
const std::map<std::string, field_importer_t> name_to_importer = {
    {"Sample ID", &Record::importer_default},
    {"Collection Day"               , &Record::importer_default},
    {"Collection Month"             , &Record::importer_default},
    {"Collection Year"              , &Record::importer_default},
    {"Species"                      , &Record::importer_default},
    {"Age"                          , &Record::importer_default},
    {"Sex"                          , &Record::importer_default},
    {"Ring #"                       , &Record::importer_default},
    {"Host_identifier"              , &Record::importer_default},
    {"Host Species"                 , &Record::importer_default},
    {"Host Common name"             , &Record::importer_default},
    {"Health"                       , &Record::importer_default},
    {"Capture Method/Capture status", &Record::importer_default},
    {"Behavior"                     , &Record::importer_default},
    {"Location"                     , &Record::importer_default},
    {"Province"                     , &Record::importer_default},
    {"Country"                      , &Record::importer_default},
    {"Latitude"                     , &Record::importer_default},
    {"Longitude"                    , &Record::importer_default},
    {"Sample material"              , &Record::importer_default},
    {"Test for influenza virus"     , &Record::importer_default},
    {"Day of Testing"               , &Record::importer_default},
    {"Month of Testing"             , &Record::importer_default},
    {"Year of Testing"              , &Record::importer_default},
    {"Pool ID"                      , &Record::importer_default},
    {"Influenza test result"        , &Record::importer_default},
    {"MA Ct Value"                  , &Record::importer_default},
    {"H5 Status"                    , &Record::importer_default},
    {"H5 Ct Value"                  , &Record::importer_default},
    {"H5 Pathotype"                 , &Record::importer_default},
    {"H7 Status"                    , &Record::importer_default},
    {"H7 Ct Value"                  , &Record::importer_default},
    {"H7 Pathotype"                 , &Record::importer_default},
    {"H9 Status"                    , &Record::importer_default},
    {"H9 Ct Value"                  , &Record::importer_default},
    {"EMC ID"                       , &Record::importer_default},
    {"AHVLA ID"                     , &Record::importer_default},
    {"First Egg Passage"            , &Record::importer_default},
    {"Second Egg Passage"           , &Record::importer_default},
    {"Passage Isolation"            , &Record::importer_default},
    {"Virus Pathotype"              , &Record::importer_default},
    {"Haemagglutinin Subtype"       , &Record::importer_default},
    {"Neuraminidase Subtype"        , &Record::importer_default},
    {"Serology Sample ID"           , &Record::importer_default},
    {"Serology Testing Day"         , &Record::importer_default},
    {"Serology Testing Month"       , &Record::importer_default},
    {"Serology Testing Year"        , &Record::importer_default},
    {"Serology Status"              , &Record::importer_default},
    {"*record-id*"                  , &Record::importer_default},
};

#pragma GCC diagnostic pop

DtraData read_sheet(const char* filename)
{
    xlnt::workbook wb;
    wb.load(filename);
    const auto ws = wb.active_sheet();
    if (ws.cell(1, 1).value<std::string>() != "DTRA version 2")
        throw std::runtime_error("\"DTRA version 2\" not found in cell A1");
    std::cerr << "DEBUG: rows:" << ws.highest_row() << " columns:" << ws.highest_column().column_string() << '\n';

    std::map<xlnt::column_t, field_importer_t> importers;
    for (xlnt::column_t col = 1; col <= ws.highest_column(); ++col) {
        const auto label = ws.cell(col, 2).value<std::string>();
        if (const auto found = name_to_importer.find(label); found != name_to_importer.end()) {
            importers[col] = found->second;
        }
        else if (std::regex_match(label, std::regex{"^20[12][0-9]-[01][0-9]-[0-3][0-9]-[0-2][0-9]-[0-5][0-9]-[0-5][0-9]$"})) { // sheet id
            std::cout << "sheet-id: " << label << '\n';
            importers[col] = &Record::record_id;
        }
        else {
            std::cerr << "WARNING: unrecognized column label " << col.column_string() << " [" << label << "]\n";
            importers[col] = &Record::importer_default;
        }
    }

    DtraData data;
    for (xlnt::row_t row = 3; row <= ws.highest_row(); ++row) {
        // std::cerr << "row " << row << '\n';
        auto& record = data.emplace_back();
        for (xlnt::column_t col = 1; col <= ws.highest_column(); ++col) {
            if (const xlnt::cell_reference cell_ref(col, row); ws.has_cell(cell_ref)) {
                // std::cerr << "col " << col.column_string() << ' ' << ws.cell(cell_ref).to_string() << '\n';
                std::invoke(importers[col], record, ws.cell(cell_ref));
            }
        }
    }
    return data;

} // read_sheet

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
