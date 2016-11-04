#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

std::vector<string> filenamelist;
std::vector<char *> filedatalist;
std::vector<int>    filesizelist;

static int parseoct(const char *p, size_t n)
{
	int i = 0;

	while (*p < '0' || *p > '7') {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}

static int is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return (0);
	return (1);
}

static int verify_checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < 512; ++n) {
		if (n < 148 || n > 155)
			/* Standard tar checksum adds unsigned bytes. */
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;

	}
	return (u == parseoct(p + 148, 8));
}

static bool untar(const char * tarpath)
{
	filenamelist.clear();
	for(int i=0;i<filedatalist.size();i++) free(filedatalist[i]);
	filedatalist.clear();
	filesizelist.clear();

	FILE * a = NULL;
	char   buff[512];
	size_t bytes_read;
	int    filesize;
	char * filedata;

	a = fopen(tarpath, "rb");
	if(NULL==a) goto ERROR;

	for (;;) {
		bytes_read = fread(buff, 1, 512, a);
		if (bytes_read < 512)        goto ERROR;
		if (is_end_of_archive(buff)) goto OK;
		if (!verify_checksum(buff))  goto ERROR;

		filesize = parseoct(buff + 124, 12);
		switch (buff[156]) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			filesize = 0;
			break;
		default:
			filenamelist.push_back(buff);
			filedata = (char *)malloc(filesize+1);
			filedata[filesize] = '\0';	//for str file
			filedatalist.push_back(filedata);
			filesizelist.push_back(filesize);
			break;
		}

		int blocksize = ceil(filesize/512.0)*512;
		int spacesize = blocksize - filesize;
		bytes_read = fread(filedata, 1, filesize, a);
		if(bytes_read!=filesize) goto ERROR;
		bytes_read = fread(buff, 1, spacesize, a);
		if(bytes_read!=spacesize) goto ERROR;
		// while (filesize > 0) {
		// 	bytes_read = fread(buff, 1, 512, a);
		// 	if (bytes_read < 512) goto ERROR;
		// 	if (filesize < 512)   bytes_read = filesize;

		// 	memcpy(filedata,buff,bytes_read);
		// 	filesize -= bytes_read;
		// 	filedata += bytes_read;
		// }
	}
ERROR:
	if(a) fclose(a);
	return false;
OK:
	if(a) fclose(a);
	return true;
}

bool modelinit(const char * path)
{
	return untar(path);
}

void modelclear()
{
	filenamelist.clear();
	for(int i=0;i<filedatalist.size();i++) free(filedatalist[i]);
	filedatalist.clear();
	filesizelist.clear();
}

char * modelsymbol(const char * prefix)
{
	string p(prefix);
	for(int i=0;i<filenamelist.size();i++)
	{
		int ret = filenamelist[i].find("symbol");
		if(-1==ret) continue;
		ret = filenamelist[i].find(p);
		if(0!=ret) continue;
		return filedatalist[i];
	}
	return NULL;
}

char * modeldata(const char * prefix)
{
	string p(prefix);
	for(int i=0;i<filenamelist.size();i++)
	{
		int ret = filenamelist[i].find("params");
		if(-1==ret) continue;
		ret = filenamelist[i].find(p);
		if(0!=ret) continue;
		return filedatalist[i];
	}
	return NULL;
}

int modelsize(const char * prefix)
{
	string p(prefix);
	for(int i=0;i<filenamelist.size();i++)
	{
		int ret = filenamelist[i].find("params");
		if(-1==ret) continue;
		ret = filenamelist[i].find(p);
		if(0!=ret) continue;
		return filesizelist[i];
	}
	return -1;
}