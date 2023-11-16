#include <iostream>
#include <future>

using namespace std::literals;

void func(std::promise<int> x)
{
	std::this_thread::sleep_for(5s);
	x.set_value(25);
}


int main()
{
	std::promise<int> prom;
	std::future<int> ftr = prom.get_future();
	std::thread tx{ func,std::move(prom) };
	std::future_status status{};

	do {
		status = ftr.wait_for(200ms);

		std::cout << "Some work ...\n";

	} while (status != std::future_status::ready);

	std::cout << "value is : " << ftr.get() << '\n';
	tx.join();
}
