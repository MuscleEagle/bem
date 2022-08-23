#define BemrayHand

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifdef BemrayHand
#pragma warning(disable:4996)
#else
#include <uuid/uuid.h>
#endif

struct BemrayData
{
	char strConfigFile[128];
	char strDependFile[128];
	char strModifyFile[128];
	char strUseFile[128];
	char strSwitch[128];
	char strCacheID[128];
	char strKindID[128];
	char strProject[128];
	char strDomain[128];
	char strCachePath[128];
	char strCachePort[128];
	char strKindPort[128];
};

bool findConfig(char* pLine, char* pLeft, char* pRight)
{
	if (!pLine) return false;
	sscanf(pLine, "%[^=]=%s", pLeft, pRight);
	if (strlen(pLeft) <= 0 && strlen(pRight) <= 0)
		return false;
	return true;
}

bool praseConfig(struct BemrayData* pData, char* pLeft, char* pRight)
{
	if (strcmp("ConfigFile", pLeft) == 0)
	{
		strcpy(pData->strConfigFile, pRight);
		return true;
	}
	if (strcmp("DependFile", pLeft) == 0)
	{
		strcpy(pData->strDependFile, pRight);
		return true;
	}
	if (strcmp("ModifyFile", pLeft) == 0)
	{
		strcpy(pData->strModifyFile, pRight);
		return true;
	}
	if (strcmp("UseFile", pLeft) == 0)
	{
		strcpy(pData->strUseFile, pRight);
		return true;
	}
	if (strcmp("Switch", pLeft) == 0)
	{
		strcpy(pData->strSwitch, pRight);
		return true;
	}
	if (strcmp("CacheID", pLeft) == 0)
	{
		strcpy(pData->strCacheID, pRight);
		return true;
	}
	if (strcmp("KindID", pLeft) == 0)
	{
		strcpy(pData->strKindID, pRight);
		return true;
	}
	if (strcmp("Project", pLeft) == 0)
	{
		strcpy(pData->strProject, pRight);
		return true;
	}
	if (strcmp("Domain", pLeft) == 0)
	{
		strcpy(pData->strDomain, pRight);
		return true;
	}
	if (strcmp("CachePath", pLeft) == 0)
	{
		strcpy(pData->strCachePath, pRight);
		return true;
	}
	if (strcmp("CachePort", pLeft) == 0)
	{
		strcpy(pData->strCachePort, pRight);
		return true;
	}
	if (strcmp("KindPort", pLeft) == 0)
	{
		strcpy(pData->strKindPort, pRight);
		return true;
	}
	return false;
}

void makeGuid(struct BemrayData* pData)
{
#ifdef BemrayHand
	strcpy(pData->strCacheID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strKindID, "a3e3a80d-df41-4235-bd18-d45878da324e");
#else
	uuid_t uuidCache;
	uuid_t uuidKind;
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strCacheID);
	uuid_generate(uuidKind);
	uuid_unparse(uuidKind, pData->strKindID);
#endif
}

void initData(struct BemrayData* pData)
{
	strcpy(pData->strConfigFile, "bemray.conf");
	strcpy(pData->strDependFile, "depend.sh");
	strcpy(pData->strModifyFile, "modify.sh");
	strcpy(pData->strUseFile, "false");
	strcpy(pData->strSwitch, "fly");
	strcpy(pData->strCachePath, "bemray");
	strcpy(pData->strCachePort, "12345");
	strcpy(pData->strKindPort, "12345");
	strcpy(pData->strProject, "bemray");
	strcpy(pData->strDomain, "bemray.com");

	makeGuid(pData);
}

bool LoadData(struct BemrayData* pData)
{
	initData(pData);
	FILE* fp = fopen(pData->strConfigFile, "r");
	if (!fp) return false;

	while (!feof(fp))
	{
		char strLine[1024];
		char strLeft[1024];
		char strRight[1024];

		fgets(strLine, 1024, fp);

		char* pItr = strchr(strLine, '\n');
		if (pItr)
			pItr[0] = '\0';

		if (findConfig(strLine, strLeft, strRight))
		{
			praseConfig(pData, strLeft, strRight);
		}
	}
	fclose(fp);
	if (strcmp(pData->strUseFile, "true") == 0)
		return true;
	return false;
}

void SaveData(struct BemrayData* pData, bool bNewUUID)
{
	FILE* fp = fopen(pData->strConfigFile, "w");
	if (!fp) return;
	if (bNewUUID)
	{
		makeGuid(pData);
	}

	fprintf(fp, "ConfigFile=%s\n", pData->strConfigFile);
	fprintf(fp, "DependFile=%s\n", pData->strDependFile);
	fprintf(fp, "ModifyFile=%s\n", pData->strModifyFile);
	fprintf(fp, "UseFile=%s\n", pData->strUseFile);
	fprintf(fp, "Switch=%s\n", pData->strSwitch);
	fprintf(fp, "Project=%s\n", pData->strProject);
	fprintf(fp, "Domain=%s\n", pData->strDomain);
	fprintf(fp, "CachePath=%s\n", pData->strCachePath);
	fprintf(fp, "CachePort=%s\n", pData->strCachePort);
	fprintf(fp, "KindPort=%s\n", pData->strKindPort);
	fprintf(fp, "CacheID=%s\n", pData->strCacheID);
	fprintf(fp, "KindID=%s\n", pData->strKindID);

	fclose(fp);
}

int GetInputNumber()
{
	int nInput = 0;
	scanf("%d", &nInput);
	return nInput;
}

bool MakeDepend(struct BemrayData* pData)
{
	printf("Enter Work Mode:\n    [1]    domain\n    [2]    project\n    [3]    both\n    [others]    neither\n");
	int nInput = GetInputNumber();

	char strSwitchOn[128];
	int nSwitch = strlen(pData->strProject) - strlen(pData->strSwitch);
	if (nSwitch > 0)
	{
		strncpy(strSwitchOn, pData->strProject, nSwitch);
		strcpy(strSwitchOn + nSwitch, pData->strSwitch);
	}
	char strDomainBash[128] = "domain.sh";
	char strProjectBash[128] = "project.sh";
	//install dependencies
	FILE* fp = NULL;
	fp = fopen(pData->strDependFile, "w");
	if (!fp) return false;

	fprintf(fp, "#!/bin/bash\n");
	if (nInput == 1 || nInput == 3)
	{
		fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strDomainBash, strDomainBash);
		fprintf(fp, "sed -i \"s/YourDomain/%s/g\" %s\n", pData->strDomain, strDomainBash);
		fprintf(fp, "bash domain.sh\n");
		fprintf(fp, "rm domain.sh\n");
		printf("domain.sh is on the way!\n");
	}
	if (nInput == 2 || nInput == 3)
	{
		fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strProjectBash, strProjectBash);
		fprintf(fp, "sed -i \"s/YourProject/%s/g\" %s\n", pData->strProject, strProjectBash);
		fprintf(fp, "sed -i \"s/YourSwitch/%s/g\" %s\n", strSwitchOn, strProjectBash);
		fprintf(fp, "bash project.sh\n");
		fprintf(fp, "rm project.sh\n");
		printf("project.sh is on the way!\n");
	}
	fclose(fp);
	return true;
}

bool MakeModify(struct BemrayData* pData)
{
	//modify config file
	FILE* fp = NULL;
	fp = fopen(pData->strModifyFile, "w");
	if (!fp) return false;

	fprintf(fp, "#!/bin/bash\n");
	fprintf(fp, "NginxDefaultFile=/etc/nginx/conf.d/default.conf\n");
	fprintf(fp, "NginxCustomFile=/etc/nginx/conf.d/custom.conf\n");
	fprintf(fp, "DefaultFile=/usr/local/etc/%s/config.json\n", pData->strProject);

	fprintf(fp, "echo \"Delete Old Nginx Default Config File!\"\n");
	fprintf(fp, "rm -f $NginxDefaultFile\n");
	fprintf(fp, "echo \"Download new default.conf\"\n");
	fprintf(fp, "wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/new.conf\n");
	fprintf(fp, "echo \"Fill Custom Setting\"\n");
	fprintf(fp, "sed -i \"s/YourDomainName/%s/g\" $NginxDefaultFile\n", pData->strDomain);

	fprintf(fp, "echo \"Delete Old Nginx Custom Config File!\"\n");
	fprintf(fp, "rm -f $NginxCustomFile\n");
	fprintf(fp, "echo \"Download new custom.conf\"\n");
	fprintf(fp, "wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/bem/main/custom.conf\n");
	fprintf(fp, "echo \"Fill Custom Setting\"\n");
	fprintf(fp, "sed -i \"s/YourDomainName/%s/g\" $NginxCustomFile\n", pData->strDomain);
	fprintf(fp, "sed -i \"s/YourCachePath/%s/g\" $NginxCustomFile\n", pData->strCachePath);
	fprintf(fp, "sed -i \"s/YourPort/%s/g\" $NginxCustomFile\n", pData->strCachePort);

	fprintf(fp, "echo \"Download new config.json\"\n");
	fprintf(fp, "wget -O $DefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/config.json\n");
	fprintf(fp, "echo \"Fill Custom Setting\"\n");

	fprintf(fp, "sed -i \"s/YourPortKCP/%s/g\" $DefaultFile\n", pData->strKindPort);
	fprintf(fp, "sed -i \"s/YourIdKCP/%s/g\" $DefaultFile\n", pData->strKindID);

	fprintf(fp, "sed -i \"s/YourPathWS/%s/g\" $DefaultFile\n", pData->strCachePath);
	fprintf(fp, "sed -i \"s/YourPortWS/%s/g\" $DefaultFile\n", pData->strCachePort);
	fprintf(fp, "sed -i \"s/YourIdWS/%s/g\" $DefaultFile\n", pData->strCacheID);

	fclose(fp);
	return true;
}

void MakeBemrayShell(struct BemrayData* pData, bool bDepend, bool bModify)
{
	FILE* fp = NULL;
	fp = fopen("bemray.sh", "w");
	if (!fp) return;

	fprintf(fp, "#!/bin/bash\n");

	fprintf(fp, "bash %s\n", pData->strDependFile);
	fprintf(fp, "rm %s\n", pData->strDependFile);
	fprintf(fp, "bash %s\n", pData->strModifyFile);
	fprintf(fp, "rm %s\n", pData->strModifyFile);

	fclose(fp);
}

int main()
{
	struct BemrayData sData;
	if (!LoadData(&sData))
	{
		printf("Please Check bemray.conf!\n");
		SaveData(&sData, true);
		return -1;
	}

	printf("Enter Guid Mode:\n    [1]    create new\n    [others]    use old\n");
	if (GetInputNumber() == 1)
		SaveData(&sData, true);

	MakeBemrayShell(&sData, MakeDepend(&sData), MakeModify(&sData));
	return 1;
}
