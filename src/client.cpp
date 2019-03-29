#include "ros/ros.h"
#include "std_msgs/String.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//typedef __int32 int32_t;
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub = n.subscribe("chatter1", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */

   std::cout << "/111111111111/" << '\n';

   int sockfd = 0;
     sockfd = socket(AF_INET , SOCK_STREAM , 0);

     if (sockfd == -1){
         printf("Fail to create a socket.");
     }

     //socket的連線

     struct sockaddr_in info;
     bzero(&info,sizeof(info));
     info.sin_family = PF_INET;

     //localhost test
     info.sin_addr.s_addr = inet_addr("192.168.0.120");
     info.sin_port = htons(5666);


     int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
     if(err==-1){
         printf("Connection error");
     }

     //std::cout << err << '\n';
     //Send a message to server
		 // uint32_t ntohl(uint32_t message);
		 // message = 1;
     uint32_t message = 1233;


		while (err==0 && ros::ok()) {
		 	/* code */
     //std::cout << "/11111111111111111111111111/" << '\n';
     //char message[] = {"Hi there"};
     //char receiveMessage[100] = {};
		 //__int64 a;
		 // uint32_t ntohl(uint32_t message);
		 // message = 1;
		 // int32_t message = 1;
     //char receiveMessage[100] = {};

      
      uint32_t message_net = htonl(message);
    //  send(sock, (const char*)&message, 4, 0);

     send(sockfd, (const char*)&message_net,sizeof(message_net),0);
     //recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
      std::cout << message << '\n';
      message++;
     //printf("%s",receiveMessage);
     //printf("close Socket\n");
     //close(sockfd);
     //std::cout << "/2222222222222222/" << '\n';
		 //message=message++;
		  //std::cout << err << '\n';
	  	// err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
		  //ros::spin();
	   }


	 std::cout << "/333333333333333333/" << '\n';
   ros::spin();

  return 0;
}
