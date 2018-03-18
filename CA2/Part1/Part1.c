#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main (void)
{
	int pid,i,buttonState;
	int buttonVal, oldButtonVal = 0;

	FILE *fp;

	fp = fopen("/sys/class/gpio/gpio60/direction","w");
        if(fp == NULL)
	{
		perror("Couldn't open GPIO60");
		return -1;
	}

	fprintf(fp,"in");	// set the direction to IN	
        fclose(fp);

	fp = fopen ("/sys/class/gpio/gpio48/direction", "w");
        fprintf (fp, "out");   // set the direction to OUT
        fclose(fp);

	pid = fork();

	if (pid == 0){

	for(i=0; i<1000; i++){

	  fp = fopen("/sys/class/gpio/gpio60/value", "r+");
	  fscanf(fp, "%i", &buttonVal);
	  fclose(fp);

	  if(buttonVal != oldButtonVal){
		
		  if(buttonState == 0){
		      fp = fopen("/sys/class/gpio/gpio48/value","w");
		      fprintf(fp,"1");
		      fclose(fp);
		      buttonState = 1;
	          }
                  else {
		             fp = fopen("/sys/class/gpio/gpio48/value","w");
		             fprintf(fp,"0");
		             fclose(fp);
			     buttonState = 0;
                  }
	   
	     oldButtonVal = buttonVal;

            }

	usleep(10000); 
	}
	}
    
   if (pid > 0){
       wait(NULL);
   }

   return 0;
}
