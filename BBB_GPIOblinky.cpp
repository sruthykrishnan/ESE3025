#include<iostream>
#include<unistd.h>
#include<string>
int main()
{
system("echo out > /sys/class/gpio/gpio68/direction");
for(int i = 0;i<100000;i++)
{
system("echo 1 > /sys/class/gpio/gpio68/value");
usleep(1000000);
system("echo 0 > /sys/class/gpio/gpio68/value");
usleep(1000000);
}
system("echo 0 > /sys/class/gpio/gpio68/value");
return 0;
}
