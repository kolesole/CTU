#pragma comment(lib, "ws2_32.lib")
#include "stdafx.h"
#include <winsock2.h>
#include "ws2tcpip.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <wincrypt.h>

#define TARGET_IP	"127.0.0.1"

#define BUFFERS_LEN 1024

#define MD5LEN  16

#define SENDER
//#define RECEIVER

#ifdef SENDER
#define TARGET_PORT 14000
#define LOCAL_PORT 15001
#endif // SENDER

#ifdef RECEIVER
#define TARGET_PORT 14001
#define LOCAL_PORT 15000
#endif // RECEIVER

typedef struct {
	int num;
	int size;
	char message[BUFFERS_LEN];
	unsigned int crc32;
	bool last;
} package_with_crc;

typedef struct {
	int num;
	int size;
	char message[BUFFERS_LEN];
	bool last;
} package;

typedef struct {
	BYTE hashBuffer[MD5LEN];
	unsigned int crc32;
} hash_package_with_crc;

typedef struct {
    BYTE hashBuffer[MD5LEN];
} hash_package;

void InitWinsock();
unsigned int crc32b(const char* message, int size);
void append_crc32(char* message, int size);
DWORD calculateMD5Hash(const wchar_t* filename, unsigned char* hashBuffer);

//**********************************************************************
int main()
{
	//LARGE_INTEGER frequency;
	//LARGE_INTEGER start;
	//LARGE_INTEGER end;
	//double executionTime;

	//QueryPerformanceFrequency(&frequency);
	//double frequencyInSeconds = (double)frequency.QuadPart;

	//QueryPerformanceCounter(&start);
	
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
	
#ifdef SENDER
	//open image file for send
	FILE* f = fopen("test.jpg", "rb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: cannot open image file for send!\n");
		closesocket(socketS);
		return 1;
	}
	//finding the size of an image
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);
	//memory allocation for image
	char* data = (char*)malloc(size * sizeof(char));
	if (data == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		fclose(f);
		closesocket(socketS);
		return 1;
	}
	//reading an image into allocated memory
	if (fread(data, 1, size, f) != size) {
		fprintf(stderr, "ERROR: cannot read image for send!\n");
		free(data);
		fclose(f);
		return 1;
	}
    //closing the image file
	fclose(f);
	//setting up a socket to send an image
	sockaddr_in addrDest;
	addrDest.sin_family = AF_INET;
	addrDest.sin_port = htons(TARGET_PORT);
	InetPton(AF_INET, _T(TARGET_IP), &addrDest.sin_addr.s_addr);
	//setting up a timeout
	int timeout = 300;
	setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	//start of sending image
	long sent_size = 0;
	while (sent_size < size) {
		int bytes_to_send = (size - sent_size) > 1024 ? 1024 : (size - sent_size);
		package_with_crc* pwc = (package_with_crc*)malloc(sizeof(package_with_crc));
		if (pwc == NULL) {
			fprintf(stderr, "ERROR: cannot allocate memory!\n");
			free(data);
			closesocket(socketS);
			return 1;
		}

		package* p = (package*)malloc(sizeof(package));
		if (p == NULL) {
			fprintf(stderr, "ERROR: cannot allocate memory!\n");
			free(data);
			free(pwc);
			closesocket(socketS);
			return 1;
		}
		pwc->last = sent_size + bytes_to_send == size ? true : false;
		p->last = pwc->last;
		//copying part(bytes_to_send) of the image into prepared memory
		memcpy(p->message, data + sent_size, bytes_to_send);
		memcpy(pwc->message, data + sent_size, bytes_to_send);
		//creating and adding CRC32 to a prepared package
		p->num = sent_size + 1;
		pwc->num = sent_size + 1;
		p->size = bytes_to_send;
		pwc->size = bytes_to_send;
		pwc->crc32 = crc32b((char*)p, sizeof(package));
		if (sendto(socketS, (char*)pwc, sizeof(package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot send image!\n");
			free(data);
			free(pwc);
			free(p);
			closesocket(socketS);
			return 1;
		}
		printf("Sending...\n");
		if (pwc->last) printf("Its last package...\n");
		char receive_message[10];
		
		if (recvfrom(socketS, receive_message, sizeof(receive_message), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
			int error = WSAGetLastError();
			if (error == WSAETIMEDOUT) {
				printf("The Package was lost, resending...\n ");
			}
			else {
				fprintf(stderr, "ERROR: socket error!\n");
				free(data);
				free(pwc);
				free(p);
				closesocket(socketS);
				return 1;
			}
			continue;
		}
		//checking what byte the receiver expects
		if (atoi(receive_message) == sent_size + bytes_to_send + 1) {
			sent_size += bytes_to_send;
			if (pwc->last) {
				free(pwc);
				free(p);
				break;
			}
		}
		else {
			printf("There was an error with the sent package, resending...\n");
		}
		free(pwc);
		free(p);
	}
	printf("The image has been sent!\n");
	free(data);
	hash_package* hp = (hash_package*)malloc(sizeof(hash_package));
	if (hp == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		closesocket(socketS);
		return 1;
	}

	hash_package_with_crc* hpwc = (hash_package_with_crc*)malloc(sizeof(hash_package_with_crc));
	if (hpwc == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(hp);
		closesocket(socketS);
		return 1;
	}

	const wchar_t* filename = L"test.jpg";
	DWORD status = calculateMD5Hash(filename, hpwc->hashBuffer);
	memcpy(hp->hashBuffer, hpwc->hashBuffer, sizeof(hpwc->hashBuffer));

	//adding crc32
	hpwc->crc32 = crc32b((char*)hp, sizeof(hash_package));
	
	Sleep(7000);
	printf("Sending hash string...\n");
	if (sendto(socketS, (char*)hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
		fprintf(stderr, "ERROR: cannot send hashString!\n");
		free(hp);
		free(hpwc);
		closesocket(socketS);
		return 1;
	}
	char message_from_receiver[15];
	char message_from_receiver1[] = "All is ok!";
	while (1) {
        recvfrom(socketS, message_from_receiver, sizeof(message_from_receiver), 0, (sockaddr*)&from, &fromlen);
		if (strstr(message_from_receiver, "All is ok!") != NULL) break;
		if (sendto(socketS, (char*)hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot send hashString!\n");
			closesocket(socketS);
			return 1;
		}
	}       
	printf("All is ok!\n");
	free(hp);
	free(hpwc);
	closesocket(socketS);

#endif // SENDER

#ifdef RECEIVER
	printf("Waiting for package ...\n");
	//open a file for record an image
	FILE* f = fopen("test_image.jpeg", "wb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: cannot open file!\n");
		closesocket(socketS);
		return 1;
	}
	//setup socket
	sockaddr_in addrDest;
	addrDest.sin_family = AF_INET;
	addrDest.sin_port = htons(TARGET_PORT);
	InetPton(AF_INET, _T(TARGET_IP), &addrDest.sin_addr.s_addr);

	long received_size = 0;
	while (1) {
		package_with_crc* receive_pwc = (package_with_crc*)malloc(sizeof(package_with_crc));
		if (receive_pwc == NULL) {
			fprintf(stderr, "ERROR: cannot allocate memory!\n");
			fclose(f);
			closesocket(socketS);
			return 1;
		}

		package* receive_p = (package*)malloc(sizeof(package));
		if (receive_p == NULL) {
			fprintf(stderr, "ERROR: cannot allocate memory!\n");
			free(receive_pwc);
			fclose(f);
			closesocket(socketS);
			return 1;
		}
		//receiving the package
		if (recvfrom(socketS, (char*)receive_pwc, sizeof(package_with_crc), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: socket error!\n");
			free(receive_pwc);
			free(receive_p);
			fclose(f);
			closesocket(socketS);
			return 1;
		}

		int size = receive_pwc->size;
		memcpy(receive_p->message, receive_pwc->message, size);
		receive_p->size = 0;
		receive_p->num = 0;
		receive_p->size = size;
		receive_p->num = receive_pwc->num;
		receive_p->last = receive_pwc->last;

		unsigned int crc32 = crc32b((char*)receive_p, sizeof(package));

		//comparison with received CRC32
		bool package_is_ok = true;
		if ((crc32 != receive_pwc->crc32) || (receive_p->num != received_size + 1)) package_is_ok = false;

		//if CRC32 converges, then the next package is requested
		if (package_is_ok == true) {
			if (fwrite(receive_pwc->message, 1, size, f) != size) {
				fprintf(stderr, "ERROR: cannot save package!\n");
				free(receive_pwc);
				free(receive_p);
				fclose(f);
				closesocket(socketS);
				return 1;
			}
			received_size += size;
		}
		char message_for_sender[10];
		sprintf(message_for_sender, "%d", received_size + 1);
		if (sendto(socketS, message_for_sender, sizeof(message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot send message for sender!\n");
			free(receive_pwc);
			free(receive_p);
			fclose(f);
			closesocket(socketS);
			return 1;
		}
		printf("Processing image...\n");
		if (receive_pwc->last && package_is_ok) {
			printf("Its last package...\n");
			int timeout = 3000;
			setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
			sendto(socketS, message_for_sender, sizeof(message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest));
			while (recvfrom(socketS, (char*)receive_pwc, sizeof(package_with_crc), 0, (sockaddr*)&from, &fromlen) != SOCKET_ERROR) {
				sendto(socketS, message_for_sender, sizeof(message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest));
			}
			free(receive_pwc);
			free(receive_p);
			fclose(f);
			break;
		}
		free(receive_pwc);
		free(receive_p);
	}
	printf("The image has been saved\n");
	hash_package* hp = (hash_package*)malloc(sizeof(hash_package));
	if (hp == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		closesocket(socketS);
		return 1;
	}

	hash_package_with_crc* hpwc = (hash_package_with_crc*)malloc(sizeof(hash_package_with_crc));
	if (hpwc == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(hp);
		closesocket(socketS);
		return 1;
	}

	BYTE hashBuffer[MD5LEN];
	const wchar_t* filename = L"test_image.jpeg";
	DWORD status = calculateMD5Hash(filename, hashBuffer);
	memcpy(hp->hashBuffer, hashBuffer, sizeof(hashBuffer));
	int timeout = 5000;
	setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	if (recvfrom(socketS, (char*)hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
		fprintf(stderr, "ERROR: cannot receive hashString!\n");
		free(hp);
		free(hpwc);
		closesocket(socketS);
		return 1;
	}
	bool hash_is_ok = true;
	if (crc32b((char*)hp, sizeof(hash_package)) != hpwc->crc32) hash_is_ok = false;
	char message_for_sender1[] = "All is ok!";
	char message_for_sender2[] = "All is bad!";

	while (!hash_is_ok) {
		if (sendto(socketS, message_for_sender2, sizeof(message_for_sender2), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot send message for sender!\n");
			free(hp);
			free(hpwc);
			closesocket(socketS);
			return 1;
		}
		if (recvfrom(socketS, (char*)hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: cannot receive hashString!\n");
			free(hp);
			free(hpwc);
			closesocket(socketS);
			return 1;
		}
		hash_is_ok = true;
		if (crc32b((char*)hp, sizeof(hash_package)) != hpwc->crc32) hash_is_ok = false;
	}
	if (hash_is_ok) {
		Sleep(2000);
		sendto(socketS, message_for_sender1, sizeof(message_for_sender1), 0, (sockaddr*)&addrDest, sizeof(addrDest));
		int new_timeout = 3000;
		setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&new_timeout, sizeof(new_timeout));
		while (recvfrom(socketS, (char*)hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&from, &fromlen) != SOCKET_ERROR) {
			sendto(socketS, message_for_sender1, sizeof(message_for_sender1), 0, (sockaddr*)&addrDest, sizeof(addrDest));
		}
		printf("All is ok!\n");
	}
	free(hp);
	free(hpwc);
	closesocket(socketS);
#endif
	//**********************************************************************
	//QueryPerformanceCounter(&end);

	//executionTime = (end.QuadPart - start.QuadPart) / frequencyInSeconds;

	//printf("%f", executionTime);


	getchar(); //wait for press Enter
	return 0;
}

void InitWinsock()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

unsigned int crc32b(const char* message, int size) {
	int i, j;
	unsigned int byte, crc, mask;

	crc = 0xFFFFFFFF;
	for (i = 0; i < size; ++i) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; --j) {    // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
	}
	return ~crc; // Final XOR value.
}

void append_crc32(char* message, int size) {
	unsigned int crc = crc32b(message, size); // Calculate CRC32
	memcpy(message + size, &crc, sizeof(crc)); // Append CRC32 to the end of the message
}

DWORD calculateMD5Hash(const wchar_t* filename, unsigned char* hashBuffer) {
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	BYTE rgbFile[BUFFERS_LEN];
	HANDLE hFile = NULL;
	DWORD cbRead = 0;
	DWORD cbHash = 0;

	// Logic to check usage goes here.
	hFile = CreateFileW(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		dwStatus = GetLastError();
		wprintf(L"Error opening file %s\nError: %d\n", filename, dwStatus);
		return dwStatus;
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContextW(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		wprintf(L"CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		return dwStatus;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
		dwStatus = GetLastError();
		wprintf(L"CryptAcquireContext failed: %d\n", dwStatus);
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return dwStatus;
	}

	while (bResult = ReadFile(hFile, rgbFile, BUFFERS_LEN, &cbRead, NULL)) {
		if (0 == cbRead) {
			break;
		}

		if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
			dwStatus = GetLastError();
			wprintf(L"CryptHashData failed: %d\n", dwStatus);
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);
			return dwStatus;
		}
	}

	if (!bResult) {
		dwStatus = GetLastError();
		wprintf(L"ReadFile failed: %d\n", dwStatus);
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return dwStatus;
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, hashBuffer, &cbHash, 0)) {
		// MD5 hash was calculated successfully
	}
	else {
		dwStatus = GetLastError();
		wprintf(L"CryptGetHashParam failed: %d\n", dwStatus);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);

	return dwStatus;
}