    #include <unistd.h>
    #include <iostream>
    #include <fstream>
    #include <string>

    using namespace std;

    int main()
    {
    std::fstream fs;

    fs.open("/sys/class/gpio/gpio3/direction");
    fs << "out";
    fs.close();

    while(1){
    fs.open("/sys/class/gpio/gpio3/value");
    fs << "1";
    fs.close();

    fs.open("/sys/class/gpio/gpio3/value");
    fs << "0";
    fs.close();
   }

    return 0;
}
