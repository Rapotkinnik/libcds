#include <boost/thread.hpp>
#include <cds/algo/backoff_strategy.h>
#include <cds/algo/flat_combining.h>

namespace cds {  namespace algo {  namespace flat_combining {
    class publication_record;
    template<typename PublicationRecord>
    class WaitEmptyStrategy{
        typedef PublicationRecord   publication_record_type;   ///< publication record type
    public:
        void wait(publication_record_type * pRec){}
        void notify(publication_record& rec){}
    };
//====================================================================
    template<typename PublicationRecord>
    class WaitBakkOffStrategy{
        typedef PublicationRecord   publication_record_type;   ///< publication record type
        cds::backoff::delay_of<2>   back_off;   ///< Back-off strategy
    public:
        void wait(publication_record_type * pRec){
            back_off();
        }
        void notify(publication_record& rec){}
    };
//====================================================================
    template<typename PublicationRecord>
    class WaitOneMutexOneCondVarStrategy{
        typedef PublicationRecord   publication_record_type;   ///< publication record type
        boost::mutex              _globalMutex;
        boost::condition_variable _globalCondVar;
    public:
        void wait(publication_record_type * pRec){
            boost::unique_lock<boost::mutex> lock(_globalMutex);
            _globalCondVar.timed_wait(lock, static_cast<boost::posix_time::seconds>(5));
        }

        void notify(publication_record& rec){
            _globalCondVar.notify_all();
        }
    };
//====================================================================
/*    template<typename PublicationRecord>
    class WaitMultMutexMultCondVarStrategy{
        typedef PublicationRecord   publication_record_type;   ///< publication record type
    public:
        void wait(publication_record_type * pRec){
            boost::unique_lock<boost::mutex> lock(pRec->_waitMutex);
            pRec->_condVar.wait(lock);
        }

        void notify(publication_record& rec){
            rec._condVar.notify_one();
        }
    };
*/
}}}//end namespace cds::algo::flat_combining
