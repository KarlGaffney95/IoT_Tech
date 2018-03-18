#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>

//Mutex lock for state variable

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int changed = 0;
int running = 1;

void* thread(void* arg){

	int oldButtonVal, buttonVal = 0;
        int i;

	FILE* fp;

	for(i = 0; i < 1000; i++){

		fp = fopen("/sys/class/gpio/gpio60/value", "r");
		fscanf(fp, "%d", &buttonVal);
		fclose(fp);

		if(buttonVal != oldButtonVal){

			if(buttonVal == 1){
				pthread_mutex_lock(&mutex1);
				changed = 1;
				pthread_mutex_unlock(&mutex1);
			}

			buttonVal = oldButtonVal;

		}

		usleep(10000);

	}
	pthread_mutex_lock(&mutex2);
	running = 0;

	pthread_mutex_unlock(&mutex2);

}

int main(int argc, char* argv[]){

	pthread_t threadID;

	void* exitStatus;

	int buttonState;
	int temp1;
	int temp2;

	FILE* fp;

	fp = fopen("/sys/class/gpio/gpio60/direction","w");
	if(fp == NULL)
	{
		perror("Couldn't open GPIO60");
		return -1;
	}

	fprintf(fp,"in");
	fclose(fp);

	fp = fopen("/sys/class/gpio/gpio48/direction","w");
	fprintf(fp,"out");
	fclose(fp);

	pthread_create(&threadID, NULL, thread, NULL);
	pthread_mutex_lock(&mutex2);
	temp2 = running;
	pthread_mutex_unlock(&mutex2);

	while(temp2){

			pthread_mutex_lock(&mutex1);
			temp1 = changed;
			pthread_mutex_unlock(&mutex1);

		if(temp1 == 1){

			fp = fopen("/sys/class/gpio/gpio60/value", "r");
			fscanf(fp, "%d", &buttonState);
			fclose(fp);

			if(buttonState == 0){

				fp = fopen("/sys/class/gpio/gpio60/value","w");
				fprintf(fp,"1");
				fclose(fp);
				buttonState = 1;
			}
			else{

				fp = fopen("/sys/class/gpio/gpio48/value","w");
				fprintf(fp,"0");
				fclose(fp);
				buttonState = 0;
			}

                        pthread_mutex_lock(&mutex1);
			changed = 0;
			pthread_mutex_unlock(&mutex1);
		}

		pthread_mutex_lock(&mutex2);
		temp2 = running;
		pthread_mutex_unlock(&mutex2);
	}

	pthread_join(threadID, &exitStatus);

	return 0;
}
