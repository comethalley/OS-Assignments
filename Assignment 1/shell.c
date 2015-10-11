#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<pwd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include <string.h>
#include<fcntl.h>
#include<errno.h>
#define MAX_L 4097
char *cwd;
char *concwd;
int flag=0;
void replace(char * o_string, char * s_string, char * r_string)
{
	char buffer[MAX_L];
	char * ch;
	if(!(ch = strstr(o_string, s_string)))
		return;
	strncpy(buffer, o_string, ch-o_string);
	buffer[ch-o_string] = 0;
	sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
	o_string[0] = 0;
	strcpy(o_string, buffer);
	flag=1;
	printf("%s]",o_string);
}
void fprompt()
{
	struct passwd *passwd;
	char hostname[64];
	passwd=getpwuid(getuid());
	//printf("The Login name is %s \n",passwd->pw_name);
	gethostname(hostname,63);
	printf("[%s@%s:",passwd->pw_name,hostname);
	fflush(stdout);
	//printf("The hostname is %s\n",hostname);
	size_t allocsize=sizeof(char) * 1024;
	char * buf;
	char *conbuf;
	conbuf=(char *)malloc(allocsize);
	concwd=getcwd(buf,allocsize);
	buf = (char *)malloc(allocsize);
	//	printf("concwd in fprompt:%s",concwd);
	if((cwd = getcwd(buf,allocsize)) != NULL)
	{

		replace(cwd,cwd,"~");
	}
	else
		perror("getcwd() error : ");

}
void prompt()
{
	struct passwd *passwd;
	char hostname[64];
	passwd=getpwuid(getuid());
	//printf("The Login name is %s \n",passwd->pw_name);
	gethostname(hostname,63);
	printf("[%s@%s:",passwd->pw_name,hostname);
	fflush(stdout);
	//printf("The hostname is %s\n",hostname);
	size_t allocsize=sizeof(char) * 1024;
	char * buf;
	char * ncwd;
	buf = (char *)malloc(allocsize);
	//printf("lala");
	//	printf("The concwd is %s\n",concwd);
	if((ncwd = getcwd(buf,allocsize)) != NULL)
		replace(ncwd,concwd,"~");
	else
		perror("getcwd() error : ");
}

void changeDirectory(char *path)
{
	char *directory = path;
	int ret;
	ret = chdir (directory);
	if(ret==0)
		{
//		printf("cd was successful");
		}
	else
		printf("error:cd was NOT successful");
}

int main()
{
	pid_t pid;
	int pids[100],pidcount=0;
	char *pidsname[100];
	char *atri[10];
	int i=0,j=0;
	fprompt();
	while(1)
	{
		char command[100][100];
		int i=0,j=0,flag=0;
	while(1){
		
		scanf("%c",&command[i][j]);
		if(command[i][j]==' ')
		{
			command[i][j]='\0';
			i++;
			j=0;
		}
		else if(command[i][j] == '\n')
		{
			command[i][j] = '\0';
			i++;
			//printf("The value of i is: %d",i);
			j=0;
			break;
		}
		else
			j++;
	}
	int k=0;
	j=0;
	while(k<i)
	{
		if(strlen(command[k])>0)
		{
			
				atri[j]=strdup(command[k]);	
				j++;

			
		}
		k++;
	}
	
	while(j<10)
	{
		atri[j]=NULL;
		j++;
	}
	if(atri[0]!=NULL)
	{
		int csd, pswd;
		csd=strcmp(atri[0],"cd");
		pswd=strcmp(atri[0],"pwd");
		if(csd==0)
		{
			changeDirectory(atri[1]);
		//	printf("CD:%s %s",atri[0],atri[1]);
		//	prompt();
			char *atri[10];
		}
		else if(pswd==0)
		{
			size_t allocsize=sizeof(char) * 1024;
			char * buf;
			char * cwd;
			buf = (char *)malloc(allocsize);

			if((cwd = getcwd(buf,allocsize)) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd() error : ");
		//	prompt();

		}
		else if(strcmp(atri[0],"psinfo") == 0)
			{
				if(atri[1] != NULL)
				{
					char comm[1024] = "/proc/";
					char comme[1024] = "/proc/";
					char commstat[1024] = "/status";
					char commexec[1024] = "/cmdline";
					char mem[100],temp2[100],temp3[100];
					strcat(comm,atri[1]);
					strcat(comme,atri[1]);
					strcat(comm,commstat);
					strcat(comme,commexec);
					size_t buflen = 1024;
					char buff[buflen];
					char status[100];
					FILE * fp;
					fp = fopen(comme,"r");
					fgets(buff,1024,fp);
					fclose(fp); 
					fp = fopen (comm, "r");
					char temp5[100];
					int temp = 0; 
					while(temp != 1)
					{
						fgets(status,100,fp);
						temp++;
					}
					fscanf(fp,"%s %s",mem,temp2);
					while(1)
					{
						fgets(mem,100,fp);
						if(strstr(mem,"VmPeak") !=NULL)
						{
							break;
						}
					}
					fscanf(fp,"%s %s",status,temp3);
					printf("Pid : %s\nStatus : %s\nMemory : %s\nExecutable Path : %s\n",atri[1],temp2,temp3,buff);
					fclose(fp);
					//printf("%s",shell);
				}
				else
				{
					FILE * fp;
					char buff[1024] = "~/./a.out";
					char status[100];
					char mem[100];
					int pid_curr = getpid();
					fp = fopen ("/proc/self/status", "r");
					char temp2[100],temp3[100],temp4[100],temp5[100];
					int temp = 0;
					while(temp != 1)
					{
						fgets(status,100,fp);
						temp++;
					}
					fscanf(fp,"%s %s",status,temp2);
					while(1)
					{
						fgets(mem,100,fp);
						if(strstr(mem,"VmPeak") != NULL)
						{
							break;
						}
					}
					fscanf(fp, "%s %s",mem,temp3);
					printf("Pid : %d\nStatus : %s\nMemory : %s\nExecutable Path : %s\n",pid_curr,temp2,temp3,buff);
					fclose(fp);
					//printf("%s",shell);
				}
			}
		else
		{
			//if(strcmp(atri[0],"ls")==0)	
			//	atri[1]=NULL;	
		//	printf("LS:%s %s",atri[0],atri[1]);

				pid=fork();
				if(pid<0)
				{
					perror("Child Proc. not created\n");
					_exit(-1);
				}
				else if(pid==0)
				{
					int ret=0;
					ret=execvp(atri[0],atri);
					if(ret<0)
					{
						perror("couldn't execute command\n");
						_exit(-1);
					}
					_exit(0);
				}
				j=0;
				
		}
		if(pidcount != 0)
			{
				int l;
				for(l=0;l<pidcount;l++)
				{
					int status;
					waitpid(pids[l], &status, 0);
					if(WIFEXITED(status))
					{
						const int es = WEXITSTATUS(status);
						if(es == 0)
						{
							printf("[%d]  %d  %s  Done\n",l,pids[l],pidsname[l]);
						}
						else
						{
							printf("[%d]  %d  %s  Error\n",l,pids[l],pidsname[l]);
						}
					}
				}
				pidcount=0;
			}
		if(flag == 1)
		{
			pids[pidcount] = pid;
			pidsname[pidcount] = atri[0];
			pidcount++;
			prompt();
			char command[100][100];
			//atri[1]=NULL;
		}
		else if(flag!=1)
		{
			wait();
			prompt();
			char command[100][100];
			//atri[1]=NULL;
		}
		
				
	}
}
return 0;
}
