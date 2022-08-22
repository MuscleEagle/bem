#include <stdio.h>
#include <uuid/uuid.h>
 
int main()
{
	char strKCPID[128];
	char strWSID[128];
	uuid_t uuidKCP;
	uuid_t uuidWS;
	
	uuid_generate(uuidKCP);
	uuid_unparse(uuidKCP, strKCPID);
	
	uuid_generate(uuidWS);
	uuid_unparse(uuidWS, strWSID);
	
	char strProject[128];
	char strDomain[128];
	char strCachePath[128];
	
	int nKCPPort;
	int nCachePort;
	
	printf( "Enter Project Name[ExampleName]:");
	scanf("%s", strProject);
	
	printf( "Enter Domain Name[ExampleDomain.com]:");
	scanf("%s", strDomain);
	
	printf( "Enter Cache Path[ExamplePath]:");
	scanf("%s", strCachePath);
	
	printf( "Enter Cache Port[PortNumber]:");
	scanf("%d", &nCachePort);

	printf( "Enter KCP Port[PortNumber]:");
	scanf("%d", &nKCPPort);
	
	{
		char cInput = 'Y';
		char strDomainBash[128] = "domain.sh";
		char strProjectBash[128] = "projcet.sh";
		//install dependencies
		FILE *fp = NULL;
		fp = fopen("dependencies.sh", "w");
		
		fprintf(fp, "#!/bin/bash\n");
		printf( "Bash domain.sh?[Y/n]:");
		cInput = getch();
		if(cInput == 'Y' || cInput == 'y'){
			fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strDomainBash, strDomainBash);
			fprintf(fp, "sed -i \"s/YourDomain/%s/g\" %s\n", strDomain, strDomainBash);
			fprintf(fp, "bash domain.sh\n");
			fprintf(fp, "rm domain.sh\n");
			printf("domain.sh is on the way!\n");		
		}
		printf( "Bash project.sh?[Y/n]:");
		cInput = getch();
		if(cInput == 'Y' || cInput == 'y'){
			fprintf(fp, "wget -O %s https://raw.githubusercontent.com/MuscleEagle/bem/main/%s\n", strProjectBash, strProjectBash);
			fprintf(fp, "sed -i \"s/YourProject/%s/g\" %s\n", strProject, strProjectBash);
			fprintf(fp, "bash project.sh\n");
			fprintf(fp, "rm project.sh\n");
			printf("project.sh is on the way!\n");
		}
		fclose(fp);
	}

	{
		//modify config file
		FILE *fp = NULL;
		fp = fopen("modifyconfig.sh", "w");
 
		fprintf(fp, "#!/bin/bash\n");
		fprintf(fp, "NginxDefaultFile=/etc/nginx/conf.d/default.conf\n");
		fprintf(fp, "NginxDefaultFile=/etc/nginx/conf.d/custom.conf\n");
		fprintf(fp, "DefaultFile=/usr/local/etc/%s/config.json\n", strProject);
		
		fprintf(fp, "echo \"Delete Old Nginx Default Config File!\"\n");
		fprintf(fp, "rm -f $NginxDefaultFile\n");
		fprintf(fp, "echo \"Download new default.conf\"\n");
		fprintf(fp, "wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/new.conf\n");
		fprintf(fp, "echo \"Fill Custom Setting\"\n");
		fprintf(fp, "sed -i \"s/YourDomainName/%s/g\" $NginxDefaultFile\n", strDomain);
		
		fprintf(fp, "echo \"Delete Old Nginx Custom Config File!\"\n");
		fprintf(fp, "rm -f $NginxCustomFile\n");
		fprintf(fp, "echo \"Download new custom.conf\"\n");
		fprintf(fp, "wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/bem/main/custom.conf\n");
		fprintf(fp, "echo \"Fill Custom Setting\"\n");
		fprintf(fp, "sed -i \"s/YourDomainName/%s/g\" $NginxCustomFile\n", strDomain);
		fprintf(fp, "sed -i \"s/YourCachePath/%s/g\" $NginxCustomFile\n", strCachePath);
		fprintf(fp, "sed -i \"s/YourPort/%d/g\" $NginxCustomFile\n", nCachePort);
		
		fprintf(fp, "echo \"Download new config.json\"\n");
		fprintf(fp, "wget -O $DefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/config.json\n");
		fprintf(fp, "echo \"Fill Custom Setting\"\n");
   
		fprintf(fp, "sed -i \"s/YourPortKCP/%d/g\" $DefaultFile\n", nKCPPort);
		fprintf(fp, "sed -i \"s/YourIdKCP/%s/g\" $DefaultFile\n", strKCPID);
  
		fprintf(fp, "sed -i \"s/YourPathWS/%s/g\" $DefaultFile\n", strCachePath);
		fprintf(fp, "sed -i \"s/YourPortWS/%d/g\" $DefaultFile\n", nCachePort);
		fprintf(fp, "sed -i \"s/YourIdWS/%s/g\" $DefaultFile\n", strWSID);
  
		fclose(fp);
	}
	return 1;
}
