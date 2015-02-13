#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
using namespace std;

int main(int argc,char** argv){

	int fd;
	struct flock f;
	char buff[60];
	if((fd = open(argv[1],O_RDWR,0641)) ==-1){
		perror("open");
		return -1;
	}
	
	else{

		f.l_type = F_WRLCK;
		f.l_whence = SEEK_END;
		f.l_start = -100;
		f.l_len=100;
	
		if(fcntl(fd,F_SETLK,&f) == -1)

		{
				
				fcntl(fd,F_GETLK,&f);
				printf("File is already locked by process id %d \n",f.l_pid);
				return -1;
		}

		else
		
		{
			sleep(20);
			printf("file locked by process id %d \n",getpid());
			lseek(fd,-50,SEEK_END);
			read(fd,buff,60);
			
		//	printf("data read from file \n");
			
		//	cout<<buff[50];			
			printf("%s \n",buff);
		
		}

		
				
		f.l_type = F_UNLCK;
		f.l_whence = SEEK_END;
		f.l_start = -100;
		f.l_len=100;

		fcntl(fd,F_SETLKW,&f);

		printf("File unlocked \n");

		close(fd);

		

	}








	return 0;
}
