/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#include "map/hdr_striped_map.h"

#include <boost/version.hpp>
#include <cds/details/defs.h>
#if CDS_COMPILER == CDS_COMPILER_MSVC && CDS_COMPILER_VERSION == CDS_COMPILER_MSVC12 && BOOST_VERSION <= 105500
namespace map {
    void StripedMapHdrTest::Refinable_slist()
    {
        CPPUNIT_MESSAGE("Skipped; for Microsoft Visual C++ 2013 and boost::container::slist you should use boost version 1.56 or above");
    }
}

#elif BOOST_VERSION >= 104800

#include <cds/container/striped_map/boost_slist.h>
#include <cds/container/striped_map.h>
#include <cds/sync/spinlock.h>


namespace map {

    namespace {
        typedef boost::container::slist<StripedMapHdrTest::pair_type> sequence_t;

        struct my_copy_policy {
            typedef sequence_t::iterator iterator;

            void operator()( sequence_t& list, iterator itInsert, iterator itWhat )
            {
                list.insert_after( itInsert, StripedMapHdrTest::pair_type( std::make_pair(itWhat->first, itWhat->second )));
            }
        };
    }

    void StripedMapHdrTest::Refinable_slist()
    {
        CPPUNIT_MESSAGE( "cmp");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::compare< cmp >
        >   map_cmp;
        test_striped2< map_cmp >();

        CPPUNIT_MESSAGE( "less");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::less< less >
        >   map_less;
        test_striped2< map_less >();

        CPPUNIT_MESSAGE( "cmpmix");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::compare< cmp >
            , co::less< less >
        >   map_cmpmix;
        test_striped2< map_cmpmix >();

        // Spinlock as lock policy
        CPPUNIT_MESSAGE( "spinlock");
        typedef cc::StripedMap< sequence_t
            , co::mutex_policy< cc::striped_set::refinable<cds::sync::spin> >
            , co::hash< hash_int >
            , co::less< less >
        >   map_spin;
        test_striped2< map_spin >();

        // Resizing policy
        CPPUNIT_MESSAGE( "load_factor_resizing<0>(8)");
        {
            typedef cc::StripedMap< sequence_t
                ,co::mutex_policy< cc::striped_set::refinable<> >
                , co::hash< hash_int >
                , co::less< less >
                , co::resizing_policy< cc::striped_set::load_factor_resizing<0> >
            >   pair_type_less_resizing_lf;
            pair_type_less_resizing_lf m(30, cc::striped_set::load_factor_resizing<0>(8) );
            test_striped_with(m);
        }

        CPPUNIT_MESSAGE( "load_factor_resizing<4>");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<4> >
        >   map_less_resizing_lf16;
        test_striped2< map_less_resizing_lf16 >();

        {
            CPPUNIT_MESSAGE( "single_bucket_size_threshold<0>(8)");
            typedef cc::StripedMap< sequence_t
                ,co::mutex_policy< cc::striped_set::refinable<> >
                , co::hash< hash_int >
                , co::less< less >
                , co::resizing_policy< cc::striped_set::single_bucket_size_threshold<0> >
            >   map_less_resizing_sbt;
            map_less_resizing_sbt m(30, cc::striped_set::single_bucket_size_threshold<0>(8));
            test_striped_with(m);
        }

        CPPUNIT_MESSAGE( "single_bucket_size_threshold<6>");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::single_bucket_size_threshold<6> >
        >   map_less_resizing_sbt16;
        test_striped2< map_less_resizing_sbt16 >();

        // Copy policy
        CPPUNIT_MESSAGE( "copy_item");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::less< less >
            , co::copy_policy< cc::striped_set::copy_item >
        >   set_copy_item;
        test_striped2< set_copy_item >();

        CPPUNIT_MESSAGE( "swap_item");
        typedef cc::StripedMap< sequence_t
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::hash< hash_int >
            , co::less< less >
            , co::copy_policy< cc::striped_set::swap_item >
        >   set_swap_item;
        test_striped2< set_swap_item >();

        CPPUNIT_MESSAGE( "move_item");
        typedef cc::StripedMap< sequence_t
            , co::hash< hash_int >
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::less< less >
            , co::copy_policy< cc::striped_set::move_item >
        >   set_move_item;
        test_striped2< set_move_item >();

        CPPUNIT_MESSAGE( "special copy_item");
        typedef cc::StripedMap< sequence_t
            , co::hash< hash_int >
            , co::compare< cmp >
            ,co::mutex_policy< cc::striped_set::refinable<> >
            , co::copy_policy< my_copy_policy >
        >   set_special_copy_item;
        test_striped2< set_special_copy_item >();
    }
}   // namespace map
#else

namespace map {
    void StripedMapHdrTest::Refinable_slist()
    {
        CPPUNIT_MESSAGE("Skipped; for boost::container::slist you should use boost version 1.48 or above");
    }
} // namespace map

#endif  // BOOST_VERSION
