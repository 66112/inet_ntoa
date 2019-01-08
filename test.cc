#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
//int main()
//{
//    struct sockaddr_in addr;
//    inet_aton("192.168.74.132",&addr.sin_addr);
//    uint32_t* ptr=(uint32_t*)(&addr.sin_addr);
//    printf("addr: %d\n",*ptr);  //addr.sin_addr的内容
//    printf("addr_str: %s\n",inet_ntoa(addr.sin_addr));  //把sin_addr的数字转成字符串
//    return 0;
//}
//////////////////////////////////////////////////////////////////
//int main()
//{
//    char* ptr1,*ptr2;
//    struct sockaddr_in addr1;
//    struct sockaddr_in addr2;
//    addr1.sin_addr.s_addr = 0;
//    addr2.sin_addr.s_addr = 0xffffffff;
//    ptr1 = inet_ntoa(addr1.sin_addr);  //按理说,ptr1 = "0.0.0.0"
//    ptr2 = inet_ntoa(addr2.sin_addr);  //按理说,ptr2 = "255.255.255.255"
//    printf("ptr1: %s ptr2: %s\n",ptr1,ptr2); //但结果都是255.255.255.255,ptr2覆盖了ptr1 
//    return 0;
//}
////////////////////////////////////////////////////////////////
pthread_mutex_t lock;
void* Fun1(void* arg)
{
    pthread_detach(pthread_self());
    struct sockaddr_in* addr = (struct sockaddr_in*)arg;
    char* ptr = inet_ntoa(addr->sin_addr);
    printf("addr1: %s\n",ptr);     //输出为"0.0.0.0" 正确
    pthread_exit(NULL);
    return NULL;
}
void* Fun2(void* arg)
{
    pthread_detach(pthread_self());
    struct sockaddr_in* addr = (struct sockaddr_in*)arg;
    char* ptr = inet_ntoa(addr->sin_addr);
    printf("addr2: %s\n",ptr);     //输出为"255.255.255.255"  正确
    pthread_exit(NULL);
    return NULL;
}
int main()     
{
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;
    struct sockaddr_in addr1;
    struct sockaddr_in addr2;
    addr1.sin_addr.s_addr = 0;
    addr2.sin_addr.s_addr = 0xffffffff;
    pthread_create(&tid1,NULL,Fun1,&addr1);
    pthread_create(&tid2,NULL,Fun2,&addr2);
    //sleep(1);  //睡一秒，等待子线程
    //pthread_join(tid1,NULL);
    //pthread_join(tid2,NULL);
    return 0;
}


