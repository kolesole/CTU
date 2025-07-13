// UDP_Communication_Framework.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "ws2_32.lib")
#include "stdafx.h"
#include <winsock2.h>
#include "ws2tcpip.h"
#include <stdio.h>
#include <stdlib.h>

#define TARGET_IP	"127.0.0.1"

#define BUFFERS_LEN 1024

//#define SENDER
#define RECEIVER

#ifdef SENDER
#define TARGET_PORT 5555
#define LOCAL_PORT 8888
#endif // SENDER

#ifdef RECEIVER
#define TARGET_PORT 8888
#define LOCAL_PORT 5555
#endif // RECEIVER


void InitWinsock();

//**********************************************************************
int main()
{
	SOCKET socketS;

	InitWinsock();

	struct sockaddr_in local;
	struct sockaddr_in from;

	int fromlen = sizeof(from);
	local.sin_family = AF_INET;
	local.sin_port = htons(LOCAL_PORT);
	local.sin_addr.s_addr = INADDR_ANY;


	socketS = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(socketS, (sockaddr*)&local, sizeof(local)) != 0) {
		printf("Binding error!\n");
		getchar(); //wait for press Enter
		return 1;
	}
	//**********************************************************************
	char buffer_rx[BUFFERS_LEN];
	char buffer_tx[BUFFERS_LEN];

#ifdef SENDER

	FILE* f = fopen("test.jpg", "rb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: cannot open image file for send!\n");
		return 1;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);

	char* data = (char*)malloc(size * sizeof(char));
	if (data == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		fclose(f);
		closesocket(socketS);
		return 1;
	}

	if (fread(data, 1, size, f) != size) {
		fprintf(stderr, "ERROR: cannot read image for send!\n");
		free(data);
		fclose(f);
		return 1;
	}
	fclose(f);

	sockaddr_in addrDest;
	addrDest.sin_family = AF_INET;
	addrDest.sin_port = htons(TARGET_PORT);
	InetPton(AF_INET, _T(TARGET_IP), &addrDest.sin_addr.s_addr);

	long sent_size = 0;
	while (sent_size < size) {
		int bytes_to_send = (size - sent_size) > 1024 ? 1024 : (size - sent_size);
		memcpy(buffer_tx, data + sent_size, bytes_to_send);

		if (sendto(socketS, buffer_tx, bytes_to_send, 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot send image!\n");
			closesocket(socketS);
			free(data);
			return 1;
		}
		printf("Sending...\n");

		sent_size += bytes_to_send;
	}

	printf("The image has been sent!\n");
	free(data);
	closesocket(socketS);

#endif // SENDER

#ifdef RECEIVER

	printf("Waiting for package ...\n");

	int size = recvfrom(socketS, buffer_rx, sizeof(buffer_rx), 0, (sockaddr*)&from, &fromlen);
	if (size == SOCKET_ERROR) {
		printf("Socket error!\n");
		closesocket(socketS);
		return 1;
	}

	FILE* f = fopen("test_image.jpeg", "wb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: cannot open file!\n");
		closesocket(socketS);
		return 1;
	}

	if (fwrite(buffer_rx, 1, size, f) != size) {
		fprintf(stderr, "ERROR: cannot save image!\n");
		fclose(f);
		closesocket(socketS);
		return 1;
	}

	while ((size = recvfrom(socketS, buffer_rx, sizeof(buffer_rx), 0, (sockaddr*)&from, &fromlen)) > 0) {
		if (fwrite(buffer_rx, 1, size, f) != size) {
			fprintf(stderr, "ERROR: cannot save image!\n");
			fclose(f);
			closesocket(socketS);
			return 1;
		}
		if (size < 1024) break;
		printf("Processing image...\n");
	}

	printf("The image has been saved\n");

	fclose(f);
	closesocket(socketS);
#endif
	//**********************************************************************

	getchar(); //wait for press Enter
	return 0;
}
void InitWinsock()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}
