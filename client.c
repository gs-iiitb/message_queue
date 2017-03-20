#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>
int msqid;

struct msg 		//structre to receive data from the client
{				
int num1;		//first number
char op; 		//operator
int num2;		//second number
int clientId;   //client Id
};
struct my_msg
{
	long mtype;
	struct msg mtext;
};
int main()
{
struct my_msg buf;
key_t key;
srand(time(NULL));
int id=rand()%100;
if((key=ftok("server.c",'B'))==-1)	//creating  a unique key for the message queue
{
	perror("ftok");
	exit(1);
}

if((msqid=msgget(key,0644))==-1) 
{
	perror("msgget");
	exit(1);
}

printf("Enter Commands:\n");
while(1)
	{
		scanf("%d %c %d",&buf.mtext.num1,&buf.mtext.op,&buf.mtext.num2);
		buf.mtext.clientId=id;
		if(msgsnd(msqid,&buf,sizeof(struct msg),0)==-1)		//sending the received command to the server
		{
			perror("msgsend");
			exit(1);
		}
    }
return 0;
}

