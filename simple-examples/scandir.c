// Scott Kuhl
// Demonstrates how to get a listing of files in a directory.
#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void printFilesInDir(char *dir)
{
	if(dir == NULL)
		return;

	printf("#### Files in directory '%s':\n", dir);
	struct dirent **dirList;
	int count = scandir(dir, &dirList, NULL, alphasort);
	if(count == -1)
	{
		perror("scandir");
		return;
	}
	for(int i=0; i<count; i++)
		printf("%s\n", dirList[i]->d_name);
	printf("\n\n");

	// Free space
	for(int i=0; i<count; i++)
		free(dirList[i]);
	free(dirList);
}

int main(void)
{
	printFilesInDir("."); // current directory
	printFilesInDir("/tmp");
	printFilesInDir("/does.not.exist");



}
