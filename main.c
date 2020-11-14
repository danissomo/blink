#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PD05 25
#define EXPORT_DIR "/sys/class/gpio/export"
#define GPIO_DIR_MODE "/sys/class/gpio/gpio%s/direction"
#define GPIO_DIR_VALUE "/sys/class/gpio/gpio%s/value"

int main(int count, char **arg){
    int fd;
    char modedir[50], valuedir[50];
    sprintf(modedir, GPIO_DIR_MODE, arg[1]);
    sprintf(valuedir, GPIO_DIR_VALUE, arg[1]);

    fd = open(EXPORT_DIR, O_WRONLY);
    if(fd == -1) printf("error open");
    write(fd, arg[1], strlen(arg[1]));
    close(fd);

    fd = open(modedir, O_WRONLY);
    if(fd == -1) printf("error open");
    write(fd, "out", 3);
    close(fd);
    
    fd = open(valuedir, O_WRONLY);
    if(fd == -1) printf("error open");
    while (1){
        sleep(1);
        write(fd, "1", 1);
        sleep(1);
        write(fd, "0", 1 );
    }
}