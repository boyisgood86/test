#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include "iniparser.h"

#define FILENAME	"./hello.txt"

int doiniparser(const char *filename,const char *section,const char *key,const char *value)
{
	char *entry = NULL;
	FILE *fp = NULL;

	if(!section || !key){
		fprintf(stderr,"%s\n","No section or key!");
		return -1;
	}
	
	if((sizeof(section) + sizeof(key)) > 256){
		fprintf(stderr,"%s\n","your string is too long !");
		return -1;
	}

	entry = (char*)malloc(sizeof(char)*256);
	if(!entry){
		perror("se malloc:");
		return -1;
	}

	bzero(entry,128);
	strcpy(entry,section);
	strcat(entry,":");
	strcat(entry,key);

	dictionary *ini = iniparser_load(filename);
	if(!ini){
		fprintf(stderr,"cannot parse file:%s\n",filename);
		return -1;
	}

	iniparser_set(ini,entry,value);

	fp = fopen(filename,"r+");
	if(!fp){
		fprintf(stderr,"cannot save file:%s\n",filename);
		return -1;
	}
	iniparser_dump_ini(ini,fp);

	fclose(fp);
	iniparser_freedict(ini);

	free(entry);
	return 0;
}

int main(void)
{
	char *section = "goo";
	char *key = "jj";
	char *value = "/mnt/tmp";
	doiniparser(FILENAME,section,key,value);
	return 0;
}
