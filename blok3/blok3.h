//
// Created by Andrey on 4/16/2023.
//

#ifndef STU_AP_BLOK3_H
#define STU_AP_BLOK3_H

void clearFile(char* filename);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
int initializeWinsock();
int getAddressInfo(const char* ipAddress, const char* portNumber, struct addrinfo** result);
int getWordLength(const char* buffer, int position);
void printBuffer(const char* buffer, int position, int color);
SOCKET connectToServer(struct addrinfo* addressInfo);
void saveToFile(char* filename, char* buffer, char* description);
void sendDataToSocket(SOCKET connectSocket, const char* sendBuffer);
void receiveDataFromSocket(SOCKET connectSocket, char* recvBuffer);
SOCKET createSocket();
int getIdSum(int id);
void decode(char* buffer);
int is_prime(int n);
void noisyString(char* send_buffer, char* recv_buffer);

#endif //STU_AP_BLOK3_H
