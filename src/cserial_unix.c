#include "cserial.h"
#include <stdio.h>

serial_t serial_open(const char * port_name,int baudrate) {

    int   i;    
    int   status;    
    int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};    
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300}; 
    int   fd;
    
    struct termios options; 
    
    fd = open( port_name, O_RDWR|O_NOCTTY|O_NDELAY);    
    if (fd<0) return INVALID_SERIAL;    
                                    
    if(fcntl(fd, F_SETFL, 0) < 0) {      
        return INVALID_SERIAL;    
    } else {    
        //printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));    
    }    
       
    if(0 == isatty(STDIN_FILENO)) {    
        //printf("standard input is not a terminal device\n");    
        return INVALID_SERIAL;    
    } else {    
        printf("isatty success!\n");    
    }                  
    //printf("fd->open=%d\n",fd);    
    
    if( tcgetattr( fd,&options) !=  0) {    
        //perror("SetupSerial 1");        
        return INVALID_SERIAL;     
    }    
         
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)    
    {    
        if  (baudrate == name_arr[i])    
        {                 
            cfsetispeed(&options, speed_arr[i]);     
            cfsetospeed(&options, speed_arr[i]);      
        }    
    }         
       
  
    options.c_cflag |= CLOCAL;       
    options.c_cflag |= CREAD;    
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8; 
    options.c_cflag &= ~PARENB;     
    options.c_iflag &= ~INPCK; 
    options.c_cflag &= ~CSTOPB;
    options.c_oflag &= ~OPOST;    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);       
    options.c_iflag &= ~(ICRNL | IXON);
    options.c_cc[VTIME] = 1;     
    options.c_cc[VMIN] = 1;    

    tcflush(fd,TCIFLUSH);    
    
    if (tcsetattr(fd,TCSANOW,&options) != 0) {    
        return INVALID_SERIAL;     
    }    
    
    return fd;
}

int serial_write(serial_t s,char * buffer, int size) {
    int len = 0;    
       
    len = write(s,buffer,size);    
    if (len == size ) {    
        //printf("send data is %s\n",send_buf);  
        return len;    
    }         
    else {          
        tcflush(s,TCOFLUSH);    
        return INVALID_SERIAL;    
    } 
}

int serial_read(serial_t s,char * buffer, int size) {
    int readlen;
    while (size) {    
        readlen = read(s, buffer,size);
        
        size -= readlen;
        buffer += readlen;
        //printf("read %d,size %d\n",readlen,size);
    }
    return 0;
}

void serial_close(serial_t s) {
    close(s);
}

int  serial_rts(serial_t s,int val) {
    return 0;
}

int  serial_cts(serial_t s) {
    return 0;
}
void serial_get_error(char *buf,unsigned long *dw) {
   
}

