#include "cserial.h"
#include "stdio.h"


int main(int argc,char ** argv) {
    char buf[] = "hello";
    char error[200];
    unsigned long errid;
    serial_t s = serial_open(argv[1],115200);
    if (s == INVALID_SERIAL) {
        serial_get_error(error,&errid);
        printf("ERROR Cannot open %s, error: %s(%d)\n",argv[1],error,errid);
    }
    serial_write(s,buf,sizeof(buf));
    serial_read(s,buf,sizeof(buf));
    printf("read %s\n",buf);
    return 0;
}