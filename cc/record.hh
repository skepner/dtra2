#pragma once

#include <string>

#include "date.hh"

// ----------------------------------------------------------------------

namespace xlnt
{
    class cell;
}

namespace dtra
{
    inline namespace v2
    {
        class Record
        {
          public:
            void importer_default(const xlnt::cell& cell);

            std::string validate();

            void set_sample_id(const xlnt::cell& cell);
            void set_collection_day(const xlnt::cell& cell);
            void set_collection_month(const xlnt::cell& cell);
            void set_collection_year(const xlnt::cell& cell);
            void set_species(const xlnt::cell& cell);
            void set_age(const xlnt::cell& cell);
            void set_sex(const xlnt::cell& cell);
            void set_ring_number(const xlnt::cell& cell);
            void set_host_identifier(const xlnt::cell& cell);
            void set_host_species(const xlnt::cell& cell);
            void set_host_common_name(const xlnt::cell& cell);
            void set_health(const xlnt::cell& cell);
            void set_capture_method_status(const xlnt::cell& cell);
            void set_behavior(const xlnt::cell& cell);
            void set_location(const xlnt::cell& cell);
            void set_province(const xlnt::cell& cell);
            void set_country(const xlnt::cell& cell);
            void set_latitude(const xlnt::cell& cell);
            void set_longitude(const xlnt::cell& cell);
            void set_sample_material(const xlnt::cell& cell);
            void set_test_for_influenza_virus(const xlnt::cell& cell);
            void set_day_of_testing(const xlnt::cell& cell);
            void set_month_of_testing(const xlnt::cell& cell);
            void set_year_of_testing(const xlnt::cell& cell);
            void set_pool_id(const xlnt::cell& cell);
            void set_influenza_test_result(const xlnt::cell& cell);
            void set_ma_ct_value(const xlnt::cell& cell);
            void set_h5_status(const xlnt::cell& cell);
            void set_h5_ct_value(const xlnt::cell& cell);
            void set_h5_pathotype(const xlnt::cell& cell);
            void set_h7_status(const xlnt::cell& cell);
            void set_h7_ct_value(const xlnt::cell& cell);
            void set_h7_pathotype(const xlnt::cell& cell);
            void set_h9_status(const xlnt::cell& cell);
            void set_h9_ct_value(const xlnt::cell& cell);
            void set_emc_id(const xlnt::cell& cell);
            void set_ahvla_id(const xlnt::cell& cell);
            void set_first_egg_passage(const xlnt::cell& cell);
            void set_second_egg_passage(const xlnt::cell& cell);
            void set_passage_isolation(const xlnt::cell& cell);
            void set_virus_pathotype(const xlnt::cell& cell);
            void set_haemagglutinin_subtype(const xlnt::cell& cell);
            void set_neuraminidase_subtype(const xlnt::cell& cell);
            void set_serology_sample_id(const xlnt::cell& cell);
            void set_serology_testing_day(const xlnt::cell& cell);
            void set_serology_testing_month(const xlnt::cell& cell);
            void set_serology_testing_year(const xlnt::cell& cell);
            void set_serology_status(const xlnt::cell& cell);
            void set_record_id(const xlnt::cell& cell);

          private:
            std::string sample_id_;
            Date        collection_date_;
            std::string species_;
            std::string age_;
            std::string sex_;
            std::string ring_number_;
            std::string host_identifier_;
            std::string host_species_;
            std::string host_common_name_;
            std::string health_;
            std::string capture_method_status_;
            std::string behavior_;
            std::string location_;
            std::string province_;
            std::string country_;
            std::string latitude_;
            std::string longitude_;
            std::string sample_material_;
            std::string test_for_influenza_virus_;
            Date        date_of_testing_;
            std::string pool_id_;
            std::string influenza_test_result_;
            std::string ma_ct_value_;
            std::string h5_status_;
            std::string h5_ct_value_;
            std::string h5_pathotype_;
            std::string h7_status_;
            std::string h7_ct_value_;
            std::string h7_pathotype_;
            std::string h9_status_;
            std::string h9_ct_value_;
            std::string emc_id_;
            std::string ahvla_id_;
            std::string first_egg_passage_;
            std::string second_egg_passage_;
            std::string passage_isolation_;
            std::string virus_pathotype_;
            std::string haemagglutinin_subtype_;
            std::string neuraminidase_subtype_;
            std::string serology_sample_id_;
            Date        serology_testing_date_;
            std::string serology_status_;
            std::string record_id_;
        };

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
