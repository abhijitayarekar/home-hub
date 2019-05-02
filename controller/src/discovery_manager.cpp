#include <iostream>
#include <chrono>
#include <iomanip>

#include "discovery_manager.h"

using namespace Controller;

void DiscoveryManager::start()
{
	PubSub::start();
	m_upnp_thread = std::thread(&DiscoveryManager::upnp_thread_func, this);
}

void DiscoveryManager::stop()
{
	PubSub::stop();
	m_upnp_thread.join();
}
		
void DiscoveryManager::upnp_thread_func()
{
	publish(m_name + " Started.");
	while (m_started) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		cout << m_name << " : upnp : Sleeping : " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")<<endl;
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 7));
	}
	publish(m_name + " Stopped.");
}
