#include "cserial.h"
#include <stdio.h>

serial_t serial_open(const char * port_name,int baudrate) {
	char full_name[20];
    DCB PortDCB;
    if (port_name[0] != '\\') {
        sprintf(full_name,"\\\\.\\%s",port_name);
    } else {
        sprintf(full_name,"%s",port_name);
    }
    serial_t s = CreateFile (full_name,GENERIC_READ | GENERIC_WRITE,0,                                   
                            NULL,OPEN_EXISTING,0,NULL);
                            
    if ( s == INVALID_HANDLE_VALUE ) {
        return INVALID_SERIAL;
    }
    PortDCB.DCBlength = sizeof (DCB);
    GetCommState (s, &PortDCB); 
    PortDCB.fBinary = TRUE; 
    PortDCB.fParity = FALSE;  
    PortDCB.fDsrSensitivity = FALSE; 
    PortDCB.fErrorChar = FALSE;  
    PortDCB.fOutxDsrFlow = FALSE; 
    PortDCB.fAbortOnError = FALSE;
    PortDCB.fNull = FALSE;  
    PortDCB.fTXContinueOnXoff = TRUE;
    PortDCB.BaudRate= baudrate;
    PortDCB.ByteSize=8;
    PortDCB.Parity = NOPARITY;
    PortDCB.StopBits =  ONESTOPBIT;
    if (!SetCommState (s, &PortDCB)) {
        CloseHandle(s);
        return INVALID_SERIAL;
    }
    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = MAXDWORD;    //0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 5000;
    CommTimeOuts.ReadTotalTimeoutConstant = 5000;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 5000;
    CommTimeOuts.WriteTotalTimeoutConstant = 5000;
    SetCommTimeouts( s, &CommTimeOuts );    
    return s;
}

int serial_write(serial_t s,char * buffer, int size) {
    DWORD dwNumBytesWritten;  
    return WriteFile (s,buffer,size,&dwNumBytesWritten,NULL);
}

int serial_read(serial_t s,char * buffer, int size) {
    DWORD dwRead; 
    ReadFile(s, buffer, size, &dwRead,NULL);
    return (int) dwRead; 
}

void serial_close(serial_t s) {
    CloseHandle(s);
}

int  serial_rts(serial_t s,int val) {
    return 0;
}

int  serial_cts(serial_t s) {
    return 0;
}
void serial_get_error(char *buf,DWORD *dw) {
   
    *dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        *dw,
        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        buf,
        0, NULL );
}
