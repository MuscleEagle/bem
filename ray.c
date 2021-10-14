#include <stdio.h>
#include <uuid/uuid.h>
 
int main()
{
   uuid_t uuidKCP;
   uuid_t uuidWS;
   char strKCPID[128];
   char strWSID[128];
   
   uuid_generate(uuidKCP);
   uuid_unparse(uuidKCP, strKCPID);
   
   uuid_generate(uuidWS);
   uuid_unparse(uuidWS, strWSID);
   
   char strKCP[128];
   char strWS[128];
   int iKCP;
   int iWS;
   
   printf( "Enter KCP Info[Path Port]:");
   scanf("%s %d", strKCP, &iKCP);
   
   printf( "Enter WS Info[Path Port]:");
   scanf("%s %d", strWS, &iWS);
   
   FILE *fp = NULL;
   fp = fopen("ray.sh", "w");
 
   fprintf(fp, "#!/bin/bash\n");
   fprintf(fp, "DefaultFile=/usr/local/etc/%s/config.json", strKCP);
   fprintf(fp, "wget -O $DefaultFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/config.json\n");
   
   fprintf(fp, "sed -i \"s/YourPortKCP/%d/g\" $DefaultFile\n", iKCP);
   fprintf(fp, "sed -i \"s/YourIdKCP/%s/g\" $DefaultFile\n", strKCPID);
  
   fprintf(fp, "sed -i \"s/YourPathWS/%s/g\" $DefaultFile\n", strWS);
   fprintf(fp, "sed -i \"s/YourPortWS/%d/g\" $DefaultFile\n", iWS);
   fprintf(fp, "sed -i \"s/YourIdWS/%s/g\" $DefaultFile\n", strWSID);
  
   fclose(fp);
   return 1;
}
