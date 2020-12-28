 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <WinSock2.h> 
 
#define PORT 12345 
#define SERVER_IP "10.10.10.133"  // receiving pc's ip
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512 
#pragma comment(lib, "WS2_32") 
 
int main() 
{ 
  sockaddr_in server_addr; 
  server_addr.sin_family = AF_INET; 
  server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); 
  server_addr.sin_port = htons(PORT);
 
  WSADATA wsaData; 
  WORD socketVersion = MAKEWORD(2, 0); 
  if(WSAStartup(socketVersion, &wsaData) != 0) 
  { 
    printf("Init socket dll error!"); 
    exit(1); 
  } 
 
  SOCKET m_Socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (SOCKET_ERROR == m_Socket) 
    { 
      printf("Create Socket Error!"); 
    exit(1); 
    } 
 


  if (SOCKET_ERROR == connect(m_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr))) 
  { 
    printf("Can Not Connect To Server IP!\n"); 
    system("pause"); 
    exit(1); 
  } 
 
 
    printf("sending To receiving pc...\n"); 
 
    sockaddr_in client_addr; 
    int server_addr_len = sizeof(server_addr); 


    char buffer[BUFFER_SIZE]; 
    memset(buffer, 0, BUFFER_SIZE); 
 
    char file_name[FILE_NAME_MAX_SIZE+1]; 
    memset(file_name, 0, FILE_NAME_MAX_SIZE+1); 
    printf("Please Input File Name On Server: "); 
    scanf("%s", &file_name); 
 
    FILE * fp = fopen(file_name, "r"); //Under Windows is "rb", which means to open a read-only binary
    if (NULL == fp) 
    { 
      printf("File: %s Not Found \n", file_name); 
    } 
        else 
    { 
      memset(buffer, 0, BUFFER_SIZE); 
      int length = 0; 
 
      while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) 
      { 
        if (send(m_Socket, buffer, length, 0) < 0) 
        { 
          printf("Send File: %s Failed\n", file_name); 
          break; 
        } 
        memset(buffer, 0, BUFFER_SIZE); 
      } 
 
      fclose(fp); 
      printf("File: %s Transfer Successful!\n", file_name); 
    } 
 
  closesocket(m_Socket); 
  WSACleanup(); 
  return 0; 
}