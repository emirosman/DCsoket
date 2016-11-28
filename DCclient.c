#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define SUNUCUPORT 2016
#define SUNUCUIP "127.0.0.1"
#define AZAMIUZUNLUK 1024

int main()
{
    int sockfd; //soket oluşturulcak değişken
    struct sockaddr_in serverAddr;// ?? sockaddr_in adında struct var ondan serveraddr diye nesne mi oluşturdum ??
    char *gonder="mesaj1";//göndericeğimiz mesaj değişkeni
    char str[AZAMIUZUNLUK];//array for save coming msg
    int gelenBayt,gidenBayt,structSize;
    //değişkenler bitti
    
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
    
    gidenBayt=send(sockfd,gonder,strlen(gonder),0);
    if(-1==gidenBayt)
    {perror("mesaj göndermede hata!");}
    else if(strlen(gonder) != gidenBayt)
    {printf("mesaj eksik gitti!");}
    else 
    {printf("mesaj gönderildi");}
    
    gelenBayt=recv(sockfd,&str,AZAMIUZUNLUK-1,0);
    if(-1==gelenBayt)
    {perror("mesaj almada hata!");}
    else if(0==gelenBayt)
    {printf("bağlantı koptu");}
    else 
    {printf("mesaj alındı: %s",str);}
    
    close(sockfd);
}




















