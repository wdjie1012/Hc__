#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <string.h>
using namespace std;

char inputBuffer[256] = {};
char message[]="hi";
int port=8700;
bool runFlag;
int forClientSockfd = 0;
int sockfd = 0;       //sockfd套接字
int recvbytes=0;                          //判断是否断开连接
struct sockaddr_in serverInfo,clientInfo; // clientInfo连接实体地址
socklen_t addrlen = sizeof(clientInfo);

char mes=1;
void server();
int main(int argc, char **argv) {
    while(1){
        thread t1(server);
        t1.detach();
        sleep(300);
    }
}
void server() {
    /**
     * 1.创建套接字
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /**
     * 2.绑定
     */
    bzero(&serverInfo, sizeof(serverInfo));
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    /**
     * 3.监听
     */
    listen(sockfd,5);
    while (1) {
        forClientSockfd = accept(sockfd, (struct sockaddr *) &clientInfo, &addrlen);
        runFlag=true;
        while(runFlag) {
            memset(inputBuffer, 0, sizeof(inputBuffer));
            recvbytes = recv(forClientSockfd, inputBuffer, sizeof(inputBuffer), 0);
            /**
             * 处理粘包
             */
            if (inputBuffer[0] == inputBuffer[1] == inputBuffer[4] == 'F' || inputBuffer[5] == 'E') {
                inputBuffer[6] = '\0';
            }
            /**
             * 异常情况退出
             */
            if(recvbytes==0||recvbytes==-1){
                runFlag=false;
                break;
            }
            /**
             * 接口
             */
            mes=1;
            switch (inputBuffer[3]){
                case 'U':
                    mes=mes;
                    break;
                case 'D':
                    mes=mes<<1;
                    break;
                case 'L':
                    mes=mes<<2;
                    break;
                case 'R':
                    mes=mes<<3;
                    break;
                case 'S':
                    mes=mes<<4;
            }
            printf("Get:%s\n", inputBuffer);
            printf("%c\n",mes);
        }
    }
}







