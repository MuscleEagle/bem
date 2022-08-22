#include<stdio.h>
#include <uuid/uuid.h>
 
struct BemrayData
{
	char strUseFile[128];
	char strSwitch[128];
	char strCacheID[128];
	char strKindID[128];
	char strProject[128];
	char strDomain[128];
	char strCachePath[128];
	char strCachePort[128];
	char strKindPort[128];
}
 
bool findConfig(char* pLine, char* pLeft, char* pRight)
{
	if(!pLine) return false;
	char* pItr = strchr(pLine, '=');
	if(!pItr) return false;
	int nCount = pItr - pLine;
	if(nCount == 0) return false;
	int nLast = strlen(pItr) - nCount - 1;
	if(nLast == 0) return false;
	strncpy(pLeft, pLine, nCount);
	strncpy(pRight, pItr + 1, nLast);
}
 
bool praseConfig(BemrayData* pData, char* pLeft, char* pRight)
{
	if(strcmp("UseFile", pLeft) == 0)
	{
		strcpy(pData->strUseFile, pRight);
		return true;
	}
	if(strcmp("Switch", pLeft) == 0)
	{
		strcpy(pData->strSwitch, pRight);
		return true;
	}
	if(strcmp("CacheID", pLeft) == 0)
	{
		strcpy(pData->strCacheID, pRight);
		return true;
	}
	if(strcmp("KindID", pLeft) == 0)
	{
		strcpy(pData->strKindID, pRight);
		return true;
	}
	if(strcmp("Project", pLeft) == 0)
	{
		strcpy(pData->strProject, pRight);
		return true;
	}
	if(strcmp("Domain", pLeft) == 0)
	{
		strcpy(pData->strDomain, pRight);
		return true;
	}
	if(strcmp("CachePath", pLeft) == 0)
	{
		strcpy(pData->strCachePath, pRight);
		return true;
	}
	if(strcmp("CachePort", pLeft) == 0)
	{
		strcpy(pData->strCachePort, pRight);
		return true;
	}
	if(strcmp("KindPort", pLeft) == 0)
	{
		strcpy(pData->strKindPort, pRight);
		return true;
	}
}
 
void initData(BemrayData* pData)
{
	strcpy(pData->strUseFile, "false");
	strcpy(pData->strSwitch, "fly");
	strcpy(pData->strCachePath, "bemray");
	strcpy(pData->strCachePort, "12345");
	strcpy(pData->strKindPort, "12345");
	strcpy(pData->strProject, "bemray");
	strcpy(pData->strDomain, "bemray.com");
	
	uuid_t uuidCache;
	uuid_t uuidKind;
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strCacheID);
	uuid_generate(uuidKind);
	uuid_unparse(uuidKind, pData->strKindID);
}

bool LoadData(BemrayData* pData)
{
	initData(pData);
	FILE *fp = fopen("bemray.conf", "r");
	if(!fp) return false;

	while(!feof(fp))
	{
		char strLine[1024];
		char strLeft[1024];
		char strRight[1024];
	
		fgets(strLine,1024,fp);
		if( findConfig(strLine, strLeft, strRight) )
		{
			praseConfig(&sData, strLeft, strRight)
		}
	}
	fclose(fp);
	if(strcmp( pData->strUseFile, "true" ) == 0)
		return true;
	return false;
}

void SaveData(BemrayData* pData, bool bNewUUID)
{
	FILE *fp = fopen("bemray.conf", "w");
	if(!fp) return;
	if(bNewUUID)
	{
		uuid_t uuidCache;
		uuid_t uuidKind;
		uuid_generate(uuidCache);
		uuid_unparse(uuidCache, pData->strCacheID);
		uuid_generate(uuidKind);
		uuid_unparse(uuidKind, pData->strKindID);
	}
	fwrite(fp, "UseFile=%s\n", pData->strUseFile);
	fwrite(fp, "Switch=%s\n", pData->strSwitch);
	fwrite(fp, "Project=%s\n", pData->strProject);
	fwrite(fp, "Domain=%s\n", pData->strDomain);
	fwrite(fp, "CachePath=%s\n", pData->strCachePath);
	fwrite(fp, "CachePort=%s\n", pData->strCachePort);
	fwrite(fp, "KindPort=%s\n", pData->strKindPort);
	fwrite(fp, "CacheID=%s\n", pData->strCacheID);
	fwrite(fp, "KindID=%s\n", pData->strKindID);
	
	fclose(fp);
}

int main()
{
	BemrayData sData;
	if(!LoadData(&sData))
	{
		printf( "Please Check bemray.conf!\n");
		SaveData(&sData, true);
		return -1;
	}
	
	char strInput[128];
	
	printf( "Enter [Y/y] to create new guid, otherwise will keep the old guid.\n");
	scanf("%s", strInput);
	if(strcmp("Y", strInput) == 0 || strcmp("y", strInput) == 0)
		SaveData(&sData, true);
	else
		SaveData(&sData, false);
	
	printf( "Enter Work Mode:\n    1.domain\n    2.project\n    3.both\n    others.neither\n");
	scanf("%s", &strInput);
	{
		char strDomainBash[128] = "domain.sh";
		char strProjectBash[128] = "project.sh";
		//install dependencies
		FILE *fp = NULL;
		fp = fopen("dependencies.sh", "w");
		
		fprintf(fp, "#!/bin/bash\n");
		if(strcmp("1", strInput) == 0 || strcmp("3", strInput) == 0)
		{
			fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strDomainBash, strDomainBash);
			fprintf(fp, "sed -i \"s/YourDomain/%s/g\" %s\n", sData.strDomain, strDomainBash);
			fprintf(fp, "bash domain.sh\n");
			fprintf(fp, "rm domain.sh\n");
			printf("domain.sh is on the way!\n");		
		}
		if(strcmp("2", strInput) == 0 || strcmp("3", strInput) == 0)
		{
			fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strProjectBash, strProjectBash);
			fprintf(fp, "sed -i \"s/YourProject/%s/g\" %s\n", sData.strProject, strProjectBash);
			fprintf(fp, "bash project.sh\n");
			fprintf(fp, "rm project.sh\n");
			printf("project.sh is on the way!\n");
		}
		fclose(fp);
	}
	return 1;
}
