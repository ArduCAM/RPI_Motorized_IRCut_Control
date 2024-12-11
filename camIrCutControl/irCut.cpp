#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>

#define CAMERA_LED_PIN 4
#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

// GPIO Pin
char *chipname = (char *)"gpiochip0";	        
struct gpiod_chip *chip;
struct gpiod_line *line;

int write_gpio(int gpio,int value)
{
    int ret;
    chip = gpiod_chip_open_by_name(chipname);
    if (chip == NULL) {
        perror("Open chip failed\n");
        return 1;
    }  
    line = gpiod_chip_get_line(chip, gpio);
	if (line == NULL) {
		perror("Get line failed\n");
        gpiod_chip_close(chip);
        return 2;
	}
    ret = gpiod_line_request_output(line, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
        gpiod_line_release(line);
        return 3;
	}
    ret = gpiod_line_set_value(line, value);
	if (ret < 0) {
		perror("Set line output failed\n");
        gpiod_line_release(line);
        return 4;
	}
    return 0;
}

int Preview_Usage(char* sPrgNm)
{
  printf("Usage : %s <0/1>\n", sPrgNm);
  printf("0: turn off 1: turn on\n");
    return 0;
}
int main(int argc, char** argv)
{ 
   if(argc <2){
    Preview_Usage(argv[0]);
    return 1;
   }
   unsigned char value = atoi(argv[1]);
   write_gpio(CAMERA_LED_PIN,value); 
}
