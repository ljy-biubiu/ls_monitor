#include "LED_RS232_API.h"

using namespace std;
#define DBUG_MODE 0
#define CHECK_MAX_NUM 5
#define  Music_Time  10
#define RS232_DECIVE_ADDR "/dev/ttyS0"

int tty_fd=0;
int play_state=0;
int play_contrl=0;
int commanded_state=0;
int connect_state=0;
pthread_t test_thread_id;
pthread_t RS232_SendBytes_thread_id;
pthread_t RS232_ReceiveDataProcessthread_id;
pthread_t LED_Contrl_thread_id;

unsigned char buff[16];   //存放数据或者命令
unsigned char CheckCmd[4]={0xAA,0x01,0x00,0xAB};//查询播放状态
unsigned char PlayCmd[4]={0xAA,0x02,0x00,0xAC};//触发报警命令
unsigned char StopCmd[4]={0xAA,0x03,0x00,0xAD};//停止报警命令

/*
函数功能: 报警灯控制主程序
*/
int StartAlarmLight()
{
	int ret=-1 ;
	int i=0;
	struct termios options;
	tty_fd = open(RS232_DECIVE_ADDR,O_RDWR|O_NOCTTY|O_NDELAY) ; //打开串口设备
	if(tty_fd < 0)
	{
		cout<<"open "<<RS232_DECIVE_ADDR<<" failed !!!"<<endl;
		goto cleanup;
	}
	else
	{
		cout<<"open "<<RS232_DECIVE_ADDR<<" sucessful !"<<endl;
	}	
	if(fcntl(tty_fd,F_SETFL,0) < 0)/*清除串口非阻塞标志*/
	{
		cout<<"fcntl failed!"<<endl;
		close(tty_fd);
		return -1;
	}

	memset(&options, 0, sizeof(options)) ;
	ret = tcgetattr(tty_fd, &options); //获取原有的串口属性的配置
	if(ret != 0)
	{
		cout<<"tcgetattr() failed:"<<RS232_DECIVE_ADDR<<endl;
		goto cleanup ;
	}
	options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	options.c_cflag &= ~(CSIZE | PARENB);
	options.c_cflag |= CS8;
	/* 设置9600波特率  */
	cfsetispeed(&options, B9600);//接收
	cfsetospeed(&options, B9600);//输出
	options.c_cflag &= ~CSTOPB;/* 设置一位停止位; */
	options.c_cc[VTIME] = 0;/* 非规范模式读取时的超时时间；*/
	options.c_cc[VMIN]  =1; /* 非规范模式读取时的最小字符数*/
	tcflush(tty_fd ,TCIFLUSH);/* tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */
	if((tcsetattr(tty_fd, TCSANOW,&options))!=0) /*激活配置*/
	{
		cout<<"tcsetattr( )  failed"<<endl;
		goto cleanup ;
	}
	if( pthread_create(&RS232_ReceiveDataProcessthread_id,NULL,RS232_ReceiveDataProcess,(void *)&tty_fd)==0 )//创建线程
	{
		pthread_detach(RS232_ReceiveDataProcessthread_id);//设置分离属性，让线程结束之后自己释放资源
	}
	else
	{
		cout<<"RS232_ReceiveDataProcess thread create failed !"<<endl;
	}
//	if( pthread_create(&test_thread_id,NULL,test_fun,(void *)&tty_fd)==0 )//创建线程
//	{
//		pthread_detach(test_thread_id);//设置分离属性，让线程结束之后自己释放资源
//	}
	while(1)
	{
		usleep(10*1000);
		if(play_contrl==true) 
		{
			commanded_state=true;//表示已经进入过报警控制过
			while(play_state  &&  i<Music_Time)//在报警
			{
				if(play_contrl==0) //突然又要关闭报警灯
				{
					#if DBUG_MODE
					cout<<"\nSTOP_PALY !"<<endl;
					#endif
					goto  STOP_PALY;
				}
				else
				{
					ret=RS232_SendBytes(tty_fd,CheckCmd,4);//发送查询报警灯播放状态命令
					if(ret>0)
					{
						#if DBUG_MODE
						cout<<"CheckCmd send sucessful"<<"(num="<<i<<")"<<endl;
						#endif
					}
					usleep(1000*1000);
					i++;
				}
			}
			i=0;
			play_state=false;
			while(play_state==false  && i<CHECK_MAX_NUM)//不在报警
			{
				RS232_SendBytes(tty_fd,PlayCmd,4);//发送报警命令
				usleep(500*1000);
				RS232_SendBytes(tty_fd,CheckCmd,4);//发送查询命令
				i++;
				if(i==CHECK_MAX_NUM)
				{
						#if DBUG_MODE
						cout<<"Device NO ACK !!! "<<"(Check_num="<<i<<")"<<endl;
						#endif
				} 
			} 
			if(i<CHECK_MAX_NUM)
			{
					#if DBUG_MODE
					cout<<"Device Alarm Success ! (Check_num="<<i<<")"<<endl;
					#endif
			} 
			i=0;
		}
		else//停止报警
		{
			STOP_PALY:
			i=0;
			while(play_state && i<CHECK_MAX_NUM)//一直发送停止报警灯播放命令，直到报警器超时或者停止报警
			{
				RS232_SendBytes(tty_fd,StopCmd,4);
				usleep(500*1000);
				RS232_SendBytes(tty_fd,CheckCmd,4);//发送查询命令
				i++;
			}
			if(commanded_state)//上一次报警过
			{
				if(i<CHECK_MAX_NUM)
				{
					#if DBUG_MODE
					cout<<"Device Stop Alarm Success ! (Check_num="<<i<<")"<<endl;
					#endif
					commanded_state=0;
					play_state=0;
				}
				if(i==CHECK_MAX_NUM)
				{
					#if DBUG_MODE
					cout<<"Device Stop Alarm No ACK !!! (Check_num="<<i<<")"<<endl;
					#endif
				}
			}
			i=0;
		}
	}
cleanup:
    close(tty_fd);
	return 0;
}

/*
函数功能: 测试报警灯
*/
void *test_fun(void *dev)
{
	int Chose_state=0; 
	#if DBUG_MODE
	cout<<"test_fun thread create success !"<<endl;
	#endif
	while(1)
	{
		printf("请选择报警状态 0=关  1=开 ：");
		scanf("%d",&Chose_state);
		LEDContrlAPI(Chose_state);
	}
	
}


int RS232_SendBytes(int fd, void * sendbuf, size_t count)
{
	int ret=-1;
	ret=write(fd,sendbuf,count);//发送查询报警灯播放状态命令
	if(ret < 0)
	{
		cout<<"write() error:"<<strerror(errno)<<endl;
		close(fd);
		return -1;
	} 
	else return ret;
}
/*
函数功能: 串口数据接收处理
*/
void *RS232_ReceiveDataProcess(void *)
{
	#if DBUG_MODE
	cout<<"RS232_ReceiveDataProcess thread create Success !"<<endl;
	#endif 
	int Receive_rv = -1 ;		 
	fd_set  rset;
	int i;
	while(1)
    {
        FD_ZERO(&rset) ;
        FD_SET(tty_fd, &rset) ;
        Receive_rv = select(tty_fd+1, &rset, NULL, NULL, NULL) ;
        if(Receive_rv < 0)
        {
			cout<<"select( ) failed !!!"<<endl;
            goto cleanup ;
        }
        if(Receive_rv == 0)
        {
			cout<<"select( ) time out !!!"<<endl;
            goto cleanup ;
        }
        memset(buff,0, sizeof(buff)) ;
        Receive_rv = read(tty_fd,buff, sizeof(buff)) ;
        if(Receive_rv < 0)
        {
			cout<<"Read() error:"<<strerror(errno)<<endl;
            goto cleanup ; 
        }
		#if DBUG_MODE
		cout<<"Receive_num="<<Receive_rv;
		#endif 
		if( Receive_rv==1 && buff[0]==0 )
		{
			connect_state=1;
			#if DBUG_MODE
			cout<<"收到报警器上电数据包！ connect_state = "<<connect_state<<endl;
			#endif 
			sleep(2);
			RS232_SendBytes(tty_fd,PlayCmd,4);//  发送报警命令，测试报警上电初始化是否正常
			#if DBUG_MODE
			cout<<"上电初始化报警命令已发送！ "<<endl;
			#endif 
		}						
		else if(Receive_rv==5 ) //判断是否是报警灯的回应数据
		{
			if((CheckDataPackage(buff,Receive_rv)==0)/*校验数据包是否正确*/)
			{
				if(buff[0]==0xAA && buff[1]==0x01 && buff[2]==0x01)//更报警灯新标志位	
				{		
					connect_state=1;				
					if( buff[3]==0x00)//报警器不在播放
					{
						play_state=0;
						commanded_state=0;
					}
					else if (buff[3]==0x01)//报警器在播放
					{
						play_state=1;
						commanded_state=1;//表示已经进入过报警控制过
					}
					else
					{
						play_state=0;
					}		
				} 
				#if DBUG_MODE
				printf(" Data：%X %X %X %X %X  PlayState = %d \n",buff[0],buff[1],buff[2],buff[3],buff[4],play_state);	
				#endif 
			}
			else
			{
				#if DBUG_MODE
				cout<<"数据包校验值不正确!"<<endl;
				#endif 
			}
		}
		else if(Receive_rv <0 || Receive_rv ==0 )
		{
			connect_state=0;
			cout<<RS232_DECIVE_ADDR<<"已断开连接....."<<endl;
			goto cleanup;
		}
		else
		{
			#if DBUG_MODE
			cout<<" Data Package Size Error!!!"<<endl;
			#endif
		}
    }
cleanup:
    close(tty_fd);
}

/*
函数功能: 报警灯控制API
*/
int LEDContrlAPI(int AlarmState)
{
	#if DBUG_MODE
	cout<<"Call LEDContrlAPI  Success ! (AlarmState = "<<AlarmState<<")"<<endl;
	#endif 
	play_contrl=AlarmState;				
	return 0;
}

/*
函数功能: 校验数据包是否正确
*/
int CheckDataPackage(unsigned char *data_buff,unsigned int  rx_size)
{
	unsigned int checksum=0;
	int i;
	if(rx_size>8 || rx_size<4)
	{
		#if DBUG_MODE
		cout<<"报警灯命令回应错误! "<<endl;
		#endif 
		return -1;
	}
	for(i=0;i<rx_size-1;i++)
	{
		checksum+=data_buff[i];
	}
	if(checksum!=data_buff[rx_size-1])
	{
		#if DBUG_MODE
		cout<<"校验和错误! "<<endl;
		#endif 
		return -1;
	}
	return 0;
}

/*
void *RS232_SendBytes(void *)
{
	printf("RS232_SendBytes\n");
	int ret = -1 ;
    while(1) 
    {
        ret = RS232_SendBytes(tty_fd,(const char*)PlayCmd,4); 
        if(ret < 0)
        {
            printf("RS232_SendBytes() error:%s\n",strerror(errno)) ;
            close(tty_fd); 
        } 
		else
		{
			printf("\nPlayCmd send sucessful\n\n");
			ret = RS232_SendBytes(tty_fd,(const char*)CheckCmd,4); 
		}
        sleep(2);
    }
}

*/
