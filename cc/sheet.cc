#include <map>
#include <regex>
#include <tuple>
#include <array>
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
                    [&record, this](auto&& pp) {
                        if constexpr (std::is_same_v<std::decay_t<decltype(pp)>, field_ptr_t<dtra::field::Date>>) {
                            if ((record.*pp).empty())
                                return std::string{};
                            switch (date_part_) {
                                case date_part::year:
                                    return std::to_string((record.*pp).year());
                                case date_part::month:
                                    return std::to_string((record.*pp).month());
                                case date_part::day:
                                    return std::to_string((record.*pp).day());
                            }
                        }
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
    auto ws = workbook_.active_sheet();
    const auto highest_column = ws.highest_column();
    const auto highest_row = ws.highest_row();

    ws.cell("AW2").value(dtra::Record::new_record_id());

    if ((highest_row - 2) < records_.size()) {
          // reserve rows
        ws.reserve(records_.size() + 2);
        for (auto row = highest_row + 1; row < (records_.size() + 3); ++row)
            ws.cell("A", row).value("");
    }
    else {
          // clear redundant rows
        for (xlnt::row_t row = static_cast<xlnt::row_t>(records_.size()) + 3; row <= highest_row; ++row)
            ws.clear_row(row);
    }
    // std::cerr << "DEBUG: records " << records_.size() << " rows " << (highest_row - 2) << '\n';

      // fill in rows
    auto rows = ws.rows(false);
    auto row = rows.begin();
    ++row;                      // skipe header
    ++row;
    size_t record_no = 0;
    for (; row != rows.end() && record_no < records_.size(); ++row, ++record_no) {
        const auto& record = records_[record_no];
        for (auto cell : *row)
            accessors_.at(cell.reference().column().index)->to_cell(record, cell);
    }
    std::cerr << "DEBUG: rows written " << record_no << '\n';

    std::cout << "Writing " << filename << '\n';
    workbook_.save(filename);

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
            records_.back().reset_record_id();
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

    const auto ws = workbook_.active_sheet();
    const auto highest_column = ws.highest_column();
    for (xlnt::column_t col = 1; col <= highest_column; ++col) {
        if (const xlnt::cell_reference cr(col, 1); ws.has_cell(cr))
            csv.add_field(ws.cell(cr).value<std::string>());
        else
            csv.add_empty_field();
    }
    csv.new_row();

    for (xlnt::column_t col = 1; col <= highest_column; ++col)
        csv.add_field(ws.cell(col, 2).value<std::string>());
    csv.new_row();

    for (const auto& record : records_) {
        for (unsigned col = 1; col <= highest_column.index; ++col)
            csv.add_field(accessors_.at(col)->csv_value(record));
        csv.new_row();
    }

    std::ofstream output(filename);
    const std::string_view data = csv;
    output.write(data.data(), static_cast<long>(data.size()));

} // dtra::v2::Sheet::write_csv

// ----------------------------------------------------------------------

std::array ceirs_titles{"Project_Identifier",
                        "Contributing_Institution",
                        "Sample_Identifier",
                        "Embargo_End_Date",
                        "Sample_Material",
                        "Sample_Transport_Medium",
                        "Sample_Receipt_Date",
                        "Strain_Name",
                        "Host_Species",
                        "Host_Common_Name",
                        "Host_Identifier",
                        "Host_ID_Type",
                        "Host_Capture_Status",
                        "Host_Health",
                        "Host_Natural_State",
                        "Host_Habitat",
                        "Host_Sex",
                        "Host_Age",
                        "Collector_Name",
                        "Collection_Date",
                        "Collection_Country",
                        "Collection_State_Province",
                        "Collection_City",
                        "Collection_POI",
                        "Collection_Latitude",
                        "Collection_Longitude",
                        "Influenza_Test_Type",
                        "Influenza_Test_Result",
                        "Influenza_Test_Interpretation",
                        "Other_Pathogens_Tested",
                        "Other_Pathogen_Test_Result",
                        "Comments"};

void dtra::v2::Sheet::write_ceirs(const char* filename, std::string first_date, std::string last_date) const
{
    acmacs::CsvWriter csv;
    for (const auto& label : ceirs_titles)
        csv.add_field(label);
    csv.new_row();

    // 2015-12-08
    // For your surveillance, sequencing, and other data submission
    // files, in the fields Sample_Identifier, Host_Identifier, and
    // Virus_Identifier: Please do not use spaces or slashes "/",
    // "\","|". Spaces are removed, slashes changed to dash "-".
    auto fix_identifier = [](std::string text) -> std::string {
        std::string result;
        for (auto cc : text) {
            if (!std::isspace(cc)) {
                switch (cc) {
                    case '/':
                    case '\\':
                    case '|':
                        result.append(1, '-');
                        break;
                    default:
                        result.append(1, cc);
                        break;
                }
            }
        }
        return result;
    };

    const std::unordered_map<std::string, std::string> sample_material_data = {
        {"TS", "TRS"},  // Tracheal swab
        {"OP", "ORP"},  // Oral-pharyngeal
        {"C", "CLO"},   // Cloacal
        {"F", "FEC"},   // Feces
        {"COP", "CCO"}, // Cloacal and oral-pharyngeal samples, when combined into one sample
        {"B", "BLO"},   // Blood
        {"SR", "SER"},  // Serum
        {"TT", "TFT"},  // Tissue from trachea
        {"CF", "CCF"},  // Cloacal and fecal samples, when combined into one sample
        {"TB", "TFB"},  // Tissue from brain
        {"TO", "OTT"},  // Other tissue
        {"L", "LUN"},   // Lungs
        {"S", "SOI"},   // Soil
        {"W", "WAT"},   // Water
        {"U", "U"},     // Unknown
    };
    auto sample_material = [&sample_material_data](const auto& record) -> std::string {
        if (const auto found = sample_material_data.find(record.sample_material_); found != sample_material_data.end())
            return found->second;
        else if (!record.sample_material_.empty() && record.sample_material_.value()[0] == 'O')
            return "OTH" + record.sample_material_.value().substr(1);
        else
            throw std::runtime_error(string::concat("Unsupported Smaple_Material", record.sample_material_.value(), " for ", record.sample_id_.value()));
    };

    for (const auto& record : records_) {
        csv.add_field("SP1-Fouchier_5000");               // Project_Identifier
        csv.add_field("CIP116");                          // "Contributing_Institution"
        csv.add_field(fix_identifier(record.sample_id_)); // "Sample_Identifier"
        csv.add_field("NA");                              // "Embargo_End_Date"
        csv.add_field(sample_material(record));           // "Sample_Material"
        csv.add_field("VTM");                             // "Sample_Transport_Medium"
        csv.add_field();                                  // "Sample_Receipt_Date"
        csv.add_field();                                  // "Strain_Name"
        csv.add_field();                                  // "Host_Species"
        csv.add_field();                                  // "Host_Common_Name"
        csv.add_field();                                  // "Host_Identifier"
        csv.add_field();                                  // "Host_ID_Type"
        csv.add_field();                                  // "Host_Capture_Status"
        csv.add_field();                                  // "Host_Health"
        csv.add_field();                                  // "Host_Natural_State"
        csv.add_field();                                  // "Host_Habitat"
        csv.add_field();                                  // "Host_Sex"
        csv.add_field();                                  // "Host_Age"
        csv.add_field("Nicola Lewis");                    // "Collector_Name"
        csv.add_field();                                  // "Collection_Date"
        csv.add_field();                                  // "Collection_Country"
        csv.add_field();                                  // "Collection_State_Province"
        csv.add_field();                                  // "Collection_City"
        csv.add_field();                                  // "Collection_POI"
        csv.add_field();                                  // "Collection_Latitude"
        csv.add_field();                                  // "Collection_Longitude"
        csv.add_field();                                  // "Influenza_Test_Type"
        csv.add_field();                                  // "Influenza_Test_Result"
        csv.add_field();                                  // "Influenza_Test_Interpretation"
        csv.add_field();                                  // "Other_Pathogens_Tested"
        csv.add_field();                                  // "Other_Pathogen_Test_Result"
        csv.add_field();                                  // "Comments"
        csv.new_row();
    }

    std::ofstream output(filename);
    const std::string_view data = csv;
    output.write(data.data(), static_cast<long>(data.size()));

} // dtra::v2::Sheet::write_ceirs

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
