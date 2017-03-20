#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
int msqid;
FILE *fp;
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
void sig_hand() //signal handler for keyboard interrupt ^C
{
	//when ^C is pressed we remove the queue and exit the code
	printf("Close the server(Y/N) :");
	char c;
	scanf("%c",&c);
	if(c=='Y')
	{
	fclose(fp);
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
	exit(1);
	}
}
int main(void)
{
    struct my_msg buf;
	fp=fopen("result.txt","w");
    key_t key;
	signal(SIGINT,sig_hand);		//attaching signal handler to the interrupt signal
    if ((key = ftok("server.c", 'B')) == -1) {  /* same key as msg_send.c */
        perror("ftok");
        exit(1);
    }

    if ((msqid=msgget(key,0644|IPC_CREAT)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }
	float res;//variable to store the result after calculation
	printf("\n****Press ^C to exit****\n");
    for(;;) { /* Server never quits! */
        if (msgrcv(msqid, &buf, sizeof(struct msg), 0, 0) == -1) 
		{
			if(errno == EINTR)
            continue;
			perror("msgrcv");
            exit(1);
        }
		switch(buf.mtext.op)//switch case logic for a simple calculator
		{
			case '+': res=buf.mtext.num1+buf.mtext.num2;
						break;
			case '-': res=buf.mtext.num1-buf.mtext.num2;
						break;
			case '*': res=buf.mtext.num1*buf.mtext.num2;
						break;
			case '/': res=buf.mtext.num1/(float)buf.mtext.num2;
						break;
		}
		fprintf(fp,"client Id:%d ",buf.mtext.clientId);
		fprintf(fp,"Answer: \"%d %c %d = %g\"\n", buf.mtext.num1,buf.mtext.op,buf.mtext.num2,res);
		printf("client Id:%d ",buf.mtext.clientId);
        printf("Answer: \"%d %c %d = %g\"\n", buf.mtext.num1,buf.mtext.op,buf.mtext.num2,res);
    }

    return 0;
}
