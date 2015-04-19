#include "file_ops.h"
#include "mem_ops.h"
#include "string_ops.h"
#include "tamper.h"

// write line in file
void WriteFile(char *file,char *str)
{
	FILE *arq;
 
	arq=fopen(file,"a"); 

	if ( arq == NULL ) 
	{
//		fclose(arq);
		DEBUG("error in WriteFile() %s",file); 
		exit(1);
	}

	fprintf(arq,"%s\n",str); 

	if( fclose(arq) == EOF )
	{
		DEBUG("error in Write() file %s",file);
		exit(1);
	}
	arq=NULL;
 
}


//read lines of file
void convert_payload(char * NameFile,char *output, char *tamper)
{
	FILE * arq;

	arq = fopen(NameFile, "r");
// todo think implement fcntl() ,toctou mitigation...
	if( arq == NULL )
	{
//		fclose(arq);
		DEBUG("error in to open() file"); 	 
		exit(1);
	}

	char line[4096];

	while( fgets(line,4095,arq) )  
	{
			
		if(strstr(tamper,"encode64"))
		{
			char *newline=encode64(line,strlen(line)-1);
			WriteFile(output,newline);
			xfree((void **)&newline);
		}

		if(strstr(tamper,"randcase"))
		{
			char *newline=rand_case(line);	
			WriteFile(output,newline);
		
			xfree((void **)&newline);
		}


		if(strstr(tamper,"urlencode"))
		{
			char *newline=urlencode(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		}

		if(strstr(tamper,"double_urlencode"))
		{
			char *newline=double_urlencode(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		}

		if(strstr(tamper,"spaces2comment"))
		{
			char *newline=spaces2comment(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		}

		if(strstr(tamper,"unmagicquote"))
		{
			char *newline=unmagicquote(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		}


		if(strstr(tamper,"apostrophe2nullencode"))
		{
			char *newline=apostrophe2nullencode(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		}

		if(strstr(tamper,"rand_comment"))
		{
			char *newline=rand_comment(line);	
			WriteFile(output,newline);

			xfree((void **)&newline);
		
		}



		if(strstr(tamper,"rand_space"))
		{
			char *newline=rand_space(line);
			WriteFile(output,newline);

			xfree((void **)&newline);
		}
		

	}
 
	if( fclose(arq) == EOF )
	{
		DEBUG("Error in close() file %s",NameFile);
		exit(1);
	}
	arq=NULL;

/*	if(lineBuffer != NULL)
	{
		free(lineBuffer);
	}
*/

}


// return size of bytes on file , same to unix cmd "du -b file"
long FileSize(const char *file)
{
	long ret;
	FILE *arq; 

        arq = fopen(file, "r");

	if ( arq == NULL )
	{
	//	fclose(arq);
		DEBUG("error in file");
		return 0;
	}

	fseek(arq, 0, SEEK_END);
	ret = ftell(arq);

	if( fclose(arq) == EOF )
	{
  		DEBUG("error in close() file %s",file);
		exit(1);
	}
	arq=NULL;

	return ret;
}



// returns random line from file
char *Random_linefile(char * namefile)
{
	FILE *f;
	int nLines = 0;
	static char line[1024];   // think recv space to nullbyte 1023
	int randLine=0,i=0;
 
	entropy_clock();  // i set entropy seed here

	memset(line,0x0,1023);

	f = fopen(namefile, "r");

	if ( f == NULL )
	{
//		fclose(f);
		DEBUG("error in file");
		exit(1);
	}

	while ( !feof(f) )
	{
		if(fgets(line, 1023, f)!=NULL) 
			nLines++;
	}

	randLine = rand() % nLines;

	fseek(f, 0, SEEK_SET);

	while (!feof(f) && i <= randLine)
		if(fgets(line, 1023, f)!=NULL)
			i++;
				
	if( fclose(f) == EOF )
	{
  		DEBUG("error in close() file %s",namefile);
		exit(1);
	}

	f=NULL;

    	return line;
}
