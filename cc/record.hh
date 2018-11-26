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
        class Directory;

          // --------------------------------------------------

        class Record
        {
          public:
            void importer_default(const xlnt::cell& cell);
            void exporter_default(xlnt::cell& cell) const;

            std::string validate(const Directory& locations, const Directory& birds);

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

            void get_sample_id(xlnt::cell& cell) const;
            void get_collection_day(xlnt::cell& cell) const;
            void get_collection_month(xlnt::cell& cell) const;
            void get_collection_year(xlnt::cell& cell) const;
            void get_species(xlnt::cell& cell) const;
            void get_age(xlnt::cell& cell) const;
            void get_sex(xlnt::cell& cell) const;
            void get_ring_number(xlnt::cell& cell) const;
            void get_host_identifier(xlnt::cell& cell) const;
            void get_host_species(xlnt::cell& cell) const;
            void get_host_common_name(xlnt::cell& cell) const;
            void get_health(xlnt::cell& cell) const;
            void get_capture_method_status(xlnt::cell& cell) const;
            void get_behavior(xlnt::cell& cell) const;
            void get_location(xlnt::cell& cell) const;
            void get_province(xlnt::cell& cell) const;
            void get_country(xlnt::cell& cell) const;
            void get_latitude(xlnt::cell& cell) const;
            void get_longitude(xlnt::cell& cell) const;
            void get_sample_material(xlnt::cell& cell) const;
            void get_test_for_influenza_virus(xlnt::cell& cell) const;
            void get_day_of_testing(xlnt::cell& cell) const;
            void get_month_of_testing(xlnt::cell& cell) const;
            void get_year_of_testing(xlnt::cell& cell) const;
            void get_pool_id(xlnt::cell& cell) const;
            void get_influenza_test_result(xlnt::cell& cell) const;
            void get_ma_ct_value(xlnt::cell& cell) const;
            void get_h5_status(xlnt::cell& cell) const;
            void get_h5_ct_value(xlnt::cell& cell) const;
            void get_h5_pathotype(xlnt::cell& cell) const;
            void get_h7_status(xlnt::cell& cell) const;
            void get_h7_ct_value(xlnt::cell& cell) const;
            void get_h7_pathotype(xlnt::cell& cell) const;
            void get_h9_status(xlnt::cell& cell) const;
            void get_h9_ct_value(xlnt::cell& cell) const;
            void get_emc_id(xlnt::cell& cell) const;
            void get_ahvla_id(xlnt::cell& cell) const;
            void get_first_egg_passage(xlnt::cell& cell) const;
            void get_second_egg_passage(xlnt::cell& cell) const;
            void get_passage_isolation(xlnt::cell& cell) const;
            void get_virus_pathotype(xlnt::cell& cell) const;
            void get_haemagglutinin_subtype(xlnt::cell& cell) const;
            void get_neuraminidase_subtype(xlnt::cell& cell) const;
            void get_serology_sample_id(xlnt::cell& cell) const;
            void get_serology_testing_day(xlnt::cell& cell) const;
            void get_serology_testing_month(xlnt::cell& cell) const;
            void get_serology_testing_year(xlnt::cell& cell) const;
            void get_serology_status(xlnt::cell& cell) const;
            void get_record_id(xlnt::cell& cell) const;

            static std::string new_record_id();

         private:
            static constexpr const char* re_sample_id = "^(217|DT)-[0-9]+$";
            static constexpr const char* sample_id_message = "expected: 217-xxxxx, DT-xxxxx";
            static constexpr const char* re_ct = "^[<>]?[0-9]+(\\.[0-9][0-9]?)?$";
            static constexpr const char* ct_message = "expected: valid CT Value";
            static constexpr const char* re_h_status = "^(P|N)$";
            static constexpr const char* h_status_message = "expected: P or N";
            static constexpr const char* re_pathotype = "^(LPAI|HPAI)$";
            static constexpr const char* pathotype_message = "expected: LPAI or HPAI";
            static constexpr const char* re_egg_passage = "^(0|1)$";
            static constexpr const char* egg_passage_message = "expected: 0 or 1";
            static std::string new_record_id_;

            field::Uppercase sample_id_{re_sample_id, sample_id_message, field::can_be_empty::no};
            field::Date      collection_date_{field::can_be_empty::no};
            field::Text      species_;
            field::Uppercase age_{"^[HAU]$", "expected: H, A, U", field::can_be_empty::no};
            field::Uppercase sex_{"^[MFU]$", "expected Sex: M, F, U", field::can_be_empty::no};
            field::Text      ring_number_;
            field::Uppercase host_identifier_{re_sample_id, sample_id_message};
            field::Text      host_species_;
            field::Text      host_common_name_;
            field::Uppercase health_{"^[HSDU]$", "expected: H(ealthy), S(ick), D(ead), U(undetermined)"};
            field::Uppercase capture_method_status_{"^(A|K|O|M|P|Z|F|U|OT.*)$", "expected: A, K, O, M, P, Z, F, OT-<text>, U"}; // see bottom of record.cc
            field::Uppercase behavior_{"^(W|D|CW|U)$", "expected: W(ild), D(omestic), CW (captive-wild), U(known)"};
            field::Text      location_{field::can_be_empty::no};
            field::Text      province_;
            field::Text      country_;
            field::Float     latitude_{-90, 90};
            field::Float     longitude_{-180, 180};
            field::Uppercase sample_material_{"^(TS|OP|C|F|COP|B|SR|TT|CF|TB|TO|L|S|W|O[- ].+|X.*)$", "expected: TS, OP, C, F, COP, B, SR, TT, CF, TB, TO, L, S, W, O -<text>, X-<text>"}; // see bottom of record.cc
            field::Uppercase test_for_influenza_virus_; // {"^RRT-PCR +MA( *,? *RRT-PCR +H5( *,? *RRT-PCR +H7)?)?$", "expected: RRT-PCR MA, RRT-PCR H5, RRT-PCR H7"}
            field::Date      date_of_testing_;
            field::Uppercase pool_id_{"^[0-9\\.]+$", "expected: numeric value"};
            field::Uppercase influenza_test_result_{"^(P|N)$", "expected: P, N"};
            field::Uppercase ma_ct_value_{re_ct, ct_message};
            field::Uppercase h5_status_{re_h_status, h_status_message};
            field::Uppercase h5_ct_value_{re_ct, ct_message};
            field::Uppercase h5_pathotype_{re_pathotype, pathotype_message};
            field::Uppercase h7_status_{re_h_status, h_status_message};
            field::Uppercase h7_ct_value_{re_ct, ct_message};
            field::Uppercase h7_pathotype_{re_pathotype, pathotype_message};
            field::Uppercase h9_status_{re_h_status, h_status_message};
            field::Uppercase h9_ct_value_{re_ct, ct_message};
            field::Text      emc_id_;
            field::Text      ahvla_id_;
            field::Uppercase first_egg_passage_{re_egg_passage, egg_passage_message};
            field::Uppercase second_egg_passage_{re_egg_passage, egg_passage_message};
            field::Uppercase passage_isolation_{"^(E1|E2|NOT *PERFORMED|NEGATIVE)$", "expected: E1, E2, not performed"};
            field::Uppercase virus_pathotype_{"^(LPAI|HPAI|NOT *IDENTIFIABLE)$", "expected: LPAI, HPAI, notidentifiable"};
            field::Uppercase haemagglutinin_subtype_{"^((H[1-9]|H1[0-6])(/(H[1-9]|H1[0-6]))*|MIXED|H +NOT +DETERMINED)$", "expected: H1-H16, mixed, H not determined"};
            field::Uppercase neuraminidase_subtype_{"^(N[1-9](/N[1-9])*|MIXED|N +NOT +DETERMINED)$", "expected: N1-N9, mixed, N not determined"};
            field::Uppercase serology_sample_id_{re_sample_id, sample_id_message};
            field::Date      serology_testing_date_;
            field::Uppercase serology_status_{"^(\\+|-|\\*)$", "expected: +, -, *"};
            field::Text      record_id_;

            void validate_hostspecies_commonname(const Directory& birds, std::vector<std::string>& reports);
            void check_dates(std::vector<std::string>& reports);
            void update_locations(const Directory& locations, std::vector<std::string>& reports);
            void update_behavior(std::vector<std::string>& reports);

        };

    } // namespace v2
} // namespace dtra

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
