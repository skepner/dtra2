#include <map>
#include <regex>

#include "sheet.hh"

// ----------------------------------------------------------------------

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif

using field_importer_t = void (dtra::Record::*)(const xlnt::cell& cell);
static const std::map<std::string, field_importer_t> name_to_importer = {
    {"Sample ID"                    , &dtra::Record::set_sample_id},
    {"Collection Day"               , &dtra::Record::set_collection_day},
    {"Collection Month"             , &dtra::Record::set_collection_month},
    {"Collection Year"              , &dtra::Record::set_collection_year},
    {"Species"                      , &dtra::Record::set_species},
    {"Age"                          , &dtra::Record::set_age},
    {"Sex"                          , &dtra::Record::set_sex},
    {"Ring #"                       , &dtra::Record::set_ring_number},
    {"Host_identifier"              , &dtra::Record::set_host_identifier},
    {"Host Species"                 , &dtra::Record::set_host_species},
    {"Host Common name"             , &dtra::Record::set_host_common_name},
    {"Health"                       , &dtra::Record::set_health},
    {"Capture Method/Capture status", &dtra::Record::set_capture_method_status},
    {"Behavior"                     , &dtra::Record::set_behavior},
    {"Location"                     , &dtra::Record::set_location},
    {"Province"                     , &dtra::Record::set_province},
    {"Country"                      , &dtra::Record::set_country},
    {"Latitude"                     , &dtra::Record::set_latitude},
    {"Longitude"                    , &dtra::Record::set_longitude},
    {"Sample material"              , &dtra::Record::set_sample_material},
    {"Test for influenza virus"     , &dtra::Record::set_test_for_influenza_virus},
    {"Day of Testing"               , &dtra::Record::set_day_of_testing},
    {"Month of Testing"             , &dtra::Record::set_month_of_testing},
    {"Year of Testing"              , &dtra::Record::set_year_of_testing},
    {"Pool ID"                      , &dtra::Record::set_pool_id},
    {"Influenza test result"        , &dtra::Record::set_influenza_test_result},
    {"MA Ct Value"                  , &dtra::Record::set_ma_ct_value},
    {"H5 Status"                    , &dtra::Record::set_h5_status},
    {"H5 Ct Value"                  , &dtra::Record::set_h5_ct_value},
    {"H5 Pathotype"                 , &dtra::Record::set_h5_pathotype},
    {"H7 Status"                    , &dtra::Record::set_h7_status},
    {"H7 Ct Value"                  , &dtra::Record::set_h7_ct_value},
    {"H7 Pathotype"                 , &dtra::Record::set_h7_pathotype},
    {"H9 Status"                    , &dtra::Record::set_h9_status},
    {"H9 Ct Value"                  , &dtra::Record::set_h9_ct_value},
    {"EMC ID"                       , &dtra::Record::set_emc_id},
    {"AHVLA ID"                     , &dtra::Record::set_ahvla_id},
    {"First Egg Passage"            , &dtra::Record::set_first_egg_passage},
    {"Second Egg Passage"           , &dtra::Record::set_second_egg_passage},
    {"Passage Isolation"            , &dtra::Record::set_passage_isolation},
    {"Virus Pathotype"              , &dtra::Record::set_virus_pathotype},
    {"Haemagglutinin Subtype"       , &dtra::Record::set_haemagglutinin_subtype},
    {"Neuraminidase Subtype"        , &dtra::Record::set_neuraminidase_subtype},
    {"Serology Sample ID"           , &dtra::Record::set_serology_sample_id},
    {"Serology Testing Day"         , &dtra::Record::set_serology_testing_day},
    {"Serology Testing Month"       , &dtra::Record::set_serology_testing_month},
    {"Serology Testing Year"        , &dtra::Record::set_serology_testing_year},
    {"Serology Status"              , &dtra::Record::set_serology_status},
    {"*record-id*"                  , &dtra::Record::set_record_id},
};

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------

void dtra::v2::Sheet::read(const char* filename)
{
    report_.clear();

    workbook_.load(filename);
    const auto ws = workbook_.active_sheet();
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
            importers[col] = &Record::set_record_id;
        }
        else {
            report_ = string::join("\n", {report_, string::concat("unrecognized column label ", col.column_string(), " [", label, ']')});
            // std::cerr << "WARNING: unrecognized column label " << col.column_string() << " [" << label << "]\n";
            importers[col] = &Record::importer_default;
        }
    }

    records_.resize(ws.highest_row() - 2);
    auto rows = ws.rows();
    auto row = rows.begin();
    ++row;                      // skipe header
    ++row;
    for (size_t record_no = 0; row != rows.end(); ++row, ++record_no) {
        auto& record = records_[record_no];
        for (const auto cell : *row) {
            std::invoke(importers[cell.reference().column()], record, cell);
        }
        if (const auto report = record.validate(locations_, birds_); !report.empty())
            report_ = string::join("\n", {report_, report});
    }

} // dtra::v2::Sheet::read

// ----------------------------------------------------------------------

void dtra::v2::Sheet::write(const char* filename) const
{
    auto ws = workbook_.active_sheet();
    // erase all cells except header (first two rows)
    for (xlnt::row_t row = 3; row <= ws.highest_row(); ++row)
        ws.clear_row(row);
    // fill in rows
    ws.reserve(records_.size() + 2);
    auto current_cell = xlnt::cell_reference("A3");
    for (const auto& record : records_) {
        ws.cell(current_cell).value(record.sample_id());
        current_cell.column_index(current_cell.column_index() + 1);
        break;
        current_cell.row(current_cell.row() + 1);
        current_cell.column_index("A");
    }
    std::cout << "Writing " << filename << '\n';
    workbook_.save(filename);

} // dtra::v2::Sheet::write

// ----------------------------------------------------------------------

void dtra::v2::Sheet::merge(const Sheet& merge_in)
{

} // dtra::v2::Sheet::merge

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
