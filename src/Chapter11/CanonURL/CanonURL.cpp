// CanonURL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_URL (256)

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: CanonURL <data>");
		return -1;
	}

	char szBuffer[MAX_URL];
	DWORD dwBuffer = MAX_URL;

	if (InternetCanonicalizeUrl(
				argv[1],
				szBuffer,
				&dwBuffer,
				0) == TRUE) {
		printf("Cleaned up version is %s\n",szBuffer);
	} else {
		printf("Error -> %d",GetLastError());
	}

	return 0;
}

