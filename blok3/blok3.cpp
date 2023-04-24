//
// Created by Andrey on 4/16/2023.
//

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <errno.h>

#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_BUFLEN 4096
#define SPEED 1 // you can change it (speed of print)
#define WIDTH 60 // you can change it (center of screen)
#define MARGIN 5 // you can change it

#pragma comment(lib, "Ws2_32.lib")

/*
    Pripojiť sa na server s IP adresou 147.175.115.34 na port 777 pomocou protokolu TCP.
    Poslať úvodnú správu (zobraziť ju v konzole).
    Prijať odpoveď (zobraziť ju v konzole).
    Postupovať podľa ďalších príkazov prijatých v komunikácii so serverom. Komunikácia funguje tak, že vždy po tom, čo Vám server niečo pošle očakáva nejakú odpoveď od Vás.
    (bodové hodnotenie je komplexné a bude zhrnuté dolu, hodnotí sa celý projekt, štruktúra a funkčnosť kódu, vizuálna stránka, ako aj splnenie úloh)
 */


void clearFile(char* filename){
    FILE* file;
    errno_t err;
    err = fopen_s(&file, "message.txt", "w");
    if (err != 0) {
        char error_msg[100];
        strerror_s(error_msg, 100, err);
        printf("Failed to open file: %s (%s)\n", filename, error_msg);
        return;
    }
    fclose(file);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

int initializeWinsock() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    }
    return iResult;
}

int getAddressInfo(const char* ipAddress, const char* portNumber, struct addrinfo** result) {
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    return getaddrinfo(ipAddress, portNumber, &hints, result);
}

int getWordLength(const char* buffer, int position) {
    int length = 0;
    while (buffer[position] != ' ' && buffer[position] != '\n') {
        length++;
        position++;
    }
    return length;
}

void printBuffer(const char* buffer, int position, int color) {
    int length = strlen(buffer);

    const int start = position == 1 ? WIDTH + MARGIN : MARGIN;
    const int end = position == 1 ? WIDTH * 2 - MARGIN : WIDTH - MARGIN;

    HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
    COORD curr_point = GetConsoleCursorPosition(console);

    curr_point.X = start;

    SetConsoleCursorPosition(console, curr_point);
    int current = start;
    int i = 0;

    while (i < length - 1)
    {
        int word_length = getWordLength(buffer, i);
        if (word_length + current <= end) {
            for (int j = i; j < i + word_length; j++)
            {
                Sleep(SPEED);
                printf("%c", buffer[j]);
                current++;
            }
            printf(" ");
            current++;
            i += word_length + 1;
        }
        else {
            printf("\n");
            current = start;
            curr_point = GetConsoleCursorPosition(console);
            curr_point.X = start;
            SetConsoleCursorPosition(console, curr_point);
            curr_point = GetConsoleCursorPosition(console);
        }
    }
    printf("\n");
}

SOCKET connectToServer(struct addrinfo* addressInfo) {
    SOCKET connectSocket = INVALID_SOCKET;
    struct addrinfo* ptr = addressInfo;
    connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        return INVALID_SOCKET;
    }
    int iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("Not connected to server...\n");
        closesocket(connectSocket);
        return INVALID_SOCKET;
    }
    printf("Connected!\n");
    return connectSocket;
}

void saveToFile(char* filename, char* buffer, char* description) {
    FILE* file;
    errno_t err;

    err = fopen_s(&file, filename, "a");
    if (err != 0) {
        char error_msg[100];
        strerror_s(error_msg, 100, err);
        printf("Failed to open file: %s (%s)\n", filename, error_msg);
        return;
    }

    fprintf(file, "%s\n%s\n", description, buffer);

    fclose(file);
}

void sendDataToSocket(SOCKET connectSocket, const char* sendBuffer) {
    int iResult = send(connectSocket, sendBuffer, (int)strlen(sendBuffer), 0);

    if (iResult == SOCKET_ERROR) {
        printf("Send was failed: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        return SOCKET_ERROR;
    }
    else {
        printBuffer(sendBuffer,0,9);
        saveToFile("message.txt", sendBuffer, "(ME) ");
    }
}

void receiveDataFromSocket(SOCKET connectSocket, char* recvBuffer) {

    int iResult = recv(connectSocket, recvBuffer, DEFAULT_BUFLEN, 0);

    if (iResult > 0) {
        printBuffer(recvBuffer,1,2);
        saveToFile("message.txt", recvBuffer, "(SERVER) ");
    }
    else if (iResult == 0) {
        printf("Connection closed\n");
    }
    else {
        printf("recv failed with error : % d\n", WSAGetLastError());
    }
}

SOCKET createSocket() {
    if (initializeWinsock() != 0) {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    struct addrinfo* result = NULL;
    if (getAddressInfo("147.175.115.34", "777", &result) != 0) {
        printf("Failed to get address info\n");
        WSACleanup();
        return 1;
    }

    SOCKET connectSocket = connectToServer(result);
    freeaddrinfo(result);
    if (connectSocket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    return connectSocket;
}

int getIdSum(int id) {
    int sum = 0;
    while (id != 0) {
        int temp = id % 10;
        sum += temp;
        id -= temp;
        id /= 10;
    }
    return sum;
}

void decode(char* buffer) {
    int key = 55;
    for (int i = 0; i < 150; i++) {
        buffer[i] ^= key;
    }
    buffer[150] = '\n';
}

int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void noisyString(char* send_buffer, char* recv_buffer) {

    memset(send_buffer, 0, sizeof(send_buffer));

    int count = 0;
    for (int i = 2; recv_buffer[i] != '\n'; i++) {
        if (is_prime(i)) {
            char ch = recv_buffer[i - 1];
            send_buffer[count++] = ch;
        }
    }
    send_buffer[count] = '\n';
}

int main() {

    system("cls");

    clearFile("message.txt");

    SOCKET connection = createSocket();

    char sendBuffer[DEFAULT_BUFLEN] = { '\n' };
    char recvBuffer[DEFAULT_BUFLEN] = { '\n' };

    printf("\n");

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "Start\n");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "YOUR STUDENT ID FROM AIS\n");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "Ok\n");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "8484848\n");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "753422\n");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%d\n", getIdSum(123434));
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%d\n", 333222333);
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%d\n", 123);
    sendDataToSocket(connection, sendBuffer);

    recv(connection, recvBuffer, DEFAULT_BUFLEN, 0);
    decode(recvBuffer);
    printBuffer(recvBuffer, 1, 2);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "Whats next?");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "40.68968805683622");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "-74");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "S.O.L.");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "PRIMENUMBER");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    noisyString(sendBuffer, recvBuffer);
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "Trinity");
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "DQPSK"); // might be another question
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    sprintf_s(sendBuffer, DEFAULT_BUFLEN, "%s\n", "16"); // might be another question
    sendDataToSocket(connection, sendBuffer);
    receiveDataFromSocket(connection, recvBuffer);

    closesocket(connection);
    WSACleanup();
    return 0;
}

