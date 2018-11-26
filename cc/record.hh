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
            std::string csv_exporter_default() const { return {}; }

            std::string validate(const Directory& locations, const Directory& birds);
            std::string merge(const Record& rec);


            static std::string new_record_id();

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

         private:
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
