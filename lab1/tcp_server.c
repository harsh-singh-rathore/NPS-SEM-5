#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 50

struct data_set {
	int number[MAXSIZE];
	int choice;
	int no;
	
}data, ans;

void bubble_sort(struct data_set *data)
{
    int c, d, t;
	int n = data->no;
  
    for (c = 0; c < (n - 1); c++) {
        for (d = 0; d < n - c - 1; d++) {
            if (data->number[d] > data->number[d + 1]) {
  
                /* Swapping */
                t = data->number[d];
                data->number[d] = data->number[d + 1];
                data->number[d + 1] = t;
            }
        }
    }
}

main()
{
	int sockfd,newsockfd,retval,i;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[MAXSIZE];
	
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1)
	{
	printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1)
	{
	close(sockfd);
	}
	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
	if(newsockfd==-1)
	{
		close(sockfd);
	}
	
	for (i = 0; ; i+=1)
	{
		
		recedbytes=recv(newsockfd,(void *) &data,sizeof(data),0);
		if(recedbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}
		// perform action
		bubble_sort(&data);
		pid_t pid = getpid();
		printf("pid: %lun", pid);
		printf("BRUH");
		int c;
		for (c = 0; c < data.no ; c++) {
        	printf("%d ", data.number[c]);
    	}
		printf("\n");
		sentbytes=send(newsockfd,(void *) &data,sizeof(data),0);
		if(sentbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}
		
	}
	close(sockfd);
	close(newsockfd);
}


