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

#define WINDOW_SIZE 6

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
	int size;
	int num_of_packages;
	unsigned int crc32;
} first_package_with_crc;

typedef struct {
	int size;
	int num_of_packages;
} first_package;

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
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double executionTime;

	QueryPerformanceFrequency(&frequency);
	double frequencyInSeconds = (double)frequency.QuadPart;

	QueryPerformanceCounter(&start);

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
	fclose(f);

	int num_of_packages = (size / 1024) + 1;
	
	first_package_with_crc fpwc;
	first_package fp;
	
	fp.num_of_packages = num_of_packages;
	fp.size = size;
	fpwc.num_of_packages = num_of_packages;
	fpwc.size = size;
	fpwc.crc32 = crc32b((char*)&fp, sizeof(first_package));
	int* packages_is_ok = (int*)malloc((num_of_packages + WINDOW_SIZE) * sizeof(int));
	if (packages_is_ok == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(data);
		return 1;
	}
	int* expected_messages = (int*)malloc((num_of_packages + WINDOW_SIZE) * sizeof(int));
	if (expected_messages == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(data);
		free(packages_is_ok);
		return 1;
	}
	package_with_crc* packages_with_crc = (package_with_crc*)malloc(num_of_packages * sizeof(package_with_crc));
	if (packages_with_crc == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(data);
		free(packages_is_ok);
		free(expected_messages);
		return 1;
	}
	int ready_size_for_send = 0;
	for (int i = 0; i < num_of_packages; i++) {
		package p;
		int bytes_to_send = (size - ready_size_for_send) > 1024 ? 1024 : (size - ready_size_for_send);
		packages_with_crc[i].last = ready_size_for_send + bytes_to_send >= size;
		p.last = packages_with_crc[i].last;
		//copying part(bytes_to_send) of the image into prepared memory
		memcpy(p.message, data + ready_size_for_send, bytes_to_send);
		memcpy(packages_with_crc[i].message, data + ready_size_for_send, bytes_to_send);
		//creating and adding CRC32 to a prepared package
		p.num = ready_size_for_send + 1;
		packages_with_crc[i].num = ready_size_for_send + 1;
		p.size = bytes_to_send;
		packages_with_crc[i].size = bytes_to_send;
		packages_with_crc[i].crc32 = crc32b((char*)&p, sizeof(package));
		packages_is_ok[i] = 0;
		expected_messages[i] = i * 1024 + 1;
		ready_size_for_send += bytes_to_send;
	}
	for (int i = 0; i < num_of_packages + WINDOW_SIZE; i++) {
		expected_messages[i] = i * 1024 + 1;
		packages_is_ok[i] = 0;
	}
	free(data);
	//setting up a socket to send an image
	sockaddr_in addrDest;
	addrDest.sin_family = AF_INET;
	addrDest.sin_port = htons(TARGET_PORT);
	InetPton(AF_INET, _T(TARGET_IP), &addrDest.sin_addr.s_addr);
	//setting up a timeout
	int timeout = 300;
	setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	while (1) {
		sendto(socketS, (char*)&fpwc, sizeof(first_package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest));
		char first_message_from_receiver[10];
		recvfrom(socketS, first_message_from_receiver, sizeof(first_message_from_receiver), 0, (sockaddr*)&from, &fromlen);
		if (atoi(first_message_from_receiver) == -1) break;
	}
	//start of sending image 
	long sent_size = 0;
	int ok_packages = 0;
	int num_of_sent_packages[WINDOW_SIZE];
	while (ok_packages < num_of_packages) {
		int iteration = 0;
		for (int package_num = 0; package_num < num_of_packages; package_num++) {
			if (packages_is_ok[package_num] == 0) {
				if (sendto(socketS, (char*)&packages_with_crc[package_num], sizeof(package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
					fprintf(stderr, "ERROR: cannot send image!\n");
					free(expected_messages);
					free(packages_is_ok);
					free(packages_with_crc);
					closesocket(socketS);
					return 1;
				}
				packages_is_ok[package_num] = 2;
				num_of_sent_packages[iteration] = package_num;
				printf("Sending %d package...\n", package_num);
				iteration++;
			}
			if (iteration == WINDOW_SIZE || package_num == num_of_packages - 1) break;
		}
		int received_messages[WINDOW_SIZE];
		for (int i = 0; i < iteration; i++) {
			char received_message[10];
			if (recvfrom(socketS, received_message, sizeof(received_message), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error == WSAETIMEDOUT) {
					printf("The Package was lost...\n ");
					received_messages[i] = -1;
					continue;
				}
				else {
					fprintf(stderr, "ERROR: socket error!\n");
					free(expected_messages);
					free(packages_is_ok);
					free(packages_with_crc);
					closesocket(socketS);
					return 1;
				}
			}
			received_messages[i] = atoi(received_message);
		}
		for (int i = 0; i < iteration; i++) {
			for (int j = i; j < iteration; j++) {
				if (received_messages[i] > received_messages[j]) {
					int buf = received_messages[i];
					received_messages[i] =  received_messages[j];
					received_messages[j] =  buf;
				}
			}
		}
		int it = 0;
		int prediction[WINDOW_SIZE];
		for (int package_num = 0; package_num < num_of_packages + WINDOW_SIZE; package_num++) {
			if (packages_is_ok[package_num] == 0) {
				prediction[it] = expected_messages[package_num];
				it++;
			}
			if (it == iteration) break;
		}
		if (ok_packages + WINDOW_SIZE < num_of_packages) {
			for (int i = 0; i < it; i++) {
				if (prediction[i] == received_messages[i]) {
					packages_is_ok[num_of_sent_packages[i]] = 1;
					printf("ok packages: %d\n", ok_packages);
					ok_packages++;
				}
				else {
					packages_is_ok[num_of_sent_packages[i]] = 0;
				}
			}
		}
		else {
			for (int i = 0; i < it; i++) {
				for (int j = 0; j < it; j++) {
					packages_is_ok[num_of_sent_packages[i]] = 0;
					if (prediction[i] == received_messages[j]) {
						packages_is_ok[num_of_sent_packages[i]] = 1;
						printf("ok packages: %d\n", ok_packages);
						ok_packages++;
						break;
					}
				}
			}
		}
	}
	printf("The image has been sent!\n");
	free(packages_with_crc);
	free(expected_messages);
	free(packages_is_ok);

	hash_package hp;
	hash_package_with_crc hpwc;

	const wchar_t* filename = L"test.jpg";
	DWORD status = calculateMD5Hash(filename, hpwc.hashBuffer);
	memcpy(hp.hashBuffer, hpwc.hashBuffer, sizeof(hpwc.hashBuffer));

	//adding crc32
	hpwc.crc32 = crc32b((char*)&hp, sizeof(hash_package));

	printf("Sending hash string...\n");
	
	while (1) {
		sendto(socketS, (char*)&hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&addrDest, sizeof(addrDest));
		char hash_message_from_receiver[10];
		recvfrom(socketS, hash_message_from_receiver, sizeof(hash_message_from_receiver), 0, (sockaddr*)&from, &fromlen);
		if (atoi(hash_message_from_receiver) == -1) break;
	}
	printf("All is ok!\n");
	closesocket(socketS);

#endif // SENDER

#ifdef RECEIVER
	printf("Waiting for package ...\n");
	//setup socket
	sockaddr_in addrDest;
	addrDest.sin_family = AF_INET;
	addrDest.sin_port = htons(TARGET_PORT);
	InetPton(AF_INET, _T(TARGET_IP), &addrDest.sin_addr.s_addr);
	int timeout = 300;
	setsockopt(socketS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

	first_package_with_crc received_fpwc;
	first_package received_fp;

	while (recvfrom(socketS, (char*)&received_fpwc, sizeof(first_package_with_crc), 0, (sockaddr*)&from, &fromlen)) {
		received_fp.size = received_fpwc.size;
		received_fp.num_of_packages = received_fpwc.num_of_packages;
		if (crc32b((char*)&received_fp, sizeof(first_package)) == received_fpwc.crc32) {
			char first_message_for_sender[10] = "-1";
			for (int i = 0; i < 1; i++) {
				sendto(socketS, first_message_for_sender, sizeof(first_message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest));
			}
			break;
		}
	}

	int size = received_fpwc.size;
	int num_of_packages = received_fpwc.num_of_packages;

	bool* packages_is_ok = (bool*)malloc((num_of_packages + WINDOW_SIZE) * sizeof(bool));
	if (packages_is_ok == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		closesocket(socketS);
		return 1;
	}

	int* expected_nums = (int*)malloc((num_of_packages + WINDOW_SIZE) * sizeof(int));
	if (expected_nums == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(packages_is_ok);
		closesocket(socketS);
		return 1;
	}

	package* packages = (package*)malloc(num_of_packages * sizeof(package));
	if (packages == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory!\n");
		free(packages_is_ok);
		free(expected_nums);
		closesocket(socketS);
		return 1;
	}
	for (int i = 0; i < num_of_packages + WINDOW_SIZE; i++) {
		packages_is_ok[i] = false;
		expected_nums[i] = i * 1024 + 1;
	}
	bool is_last = false;
	int num = 0;


	while (num < num_of_packages) {
		int iteration;
		int received_packages[WINDOW_SIZE];
		for (iteration = 0; iteration < min(WINDOW_SIZE, num_of_packages - num); iteration++) {

			package_with_crc received_pwc;
			package received_p;

			//receiving the package
			if (recvfrom(socketS, (char*)&received_pwc, sizeof(package_with_crc), 0, (sockaddr*)&from, &fromlen) == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT) continue;
				fprintf(stderr, "ERROR: socket error!\n");
				free(packages_is_ok);
				free(expected_nums);
				free(packages);
				closesocket(socketS);
				return 1;
			}

			memcpy(received_p.message, received_pwc.message, received_pwc.size);
			received_p.size = received_pwc.size;
			received_p.num = received_pwc.num;
			received_p.last = received_pwc.last;

			unsigned int crc32 = crc32b((char*)&received_p, sizeof(package));
			int it = 0;
			if (crc32 == received_pwc.crc32) {
				for (int package_num = 0; package_num < num_of_packages; package_num++) {
					if (!packages_is_ok[package_num]) {
						it++;
						if (expected_nums[package_num] == received_p.num) {
							memcpy(packages[package_num].message, received_p.message, received_p.size);
							packages[package_num].size = received_p.size;
							packages[package_num].num = received_p.num;
							packages[package_num].last = received_p.last;
							packages_is_ok[package_num] = true;
							if (packages[package_num].last) is_last = true;
							printf("package %d is ok\n", package_num);
							num++;
							break;
						}
						if (it == min(WINDOW_SIZE, num_of_packages - num)) break;
					}
				}
			}
		}
		int it = 0;
		if (num >= num_of_packages - 1) {
			for (int i = 0; i < 10; i++) {
				it = 0;
				for (int package_num = 0; package_num < num_of_packages + WINDOW_SIZE; package_num++) {
					char message_for_sender[10];
					if (!packages_is_ok[package_num]) {
						sprintf(message_for_sender, "%d", expected_nums[package_num]);
						if (sendto(socketS, message_for_sender, sizeof(message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
							fprintf(stderr, "ERROR: cannot send message for sender!\n");
							closesocket(socketS);
							return 1;
						}
						it++;
					}
					if (it == iteration) break;
				}
				printf("Processing image...\n");
			}
		}
		else {
			it = 0;
			for (int package_num = 0; package_num < num_of_packages + WINDOW_SIZE; package_num++) {
				char message_for_sender[10];
				if (!packages_is_ok[package_num]) {

					sprintf(message_for_sender, "%d", expected_nums[package_num]);
					if (sendto(socketS, message_for_sender, sizeof(message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest)) == SOCKET_ERROR) {
						fprintf(stderr, "ERROR: cannot send message for sender!\n");
						closesocket(socketS);
						return 1;
					}
					it++;
				}
				if (it == iteration) break;
			}
			printf("Processing image...\n");
		}
	}
	FILE* f = fopen("test_image.jpeg", "wb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: cannot open file!\n");
		closesocket(socketS);
		return 1;
	}
	for (int i = 0; i < num_of_packages; i++) {
		fwrite(packages[i].message, 1, packages[i].size, f);
	}
	fclose(f);
	free(packages);
	free(packages_is_ok);
	free(expected_nums);
	printf("The image has been saved\n");

	hash_package hp;
	hash_package_with_crc hpwc;

	BYTE hashBuffer[MD5LEN];
	const wchar_t* filename = L"test_image.jpeg";
	DWORD status = calculateMD5Hash(filename, hpwc.hashBuffer);
	memcpy(hp.hashBuffer, hpwc.hashBuffer, sizeof(hpwc.hashBuffer));

	//adding crc32
	hpwc.crc32 = crc32b((char*)&hp, sizeof(hash_package));
	hash_package received_hp;
	hash_package_with_crc received_hpwc;
	while (recvfrom(socketS, (char*)&received_hpwc, sizeof(hash_package_with_crc), 0, (sockaddr*)&from, &fromlen)) {
		memcpy(received_hp.hashBuffer, received_hpwc.hashBuffer, sizeof(received_hpwc.hashBuffer));
		if (crc32b((char*)&hp, sizeof(hash_package)) == received_hpwc.crc32) {
			char last_message_for_sender[10] = "-1";
			for (int i = 0; i < 10; i++) {
				sendto(socketS, last_message_for_sender, sizeof(last_message_for_sender), 0, (sockaddr*)&addrDest, sizeof(addrDest));
			}
			break;
		}
	}

	printf("All is ok!\n");
	closesocket(socketS);
#endif
	//**********************************************************************
	QueryPerformanceCounter(&end);

	executionTime = (end.QuadPart - start.QuadPart) / frequencyInSeconds;

	printf("%f", executionTime);


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