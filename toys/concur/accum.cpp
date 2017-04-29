#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

std::thread::id master_thread; 

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        std::thread::id my_id = std::this_thread::get_id();
        if (my_id == master_thread) {
            std::cout << "master thread: " << my_id << std::endl;
        }
        result = std::accumulate(first,last,result);
    }
};


template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first,last); // input range

    if (!length) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = 
        (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads = 
        std::thread::hardware_concurrency();

    unsigned long num_threads = 
        std::max(hardware_threads!=0 ? hardware_threads : 2, max_threads);
    num_threads = 16;
    std::cout << "num threads: " << num_threads << '\n';

    unsigned long const block_size = length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
                accumulate_block<Iterator,T>(),
                block_start, block_end, std::ref(results[i]));
        if (i == 7) {
            master_thread = threads[i].get_id();
        }
        block_start = block_end;
    }
    accumulate_block<Iterator,T>()(
            block_start, last, results[num_threads-1]);

    std::for_each(threads.begin(), threads.end(), 
            std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);


}


int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // start with first element
                                    [](std::string a, int b) {
                                        return a + '-' + std::to_string(b);
                                    });
    std::cout << "sum: " << sum << '\n'
              << "product: " << product << '\n'
              << "dash-separated string: " << s << '\n';    

    sum = parallel_accumulate(v.begin(), v.end(), 42);
    std::cout << "sum: " << sum << '\n';

}
