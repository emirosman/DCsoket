#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define SUNUCUPORT 2015
#define SUNUCUIP "127.0.0.1"
#define AZAMIUZUNLUK 1024

    int sockfd; //soket oluşturulcak değişken
    struct sockaddr_in serverAddr;// ?? sockaddr_in adında struct var ondan serveraddr diye nesne mi oluşturdum ??
    char gonder[30];//AZAMIUZUNLUK ile değişsin
    char str[AZAMIUZUNLUK];//array for save coming msg
    int gelenBayt,gidenBayt,structSize;
    //değişkenler global olarak tanımlandı ki fonksiyon parametreleriyle uğraştırmasın

void *yaz()
{
while(1)
{
    printf("\nmsj:"); scanf("%s",gonder);
    gidenBayt=send(sockfd,gonder,strlen(gonder),0);
    if(-1==gidenBayt)
    {perror("send hata");}
    else if (strlen(gonder) != gidenBayt)
    {printf("gönderilen giden eşit değil");}
    
 }
}


void *oku()
{   
while(1)
{
    memset(str,0,AZAMIUZUNLUK*sizeof str[0]);
    gelenBayt=recv(sockfd,&str,AZAMIUZUNLUK-1,0);
    if(-1==gelenBayt)
    {perror("recv hata");}
    else if (0==gelenBayt)
    {printf("bağlantı koptu");break;}
    else
    {
        /*if(str[0]=="8")//çıkış tuşu konmalı ?
        {break;}
        else*/
        {printf("msj alındı: %s \n",str);}
    }
}
}


int main()
{
    pthread_t thread[2];
    int tired1,tired2;
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);//soket oluşturuldu sockfd de tutuldu
    if(-1==sockfd)//hata olursa sockfd ye -1 döner
    {perror("soket oluşturmada hata!");}
    
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(SUNUCUPORT);
    serverAddr.sin_addr.s_addr=inet_addr(SUNUCUIP);
    memset(&(serverAddr.sin_zero),'\0',8);
    //sunucuyla alakalı tanımlamalar yapıldı
    
    if(-1==connect(sockfd,(struct sockaddr *)&serverAddr,sizeof (struct sockaddr)))
    {perror("'connect' bağlantı kurmada hata!");}
    //sunucuyla bağlantı kuruldu
    
    tired1=pthread_create(thread+0,NULL,yaz,NULL);
    tired2=pthread_create(thread+1,NULL,oku,NULL);
    
    pthread_exit(NULL);
    close(sockfd);
}





















