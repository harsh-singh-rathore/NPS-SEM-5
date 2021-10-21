#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 50
struct data_set {
	int number[MAXSIZE];
	int choice;
	int no;
}data, ans;

main()
{
	char buff[MAXSIZE];
	int sockfd,retval,i;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
		return;
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection error");
		return;
	}
	
	char resp[10] = "\0";	
	while(strcmp(resp, "exit") != 0) {
		printf("enter choice: 1 for sort 2 for even odd: ");
		int choice;
		scanf("%i", &choice);
		printf("LOL");
		data.choice = choice;
		printf("Enter Number of Elements: ");
		scanf("%d", &data.no);
		int i;
		for(i = 0; i<data.no; i++) {
			scanf("%d", &data.number[i]);
		}
		sentbytes=send(sockfd,(void *) &data,sizeof(data),0);
		if(sentbytes==-1)
		{
			printf("Error in Sending the array");
			close(sockfd);
		}
		recedbytes=recv(sockfd,(void *) &ans,sizeof(ans),0);
		if(recedbytes < 0) {
			printf("Error in receiving");
		}
		printf("The answer received is");
		for(i=0; i<ans.no; i++) {
			printf("%d ", ans.number[i]);
		}
		printf("\n Do you want to proceed(Enter exit to exit)"); 
		gets(resp);
		
	}
	close(sockfd);
}

