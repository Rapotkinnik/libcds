/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#include "priority_queue/hdr_intrusive_pqueue.h"
#include <cds/intrusive/mspriority_queue.h>

namespace priority_queue {
    namespace intrusive_pqueue {
        template <typename T, typename Traits>
        struct constants<cds::intrusive::MSPriorityQueue<T, Traits> > {
            static size_t const nCapacity = c_nCapacity - 1;
        };
    }

    namespace {
        typedef cds::opt::v::dynamic_buffer< char > buffer_type;
    }

    void IntrusivePQueueHdrTest::MSPQueue_dyn()
    {
        struct pqueue_traits : public cds::intrusive::mspriority_queue::traits
        {
            typedef buffer_type buffer;
        };
        typedef cds::intrusive::MSPriorityQueue< IntrusivePQueueHdrTest::key_type, pqueue_traits > pqueue;

        test_msq_dyn<pqueue>();
    }

    void IntrusivePQueueHdrTest::MSPQueue_dyn_cmp()
    {
        struct pqueue_traits : public cds::intrusive::mspriority_queue::traits
        {
            typedef buffer_type buffer;
            typedef IntrusivePQueueHdrTest::compare compare;
        };
        typedef cds::intrusive::MSPriorityQueue< IntrusivePQueueHdrTest::key_type, pqueue_traits > pqueue;

        test_msq_dyn<pqueue>();
    }

    void IntrusivePQueueHdrTest::MSPQueue_dyn_less()
    {
        struct pqueue_traits : public
            cds::intrusive::mspriority_queue::make_traits <
                cds::opt::buffer< buffer_type >
                , cds::opt::less < std::less<IntrusivePQueueHdrTest::key_type> >
            > ::type
        {};
        typedef cds::intrusive::MSPriorityQueue< IntrusivePQueueHdrTest::key_type, pqueue_traits > pqueue;

        test_msq_dyn<pqueue>();
    }

    void IntrusivePQueueHdrTest::MSPQueue_dyn_cmpless()
    {
        typedef cds::intrusive::MSPriorityQueue< IntrusivePQueueHdrTest::key_type,
            cds::intrusive::mspriority_queue::make_traits<
                cds::opt::buffer< buffer_type >
                ,cds::opt::less< std::less<IntrusivePQueueHdrTest::key_type> >
                ,cds::opt::compare< IntrusivePQueueHdrTest::compare >
            >::type
        > pqueue;

        test_msq_dyn<pqueue>();
    }

    void IntrusivePQueueHdrTest::MSPQueue_dyn_cmp_mtx()
    {
        typedef cds::intrusive::MSPriorityQueue< IntrusivePQueueHdrTest::key_type,
            cds::intrusive::mspriority_queue::make_traits<
                cds::opt::buffer< buffer_type >
                ,cds::opt::compare< IntrusivePQueueHdrTest::compare >
                ,cds::opt::lock_type<std::mutex>
            >::type
        > pqueue;

        test_msq_dyn<pqueue>();
    }

} // namespace priority_queue
