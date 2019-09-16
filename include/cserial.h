#ifndef _CSERIAL_H
#define _CSERIAL_H


#ifdef __MINGW32__
#define OS_WIN
#else
#define OS_UNIX
#endif

#ifdef OS_WIN

#include <Windows.h>

typedef  HANDLE serial_t;
#define INVALID_SERIAL INVALID_HANDLE_VALUE

#endif //OS_WIN



serial_t serial_open(const char * port_name,int baudrate);
int  serial_write(serial_t s,char * buffer, int size);
int  serial_read(serial_t s,char * buffer, int size);
void serial_close(serial_t s);
int  serial_rts(serial_t s,int val);
int  serial_cts(serial_t s); 
void serial_get_error(char *buf,DWORD *dw);
 
#endif