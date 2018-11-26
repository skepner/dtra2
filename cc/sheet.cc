#include <map>
#include <regex>
#include <tuple>
#include <fstream>

#include "sheet.hh"
#include "csv.hh"

// ----------------------------------------------------------------------


// template <typename T> dtra::field::Field* get(dtra::Record& record, field_ptr_t<T> field)
// {
//     return &record.*field;
// }

// using field_t = dtra::field::Field dtra::Record::*;
// field_t xx = &dtra::Record::sample_id_;

// ----------------------------------------------------------------------

namespace dtra
{
    inline namespace v2
    {
        template <typename T> using field_ptr_t = T dtra::Record::*;

        class Accessor
        {
          public:
            enum class date_part { year, month, day };

            template <typename T> Accessor(field_ptr_t<T> ptr) : ptr_{ptr} {}
            Accessor(field_ptr_t<dtra::field::Date> ptr, enum date_part date_part) : ptr_{ptr}, date_part_{date_part} {}

            std::string csv_value(const dtra::Record& record) const
            {
                return std::visit(
                    [&record](auto&& pp) {
                        if constexpr (std::is_same_v<std::decay_t<decltype(pp)>, field_ptr_t<dtra::field::Date>>)
                            return (record.*pp).csv_value();
                        else
                            return (record.*pp).csv_value();
                    },
                    ptr_);
            }

            void from_cell(dtra::Record& record, const xlnt::cell& cell) const
            {
                std::visit(
                    [&record, &cell, this](auto&& pp) {
                        if constexpr (std::is_same_v<std::decay_t<decltype(pp)>, field_ptr_t<dtra::field::Date>>) {
                            switch (date_part_) {
                                case date_part::year:
                                    (record.*pp).set_year(cell.to_string());
                                    break;
                                case date_part::month:
                                    (record.*pp).set_month(cell.to_string());
                                    break;
                                case date_part::day:
                                    (record.*pp).set_day(cell.to_string());
                                    break;
                            }
                        }
                        else
                            (record.*pp).from_cell(cell);
                    },
                    ptr_);
            }

            void to_cell(const dtra::Record& record, xlnt::cell& cell) const
            {
                std::visit(
                    [&record, &cell, this](auto&& pp) {
                        if constexpr (std::is_same_v<std::decay_t<decltype(pp)>, field_ptr_t<dtra::field::Date>>) {
                            switch (date_part_) {
                                case date_part::year:
                                    cell.value((record.*pp).year());
                                    break;
                                case date_part::month:
                                    cell.value((record.*pp).month());
                                    break;
                                case date_part::day:
                                    cell.value((record.*pp).day());
                                    break;
                            }
                        }
                        else
                            (record.*pp).to_cell(cell);
                    },
                    ptr_);
            }

          private:
            std::variant<field_ptr_t<dtra::field::Text>, field_ptr_t<dtra::field::Uppercase>, field_ptr_t<dtra::field::Date>, field_ptr_t<dtra::field::Float>> ptr_;
            date_part date_part_ = date_part::year;
        };
    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif

static const std::map<std::string, const dtra::Accessor> name_to_accessor = {
    {"Sample ID", {&dtra::Record::sample_id_}},
    {"Collection Day", {&dtra::Record::collection_date_, dtra::Accessor::date_part::day}},
    {"Collection Month", {&dtra::Record::collection_date_, dtra::Accessor::date_part::month}},
    {"Collection Year", {&dtra::Record::collection_date_, dtra::Accessor::date_part::year}},
    {"Species", {&dtra::Record::species_}},
    {"Age", {&dtra::Record::age_}},
    {"Sex", {&dtra::Record::sex_}},
    {"Ring #", {&dtra::Record::ring_number_}},
    {"Host_identifier", {&dtra::Record::host_identifier_}},
    {"Host Species", {&dtra::Record::host_species_}},
    {"Host Common name", {&dtra::Record::host_common_name_}},
    {"Health", {&dtra::Record::health_}},
    {"Capture Method/Capture status", {&dtra::Record::capture_method_status_}},
    {"Behavior", {&dtra::Record::behavior_}},
    {"Location", {&dtra::Record::location_}},
    {"Province", {&dtra::Record::province_}},
    {"Country", {&dtra::Record::country_}},
    {"Latitude", {&dtra::Record::latitude_}},
    {"Longitude", {&dtra::Record::longitude_}},
    {"Sample material", {&dtra::Record::sample_material_}},
    {"Test for influenza virus", {&dtra::Record::test_for_influenza_virus_}},
    {"Day of Testing", {&dtra::Record::date_of_testing_, dtra::Accessor::date_part::day}},
    {"Month of Testing", {&dtra::Record::date_of_testing_, dtra::Accessor::date_part::month}},
    {"Year of Testing", {&dtra::Record::date_of_testing_, dtra::Accessor::date_part::year}},
    {"Pool ID", {&dtra::Record::pool_id_}},
    {"Influenza test result", {&dtra::Record::influenza_test_result_}},
    {"MA Ct Value", {&dtra::Record::ma_ct_value_}},
    {"H5 Status", {&dtra::Record::h5_status_}},
    {"H5 Ct Value", {&dtra::Record::h5_ct_value_}},
    {"H5 Pathotype", {&dtra::Record::h5_pathotype_}},
    {"H7 Status", {&dtra::Record::h7_status_}},
    {"H7 Ct Value", {&dtra::Record::h7_ct_value_}},
    {"H7 Pathotype", {&dtra::Record::h7_pathotype_}},
    {"H9 Status", {&dtra::Record::h9_status_}},
    {"H9 Ct Value", {&dtra::Record::h9_ct_value_}},
    {"EMC ID", {&dtra::Record::emc_id_}},
    {"AHVLA ID", {&dtra::Record::ahvla_id_}},
    {"First Egg Passage", {&dtra::Record::first_egg_passage_}},
    {"Second Egg Passage", {&dtra::Record::second_egg_passage_}},
    {"Passage Isolation", {&dtra::Record::passage_isolation_}},
    {"Virus Pathotype", {&dtra::Record::virus_pathotype_}},
    {"Haemagglutinin Subtype", {&dtra::Record::haemagglutinin_subtype_}},
    {"Neuraminidase Subtype", {&dtra::Record::neuraminidase_subtype_}},
    {"Serology Sample ID", {&dtra::Record::serology_sample_id_}},
    {"Serology Testing Day", {&dtra::Record::serology_testing_date_, dtra::Accessor::date_part::day}},
    {"Serology Testing Month", {&dtra::Record::serology_testing_date_, dtra::Accessor::date_part::month}},
    {"Serology Testing Year", {&dtra::Record::serology_testing_date_, dtra::Accessor::date_part::year}},
    {"Serology Status", {&dtra::Record::serology_status_}},
    {"*record-id*", {&dtra::Record::record_id_}}
};

// using field_importer_t = void (dtra::Record::*)(const xlnt::cell& cell);
// using field_exporter_t = void (dtra::Record::*)(xlnt::cell& cell) const;
// using csv_exporter_t = std::string (dtra::Record::*)() const;

// static const std::map<std::string, std::tuple<field_importer_t, field_exporter_t, csv_exporter_t>> name_to_importer = {
//     {"Sample ID"                    , {&dtra::Record::set_sample_id, &dtra::Record::get_sample_id, &dtra::Record::csv_sample_id}},
//     {"Collection Day"               , {&dtra::Record::set_collection_day, &dtra::Record::get_collection_day, &dtra::Record::csv_collection_day}},
//     {"Collection Month"             , {&dtra::Record::set_collection_month, &dtra::Record::get_collection_month, &dtra::Record::csv_collection_month}},
//     {"Collection Year"              , {&dtra::Record::set_collection_year, &dtra::Record::get_collection_year, &dtra::Record::csv_collection_year}},
//     {"Species"                      , {&dtra::Record::set_species, &dtra::Record::get_species, &dtra::Record::csv_species}},
//     {"Age"                          , {&dtra::Record::set_age, &dtra::Record::get_age, &dtra::Record::csv_age}},
//     {"Sex"                          , {&dtra::Record::set_sex, &dtra::Record::get_sex, &dtra::Record::csv_sex}},
//     {"Ring #"                       , {&dtra::Record::set_ring_number, &dtra::Record::get_ring_number, &dtra::Record::csv_ring_number}},
//     {"Host_identifier"              , {&dtra::Record::set_host_identifier, &dtra::Record::get_host_identifier, &dtra::Record::csv_host_identifier}},
//     {"Host Species"                 , {&dtra::Record::set_host_species, &dtra::Record::get_host_species, &dtra::Record::csv_host_species}},
//     {"Host Common name"             , {&dtra::Record::set_host_common_name, &dtra::Record::get_host_common_name, &dtra::Record::csv_host_common_name}},
//     {"Health"                       , {&dtra::Record::set_health, &dtra::Record::get_health, &dtra::Record::csv_health}},
//     {"Capture Method/Capture status", {&dtra::Record::set_capture_method_status, &dtra::Record::get_capture_method_status, &dtra::Record::csv_capture_method_status}},
//     {"Behavior"                     , {&dtra::Record::set_behavior, &dtra::Record::get_behavior, &dtra::Record::csv_behavior}},
//     {"Location"                     , {&dtra::Record::set_location, &dtra::Record::get_location, &dtra::Record::csv_location}},
//     {"Province"                     , {&dtra::Record::set_province, &dtra::Record::get_province, &dtra::Record::csv_province}},
//     {"Country"                      , {&dtra::Record::set_country, &dtra::Record::get_country, &dtra::Record::csv_country}},
//     {"Latitude"                     , {&dtra::Record::set_latitude, &dtra::Record::get_latitude, &dtra::Record::csv_latitude}},
//     {"Longitude"                    , {&dtra::Record::set_longitude, &dtra::Record::get_longitude, &dtra::Record::csv_longitude}},
//     {"Sample material"              , {&dtra::Record::set_sample_material, &dtra::Record::get_sample_material, &dtra::Record::csv_sample_material}},
//     {"Test for influenza virus"     , {&dtra::Record::set_test_for_influenza_virus, &dtra::Record::get_test_for_influenza_virus, &dtra::Record::csv_test_for_influenza_virus}},
//     {"Day of Testing"               , {&dtra::Record::set_day_of_testing, &dtra::Record::get_day_of_testing, &dtra::Record::csv_day_of_testing}},
//     {"Month of Testing"             , {&dtra::Record::set_month_of_testing, &dtra::Record::get_month_of_testing, &dtra::Record::csv_month_of_testing}},
//     {"Year of Testing"              , {&dtra::Record::set_year_of_testing, &dtra::Record::get_year_of_testing, &dtra::Record::csv_year_of_testing}},
//     {"Pool ID"                      , {&dtra::Record::set_pool_id, &dtra::Record::get_pool_id, &dtra::Record::csv_pool_id}},
//     {"Influenza test result"        , {&dtra::Record::set_influenza_test_result, &dtra::Record::get_influenza_test_result, &dtra::Record::csv_influenza_test_result}},
//     {"MA Ct Value"                  , {&dtra::Record::set_ma_ct_value, &dtra::Record::get_ma_ct_value, &dtra::Record::csv_ma_ct_value}},
//     {"H5 Status"                    , {&dtra::Record::set_h5_status, &dtra::Record::get_h5_status, &dtra::Record::csv_h5_status}},
//     {"H5 Ct Value"                  , {&dtra::Record::set_h5_ct_value, &dtra::Record::get_h5_ct_value, &dtra::Record::csv_h5_ct_value}},
//     {"H5 Pathotype"                 , {&dtra::Record::set_h5_pathotype, &dtra::Record::get_h5_pathotype, &dtra::Record::csv_h5_pathotype}},
//     {"H7 Status"                    , {&dtra::Record::set_h7_status, &dtra::Record::get_h7_status, &dtra::Record::csv_h7_status}},
//     {"H7 Ct Value"                  , {&dtra::Record::set_h7_ct_value, &dtra::Record::get_h7_ct_value, &dtra::Record::csv_h7_ct_value}},
//     {"H7 Pathotype"                 , {&dtra::Record::set_h7_pathotype, &dtra::Record::get_h7_pathotype, &dtra::Record::csv_h7_pathotype}},
//     {"H9 Status"                    , {&dtra::Record::set_h9_status, &dtra::Record::get_h9_status, &dtra::Record::csv_h9_status}},
//     {"H9 Ct Value"                  , {&dtra::Record::set_h9_ct_value, &dtra::Record::get_h9_ct_value, &dtra::Record::csv_h9_ct_value}},
//     {"EMC ID"                       , {&dtra::Record::set_emc_id, &dtra::Record::get_emc_id, &dtra::Record::csv_emc_id}},
//     {"AHVLA ID"                     , {&dtra::Record::set_ahvla_id, &dtra::Record::get_ahvla_id, &dtra::Record::csv_ahvla_id}},
//     {"First Egg Passage"            , {&dtra::Record::set_first_egg_passage, &dtra::Record::get_first_egg_passage, &dtra::Record::csv_first_egg_passage}},
//     {"Second Egg Passage"           , {&dtra::Record::set_second_egg_passage, &dtra::Record::get_second_egg_passage, &dtra::Record::csv_second_egg_passage}},
//     {"Passage Isolation"            , {&dtra::Record::set_passage_isolation, &dtra::Record::get_passage_isolation, &dtra::Record::csv_passage_isolation}},
//     {"Virus Pathotype"              , {&dtra::Record::set_virus_pathotype, &dtra::Record::get_virus_pathotype, &dtra::Record::csv_virus_pathotype}},
//     {"Haemagglutinin Subtype"       , {&dtra::Record::set_haemagglutinin_subtype, &dtra::Record::get_haemagglutinin_subtype, &dtra::Record::csv_haemagglutinin_subtype}},
//     {"Neuraminidase Subtype"        , {&dtra::Record::set_neuraminidase_subtype, &dtra::Record::get_neuraminidase_subtype, &dtra::Record::csv_neuraminidase_subtype}},
//     {"Serology Sample ID"           , {&dtra::Record::set_serology_sample_id, &dtra::Record::get_serology_sample_id, &dtra::Record::csv_serology_sample_id}},
//     {"Serology Testing Day"         , {&dtra::Record::set_serology_testing_day, &dtra::Record::get_serology_testing_day, &dtra::Record::csv_serology_testing_day}},
//     {"Serology Testing Month"       , {&dtra::Record::set_serology_testing_month, &dtra::Record::get_serology_testing_month, &dtra::Record::csv_serology_testing_month}},
//     {"Serology Testing Year"        , {&dtra::Record::set_serology_testing_year, &dtra::Record::get_serology_testing_year, &dtra::Record::csv_serology_testing_year}},
//     {"Serology Status"              , {&dtra::Record::set_serology_status, &dtra::Record::get_serology_status, &dtra::Record::csv_serology_status}},
//     {"*record-id*"                  , {&dtra::Record::set_record_id, &dtra::Record::get_record_id, &dtra::Record::csv_record_id}},
// };

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------

void dtra::v2::Sheet::make_index(const xlnt::worksheet& worksheet)
{
    if (accessors_.empty()) {
        const auto highest_column = worksheet.highest_column();
        for (xlnt::column_t col = 1; col <= highest_column; ++col) {
            const auto label = worksheet.cell(col, 2).value<std::string>();
            if (const auto found = name_to_accessor.find(label); found != name_to_accessor.end()) {
                accessors_[col.index] = &found->second;
            }
            else if (std::regex_match(label, std::regex{"^20[12][0-9]-[01][0-9]-[0-3][0-9]-[0-2][0-9]-[0-5][0-9]-[0-5][0-9]$"})) { // sheet id
                std::cout << "sheet-id: " << label << '\n';
                accessors_[col.index] = &name_to_accessor.find("*record-id*")->second;
            }
            else {
                report_ = string::join("\n", {report_, string::concat("unrecognized column label ", col.column_string(), " [", label, ']')});
                // std::cerr << "WARNING: unrecognized column label " << col.column_string() << " [" << label << "]\n";
            }
        }
    }

} // dtra::v2::Sheet::make_index

// ----------------------------------------------------------------------

void dtra::v2::Sheet::read(const char* filename)
{
    report_.clear();

    workbook_.load(filename);
    const auto ws = workbook_.active_sheet();
    if (ws.cell(1, 1).value<std::string>() != "DTRA version 2")
        throw std::runtime_error("\"DTRA version 2\" not found in cell A1");
    make_index(ws);

    const auto highest_column = ws.highest_column();
    std::cerr << "DEBUG: rows:" << ws.highest_row() << " columns:" << highest_column.column_string() << '\n';

    records_.resize(ws.highest_row() - 2);
    auto rows = ws.rows();
    auto row = rows.begin();
    ++row;                      // skipe header
    ++row;
    for (size_t record_no = 0; row != rows.end(); ++row, ++record_no) {
        auto& record = records_[record_no];
        for (const auto cell : *row)
            accessors_[cell.reference().column().index]->from_cell(record, cell);
        if (const auto report = record.validate(locations_, birds_); !report.empty())
            report_ = string::join("\n", {report_, report});
    }

} // dtra::v2::Sheet::read

// ----------------------------------------------------------------------

void dtra::v2::Sheet::write(const char* filename) const
{
    //   // std::cerr << "DEBUG: write\n";
    // auto ws = workbook_.active_sheet();
    // const auto highest_column = ws.highest_column();

    //   // column fillers
    // std::map<xlnt::column_t, field_exporter_t> exporters;
    // for (xlnt::column_t col = 1; col <= highest_column; ++col) {
    //     const auto label = ws.cell(col, 2).value<std::string>();
    //     if (const auto found = name_to_importer.find(label); found != name_to_importer.end())
    //         exporters[col] = std::get<field_exporter_t>(found->second);
    //     else if (std::regex_match(label, std::regex{"^20[12][0-9]-[01][0-9]-[0-3][0-9]-[0-2][0-9]-[0-5][0-9]-[0-5][0-9]$"})) // sheet id
    //         exporters[col] = &Record::get_record_id;
    //     else {
    //         std::cerr << "WARNING: unrecognized column label " << col.column_string() << " [" << label << "]\n";
    //         exporters[col] = &Record::exporter_default;
    //     }
    // }

    // ws.cell("AW2").value(dtra::Record::new_record_id());

    // const auto highest_row = ws.highest_row();
    // if ((highest_row - 2) < records_.size()) {
    //       // reserve rows
    //     ws.reserve(records_.size() + 2);
    //     for (auto row = highest_row + 1; row < (records_.size() + 3); ++row)
    //         ws.cell("A", row).value("");
    // }
    // else {
    //       // clear redundant rows
    //     for (xlnt::row_t row = static_cast<xlnt::row_t>(records_.size()) + 3; row <= highest_row; ++row)
    //         ws.clear_row(row);
    // }
    // // std::cerr << "DEBUG: records " << records_.size() << " rows " << (highest_row - 2) << '\n';

    //   // fill in rows
    // auto rows = ws.rows(false);
    // auto row = rows.begin();
    // ++row;                      // skipe header
    // ++row;
    // size_t record_no = 0;
    // for (; row != rows.end() && record_no < records_.size(); ++row, ++record_no) {
    //     const auto& record = records_[record_no];
    //     for (auto cell : *row) {
    //         // std::cerr << cell.reference().row() << ' ' << cell.reference().column().index << '\n';
    //         std::invoke(exporters[cell.reference().column()], record, cell);
    //     }
    // }
    // std::cerr << "DEBUG: rows written " << record_no << '\n';

    // std::cout << "Writing " << filename << '\n';
    // workbook_.save(filename);

} // dtra::v2::Sheet::write

// ----------------------------------------------------------------------

void dtra::v2::Sheet::merge(const Sheet& merge_in)
{
    for (const auto& rec : merge_in.records_) {
        if (auto* target = find(rec.sample_id_); target) {
            const auto report = target->merge(rec);
            report_ = string::join("\n", {report_, report});
        }
        else {
            records_.push_back(rec);
        }
    }

} // dtra::v2::Sheet::merge

// ----------------------------------------------------------------------

dtra::v2::Record* dtra::v2::Sheet::find(const dtra::v2::field::Uppercase& sample_id)
{
    for (auto& rec : records_)
        if (rec.sample_id_ == sample_id)
            return &rec;
    return nullptr;

} // dtra::v2::Sheet::find

// ----------------------------------------------------------------------

void dtra::v2::Sheet::write_csv(const char* filename) const
{
    acmacs::CsvWriter csv;

    // const auto ws = workbook_.active_sheet();
    // const auto highest_column = ws.highest_column();
    // for (xlnt::column_t col = 1; col <= highest_column; ++col) {
    //     if (const xlnt::cell_reference cr(col, 1); ws.has_cell(cr))
    //         csv.add_field(ws.cell(cr).value<std::string>());
    //     else
    //         csv.add_empty_field();
    // }
    // csv.new_row();
    //   // column fillers
    // std::map<unsigned, csv_exporter_t> exporters;
    // for (xlnt::column_t col = 1; col <= highest_column; ++col) {
    //     const auto label = ws.cell(col, 2).value<std::string>();
    //     csv.add_field(label);
    //     if (const auto found = name_to_importer.find(label); found != name_to_importer.end())
    //         exporters[col.index] = std::get<csv_exporter_t>(found->second);
    //     else if (std::regex_match(label, std::regex{"^20[12][0-9]-[01][0-9]-[0-3][0-9]-[0-2][0-9]-[0-5][0-9]-[0-5][0-9]$"})) // sheet id
    //         exporters[col.index] = &Record::csv_record_id;
    //     else {
    //         std::cerr << "WARNING: unrecognized column label " << col.index << " [" << label << "]\n";
    //         exporters[col.index] = &Record::csv_exporter_default;
    //     }
    // }
    // csv.new_row();

    // for (const auto& record : records_) {
    //     for (size_t col = 1; col <= highest_column.index; ++col)
    //         csv.add_field(std::invoke(exporters[static_cast<unsigned>(col)], record));
    //     csv.new_row();
    // }

    std::ofstream output(filename);
    const std::string_view data = csv;
    output.write(data.data(), static_cast<long>(data.size()));

} // dtra::v2::Sheet::write_csv

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
