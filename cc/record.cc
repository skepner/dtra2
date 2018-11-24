#include "xlnt.hh"
#include "float.hh"
#include "record.hh"
#include "directories.hh"

// ----------------------------------------------------------------------

void dtra::v2::Record::importer_default(const xlnt::cell& /*cell*/)
{

} // dtra::v2::Record::importer_default

// ----------------------------------------------------------------------

std::string dtra::v2::Record::validate(const Directory& locations, const Directory& birds)
{
    // There are internal dependencies between fields of the record:
    // 1. If "capture method/capture status" is K, then enforce "health' to be U
    // 2. If "sample material" contains OP, convert it to TS.
    //     Nicola 2014-11-28 13:48: OP and TS are pretty much the same
    //     thing. One is oro-pharyngeal swab and one is tracheal
    //     swab. No-one accurately records whether they get past the
    //     larynx into the tracheal for each swab and likely it makes no
    //     difference as virus will be in both sites.

    if (capture_method_status_ == "K")
        health_ = "U";
    if (sample_material_ == "OP")
        sample_material_ = "TS";

    std::vector<std::string> reports;
    auto add_report = [&reports](std::string field_name, const auto& field) {
        if (const auto field_report = field.validate(); !field_report.empty()) {
            for (const auto& subreport : field_report)
                reports.push_back(field_name + ": " + subreport);
        }
    };

    add_report("Sample ID", sample_id_);
    add_report("Collection Date", collection_date_);
    add_report("Species", species_);
    add_report("Age", age_);
    add_report("Sex", sex_);
    add_report("Ring #", ring_number_);
    add_report("Host_identifier", host_identifier_);
    add_report("Host Species", host_species_);
    add_report("Host Common name", host_common_name_);
    add_report("Health", health_);
    add_report("Capture Method/Capture status", capture_method_status_);
    add_report("Behavior", behavior_);
    add_report("Location", location_);
    add_report("Province", province_);
    add_report("Country", country_);
    add_report("Latitude", latitude_);
    add_report("Longitude", longitude_);
    add_report("Sample material", sample_material_);
    add_report("Test for influenza virus", test_for_influenza_virus_);
    add_report("Date of Testing", date_of_testing_);
    add_report("Pool ID", pool_id_);
    add_report("Influenza test result", influenza_test_result_);
    add_report("MA Ct Value", ma_ct_value_);
    add_report("H5 Status", h5_status_);
    add_report("H5 Ct Value", h5_ct_value_);
    add_report("H5 Pathotype", h5_pathotype_);
    add_report("H7 Status", h7_status_);
    add_report("H7 Ct Value", h7_ct_value_);
    add_report("H7 Pathotype", h7_pathotype_);
    add_report("H9 Status", h9_status_);
    add_report("H9 Ct Value", h9_ct_value_);
    add_report("EMC ID", emc_id_);
    add_report("AHVLA ID", ahvla_id_);
    add_report("First Egg Passage", first_egg_passage_);
    add_report("Second Egg Passage", second_egg_passage_);
    add_report("Passage Isolation", passage_isolation_);
    add_report("Virus Pathotype", virus_pathotype_);
    add_report("Haemagglutinin Subtype", haemagglutinin_subtype_);
    add_report("Neuraminidase Subtype", neuraminidase_subtype_);
    add_report("Serology Sample ID", serology_sample_id_);
    add_report("Serology Testing Date", serology_testing_date_);
    add_report("Serology Status", serology_status_);
    // add("*record-id*"                  , record_id_);

    check_dates(reports);
    validate_hostspecies_commonname(birds, reports);
    update_locations(locations, reports);
    update_behavior(reports);

    if (reports.empty())
        return {};

    return sample_id_ + ":\n  " + string::join("\n  ", reports);

} // dtra::v2::Record::validate

// ----------------------------------------------------------------------

// Checks Host species and Host common name correspondence, in case
// one of them is not filled, fill it (via Directories).  Returns
// either list of errors or corrected map of records.

void dtra::v2::Record::validate_hostspecies_commonname(const Directory& birds, std::vector<std::string>& reports)
{
    try {
        if (!host_common_name_.empty() || !host_species_.empty()) {
            std::string new_host_species, new_host_common_name;
            if (!host_common_name_.empty()) {
                new_host_species = birds.find("englishToScientific", string::lower(host_common_name_));
                if (new_host_species.empty())
                    throw std::runtime_error(string::concat("common name \"", host_common_name_, "\" not found in the database"));
            }
            if (!host_species_.empty()) {
                new_host_common_name = birds.find("scientificToEnglish", string::lower(host_species_));
                if (new_host_common_name.empty())
                    throw std::runtime_error(string::concat("host species \"", host_species_, "\" not found in the database"));
            }
            if (host_common_name_.empty())
                host_common_name_ = new_host_common_name;
            else if (host_species_.empty())
                host_species_ = new_host_common_name;
            else if (host_common_name_ != new_host_common_name && host_species_ != new_host_species)
                throw std::runtime_error(string::concat("common name \"", host_common_name_, "\" and host species \"", host_species_, "\" mismatch"));
            else
                ;               // match
        }
        else {
            throw std::runtime_error("Neither host species nor host common name provided, please put one of them, the system will fill the other");
        }
    }
    catch (std::exception& err) {
        reports.push_back(err.what());
    }

} // dtra::v2::Record::validate_hostspecies_commonname

// ----------------------------------------------------------------------

void dtra::v2::Record::check_dates(std::vector<std::string>& reports)
{
    if (!date_of_testing_.empty() && collection_date_ > date_of_testing_)
        reports.push_back(string::concat("collection date ", collection_date_.to_string(), " > date of testing ", date_of_testing_.to_string()));
    if (!serology_testing_date_.empty() && collection_date_ > serology_testing_date_)
        reports.push_back(string::concat("collection date ", collection_date_.to_string(), " > serology testing date ", serology_testing_date_.to_string()));

} // dtra::v2::Record::check_dates

// ----------------------------------------------------------------------

void dtra::v2::Record::update_locations(const Directory& locations, std::vector<std::string>& reports)
{
    try {
        const auto& loc_data = locations.find(string::lower(location_));
        if (loc_data.is_null())
            throw std::runtime_error(string::concat("location not found: ", location_));

        const auto check = [this,&loc_data](const char* field_name, field::Text& field) {
            const std::string_view expected = loc_data[field_name];
            if (field.empty())
                field = expected;
            else if (field != expected)
                throw std::runtime_error(string::concat("invalid ", field, " (", field, ") for ", location_, " (expected: ", expected, "), please leave Province, Country, Latitude, Longitude fields empty to allow system to fill them with the correct content"));
        };

        const auto check_float = [this,&loc_data](const char* field_name, field::Float& field) {
            const double expected = loc_data[field_name];
            if (field.empty())
                field = expected;
            else if (!float_equal(static_cast<double>(field), expected))
                throw std::runtime_error(string::concat("invalid ", field, " (", field, ") for ", location_, " (expected: ", expected, "), please leave Province, Country, Latitude, Longitude fields empty to allow system to fill them with the correct content"));
        };

        check("province", province_);
        check("country", country_);
        check_float("latitude", latitude_);
        check_float("longitude", longitude_);
    }
    catch (std::exception& err) {
        reports.push_back(err.what());
    }

} // dtra::v2::Record::update_locations

// ----------------------------------------------------------------------

// Nic 2015-02-10: If 'domesticus' in the species field please
// autofill behavior as D, All other species entries please autofill
// behavior as W
void dtra::v2::Record::update_behavior(std::vector<std::string>& reports)
{
    const bool domesticus = host_species_.find("domesticus") != std::string::npos;
    if (behavior_.empty())
        behavior_ = domesticus ? "D" : "W";
    else if ((domesticus && behavior_ != "D") || (!domesticus && behavior_ != "W"))
        reports.push_back(string::concat("host species ", host_species_, " does not correspond to behavior ", behavior_));

} // dtra::v2::Record::update_behavior

// ----------------------------------------------------------------------

void dtra::v2::Record::set_sample_id(const xlnt::cell& cell)
{
    sample_id_ = cell.to_string();

} // dtra::v2::Record::set_sample_id

// ----------------------------------------------------------------------

void dtra::v2::Record::set_collection_day(const xlnt::cell& cell)
{
    collection_date_.set_day(cell.to_string());

} // dtra::v2::Record::set_collection_day

// ----------------------------------------------------------------------

void dtra::v2::Record::set_collection_month(const xlnt::cell& cell)
{
    collection_date_.set_month(cell.to_string());

} // dtra::v2::Record::set_collection_month

// ----------------------------------------------------------------------

void dtra::v2::Record::set_collection_year(const xlnt::cell& cell)
{
    collection_date_.set_year(cell.to_string());

} // dtra::v2::Record::set_collection_year

// ----------------------------------------------------------------------

void dtra::v2::Record::set_species(const xlnt::cell& cell)
{
    species_ = cell.to_string();

} // dtra::v2::Record::set_species

// ----------------------------------------------------------------------

void dtra::v2::Record::set_age(const xlnt::cell& cell)
{
    age_ = cell.to_string();

} // dtra::v2::Record::set_age

// ----------------------------------------------------------------------

void dtra::v2::Record::set_sex(const xlnt::cell& cell)
{
    sex_ = cell.to_string();

} // dtra::v2::Record::set_sex

// ----------------------------------------------------------------------

void dtra::v2::Record::set_ring_number(const xlnt::cell& cell)
{
    ring_number_ = cell.to_string();

} // dtra::v2::Record::set_ring_number

// ----------------------------------------------------------------------

void dtra::v2::Record::set_host_identifier(const xlnt::cell& cell)
{
    host_identifier_ = cell.to_string();

} // dtra::v2::Record::set_host_identifier

// ----------------------------------------------------------------------

void dtra::v2::Record::set_host_species(const xlnt::cell& cell)
{
    host_species_ = cell.to_string();

} // dtra::v2::Record::set_host_species

// ----------------------------------------------------------------------

void dtra::v2::Record::set_host_common_name(const xlnt::cell& cell)
{
    host_common_name_ = cell.to_string();

} // dtra::v2::Record::set_host_common_name

// ----------------------------------------------------------------------

void dtra::v2::Record::set_health(const xlnt::cell& cell)
{
    health_ = cell.to_string();

} // dtra::v2::Record::set_health

// ----------------------------------------------------------------------

void dtra::v2::Record::set_capture_method_status(const xlnt::cell& cell)
{
    capture_method_status_ = cell.to_string();

} // dtra::v2::Record::set_capture_method_status

// ----------------------------------------------------------------------

void dtra::v2::Record::set_behavior(const xlnt::cell& cell)
{
    behavior_ = cell.to_string();

} // dtra::v2::Record::set_behavior

// ----------------------------------------------------------------------

void dtra::v2::Record::set_location(const xlnt::cell& cell)
{
    location_ = cell.to_string();

} // dtra::v2::Record::set_location

// ----------------------------------------------------------------------

void dtra::v2::Record::set_province(const xlnt::cell& cell)
{
    province_ = cell.to_string();

} // dtra::v2::Record::set_province

// ----------------------------------------------------------------------

void dtra::v2::Record::set_country(const xlnt::cell& cell)
{
    country_ = cell.to_string();

} // dtra::v2::Record::set_country

// ----------------------------------------------------------------------

void dtra::v2::Record::set_latitude(const xlnt::cell& cell)
{
    latitude_ = cell.to_string();

} // dtra::v2::Record::set_latitude

// ----------------------------------------------------------------------

void dtra::v2::Record::set_longitude(const xlnt::cell& cell)
{
    longitude_ = cell.to_string();

} // dtra::v2::Record::set_longitude

// ----------------------------------------------------------------------

void dtra::v2::Record::set_sample_material(const xlnt::cell& cell)
{
    sample_material_ = cell.to_string();

} // dtra::v2::Record::set_sample_material

// ----------------------------------------------------------------------

void dtra::v2::Record::set_test_for_influenza_virus(const xlnt::cell& cell)
{
    test_for_influenza_virus_ = cell.to_string();

} // dtra::v2::Record::set_test_for_influenza_virus

// ----------------------------------------------------------------------

void dtra::v2::Record::set_day_of_testing(const xlnt::cell& cell)
{
    date_of_testing_.set_day(cell.to_string());

} // dtra::v2::Record::set_day_of_testing

// ----------------------------------------------------------------------

void dtra::v2::Record::set_month_of_testing(const xlnt::cell& cell)
{
    date_of_testing_.set_month(cell.to_string());

} // dtra::v2::Record::set_month_of_testing

// ----------------------------------------------------------------------

void dtra::v2::Record::set_year_of_testing(const xlnt::cell& cell)
{
    date_of_testing_.set_year(cell.to_string());

} // dtra::v2::Record::set_year_of_testing

// ----------------------------------------------------------------------

void dtra::v2::Record::set_pool_id(const xlnt::cell& cell)
{
    pool_id_ = cell.to_string();

} // dtra::v2::Record::set_pool_id

// ----------------------------------------------------------------------

void dtra::v2::Record::set_influenza_test_result(const xlnt::cell& cell)
{
    influenza_test_result_ = cell.to_string();

} // dtra::v2::Record::set_influenza_test_result

// ----------------------------------------------------------------------

void dtra::v2::Record::set_ma_ct_value(const xlnt::cell& cell)
{
    ma_ct_value_ = cell.to_string();

} // dtra::v2::Record::set_ma_ct_value

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h5_status(const xlnt::cell& cell)
{
    h5_status_ = cell.to_string();

} // dtra::v2::Record::set_h5_status

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h5_ct_value(const xlnt::cell& cell)
{
    h5_ct_value_ = cell.to_string();

} // dtra::v2::Record::set_h5_ct_value

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h5_pathotype(const xlnt::cell& cell)
{
    h5_pathotype_ = cell.to_string();

} // dtra::v2::Record::set_h5_pathotype

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h7_status(const xlnt::cell& cell)
{
    h7_status_ = cell.to_string();

} // dtra::v2::Record::set_h7_status

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h7_ct_value(const xlnt::cell& cell)
{
    h7_ct_value_ = cell.to_string();

} // dtra::v2::Record::set_h7_ct_value

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h7_pathotype(const xlnt::cell& cell)
{
    h7_pathotype_ = cell.to_string();

} // dtra::v2::Record::set_h7_pathotype

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h9_status(const xlnt::cell& cell)
{
    h9_status_ = cell.to_string();

} // dtra::v2::Record::set_h9_status

// ----------------------------------------------------------------------

void dtra::v2::Record::set_h9_ct_value(const xlnt::cell& cell)
{
    h9_ct_value_ = cell.to_string();

} // dtra::v2::Record::set_h9_ct_value

// ----------------------------------------------------------------------

void dtra::v2::Record::set_emc_id(const xlnt::cell& cell)
{
    emc_id_ = cell.to_string();

} // dtra::v2::Record::set_emc_id

// ----------------------------------------------------------------------

void dtra::v2::Record::set_ahvla_id(const xlnt::cell& cell)
{
    ahvla_id_ = cell.to_string();

} // dtra::v2::Record::set_ahvla_id

// ----------------------------------------------------------------------

void dtra::v2::Record::set_first_egg_passage(const xlnt::cell& cell)
{
    first_egg_passage_ = cell.to_string();

} // dtra::v2::Record::set_first_egg_passage

// ----------------------------------------------------------------------

void dtra::v2::Record::set_second_egg_passage(const xlnt::cell& cell)
{
    second_egg_passage_ = cell.to_string();

} // dtra::v2::Record::set_second_egg_passage

// ----------------------------------------------------------------------

void dtra::v2::Record::set_passage_isolation(const xlnt::cell& cell)
{
    passage_isolation_ = cell.to_string();

} // dtra::v2::Record::set_passage_isolation

// ----------------------------------------------------------------------

void dtra::v2::Record::set_virus_pathotype(const xlnt::cell& cell)
{
    virus_pathotype_ = cell.to_string();

} // dtra::v2::Record::set_virus_pathotype

// ----------------------------------------------------------------------

void dtra::v2::Record::set_haemagglutinin_subtype(const xlnt::cell& cell)
{
    haemagglutinin_subtype_ = cell.to_string();

} // dtra::v2::Record::set_haemagglutinin_subtype

// ----------------------------------------------------------------------

void dtra::v2::Record::set_neuraminidase_subtype(const xlnt::cell& cell)
{
    neuraminidase_subtype_ = cell.to_string();

} // dtra::v2::Record::set_neuraminidase_subtype

// ----------------------------------------------------------------------

void dtra::v2::Record::set_serology_sample_id(const xlnt::cell& cell)
{
    serology_sample_id_ = cell.to_string();

} // dtra::v2::Record::set_serology_sample_id

// ----------------------------------------------------------------------

void dtra::v2::Record::set_serology_testing_day(const xlnt::cell& cell)
{
    serology_testing_date_.set_day(cell.to_string());

} // dtra::v2::Record::set_serology_testing_day

// ----------------------------------------------------------------------

void dtra::v2::Record::set_serology_testing_month(const xlnt::cell& cell)
{
    serology_testing_date_.set_month(cell.to_string());

} // dtra::v2::Record::set_serology_testing_month

// ----------------------------------------------------------------------

void dtra::v2::Record::set_serology_testing_year(const xlnt::cell& cell)
{
    serology_testing_date_.set_year(cell.to_string());

} // dtra::v2::Record::set_serology_testing_year

// ----------------------------------------------------------------------

void dtra::v2::Record::set_serology_status(const xlnt::cell& cell)
{
    serology_status_ = cell.to_string();

} // dtra::v2::Record::set_serology_status

// ----------------------------------------------------------------------

void dtra::v2::Record::set_record_id(const xlnt::cell& cell)
{
    record_id_ = cell.to_string();

} // dtra::v2::Record::set_record_id

// ----------------------------------------------------------------------

// capture_method_status_
// ----------------------
// A=Active surveillance (e.g. trap); sampling not initiated by an outbreak
// K=Opportunistically sampled (e.g., hunter-killed or killed in order to take sample)
// O=Sample collected in response to outbreak (sick or dying birds)
// M=Market Sample
// P=Sample obtained from a pet
// Z=Sample obtained from a zoo
// F=Farm Sample
// OT= Other; plus free text (e.g. OT-restaurant)
// U=Undetermined

// sample_material_
// ----------------------
// TS = Tracheal swab
// OP = Oral-pharyngeal
// C = Cloacal
// F = Feces
// COP = Cloacal and oral-pharyngeal samples, when combined into one sample
// B= Blood
// SR = Serum
// TT = Tissue from trachea
// CF = Cloacal and fecal samples, when combined into one sample
// TB = Tissue from brain
// TO = Other tissue
// L = Lungs
// S = Soil
// W = Water
// O = Other; plus free typed out text (e.g. O - feather)
// U = Unknown

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
