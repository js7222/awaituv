
#include <experimental/coroutine>

#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/system_timer.hpp> 
#include <boost/thread/future.hpp>
#include <boost/thread.hpp> 

using namespace boost::asio; 

using namespace std::chrono; 

template <typename... Args> 
struct std::experimental::coroutine_traits<boost::future<void>, Args...>
{ 
    struct promise_type
    { 
	boost::promise<void> p; 
	auto get_return_object() { return p.get_future(); } 
	std::experimental::suspend_never initial_suspend() { return {}; } 
	std::experimental::suspend_never final_suspend() { return {}; } 
	void set_exception(std::exception_ptr e) { p.set_exception(std::move(e)); } 
	void return_void() { p.set_value(); } 
	void unhandled_exception() { std::terminate(); }
    };
}; 


template <typename R, typename... Args> 
struct std::experimental::coroutine_traits<boost::future<R>, Args...>
{ 
    struct promise_type
    { 
	boost::promise<R> p; 
	auto get_return_object() { return p.get_future(); } 
	std::experimental::suspend_never initial_suspend() { return {}; } 
	std::experimental::suspend_never final_suspend() { return {}; } 
	void set_exception(std::exception_ptr e) { p.set_exception(std::move(e)); } 
	template <typename U> void return_value(U &&u) { 
	    p.set_value(std::forward<U>(u)); 
	}
	void unhandled_exception() { std::terminate(); }
    }; 
}; 



boost::future<void> f()
{ 
    puts("Hi!"); 
    co_return; 
} 
  
boost::future<int> g()
{ 
    co_return 42; 
} 

auto pass_the_pointer(std::unique_ptr<int>&& ptr)
{
    std::cout << "ptr.get() in function: " << ptr.get() << '\n';

    return std::move(ptr);
}


int main()
{
    f();
    g();
    io_service io; 
    system_timer timer(io); 
    std::cout << "BOOST_THREAD_VERSION: " << BOOST_THREAD_VERSION << "\n";
    timer.expires_from_now(1000ms); 

    std::unique_ptr<int> ptr = std::make_unique<int>(static_cast<int>('a'));
    std::cout << "ptr.get(): " << ptr.get() << '\n';

    auto p2 =pass_the_pointer(std::move(ptr));

    std::cout << "ptr.get() after function: " << ptr.get() << '\n';
    std::cout << "p2.get(): " << p2.get() << '\n';    
    puts("waiting for a tick"); 

    auto p = boost::promise<int>{};

    auto f = p.get_future();
//    io.post([&] { p.set_value(42); });

    timer.async_wait([&p](boost::system::error_code ec) { 
	    if (ec)
	    {
		printf("timer failed: %d\n", ec.value());
	    }
	    else
	    {
		puts("tick");
		p.set_value(990);
	    }
	}); 

    
    io.run();
    printf("%d\n", f.get());

};
