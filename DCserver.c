#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define LISTENPORT 2019
#define AZAMIUZUNLUK 1024

int main()
{
    int sockfd,newfd;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char gonder[30]="server msj1";
    char str[AZAMIUZUNLUK];
    int gelenBayt,gidenBayt,structSize;
    //değişkenler tanımlandı
    
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
    int i=0;
    for(i;i<5;i++)
    {
    gelenBayt=recv(newfd,&str,AZAMIUZUNLUK-1,0);
    if(-1==gelenBayt)
    {perror("recv hata!");}
    else if(0==gelenBayt)
    {printf("bağlantı koptu");}
    else
    {printf("%d bayt aldım mesaj: %s \n",gelenBayt,str);}
    //mesaj alındı soketi send e alıp mesaj yollanıcak
    memset(gonder,'\0',30);//hafızanın temizlenmesi gerekiyor
    printf("mesaj gir:");scanf("%s",gonder);
    gidenBayt=send(newfd,gonder,strlen(gonder),0);
    if(-1==gidenBayt)
    {perror("send hata!");}
    else if(strlen(gonder) != gidenBayt)
    {printf("mesaj eksik gönderildi!");}
    else
    {printf("mesaj gönderildi:%s \n",gonder);}
    }
    close(newfd);
    close(sockfd);
    
}















