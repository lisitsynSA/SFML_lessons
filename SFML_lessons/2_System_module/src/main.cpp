#include <iostream>
#include "SFML/System.hpp"

void func();
void func2(int x);

sf::Mutex mutex;

int main()
{
	std::cout << "SFML  START\n"; // -subsystem,windows in linker flags turn off console

	/// HANDLING TIME

	sf::Clock clock; // starts the clock

	sf::Time t1 = sf::microseconds(10000);
	sf::Time t2 = sf::milliseconds(10);
	sf::Time t3 = sf::seconds(0.01f); // 9999 usec or 9 msec
	// t1==t2~=t3
	std::cout << "T1 == T2 : " << (t1 == t2) <<\
			   "; T2 == T3 : " << (t2 == t3) << ";\n";

	sf::Time time = t3 + t1; // 19999 usec or 19 msec or 0.01999 sec

	sf::Int64 usec = time.asMicroseconds();
	sf::Int32 msec = time.asMilliseconds();
	float     sec  = time.asSeconds();

	std::cout << "Time: usec " << usec << "; msec " << msec << "; sec " << sec << ";\n";

	sf::Time elapsed1 = clock.restart(); // get Clock and start the new clock
	std::cout << elapsed1.asSeconds() << "\n";

	sf::Time elapsed2 = clock.getElapsedTime(); // get Clock
	std::cout << elapsed2.asSeconds() << "\n";

	/// THREADS

    // create a thread with func() as entry point
    sf::Thread thread1(&func);
    sf::Thread thread2(&func2, 25);
    //sf::Thread thread(&MyClass::func, &object); - for function from MyClass

    // run it
    thread1.launch();

    // wait 5 sec
    sf::sleep(sf::milliseconds(5000));

    // mutex for writing in console
    std::cout << "[Main thread] Try to lock mutex\n";
    mutex.lock();
    std::cout << "[Main thread] Mutex lock SUCCESS\n";

    // the main thread continues to run...
    std::cout << "[Main thread]\n";

    // free mutex on writing in console
    mutex.unlock();

    // run it
    thread2.launch();
    // block execution until the thread is finished
    thread2.wait();


    // block execution until the thread is finished
    thread1.wait();

    // wait 3 sec
    sf::sleep(sf::milliseconds(3000));

	return 0;
}

void func()
{
	// mutex for writing in console
	// it unlock with destructor in the end of function or exception
	sf::Lock lock(mutex); // mutex.lock()
    // this function is started when thread.launch() is called
    std::cout << "[Thread1] func(void)\n";
    for (int i = 0; i < 10; i++)
    {
    	// wait 1 sec
    	sf::sleep(sf::milliseconds(1000));
    	std::cout << "[Thread1] " << i << "\n";
    }
    sf::Thread thread(&func2, 725);
    // run it
    thread.launch();
    // after thread's destructor thread.wait() is calling
	std::cout << "[Thread1] END\n";
}// mutex.unlock() & thread.wait();


void func2(int x)
{
    std::cout << "[Thread2] func(int x = " << x << ")\n";
	// wait 1 sec
	sf::sleep(sf::milliseconds(1000));
	std::cout << "[Thread2] END\n";
}
