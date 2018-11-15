#include "xlnt.hh"
#include "record.hh"

// ----------------------------------------------------------------------

void dtra::v2::Record::importer_default(const xlnt::cell& /*cell*/)
{

} // dtra::v2::Record::importer_default

// ----------------------------------------------------------------------

void dtra::v2::Record::validate()
{

} // dtra::v2::Record::validate

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
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
