/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 29-10-2019					                                  */
/******************************************************************************/

#include <iostream>				//	cout 	
#include <sys/inotify.h>		// 	inotify API
#include <unistd.h>				//	read
#include <cstdlib>				//	malloc, free

#include "dir_monitor.hpp"		//	Header file		
#include "reactor.hpp"
#include "factory.hpp"
#include "action.hpp"

using namespace ilrd;
void Foo(std::string a)
{
	std::cout << "foooooo" << std::endl;
}
void SimpleTest();


int main()
{
	ServiceLocator<std::string> sl;
	Reactor reactor;
	Factory<char, Action> factory;

	sl.Add("reactor", reactor);
	sl.Add("factory", factory);

	std::string path("/home/student/Ori-Michaeli/projects/minion_project/add_ons/");
	DirMonitor dirMonitor(path, Foo, sl);

	reactor.Run();
	//SimpleTest();

	return 0;
}

void SimpleTest()
{
	int fd = inotify_init();

    inotify_add_watch(fd, "/home/student/Ori-Michaeli/projects/minion_project/dir_monitor/", IN_CREATE | IN_MODIFY | IN_DELETE | IN_MOVED_TO);

    size_t bufsiz = sizeof(struct inotify_event) + 100 + 1;
    struct inotify_event* event = reinterpret_cast<struct inotify_event *>									  (malloc(bufsiz));
    /* wait for an event to occur */
    read(fd, event, bufsiz);
    std::cout << "event->wd " << event->wd << std::endl;
    std::cout << "event->mask " << event->mask << std::endl;
    std::cout << "event->cookie " << event->cookie << std::endl;
    std::cout << "event->len " << event->len << std::endl;
    std::cout << "event->name " << event->name << std::endl;
    free(event);

    // std::cout << fd << std::endl;
}


