/////////////////////////////////////////////////////////////////////////////
//
// Demo program for Sentinel LDK licensing services
//
//
// Copyright (C) 2014, SafeNet, Inc. All rights reserved.
//
//
// Sentinel DEMOMA key required with feature 3 and 42 enabled
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "errorprinter.h"
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include<fstream>
#include <streambuf>
#include <sstream>  


using namespace std;

int main(int argc, char* argv[])
{
printf("linux_ling\n");
    struct ifreq ifreq;
    int sock = 0;
    char mac[32] = "";
	char *mac_string="enp3s0";//or change your real macaddress name such as eth0

       unsigned long s1,s2,s3,s4;
     char string[128];
     char szCpuId[1024];
     char p1[128], p2[128];
     unsigned int eax = 0;
            unsigned int ebx,ecx,edx;

     asm volatile
     ( "cpuid"
            : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
            : "0"(0)
     );
     snprintf(szCpuId, 5, "%s", (char *)&ebx);
            snprintf(szCpuId+4, 5, "%s", (char *)&edx);
            snprintf(szCpuId+8, 5, "%s", (char *)&ecx);

     asm volatile
     ( "movl $0x01 , %%eax ; \n\t"
      "xorl %%edx , %%edx ;\n\t"
      "cpuid ;\n\t"
      "movl %%edx ,%0 ;\n\t"
      "movl %%eax ,%1 ; \n\t"
      :"=m"(s1),"=m"(s2)
     );

     sprintf((char *)p1, "-%08X\n%08X-", s1, s2);
     snprintf(szCpuId+12, 20, "%s", (char *)p1);

     asm volatile
     ( "movl $0x03,%%eax ;\n\t"
      "xorl %%ecx,%%ecx ;\n\t"
      "xorl %%edx,%%edx ;\n\t"
      "cpuid ;\n\t"
      "movl %%edx,%0 ;\n\t"
      "movl %%ecx,%1 ;\n\t"
      :"=m"(s3),"=m"(s4)
     );

     sprintf((char *)p2, "%08X-%08X\n", s3, s4);
     snprintf(szCpuId+31, 19, "%s", (char *)p2);



   // struct ifreq ifreq;
   // int sock = 0;
   // char mac[32] = "";
	//char *mac_string="enp3s0";

    if(argc < 2){
       // printf("Usage: ./main eth0");
       // return 1;
    }

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("error sock");
        return 2;
    }

    //strcpy(ifreq.ifr_name,argv[1]);
	strcpy(ifreq.ifr_name,mac_string);
    if(ioctl(sock,SIOCGIFHWADDR,&ifreq) < 0)
    {
        perror("error ioctl");
        return 3;
    }

    int i = 0;
    for(i = 0; i < 6; i++){
        sprintf(mac+3*i, "%02X:", (unsigned char)ifreq.ifr_hwaddr.sa_data[i]);
    }
    mac[strlen(mac) - 1] = 0;
	for(int i=0;i<strlen(mac);i++){
			//printf( "%c\n",'a');
			//mac[i]
			printf( "%c\n",mac[i]+3);
	}
  //  fp=fopen("xxx.txt","w");
//	for(int i=0;i<strlen(mac);i++){
//		fprintf(fp,"%c",mac[i]+3);
		//fprintf(fp,"szCpuId[%d]=0x%x\n",i,szCpuId[i]);
//	}
//	fclose(fp);
   // printf("MAC: %s\n", mac);
	
		FILE *fp;
	//mac[strlen(mac) - 1] = 0;
    fp=fopen("registor_m.dat","w");
   		char b[]={'H','e','l','l','o','\0'};
   		int m=sizeof(b);
		int c[]={9,4,5,6,3,1,8,7,8,2};

		for(int i=0;i<strlen(mac);i++){
		  fprintf(fp,"%d",mac[i]+c[i%10]*10000+c[9-i%10]*100000);
   		}
	fclose(fp);
	fp=fopen("registor_c.dat","w");
		for(int i=0;i<sizeof(szCpuId);i++){
		if(szCpuId[i]==NULL)break;
		//szCpuId[i]=(szCpuId[i]+(8^b[i%m]));
		fprintf(fp,"%d",szCpuId[i]+c[i%10]*10000+c[9-i%10]*100000);
		//fprintf(fp,"szCpuId[%d]=0x%x\n",i,szCpuId[i]);
		}

	fclose(fp);
		for(int i=0;i<sizeof(szCpuId);i++){
		if(szCpuId[i]==NULL)break;
		//szCpuId[i]=(szCpuId[i]-(8^b[i%m]));
		}
     //printf((char*)szCpuId);
    }
