//============================================================================
// Name        : HelloWorldReview.cpp
// Author      : TomB
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



using namespace std;



int main() {

	int file;
	char *filename = "/dev/i2c-1";

	if ((file = open(filename, O_RDWR)) < 0)
	{
		perror("Failed to open 12c bus");
		exit(1);
	}

	int addr = 0x68;
	if (ioctl(file, I2C_SLAVE, addr)<0){
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}

	char buf[0x12] = {0};
	int dataTop;
	int dataLow;
	char channel;

    while(1){
		//USING I2C READ
		//if (read(file, buf, 0x12) != 0x12){
			/* ERROR HANDLING: i2c transaction failed */
			//printf("Failed to read from the i2c bus.\n");
		//}
		//else {
			//data = (int)((buf[0] & 0b00001111)<<8)+buf[1];
			 char writeBuffer[1] = {0x00};
			 write(file, writeBuffer, 1);
			 read(file, buf, 0x1);
			 dataLow=(buf[0] & 0b00001111);
			 dataTop=((buf[0] & 0b01110000)>>4);
			printf("Seconds: %d%d \n",dataTop,dataLow);
			sleep(1);
		//}
	}


	//seconds = read(file, channel, 1);
	return 0;
}
