#include <iostream>
#include <fstream>
#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define RPI_FIRMWARE_DEV "/dev/vcio"
#define IOCTL_RPI_FIRMWARE_PROPERTY _IOWR(100, 0, char*)
#define RPI_FIRMWARE_STATUS_REQUEST 0
#define RPI_FIRMWARE_STATUS_SUCCESS 0x80000000
#define RPI_FIRMWARE_STATUS_ERROR   0x80000001
#define RPI_FIRMWARE_PROPERTY_END   0
#define RPI_FIRMWARE_SET_GPIO_STATE 0x00038041


#define RPI_MANUFACTURER_MASK                    (0xf << 16)
#define RPI_WARRANTY_MASK                        (0x3 << 24)
#define LINE_WIDTH_MAX                           80
#define HW_VER_STRING                            "Revision"
#define HIGH                                     1
#define LOW                                      0
int write_real_gpio(int gpio,int value);
int write_virtual_gpio(int gpio,int value);
//	define the support board version 
using namespace std;
typedef struct {
    uint32_t hwver;
    uint32_t cameraLedPin;
    char *desc;
    int (*pFunc)(int value1,int value2);
} rpi_hw_t;

static const rpi_hw_t rpi_hw_info[] = {
    // Model B+ Rev 1.0
    {
        .hwver  = 0x02,
        .cameraLedPin = 32,
        .desc = "Model B",
        .pFunc = write_real_gpio,
    },
    // Model ZERO W 
    {
        .hwver  = 0x9000c1,
        .cameraLedPin = 40,
        .desc = "Mode Zero w",
        .pFunc = write_real_gpio,
    },
    // Model 3B
    {
        .hwver  = 0xa02082,
        .cameraLedPin = 134,
        .desc = "Model 3B",
        .pFunc = write_virtual_gpio,
    },
     // Model 3B
    {
        .hwver  = 0xa020d3,
        .cameraLedPin = 134,
        .desc = "Model 3B",
        .pFunc = write_virtual_gpio,
    },
     // Model 3A+
    {
        .hwver  = 0x9020e0,
        .cameraLedPin = 134,
        .desc = "Model 3B",
        .pFunc = write_virtual_gpio,
    },
};
const rpi_hw_t *rpi_hw_detect(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char line[LINE_WIDTH_MAX];
    const rpi_hw_t *result = NULL;

    if (!f)
    {
        return NULL;
    }

    while (fgets(line, LINE_WIDTH_MAX - 1, f))
    {
        if (strstr(line, HW_VER_STRING))
        {
            uint32_t rev;
            char *substr;
            unsigned i;

            substr = strstr(line, ": ");
            if (!substr)
            {
                continue;
            }

            errno = 0;
            rev = strtoul(&substr[1], NULL, 16);  // Base 16
            if (errno)
            {
                continue;
            }
            printf("The hardware version =  %x\r\n", rev);
            for (i = 0; i < (sizeof(rpi_hw_info) / sizeof(rpi_hw_info[0])); i++)
            {
                uint32_t hwver = rpi_hw_info[i].hwver;
                // Take out warranty and manufacturer bits
                hwver &= ~(RPI_WARRANTY_MASK | RPI_MANUFACTURER_MASK);
                rev &= ~(RPI_WARRANTY_MASK | RPI_MANUFACTURER_MASK);
                
                if (rev == hwver)
                {
                    result = &rpi_hw_info[i];

                    goto done;
                }
            }
        }
    }

done:
    fclose(f);
    return result;
}

int write_real_gpio(int gpio,int value){
char buffer[1024] = {0};
sprintf(buffer,"gpio -g write %d %d",gpio, value);
printf("%s\n",buffer);
system(buffer);
return 0;
}
int write_virtual_gpio(int gpio,int value){
    int fd;
  fd = open(RPI_FIRMWARE_DEV, O_NONBLOCK);
  if (fd == -1) {
    return -1;
  }
    uint32_t buf[] = { 
        8 * sizeof(uint32_t), 
        RPI_FIRMWARE_STATUS_REQUEST, 
        RPI_FIRMWARE_SET_GPIO_STATE, 
        2 * sizeof(int), 
        0, 
        gpio,
        value ? 1 : 0,
        RPI_FIRMWARE_PROPERTY_END
    };
    int ret = ioctl(fd, IOCTL_RPI_FIRMWARE_PROPERTY, buf);
    if(ret == -1){
        return -1;
    }
    if(buf[1] != RPI_FIRMWARE_STATUS_SUCCESS){
        return -1;
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
   const rpi_hw_t *rpi_hw;
  if(argc <2){
  Preview_Usage(argv[0]);
  return 1;
  }
   unsigned char value = atoi(argv[1]);
   rpi_hw = rpi_hw_detect();
   if(!rpi_hw->pFunc(rpi_hw->cameraLedPin,value)){
     printf("OK\r\n");
   }
}
