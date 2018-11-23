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
            static constexpr const char* re_sample_id = "^(217|DT)-[0-9]+$";

            field::Uppercase sample_id_{re_sample_id, "expected: 217-xxxxx, DT-xxxxx", field::can_be_empty::no};
            field::Date      collection_date_{field::can_be_empty::no};
            field::Text      species_;
            field::Uppercase age_{"^[HAU]$", "expected: H, A, U", field::can_be_empty::no};
            field::Uppercase sex_{"^[MFU]$", "expected Sex: M, F, U", field::can_be_empty::no};
            field::Text      ring_number_;
            field::Uppercase host_identifier_{re_sample_id, "expected: 217-xxxxx, DT-xxxxx"};
            field::Text      host_species_;
            field::Text      host_common_name_;
            field::Uppercase health_{"^[HSDU]$", "expected: H(ealthy), S(ick), D(ead), U(undetermined)"};
            field::Uppercase capture_method_status_{"^(A|K|O|M|P|Z|F|U|OT.*)$", "expected: A, K, O, M, P, Z, F, OT-<text>, U"}; // see bottom of record.cc
            field::Uppercase behavior_{"^(W|D|CW|U)$", "expected: W(ild), D(omestic), CW (captive-wild), U(known)"};
            field::Text      location_{field::can_be_empty::no};
            field::Text      province_;
            field::Text      country_;
            field::Text      latitude_;
            field::Text      longitude_;
            field::Text      sample_material_;
            field::Text      test_for_influenza_virus_;
            field::Date      date_of_testing_;
            field::Text      pool_id_;
            field::Text      influenza_test_result_;
            field::Text      ma_ct_value_;
            field::Text      h5_status_;
            field::Text      h5_ct_value_;
            field::Text      h5_pathotype_;
            field::Text      h7_status_;
            field::Text      h7_ct_value_;
            field::Text      h7_pathotype_;
            field::Text      h9_status_;
            field::Text      h9_ct_value_;
            field::Text      emc_id_;
            field::Text      ahvla_id_;
            field::Text      first_egg_passage_;
            field::Text      second_egg_passage_;
            field::Text      passage_isolation_;
            field::Text      virus_pathotype_;
            field::Text      haemagglutinin_subtype_;
            field::Text      neuraminidase_subtype_;
            field::Text      serology_sample_id_;
            field::Date      serology_testing_date_;
            field::Text      serology_status_;
            field::Text      record_id_;
        };

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
