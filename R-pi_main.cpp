#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include"proj_decl.h"

using namespace std;

class IPC{
    private:
    unsigned int socket_no;
    
    public:
    virtual status  open_channel()=0;
    virtual status  close_channel()=0;
};

class Socket:public IPC{
    private:
            int domain;
            int type;
            int protocol;
            int soc_fd;
    public:
            soc_struct soc_struct_head;
            Socket(int domain=AF_UNIX,int type =SOCK_STREAM ,int protocol=0)
            {
                this->domain  = domain;
                this->type    = type;
                this->protocol= protocol;
            }
            status socket_init();
            status open_channel();
            status close_channel();

};

class MsgQue:public IPC{
    private:

    public:
    status open_channel();
    status close_channel();
};

int main()
{
    cout<<__LINE__<<"Hello World"<<endl;    
    Socket soc_obj(AF_INET);
    soc_obj.open_channel();
    while(1)
    {
        sleep(1);
    }
    
}


/* Need to do below code dynamic
on the basis of Socket type Structure should be filled  */

status Socket:: socket_init(void)
{
    soc_struct_head.sin_family          = AF_INET; 
    soc_struct_head.sin_port            = 2000;
    soc_struct_head.sin_addr.s_addr     = inet_addr("127.0.0.1");
    return SUCCESS;
}


    #define MAX_PENDING_CONNECTION 10

status Socket:: open_channel(void)
{
    int ret=0;
    pthread_t pthread_accept;
    socket_init();
    soc_fd = socket(domain,type,protocol);
    if (soc_fd == -1)
    {
        cout<<"socket Error"<<endl;
    }
  //  cout<<"socfd"<<soc_fd<<"&socfd"<<&soc_fd <<endl;
    ret = bind(soc_fd,(const struct sockaddr *)&soc_struct_head,sizeof(soc_struct));
    if (ret == -1)
    {
        cout<<"bind Error"<<endl;
    }
    ret = listen(soc_fd,MAX_PENDING_CONNECTION );
    if (ret == -1)
    {
        cout<<"listen Error"<<endl;
    }


    ret= pthread_create(&pthread_accept,NULL,&soc_conn_thread,(void *)&soc_fd);
    if(0!=ret)
    {
        cout<<"pthread_create Failed"<<endl;
        /*
        * print error code Here and design retry stratergy if socket is already created
        */
    }

return SUCCESS;    
}
status Socket:: close_channel(void)
{

return SUCCESS;
}


status MsgQue:: open_channel(void)
{

return SUCCESS;
}

status MsgQue:: close_channel(void)
{

return SUCCESS;
}


void* soc_conn_thread(void *soc_fd_ptr)
{
    int thread_running = true; 
    socklen_t   sock_struct_len=0;
    soc_struct soc_que_struct[10];
    int i=0;
    pthread_t thread_info= pthread_self();
    int soc_fd= *( (int *)soc_fd_ptr);
    cout<<"socfd"<<soc_fd<<endl;
    cout<<"soc_conn_thread created"<<endl;
    while(thread_running)
    {
        int soc_fd_cl = accept(soc_fd,  (struct sockaddr *)&soc_que_struct,&sock_struct_len );
        if(-1 == soc_fd_cl)
        {
           cout<<"Accept connection Failed"<<endl;
        }
        memcpy((void*)(soc_que_struct+i),(void *)soc_que_struct,sizeof(soc_struct));
        i++;
//Store accepted connection in data structure Here
//send a connection estabilised message to client
    }
return NULL;
}

void *soc_disConn_thread(void *arg)
{
    cout<<"soc_disConn_thread"<<endl;
    return NULL;
}
