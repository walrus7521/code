// Making timers and processing timer events as tasks.
//  see github.com/apolukhin/Boost-Cookbook-4880OS/blob/master/Chapter06/

#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>
#include "task_processor_base.hpp"

namespace detail {
    typedef boost::asio::deadline_timer::duration_type duration_type;

    template <class Functor>
    struct timer_task: public task_wrapped<Functor> {
    private:
        typedef task_wrapped<Functor> base_t;
        boost::shared_ptr<boost::asio::deadline_timer> timer_;

    public:
        template <class Time>
        explicit timer_task(
            boost::asio::io_service& ios,
            const Time& duration_or_time,
            const Functor& task_unwrapped)
        : base_t(task_unwrapped), 
          timer_(boost::make_shared<boost::asio::deadline_timer>(
            boost::ref(ios), duration_or_time
         ))
        {}

        void push_task() const {
            timer_->async_wait(*this);
        }

        void operator()(const boost::system::error_code& error) const {
            if (!error) {
                base_t::operator()();
            } else {
                std::cerr << error << '\n';
            }
        }
    };
}

namespace detail {
    template <class Time, class Functor>
    inline timer_task<Functor> make_timer_task(
            boost::asio::io_service& ios,
            const Time& duration_or_time,
            const Functor& task_unwrapped) {
        return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
    }
}

namespace tp_timers {

    class tasks_processor: public tp_base::tasks_processor {
    public:
        static tasks_processor& get();
    
        typedef boost::asio::deadline_timer::duration_type duration_type;

        template <class Functor>
        void run_after(duration_type duration, const Functor& f) {
            detail::make_timer_task(ios_, duration, f)
                .push_task();
        }

        typedef boost::asio::deadline_timer::time_type time_type;

        template <class Functor>
        void run_at(time_type time, const Functor& f) {
            detail::make_timer_task(ios_, time, f)
                .push_task();
        }
    };

} // namespace tp_timers

class task_queue {
    typedef boost::asio::deadline_timer::duration_type duration_type;
    boost::asio::io_service         ios_;

    template <class Functor>
    void run_after(duration_type duration, const Functor& f) {
        detail::make_timer_task(ios_, duration, f)
            .push_task();
    }
};

using namespace tp_timers;

tasks_processor& tasks_processor::get() {
    static tasks_processor proc;
    return proc;
}

void test_func(int& i) {
    i = 1;
    std::cout << "test_func\n";
    tasks_processor::get().stop();
}

void test_func1() {
    std::cout << "test_func1\n";
    throw std::logic_error("It works!");
}

#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    const int seconds_to_wait = 3;
    int i = 0;

    tasks_processor::get().run_after(
        boost::posix_time::seconds(seconds_to_wait),
        boost::bind(&test_func, boost::ref(i)));

    tasks_processor::get().run_at(
        boost::posix_time::from_time_t(time(NULL) + 1), 
        &test_func1);

    int t1 = static_cast<int>(time(NULL));
    assert(i == 0);

    tasks_processor::get().start();
    assert(i == 1);
    int t2 = static_cast<int>(time(NULL));
    assert(t2 - t1 >= seconds_to_wait);

}
