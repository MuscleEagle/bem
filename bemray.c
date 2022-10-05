//#define BemrayHand

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
	//Config File Name
	char strConfigFile[128];
	//Bash Domain Shell
	char strDependFile[128];
	//Modify Nginx Shell
	char strModifyFile[128];
	//Is Config File Ready?
	char strUseFile[128];
	//Author
	char strAuthor[128];
	//Project Name
	char strProject[128];
	//Domain Name
	char strDomain[128];

	//LessXtcpID
	char strLessXtcpID[128];

	//Trojan
	char strTrojanPort[128];
	char strTrojanPass[128];

	//LessWs
	char strLessWsID[128];
	char strLessWsPath[128];
	char strLessWsPort[128];

	//MessTcp
	char strMessTcpID[128];
	char strMessTcpPath[128];
	char strMessTcpPort[128];

	//MessWs
	char strMessWsID[128];
	char strMessWsPath[128];
	char strMessWsPort[128];

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
	//Head
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
	if (strcmp("Author", pLeft) == 0)
	{
		strcpy(pData->strAuthor, pRight);
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
	//Data
	if (strcmp("LessXtcpID", pLeft) == 0)
	{
		strcpy(pData->strLessXtcpID, pRight);
		return true;
	}
	if (strcmp("TrojanPort", pLeft) == 0)
	{
		strcpy(pData->strTrojanPort, pRight);
		return true;
	}
	if (strcmp("TrojanPass", pLeft) == 0)
	{
		strcpy(pData->strTrojanPass, pRight);
		return true;
	}
	if (strcmp("LessWsID", pLeft) == 0)
	{
		strcpy(pData->strLessWsID, pRight);
		return true;
	}
	if (strcmp("LessWsPath", pLeft) == 0)
	{
		strcpy(pData->strLessWsPath, pRight);
		return true;
	}
	if (strcmp("LessWsPort", pLeft) == 0)
	{
		strcpy(pData->strLessWsPort, pRight);
		return true;
	}
	if (strcmp("MessTcpID", pLeft) == 0)
	{
		strcpy(pData->strMessTcpID, pRight);
		return true;
	}
	if (strcmp("MessTcpPath", pLeft) == 0)
	{
		strcpy(pData->strMessTcpPath, pRight);
		return true;
	}
	if (strcmp("MessTcpPort", pLeft) == 0)
	{
		strcpy(pData->strMessTcpPort, pRight);
		return true;
	}

	if (strcmp("MessWsID", pLeft) == 0)
	{
		strcpy(pData->strMessWsID, pRight);
		return true;
	}
	if (strcmp("MessWsPath", pLeft) == 0)
	{
		strcpy(pData->strMessWsPath, pRight);
		return true;
	}
	if (strcmp("MessWsPort", pLeft) == 0)
	{
		strcpy(pData->strMessWsPort, pRight);
		return true;
	}
	return false;
}

void makeGuid(struct BemrayData* pData)
{
#ifdef BemrayHand
	strcpy(pData->strLessXtcpID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strLessWsID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strMessTcpID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strMessWsID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
#else
	uuid_t uuidCache;
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strLessXtcpID);
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strLessWsID);
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strMessTcpID);
	uuid_generate(uuidCache);
	uuid_unparse(uuidCache, pData->strMessWsID);
#endif
}

void initData(struct BemrayData* pData)
{
	strcpy(pData->strConfigFile, "bemray.conf");
	strcpy(pData->strDependFile, "depend.sh");
	strcpy(pData->strModifyFile, "modify.sh");
	strcpy(pData->strUseFile, "false");
	strcpy(pData->strAuthor, "v2fly");
	strcpy(pData->strProject, "bemray");
	strcpy(pData->strDomain, "bemray.com");

	strcpy(pData->strLessXtcpID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strTrojanPort, "1310");
	strcpy(pData->strTrojanPass, "12345");
	strcpy(pData->strLessWsID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strLessWsPath, "websocket");
	strcpy(pData->strLessWsPort, "1234");
	strcpy(pData->strMessTcpID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strMessTcpPath, "vmesstcp");
	strcpy(pData->strMessTcpPort, "2345");
	strcpy(pData->strMessWsID, "fb2b85b3-cdde-4a7c-8202-33f465799c67");
	strcpy(pData->strMessWsPath, "vmessws");
	strcpy(pData->strMessWsPort, "3456");

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
	fprintf(fp, "Author=%s\n", pData->strAuthor);
	fprintf(fp, "Project=%s\n", pData->strProject);
	fprintf(fp, "Domain=%s\n", pData->strDomain);

	fprintf(fp, "LessXtcpID=%s\n", pData->strLessXtcpID);
	fprintf(fp, "TrojanPort=%s\n", pData->strTrojanPort);
	fprintf(fp, "TrojanPass=%s\n", pData->strTrojanPass);
	fprintf(fp, "LessWsID=%s\n", pData->strLessWsID);
	fprintf(fp, "LessWsPath=%s\n", pData->strLessWsPath);
	fprintf(fp, "LessWsPort=%s\n", pData->strLessWsPort);
	fprintf(fp, "MessTcpID=%s\n", pData->strMessTcpID);
	fprintf(fp, "MessTcpPath=%s\n", pData->strMessTcpPath);
	fprintf(fp, "MessTcpPort=%s\n", pData->strMessTcpPort);
	fprintf(fp, "MessWsID=%s\n", pData->strMessWsID);
	fprintf(fp, "MessWsPath=%s\n", pData->strMessWsPath);
	fprintf(fp, "MessWsPort=%s\n", pData->strMessWsPort);

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
	printf("Enter Work Mode:\n");
	printf("1.domain\n");
	printf("2.project\n");
	printf("3.both\n");
	printf("0.neither\n");
	int nInput = GetInputNumber();

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
		fprintf(fp, "sed -i \"s/DomainName/%s/g\" %s\n", pData->strDomain, strDomainBash);
		fprintf(fp, "bash domain.sh\n");
		fprintf(fp, "rm domain.sh\n");
		printf("domain.sh is on the way!\n");
	}
	if (nInput == 2 || nInput == 3)
	{
		fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strProjectBash, strProjectBash);
		fprintf(fp, "sed -i \"s/ProjectName/%s/g\" %s\n", pData->strProject, strProjectBash);
		fprintf(fp, "sed -i \"s/AuthorName/%s/g\" %s\n", pData->strAuthor, strProjectBash);
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
	fprintf(fp, "sed -i \"s/DomainName/%s/g\" $NginxDefaultFile\n", pData->strDomain);

	fprintf(fp, "echo \"Delete Old Nginx Custom Config File!\"\n");
	fprintf(fp, "rm -f $NginxCustomFile\n");
	fprintf(fp, "echo \"Download new custom.conf\"\n");
	fprintf(fp, "wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/bem/main/custom.conf\n");
	fprintf(fp, "echo \"Fill Custom Setting\"\n");
	fprintf(fp, "sed -i \"s/DomainName/%s/g\" $NginxCustomFile\n", pData->strDomain);
	fprintf(fp, "sed -i \"s/LessWsPath/%s/g\" $NginxCustomFile\n", pData->strLessWsPath);
	fprintf(fp, "sed -i \"s/LessWsPort/%s/g\" $NginxCustomFile\n", pData->strLessWsPort);
	fprintf(fp, "sed -i \"s/MessTcpPath/%s/g\" $NginxCustomFile\n", pData->strMessTcpPath);
	fprintf(fp, "sed -i \"s/MessTcpPort/%s/g\" $NginxCustomFile\n", pData->strMessTcpPort);
	fprintf(fp, "sed -i \"s/MessWsPath/%s/g\" $NginxCustomFile\n", pData->strMessWsPath);
	fprintf(fp, "sed -i \"s/MessWsPort/%s/g\" $NginxCustomFile\n", pData->strMessWsPort);

	fprintf(fp, "echo \"Download new config.json\"\n");
	fprintf(fp, "wget -O $DefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/config.json\n");
	fprintf(fp, "echo \"Fill Custom Setting\"\n");

	fprintf(fp, "sed -i \"s/ProjectName/%s/g\" $DefaultFile\n", pData->strProject);
	fprintf(fp, "sed -i \"s/DomainName/%s/g\" $DefaultFile\n", pData->strDomain);

	fprintf(fp, "sed -i \"s/LessXtcpID/%s/g\" $DefaultFile\n", pData->strLessXtcpID);
	fprintf(fp, "sed -i \"s/TrojanPort/%s/g\" $DefaultFile\n", pData->strTrojanPort);
	fprintf(fp, "sed -i \"s/TrojanPass/%s/g\" $DefaultFile\n", pData->strTrojanPass);
	fprintf(fp, "sed -i \"s/LessWsID/%s/g\" $DefaultFile\n", pData->strLessWsID);
	fprintf(fp, "sed -i \"s/LessWsPath/%s/g\" $DefaultFile\n", pData->strLessWsPath);
	fprintf(fp, "sed -i \"s/LessWsPort/%s/g\" $DefaultFile\n", pData->strLessWsPort);
	fprintf(fp, "sed -i \"s/MessTcpID/%s/g\" $DefaultFile\n", pData->strMessTcpID);
	fprintf(fp, "sed -i \"s/MessTcpPath/%s/g\" $DefaultFile\n", pData->strMessTcpPath);
	fprintf(fp, "sed -i \"s/MessTcpPort/%s/g\" $DefaultFile\n", pData->strMessTcpPort);
	fprintf(fp, "sed -i \"s/MessWsID/%s/g\" $DefaultFile\n", pData->strMessWsID);
	fprintf(fp, "sed -i \"s/MessWsPath/%s/g\" $DefaultFile\n", pData->strMessWsPath);
	fprintf(fp, "sed -i \"s/MessWsPort/%s/g\" $DefaultFile\n", pData->strMessWsPort);

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
