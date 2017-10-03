#include "Windows.h"
#include <thread>
using namespace std;
void print(DWORD* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%u,",arr[i]);
	}
	printf("\n");
}
void merge(DWORD*  b, DWORD* c, int halflen) {
	DWORD* temp = new DWORD[halflen * 2];
	for (int i = 0, j = 0, k = 0; k < halflen * 2; k++) {
		if (i >= halflen) {
			temp[k] = c[j];
			j++;
		}else
		if (j >= halflen) {
			temp[k] = b[i];
			i++;
		}else
		if (b[i] < c[j]) {
			temp[k] = b[i];
			i++;
		}
		else {
			temp[k] = c[j];
			j++;
		}
	}
	memcpy(b, temp, sizeof(DWORD)*halflen * 2);
}
void paramergy(DWORD* a, int len) {
	if (len == 1) return;
	DWORD* b = a;
	int halflen = len / 2;
	DWORD* c = a + halflen;
	
	thread bthread(paramergy,b,halflen);
	thread cthread(paramergy,c,halflen);

	bthread.join();
	cthread.join();

	merge(b, c, halflen);
}

int main() {
	DWORD arr[64];
	for (int i = 64; i > 0; i--) {
		arr[64 - i] = i;
	}
	print(arr, 64);
	paramergy(arr, 64);
	print(arr, 64);
	return 0;
}