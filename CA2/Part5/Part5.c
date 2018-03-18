#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/epoll.h>

void* threadFunction(void* arg){

	int lastState = 0;
	int currentState = 0;
	int previousLed;

	FILE* file;

	int fd = open("/sys/class/gpio/gpio45/value", O_RDONLY | O_NONBLOCK);

	if(fd == -1){
	   	perror("Can't open GPIO file");
	}
	
	int epollfd = epoll_create(100);

	if(epollfd == -1){
	   	perror("epoll create failed");
	}

	struct epoll_event ev;

	ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
	ev.data.fd = fd;

	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1){

	   	perror("GPIO: Failed to add control interface");
	}
	int epollRet = epoll_wait(epollfd, &ev, 1, -1);

	for(int i = 0; i < 1000; i++){

		epollRet = epoll_wait(epollfd, &ev, 1, -1);

		if(epollRet == -1){
			perror("GPIO: Poll Wait fail");
		}
		usleep(10000);

		file = fopen("/sys/class/gpio/gpio45/value", "r");
		fscanf(file, "%d", &currentState);
		fclose(file);
	
		if(currentState == 1){
			file = fopen("/sys/class/gpio/gpio60/value", "r");
			fscanf(file, "%d", &previousLed);
			fclose(file);

			if(previousLed == 0){
				file = fopen("/sys/class/gpio/gpio60/value","w");
				fprintf(file,"1");
				fclose(file);
			}

			else if(previousLed == 1){
				file = fopen("/sys/class/gpio/gpio60/value","w");
				fprintf(file,"0");	
				fclose(file);

			}

		}

	}

}

int main(void){

	pthread_t threadID;
	void* exitStatus;

	FILE* file;

	file = fopen("/sys/class/gpio/gpio45/direction","w");
	fprintf(file,"in");
	fclose(file);

	file = fopen("/sys/class/gpio/gpio60/direction","w");
	fprintf(file,"out");
	fclose(file);

	file = fopen("/sys/class/gpio/gpio45/edge","w");
	fprintf(file,"rising");	
	fclose(file);

	pthread_create(&threadID, NULL, threadFunction, NULL);
	pthread_join(threadID, &exitStatus);

	return 0;
}