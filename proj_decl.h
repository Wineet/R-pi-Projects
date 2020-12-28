#include<iostream>

typedef enum{SUCCESS,FAIL}status;

class IPC;
class MsgQue;
class Socket;

typedef struct sockaddr_in soc_struct; 



void *soc_conn_thread(void *);
void *soc_disConn_thread(void *);