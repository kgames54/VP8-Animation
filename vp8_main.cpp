#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "base64.h"

using namespace std;

int ExtractFilePath (const char *pszFileName, char* pszFilePath, int nBufferLength)
{
  const char *pSlashPos = strrchr(pszFileName, '\\');
  if (!pSlashPos)
    strrchr(pszFileName, '/');
  if (!pSlashPos)
    return 0; // no slash found - bad file name
 
  int nPathLength = pSlashPos - pszFileName;
 
  int nCharsToCopy = nPathLength >= nBufferLength ? nBufferLength - 1 : nPathLength;
 
  if (pszFilePath)
  {
    strncpy (pszFilePath, pszFileName, nCharsToCopy);
    pszFilePath [nCharsToCopy] = 0;
  }
 
  return nPathLength+1;
}

int shellExecVP8HTML(int count, char *files[], char *fileName, char *dirApp)
{
char *line = new char[512];
char *fileUrl = new char[strlen(dirApp)+strlen(fileName)+2];
sprintf(fileUrl,"%s\\%s",dirApp,fileName);
FILE *f = fopen(fileUrl,"w");
sprintf(line,"mkdir %s\\temp 2> NUL",dirApp);
system(line);

	for(int i=0; i < count; i++)
	{
	sprintf(line,"%s\\ffmpeg.exe -i \"%s\" \"%s\\temp\\output_%d.webp\" 2> %s\\bin\\logs.txt",dirApp,files[i],dirApp,i,dirApp);
	system(line);
	}

char *head = "<html><head><title>Animation</title></head><body><div>";
fwrite(head,strlen(head),1,f);
sprintf(line,"<input type=\"hidden\" id=\"count\" name=\"count\" value=\"%d\" />",count);
fwrite(line,strlen(line),1,f);

	for(int i=0; i < count; i++)
	{
	sprintf(line,"%s\\temp\\output_%d.webp",dirApp,i);
	char *b64Code = base64_to_file(line);
	//char *typeVisible = new char[64];
	//sprintf(typeVisible,"visible",NULL);
	char *fformat = "<img id=\"frame%d\" src=\"data:image/webp;base64,%s\" style=\"position: absolute; visibility: hidden;\"/>";
	char *frame = new char[strlen(fformat)+strlen(b64Code)+1];
		if(strlen(b64Code) > 1)
		{
		sprintf(frame,fformat,i,b64Code);
		fwrite(frame,strlen(frame),1,f);
		}
	}

	char *footer = "<script src=\"main.js\"></script></div></body></html>";
	fwrite(footer,strlen(footer),1,f);

	fclose(f);

	sprintf(line,"rmdir /s /q %s\\temp",dirApp);
	system(line);
	return 0;
}

int shellExecVP8(int count, char *files[], char *fileName, char *appPath)
{
char *fileUrl = new char[strlen(appPath)+strlen(fileName)+2];
sprintf(fileUrl,"%s\\%s",appPath,fileName);
char *line = new char[512];
FILE *f = fopen(fileUrl,"w");
sprintf(line,"mkdir %s\\temp 2> NUL",appPath);
system(line);

	for(int i=0; i < count; i++)
	{
	sprintf(line,"%s\\ffmpeg.exe -i \"%s\" \"%s\\temp\\output_%d.webp\" 2> %s\\bin\\logs.txt",appPath,files[i],appPath,i,appPath);
	system(line);
	}
	
	char *xmlHead = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	fwrite(xmlHead,strlen(xmlHead),1,f);

	char *frames = "<frames list=\"true\">\n";
	fwrite(frames,strlen(frames),1,f);

	for(int i=0; i < count; i++)
	{
	sprintf(line,"%s\\temp\\output_%d.webp",appPath,i);
	char *b64Code = base64_to_file(line);
	char *oframe = "<frame>", *cframe = "</frame>\n";
	fwrite(oframe,strlen(oframe),1,f);
	fwrite(b64Code,strlen(b64Code),1,f);
	fwrite(cframe,strlen(cframe),1,f);
	}

	char *cframes = "</frames>";
	fwrite(cframes,strlen(cframes),1,f);

	fclose(f);

	sprintf(line,"rmdir /s /q %s\\temp",appPath);
	system(line);
	return 0;
}

int main(int argc, char *argv[])
{
	system("@echo on");
	for(int i=0; i<33; i++)
	{
	if(i < 10)sprintf(num,"000%d",i);
	if((i > 10) && (i < 100))sprintf(num,"00%d",i);
	sprintf(line,"ffmpeg.exe -i \"D:\\HPDrivers\\SDHC\\WWII\\beret_soldier\\walk_soldier_beret\\walk_up_soldier_beret_%s.png\" \"D:\\HPDrivers\\SDHC\\externlink\\Release\\output_%d.webp\" 2> bin\\logs.txt",num,i);
	system(line);
	}
	system("@echo success >> bin\\result.txt");
	system("exit");

	int nCharsRequired = ExtractFilePath (argv[0], NULL, 0);
	pathApp = new char[nCharsRequired];
	ExtractFilePath (argv[0], pathApp, nCharsRequired);
	if(argc > 1)
		shellExecVP8HTML(argc,argv,"tempFile.html",pathApp);
	system("pause");
    return 0;
}

