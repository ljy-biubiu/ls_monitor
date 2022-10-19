#include "LED_serverAPI.h"
#include <stdlib.h>
#include <QDebug>
#define CHECK_MAX_NUM 3
#define SERVER_PORT 8234

static unsigned char CheckCmd[4]={0xAA,0x01,0x00,0xAB};//查询播放状态
static unsigned char PlayCmd[4]={0xAA,0x02,0x00,0xAC};//触发报警命令
static unsigned char StopCmd[4]={0xAA,0x03,0x00,0xAD};//停止报警命令

#pragma pack(1)  //以下结构体以一个字节对齐

//定义服务器端存放客户端信息的结构
struct TCPClientInfo
{
	int clientfd;  //客户端的套接字描述符
	struct in_addr ip; //存放 32位 ip地址
	pthread_t ClientThread_id;
	int play_state;
	int play_contrl;
	int commanded_state;
	int connect_state;
	struct TCPClientInfo *next; //保存下一个节点的地址
};

struct TCPClientInfo *ClientInfoListHead=NULL;  //客户端信息的链表头

#pragma pack(1) //以下结构体以一个字节对齐

//定义socket数据传输的结构体
struct SocketPackageData
{
	unsigned char Cmd[16];   //存放数据或者命令
};


/*
函数功能: 创建链表头
*/
struct TCPClientInfo *CreteListHead(struct TCPClientInfo *head)
{
	if(head==NULL)
	{
        head=(struct TCPClientInfo *)malloc(sizeof(struct TCPClientInfo));
		head->next=NULL;  
	}
	return head;
}

void AddListNode(struct TCPClientInfo *head,struct TCPClientInfo client_fd_data);
void DeleteListNode(struct TCPClientInfo *head,struct in_addr ip);
int GetListNodeCnt(struct TCPClientInfo *head);
int CheckDataPackage(struct SocketPackageData data,unsigned int  rx_size);


int StartAlarmLight_IP()
{
	int tcp_server_port;  //服务器的端口号
	int tcp_server_fd; //服务器套接字描述符
	int *tcp_client_fd=NULL; //客户端套接字描述符(定义为指针是为了后面好创建客户端信息链表)
	int Contrl_thread_state=0;
	int ret=0;
	socklen_t tcp_client_addrlen=0;
	struct sockaddr_in tcp_server;//地址结构体
	struct sockaddr_in tcp_client;
	struct TCPClientInfo *p=NULL;
	 
	tcp_server_port=SERVER_PORT; 

	/*1. 创建网络套接字*/
	tcp_server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(tcp_server_fd<0)
	{
		printf("TCP服务器端套接字创建失败!\n");
		return -1;
	}

	/*2. 绑定端口号,创建服务器*/
	tcp_server.sin_family=AF_INET; //IPV4协议类型
	tcp_server.sin_port=htons(tcp_server_port);//端口号赋值,将本地字节序转为网络字节序
	tcp_server.sin_addr.s_addr=INADDR_ANY; //将本地IP地址赋值给结构体成员

	if(bind(tcp_server_fd,(const struct sockaddr*)&tcp_server,sizeof(struct sockaddr))<0)
	{
		printf("TCP服务器端口绑定失败!\n");
		return -1;
	}

	/*3. 设置监听的客户端数量*/
	listen(tcp_server_fd,100);
	
	/*4. 等待客户端连接(来一个客户端就把他放到链表里)*/
	pthread_t test_thread_id;
	pthread_t thread_id;
	pthread_t Contrl_thread_id;


	ClientInfoListHead=CreteListHead(ClientInfoListHead);
	
	while(1)
	{
		struct TCPClientInfo *tcp_client_data;
        tcp_client_data=(struct TCPClientInfo *)malloc(sizeof(struct TCPClientInfo)); //申请空间
		tcp_client_addrlen=sizeof(struct sockaddr);

		if(Contrl_thread_state==0)
		{

			if( pthread_create(&Contrl_thread_id,NULL,ContrlPthread_func_IP,(void *)ClientInfoListHead)==0 )/*创建控制线程*/
			{
				Contrl_thread_state=1;
				pthread_detach(Contrl_thread_id);/*2. 设置分离属性，让线程结束之后自己释放资源*/
			}
			else
			{
				Contrl_thread_state=0;
				printf("报警灯控制线程创建失败！\n");
			}

			/*if( pthread_create(&test_thread_id,NULL,test_fun_IP,(void *)ClientInfoListHead)==0 )/*创建test线程
			{
				pthread_detach(test_thread_id);
			}
			else
			{
				printf("test线程创建失败！\n");
			}*/
		}

		tcp_client_data->clientfd=accept(tcp_server_fd,(struct sockaddr *)&tcp_client,&tcp_client_addrlen);
		if(tcp_client_data->clientfd<0)
		{
			printf("TCP服务器:等待客户端连接失败！！！\n");
		}
		else
		{
			memcpy((struct in_addr *)&(tcp_client_data->ip),&tcp_client.sin_addr,sizeof(tcp_client.sin_addr));
			printf("\n已经连接的客户端信息: %s:%d\n",inet_ntoa(tcp_client.sin_addr),ntohs(tcp_client.sin_port));//打印连接的客户端地址信息	
	
			if(pthread_create(&thread_id,NULL,SocketPthread_func_IP,(void *)tcp_client_data)==0)/*1. 创建线程*/
			{
				tcp_client_data->ClientThread_id=thread_id;
				tcp_client_data->ip=tcp_client.sin_addr;
				tcp_client_data->connect_state=1;
				p=ClientInfoListHead;
				while(p->next!=NULL)//把连接的客户端信息更新到节点列表
				{
					p=p->next;
					if(p->ip.s_addr == tcp_client_data->ip.s_addr ) 
					{
						//if(p->ClientThread_id != tcp_client_data->ClientThread_id)
						//{
							//ret=pthread_cancel(p->ClientThread_id);
							//printf("Cancel pthread_id=%ld %s!\n",p->ClientThread_id,ret==0?"OK":"Fail");
						//} 
						DeleteListNode(ClientInfoListHead,tcp_client_data->ip);
					}
				}
				AddListNode(ClientInfoListHead,*tcp_client_data);
				//DisplayListDeviceInfo_IP();	
				pthread_detach(thread_id);/*2. 设置分离属性，让线程结束之后自己释放资源*/
			}
		}
	}
	return 0;
}

void *test_fun_IP()
{
	int Chose_ip,Chose_state=0; 
	printf("test_fun_IP线程创建成功！！！\n");
	while(1)
	{
		printf("请选择Point的报警状态 0=关  1=开 ：");
		scanf("%d %d",&Chose_ip,&Chose_state);
		switch(Chose_ip)
		{
			case 1:LEDContrlAPI_IP("192.168.1.118",Chose_state);break;
			case 3:LEDContrlAPI_IP("192.168.1.119",Chose_state);break;
			case 4:LEDContrlAPI_IP("192.168.1.120",Chose_state);break;
			case 7:LEDContrlAPI_IP("192.168.1.122",Chose_state);break;
			case 10:LEDContrlAPI_IP("192.168.1.121",Chose_state);break;
			case 11:LEDContrlAPI_IP("192.168.1.123",Chose_state);break;
			case 12:LEDContrlAPI_IP("192.168.1.110",Chose_state);break;
			default :break;
		}
		
	}
	
}

int LEDContrlAPI_IP(const char *chose_ip,unsigned char AlarmState)
{

	struct TCPClientInfo *p=NULL;
    int Find_State=0;
    //printf("IP=%s int_IP=%d报警灯API控制函数调用成功(ListCount=%d)！！！\n",chose_ip,inet_addr(chose_ip),GetListNodeCnt(ClientInfoListHead));
    p=ClientInfoListHead;
    if(p != NULL)
    {
        if(p->next!=NULL)
        {
            while(p->next!=NULL)
            {
                p=p->next;
                if(p->ip.s_addr == inet_addr(chose_ip) && p->connect_state)
                {
                    p->play_contrl=AlarmState;
                    Find_State=1;
                    printf("Find %s Device！\n",chose_ip);
                }
                if(p->next==NULL && Find_State==0)
                {
                    printf("要触发的%s设备IP不存在！！\n",chose_ip);
                    return -1;
                }
            }
        //    printf("IP=%s设备成功 <%s>报警标志位！\n",chose_ip,AlarmState==0?"关闭":"开启");

        }
        else
        {
            printf("ListHead No Devices Exist！\n");
            return -2;
        }
    }
	return 0;
}


void *ContrlPthread_func_IP(void *dev)
{
    struct TCPClientInfo *p=(struct TCPClientInfo *)dev;
	int i=0;
	printf("报警灯控制线程创建成功！！！\n");
	free(dev);//释放占用的空间
	while(1)
	{
		p=ClientInfoListHead;
		usleep(10*1000);
		while(p->next!=NULL)
		{
			p=p->next;
			if(p->play_contrl) 
			{
				p->commanded_state=1;//表示已经进入过报警控制过
				while(p->play_state && i<10)//在报警
				{
					if(p->play_contrl==0) //突然又要关闭报警灯
					{
						printf("\nSTOP_PALY被调用！！！\n");
						goto  STOP_PALY;
					}
					write(p->clientfd,CheckCmd,4);//发送查询报警灯播放状态命令
					sleep(1);
					i++;
				}
				i=0;
				while(p->play_state==0 && i<CHECK_MAX_NUM)
				{
					write(p->clientfd,PlayCmd,4);//发送报警命令
					sleep(1);
					write(p->clientfd,CheckCmd,4);//发送查询命令
					sleep(1);
					i++;
					if(i==CHECK_MAX_NUM) printf("\nIP=%s Device NO ACK !!! (Check_num=%d)\n",inet_ntoa(p->ip),i);
				} 
				if(i<CHECK_MAX_NUM) printf("\nIP=%s Device Alarm Success!!! (Check_num=%d)\n",inet_ntoa(p->ip),i);
				i=0;
			}
			else//停止报警
			{
				STOP_PALY:
				while(p->play_state && i<CHECK_MAX_NUM)//一直发送停止报警灯播放命令，直到报警器超时或者停止报警
				{
					write(p->clientfd,StopCmd,4);
					sleep(1);
					write(p->clientfd,CheckCmd,4);//发送查询命令
					sleep(1);
					i++;
				}

				if(p->commanded_state)//上一次报警过
				{
					if(i<CHECK_MAX_NUM)
					{
                    //	printf("报警灯控制线程成功给IP= %s 发送停止报警播放命令！ (Check_num=%d)\n",inet_ntoa(p->ip),i);
						p->commanded_state=0;
						p->play_state=0;
					}
					if(i==CHECK_MAX_NUM)
					{
						printf("\nIP=%s Device Stop Alarm No ACK!!! (Check_num=%d)\n",inet_ntoa(p->ip),i);
					}
				}
				i=0;
			}
		}
	}
	printf("报警灯控制线程意外终止！！！\n");
}

/*
函数功能:  TCP客户端处理函数
*/
void *SocketPthread_func_IP(void *dev)
{
	struct SocketPackageData RxData; //保存接收和发送的数据
	struct SocketPackageData TxData; //保存接收和发送的数据
	struct TCPClientInfo *p=ClientInfoListHead;
	struct TCPClientInfo tcp_client_data;//客户端套接字描述符以及指定人的人名
	fd_set readfds; //读事件的文件操作集合
	int select_state; //接收返回值
	int list_cnt=0;
	int Find_state=0;
	int API=0;
	unsigned int  rx_cnt;
	memcpy((void *)&tcp_client_data,(void *)dev,sizeof(struct TCPClientInfo));	//内存数据拷贝
	free(dev); //释放占用的空间

	while(1)
	{
		FD_ZERO(&readfds);/*5.1 清空文件操作集合*/
		FD_SET(tcp_client_data.clientfd,&readfds); /*5.2 添加要监控的文件描述符*/
		select_state=select(tcp_client_data.clientfd+1,&readfds,NULL,NULL,NULL);/*5.3 监控文件描述符*/
		if(select_state>0)//表示有事件产生
		{
			if(FD_ISSET(tcp_client_data.clientfd,&readfds))/*5.4 测试指定的文件描述符是否产生了读事件*/
			{	
				rx_cnt=read(tcp_client_data.clientfd,&RxData,sizeof(struct SocketPackageData));	/*5.5 读取数据*/
            //	printf("数据包大小 rx_cnt=%d  ",rx_cnt);
				if( rx_cnt==1 && RxData.Cmd[0]==0 )
				{
                    //	printf("收到报警器上电数据包！！！ clientfd= %d  数据：%X     客户端IP:%s   connect_state = %d  thread_id=%ld\n",
                        //tcp_client_data.clientfd,RxData.Cmd[0],inet_ntoa(tcp_client_data.ip),tcp_client_data.connect_state,tcp_client_data.ClientThread_id);
						sleep(2);
						write(tcp_client_data.clientfd,PlayCmd,4);//  发送报警命令，测试报警上电初始化是否正常
                    //	printf("IP=%s 上电初始化报警命令已发送！\n ",inet_ntoa(tcp_client_data.ip));
				}						
				else if(rx_cnt==5 ) //判断是否是报警灯的回应数据（主要还是要过滤雷达的数据包）
				{
						if((CheckDataPackage(RxData,rx_cnt)==0)/*校验数据包是否正确*/)
						{
							if(RxData.Cmd[0]==0xAA && RxData.Cmd[1]==0x01 && RxData.Cmd[2]==0x01)//
							{
								p=ClientInfoListHead; //将指针重新执行链表头							
								while(p->next!=NULL)//更报警灯新标志位
								{
									p=p->next;	
									if(p->clientfd==tcp_client_data.clientfd )
									{
                                    //		printf("成功找到 IP=%s 硬件  clientfd=%d   并更新报警灯标志位 ！\n",inet_ntoa(p->ip), p->clientfd);
											if( RxData.Cmd[3]==0x00)//报警器不在播放
											{
												p->play_state=0;
												p->commanded_state=0;
												tcp_client_data.play_state=0;
												tcp_client_data.commanded_state=0;
											}
											else if (RxData.Cmd[3]==0x01)//报警器在播放
											{
												p->play_state=1;
												p->commanded_state=1;
												tcp_client_data.play_state=1;
												tcp_client_data.commanded_state=1;//表示已经进入过报警控制过
											}
											else
											{
												p->play_state=0;
												tcp_client_data.play_state=0;
											}
											break;	
									}
								}					
							}
                        //	printf("clientfd= %d  数据：%X %X %X %X %X 客户端IP:%s PlayState = %d    thread_id=%ld\n",
                        //	tcp_client_data.clientfd,RxData.Cmd[0],RxData.Cmd[1],RxData.Cmd[2],RxData.Cmd[3],RxData.Cmd[4],
                        //	inet_ntoa(tcp_client_data.ip),tcp_client_data.play_state,tcp_client_data.ClientThread_id);
						}
						else
						{
							printf("数据包校验值不正确!\n");
						}
				}
				else if(rx_cnt==0)
				{
					printf("对方已断开连接.....\n");
					break;
				}
				else if(rx_cnt==15 && RxData.Cmd[0]=='w')//www.lslidar.com
				{
					write(tcp_client_data.clientfd,"www.lslidar.com",15);
                //	printf("收到心跳包！clientfd= %d\t数据：%s 客户端IP:%s thread_id=%ld\n",
                //	tcp_client_data.clientfd,RxData.Cmd,inet_ntoa(tcp_client_data.ip),tcp_client_data.ClientThread_id);
				}
				else
				{
					printf("数据包大小接收不正确!\n");
				}
			}
		}
		else if(select_state<0) //表示产生了错误
		{
			printf("select函数产生异常!\n");
			break;
		}
	}
	tcp_client_data.connect_state=0;
	DeleteListNode(ClientInfoListHead,tcp_client_data.ip);	
	printf("\n已经删除clientfd=%d  IP= %s 的连接!!!\n",tcp_client_data.clientfd,inet_ntoa(tcp_client_data.ip));
	close(tcp_client_data.clientfd);/*6. 关闭连接*/
}



/*
函数功能: 在链表结尾添加链表节点
*/
void AddListNode(struct TCPClientInfo *head,struct TCPClientInfo tcp_client_data)
{
	struct TCPClientInfo *p=head;			
	struct TCPClientInfo *NewNode=NULL;
	while(p->next!=NULL)//1. 找到链表结尾的节点
	{
		p=p->next;//移动到下一个节点
	}
    NewNode=(struct TCPClientInfo *)malloc(sizeof(struct TCPClientInfo));//2. 申请新节点
	if(NewNode==NULL)
	{
		printf("链表节点空间申请失败!\n");
	}
	else
	{
		memcpy((void *)NewNode,(void *)&tcp_client_data,sizeof(struct TCPClientInfo));	//内存数据拷贝
		NewNode->next=NULL;
		p->next=NewNode; //3. 添加到链表节点
        //printf("成功添加节点 clientfd= %d\t客户端IP:%s\tthread_id=%ld\n",NewNode->clientfd,inet_ntoa(NewNode->ip),NewNode->ClientThread_id);
	}	
}

/*
函数功能: 根据ip删除指定节点
*/
void DeleteListNode(struct TCPClientInfo *head,struct in_addr ip)
{
	struct TCPClientInfo *p=head;
	struct TCPClientInfo *temp=NULL;

	while(p->next!=NULL)
	{
		temp=p;//保存上节点地址
		p=p->next;//下一个节点
		if(p->ip.s_addr==ip.s_addr)	
		{
			temp->next=p->next;
            //printf("成功删除节点 clientfd= %d\t客户端IP:%s\tthread_id=%ld\n",p->clientfd,inet_ntoa(p->ip),p->ClientThread_id);
			free(p);//释放p指向的节点
		}
	}
}

/*
函数功能: 获取节点的数量
*/
int GetListNodeCnt(struct TCPClientInfo *head)
{
	struct TCPClientInfo *p=head;
	int count=0;
	while(p->next!=NULL)
	{
		p=p->next;
		count++;
	}
	return count;
}

/*
函数功能: 校验数据包是否正确
*/
int CheckDataPackage(struct SocketPackageData data,unsigned int  rx_size)
{
	unsigned int checksum=0;
	int i;
	if(rx_size>8 || rx_size<4)
	{
		printf("报警灯命令回应错误!\n");
		return -1;
	}
	for(i=0;i<rx_size-1;i++)//这样到好处是当buff的大小变化不会影响校验循环次数
	{
		checksum+=data.Cmd[i];
	}
	if(checksum!=data.Cmd[rx_size-1])
	{
		printf("校验和错误!\n");
		return -1;
	}
	return 0;
}

void DisplayListDeviceInfo_IP()
{
	struct TCPClientInfo *p=ClientInfoListHead;
	while(p->next != NULL)
	{
		p=p->next;
    //	printf("Device IP=%s  int_IP=%d clientfd=%d connect_state=%d play_state=%d play_contrl=%d commanded_state=%d ClientThread_id=%ld\n",
        //		inet_ntoa(p->ip),p->ip.s_addr,p->clientfd,p->connect_state,p->play_state,p->play_contrl,p->commanded_state,p->ClientThread_id);
	}
}

