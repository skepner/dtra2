#include <map>
#include <regex>

#include "sheet.hh"

// ----------------------------------------------------------------------

using field_importer_t = void (dtra::Record::*)(const xlnt::cell& cell);
using field_exporter_t = void (dtra::Record::*)(xlnt::cell& cell) const;

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif

static const std::map<std::string, std::pair<field_importer_t, field_exporter_t>> name_to_importer = {
    {"Sample ID"                    , {&dtra::Record::set_sample_id, &dtra::Record::get_sample_id}},
    {"Collection Day"               , {&dtra::Record::set_collection_day, &dtra::Record::get_collection_day}},
    {"Collection Month"             , {&dtra::Record::set_collection_month, &dtra::Record::get_collection_month}},
    {"Collection Year"              , {&dtra::Record::set_collection_year, &dtra::Record::get_collection_year}},
    {"Species"                      , {&dtra::Record::set_species, &dtra::Record::get_species}},
    {"Age"                          , {&dtra::Record::set_age, &dtra::Record::get_age}},
    {"Sex"                          , {&dtra::Record::set_sex, &dtra::Record::get_sex}},
    {"Ring #"                       , {&dtra::Record::set_ring_number, &dtra::Record::get_ring_number}},
    {"Host_identifier"              , {&dtra::Record::set_host_identifier, &dtra::Record::get_host_identifier}},
    {"Host Species"                 , {&dtra::Record::set_host_species, &dtra::Record::get_host_species}},
    {"Host Common name"             , {&dtra::Record::set_host_common_name, &dtra::Record::get_host_common_name}},
    {"Health"                       , {&dtra::Record::set_health, &dtra::Record::get_health}},
    {"Capture Method/Capture status", {&dtra::Record::set_capture_method_status, &dtra::Record::get_capture_method_status}},
    {"Behavior"                     , {&dtra::Record::set_behavior, &dtra::Record::get_behavior}},
    {"Location"                     , {&dtra::Record::set_location, &dtra::Record::get_location}},
    {"Province"                     , {&dtra::Record::set_province, &dtra::Record::get_province}},
    {"Country"                      , {&dtra::Record::set_country, &dtra::Record::get_country}},
    {"Latitude"                     , {&dtra::Record::set_latitude, &dtra::Record::get_latitude}},
    {"Longitude"                    , {&dtra::Record::set_longitude, &dtra::Record::get_longitude}},
    {"Sample material"              , {&dtra::Record::set_sample_material, &dtra::Record::get_sample_material}},
    {"Test for influenza virus"     , {&dtra::Record::set_test_for_influenza_virus, &dtra::Record::get_test_for_influenza_virus}},
    {"Day of Testing"               , {&dtra::Record::set_day_of_testing, &dtra::Record::get_day_of_testing}},
    {"Month of Testing"             , {&dtra::Record::set_month_of_testing, &dtra::Record::get_month_of_testing}},
    {"Year of Testing"              , {&dtra::Record::set_year_of_testing, &dtra::Record::get_year_of_testing}},
    {"Pool ID"                      , {&dtra::Record::set_pool_id, &dtra::Record::get_pool_id}},
    {"Influenza test result"        , {&dtra::Record::set_influenza_test_result, &dtra::Record::get_influenza_test_result}},
    {"MA Ct Value"                  , {&dtra::Record::set_ma_ct_value, &dtra::Record::get_ma_ct_value}},
    {"H5 Status"                    , {&dtra::Record::set_h5_status, &dtra::Record::get_h5_status}},
    {"H5 Ct Value"                  , {&dtra::Record::set_h5_ct_value, &dtra::Record::get_h5_ct_value}},
    {"H5 Pathotype"                 , {&dtra::Record::set_h5_pathotype, &dtra::Record::get_h5_pathotype}},
    {"H7 Status"                    , {&dtra::Record::set_h7_status, &dtra::Record::get_h7_status}},
    {"H7 Ct Value"                  , {&dtra::Record::set_h7_ct_value, &dtra::Record::get_h7_ct_value}},
    {"H7 Pathotype"                 , {&dtra::Record::set_h7_pathotype, &dtra::Record::get_h7_pathotype}},
    {"H9 Status"                    , {&dtra::Record::set_h9_status, &dtra::Record::get_h9_status}},
    {"H9 Ct Value"                  , {&dtra::Record::set_h9_ct_value, &dtra::Record::get_h9_ct_value}},
    {"EMC ID"                       , {&dtra::Record::set_emc_id, &dtra::Record::get_emc_id}},
    {"AHVLA ID"                     , {&dtra::Record::set_ahvla_id, &dtra::Record::get_ahvla_id}},
    {"First Egg Passage"            , {&dtra::Record::set_first_egg_passage, &dtra::Record::get_first_egg_passage}},
    {"Second Egg Passage"           , {&dtra::Record::set_second_egg_passage, &dtra::Record::get_second_egg_passage}},
    {"Passage Isolation"            , {&dtra::Record::set_passage_isolation, &dtra::Record::get_passage_isolation}},
    {"Virus Pathotype"              , {&dtra::Record::set_virus_pathotype, &dtra::Record::get_virus_pathotype}},
    {"Haemagglutinin Subtype"       , {&dtra::Record::set_haemagglutinin_subtype, &dtra::Record::get_haemagglutinin_subtype}},
    {"Neuraminidase Subtype"        , {&dtra::Record::set_neuraminidase_subtype, &dtra::Record::get_neuraminidase_subtype}},
    {"Serology Sample ID"           , {&dtra::Record::set_serology_sample_id, &dtra::Record::get_serology_sample_id}},
    {"Serology Testing Day"         , {&dtra::Record::set_serology_testing_day, &dtra::Record::get_serology_testing_day}},
    {"Serology Testing Month"       , {&dtra::Record::set_serology_testing_month, &dtra::Record::get_serology_testing_month}},
    {"Serology Testing Year"        , {&dtra::Record::set_serology_testing_year, &dtra::Record::get_serology_testing_year}},
    {"Serology Status"              , {&dtra::Record::set_serology_status, &dtra::Record::get_serology_status}},
    {"*record-id*"                  , {&dtra::Record::set_record_id, &dtra::Record::get_record_id}},
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
            importers[col] = found->second.first;
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
      // std::cerr << "DEBUG: write\n";
    auto ws = workbook_.active_sheet();

      // column fillers
    std::map<xlnt::column_t, field_exporter_t> exporters;
    for (xlnt::column_t col = 1; col <= ws.highest_column(); ++col) {
        const auto label = ws.cell(col, 2).value<std::string>();
        if (const auto found = name_to_importer.find(label); found != name_to_importer.end())
            exporters[col] = found->second.second;
        else if (std::regex_match(label, std::regex{"^20[12][0-9]-[01][0-9]-[0-3][0-9]-[0-2][0-9]-[0-5][0-9]-[0-5][0-9]$"})) // sheet id
            exporters[col] = &Record::get_record_id;
        else {
            std::cerr << "WARNING: unrecognized column label " << col.column_string() << " [" << label << "]\n";
            exporters[col] = &Record::exporter_default;
        }
    }

    ws.cell("AW2").value(dtra::Record::new_record_id());

    if ((ws.highest_row() - 2) < records_.size()) {
          // reserve rows
        ws.reserve(records_.size() + 2);
        for (auto row = ws.highest_row() + 1; row < (records_.size() + 3); ++row)
            ws.cell("A", row).value("");
    }
    else {
          // clear redundant rows
        for (xlnt::row_t row = static_cast<xlnt::row_t>(records_.size()) + 3; row <= ws.highest_row(); ++row)
            ws.clear_row(row);
    }
    // std::cerr << "DEBUG: records " << records_.size() << " rows " << (ws.highest_row() - 2) << '\n';

      // fill in rows
    auto rows = ws.rows(false);
    auto row = rows.begin();
    ++row;                      // skipe header
    ++row;
    size_t record_no = 0;
    for (; row != rows.end() && record_no < records_.size(); ++row, ++record_no) {
        const auto& record = records_[record_no];
        for (auto cell : *row) {
            // std::cerr << cell.reference().row() << ' ' << cell.reference().column().index << '\n';
            std::invoke(exporters[cell.reference().column()], record, cell);
        }
    }
    std::cerr << "DEBUG: rows written " << record_no << '\n';

    std::cout << "Writing " << filename << '\n';
    workbook_.save(filename);

} // dtra::v2::Sheet::write

// ----------------------------------------------------------------------

void dtra::v2::Sheet::merge(const Sheet& merge_in)
{
    for (const auto& rec : merge_in.records_) {
        records_.push_back(rec);
    }

} // dtra::v2::Sheet::merge

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
