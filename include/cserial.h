#ifndef _CSERIAL_H
#define _CSERIAL_H

#include <stdio.h>   
#include <stdlib.h>
#include <string.h>    

#ifdef __MINGW32__
#define OS_WIN
#else
#define OS_UNIX
#endif

#ifdef OS_WIN

#include <Windows.h>

typedef  HANDLE serial_t;
#define INVALID_SERIAL INVALID_HANDLE_VALUE

#else

#include <unistd.h>   
#include <sys/types.h>     
#include <sys/stat.h>       
#include <fcntl.h>   
#include <termios.h>    
#include <errno.h>  

typedef  int serial_t;
#define INVALID_SERIAL -1
   
#endif //OS_WIN

#ifndef TRUE
#define FALSE  -1    
#define TRUE   0
#endif

serial_t serial_open(const char * port_name,int baudrate);
int  serial_write(serial_t s,char * buffer, int size);
int  serial_read(serial_t s,char * buffer, int size);
void serial_close(serial_t s);
int  serial_rts(serial_t s,int val);
int  serial_cts(serial_t s); 
void serial_get_error(char *buf,unsigned long *dw);
 
#endif
