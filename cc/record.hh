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
        class TextField : public std::string
        {
         public:
            using std::string::string;
            TextField& operator=(const std::string& source) { std::string::operator=(source); return *this; }
            TextField& operator=(std::string&& source) { std::string::operator=(std::move(source)); return *this; }

            std::vector<std::string> validate() const { return {}; }
        };

          // --------------------------------------------------

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
            TextField sample_id_;
            Date      collection_date_;
            TextField species_;
            TextField age_;
            TextField sex_;
            TextField ring_number_;
            TextField host_identifier_;
            TextField host_species_;
            TextField host_common_name_;
            TextField health_;
            TextField capture_method_status_;
            TextField behavior_;
            TextField location_;
            TextField province_;
            TextField country_;
            TextField latitude_;
            TextField longitude_;
            TextField sample_material_;
            TextField test_for_influenza_virus_;
            Date      date_of_testing_;
            TextField pool_id_;
            TextField influenza_test_result_;
            TextField ma_ct_value_;
            TextField h5_status_;
            TextField h5_ct_value_;
            TextField h5_pathotype_;
            TextField h7_status_;
            TextField h7_ct_value_;
            TextField h7_pathotype_;
            TextField h9_status_;
            TextField h9_ct_value_;
            TextField emc_id_;
            TextField ahvla_id_;
            TextField first_egg_passage_;
            TextField second_egg_passage_;
            TextField passage_isolation_;
            TextField virus_pathotype_;
            TextField haemagglutinin_subtype_;
            TextField neuraminidase_subtype_;
            TextField serology_sample_id_;
            Date      serology_testing_date_;
            TextField serology_status_;
            TextField record_id_;
        };

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
