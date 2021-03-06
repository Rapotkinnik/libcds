/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#include "set2/set_insdel_func.h"
#include "set2/set_type_cuckoo.h"

namespace set2 {
    CDSUNIT_DEFINE_CuckooSet( cc::cuckoo::implementation_tag, Set_InsDel_func )

    CPPUNIT_TEST_SUITE_PART( Set_InsDel_func, run_CuckooSet )
        CDSUNIT_TEST_CuckooSet
    CPPUNIT_TEST_SUITE_END_PART()

} // namespace set2
