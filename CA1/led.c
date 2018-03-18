    #include <unistd.h>
    #include <stdio.h>

    int main(){

            FILE *export = NULL;        //declare pointers
            FILE *dir = NULL;
            char str1[] = "low";
            char str2[] = "high";

	    while(1){
            dir = fopen ("/sys/class/gpio/gpio49/direction", "w");
            fwrite (str2, 1, sizeof(str1), dir);   //set the pin to HIGH
            fclose (dir);

            dir = fopen ("/sys/class/gpio/gpio49/direction", "w");
            fwrite (str1, 1, sizeof(str1), dir);   //set the pin to LOW
            fclose (dir);
	}


	return 0;
    }
