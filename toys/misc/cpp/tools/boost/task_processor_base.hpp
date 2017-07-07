#ifndef TASK_PROCESSOR_BASE
#define TASK_PROCESSOR_BASE

#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>

namespace detail {
    
template <class T>
struct task_wrapped {
private:
    T task_unwrapped_;

public:
    explicit task_wrapped(const T& task_unwrapped)
        : task_unwrapped_(task_unwrapped)
    {}

    void operator()() const {
        try {
            boost::this_thread::interruption_point();
        } catch (const boost::thread_interrupted&) {}

        try {
            task_unwrapped_();
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << '\n';
        } catch (const boost::thread_interrupted&) {
            std::cerr << "Thread interrupted\n";
        } catch (...) {
            std::cerr << "Unknown exception\n";
        }
    }
};

template <class T>
inline task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
    return task_wrapped<T>(task_unwrapped);
}

} // namespace detail

namespace tp_base {

class tasks_processor: private boost::noncopyable {
protected:
    boost::asio::io_service         ios_;
    boost::asio::io_service::work   work_;

    tasks_processor()
        : ios_(), work_(ios_) 
    {}

public:
    static tasks_processor& get() { 
        static tasks_processor proc;
        return proc;
    };

    template <class T>
    inline void push_task(const T& task_unwrapped) {
        ios_.post(detail::make_task_wrapped(task_unwrapped));
    }

    void start() {
        ios_.run();
    }
    void stop() {
        ios_.stop();
    }
}; // tasks_processor


int g_val = 0;
void func_test() {
    ++g_val;
    if (g_val == 3) {
        throw std::logic_error("just checking");
    }

    boost::this_thread::interruption_point();
    if (g_val == 10) {
        // emulation of thread interrupt
        throw boost::thread_interrupted();
    }
    if (g_val == 90) {
        tasks_processor::get().stop();
    }
}


} // namespace tp_base

#endif

