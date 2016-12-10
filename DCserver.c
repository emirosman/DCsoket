#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define LISTENPORT 2015
#define AZAMIUZUNLUK 1024

    int sockfd,newfd;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char gonder[30];
    char str[AZAMIUZUNLUK];
    int gelenBayt,gidenBayt,structSize;
    //fonksiyonlara parametre göndermemek için değişkenler global tanımlandı

void *oku()
{
while(1)
{
    memset(str,0,AZAMIUZUNLUK*sizeof str[0]);
    gelenBayt=recv(newfd,&str,AZAMIUZUNLUK-1,0);
    if(-1==gelenBayt)
    {perror("msj okunamadı:recv!");}
    else if(0==gelenBayt)
    {perror("bağlantı koptu");break;}
    else
    {
        /*if(str[0]=="8")//8 çıkış tuşu konmalı
        {break;}
        else*/
        //{printf("%d Bayt aldım: %s",gelenBayt,str);} //bu şekilde gelen mesajı mesaj yolladıktan sonra gösteriyo neden ??
        {printf("msj alındı: %s \n",str);}
    }
}
}
void *yaz()
{
while(1)
{
    printf("\nmsj:");scanf("%s",gonder);
    gidenBayt=send(newfd,gonder,strlen(gonder),0);
    if(gidenBayt==-1)
    {perror("msj yollanamadı:send!\n");}
    else if(strlen(gonder) != gidenBayt)
    {printf("gönderilen giden eşit değil:send! \n");}
 }  
}


int main()
{
    pthread_t thread[2];
    int tired1,tired2;
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sockfd)
    {perror("soket oluşturmada hata!");}
    
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(LISTENPORT);
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    memset(&(serverAddr.sin_zero),'\0',8);
    //server için parametreler tanımlandı
    
    if(-1==bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(struct sockaddr)));
    {perror("bind hata!");}
    //soket oluşturuldu bind edildi dinlemeye alınıcak
    
    if(-1==listen(sockfd,20))//izin verilecek maksimum bağlantı sayısı 20
    {perror("listen hata!");}
    //soketi listen a alındı bağlantı kabul edilicek
    structSize=sizeof(clientAddr);
    
    newfd=accept(sockfd,(struct sockaddr *)&clientAddr,&structSize);
    if(-1==newfd)
    {perror("accept hata");}
    //bağlantı kuruldu mesaj okunucak
    
    tired1=pthread_create(thread+0,NULL,yaz,NULL);
    tired2=pthread_create(thread+1,NULL,oku,NULL);

    pthread_exit(NULL);
    close(newfd);
    close(sockfd);
    
}















