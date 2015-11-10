/*
Author:Antonio Costa aka " Cooler_ "
contact: coolerlair[at]gmail[dot]com


    Copyright (C) 2015 payload mask authors,
    
    This file is part of payloadmask
    
    Payload mask is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    payload mask is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

$ make
$./payloadmask


*/
#include <stdio.h> 
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include "mem_ops.h"
#include "file_ops.h"
#include "validate.h"

// colors macro
#define RED "\033[22;31m"
#define YELLOW "\033[01;33m"
#define CYAN "\033[22;36m"
#define GREEN "\033[22;32m"
#define LAST "\033[0m"

void init_banner_mask()
{
 puts(
 GREEN
   "\n   ...:::_PAYLOAD:MASK_:::...    v0.1        \n"                      
   "     Just another payload lists editor to bypass WAF              \n\n" 
 YELLOW
 LAST
 "--payload :	Payload list to make edit\n\n"
 "--out :	Output of new payload list\n\n"
 "--tamper : Payload tamper to try bypass filters\n   Choice one option :\n    encode64 : to encode payload to 64 base \n    randcase : to use lower and upper case random position in string\n"
 "    urlencode :  converts characters into a format that can be transmitted over the Internet, percent encoding\n    double_urlencode : converts payload two times with urlencode\n"
"    spaces2comment:  change spaces ' ' to comment '/**/'\n    unmagicquote: change apostrophe to a multi-byte  \n"
"    apostrophe2nullencode: change apostrophe to illegal double unicode counterpart\n    rand_comment: to use random comment '/**/' position in payload string\n"
"    rand_space: write random ' ' blank spaces\n"
"    replace_keywords: replace especial words, SELECT to SELselectECT etc...\n"
YELLOW
YELLOW
YELLOW
LAST
"\n  Example: ./payloadmask -p payloads/xss.txt -o test_new.txt -t randcase\n...\n"
 "Coded by Cooler_\n coolerlair[at]gmail[dot]com\n "
 );
 puts(LAST);
}

static struct option long_options[] =
{
	{"payload", required_argument, NULL, 'p'},
	{"out", required_argument, NULL, 'o'},	
	{"tamper", required_argument, NULL, 't'},
	{NULL, 0, NULL, 0}
};


int 
main(int argc, char ** argv)
{
 char c;
 char *pack[4]; 
 short y=3;

 	no_write_coredump ();
 	load_signal_alarm ();


	if(argc < 3) 
	{
		init_banner_mask();
		DEBUG(" Need more arguments.\n");
		exit(0);
	}
 

 	while(y>-1)
 	{
  		pack[y]=NULL;
  		y--;
 	}

 	opterr = 0;

 	while((c = getopt_long(argc, argv, "p:o:t:",long_options,NULL)) != -1)
  		switch(c) 
  		{
// payload list
			case 'p':
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[0] = optarg;
    					printf("Payloads: %s \n",optarg);
    					
				} else {
					DEBUG("Error \nArgument Payloads is very large  \n");
					exit(1);
				}
				break;

// output
			case 'o':
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[1] = optarg;
    					printf("Custom output: %s \n",optarg);
    					
				} else {
					DEBUG("Error \nArgument output is very large  \n");
					exit(1);
				}
				break;

   			case 't':    				
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[2] = optarg;
    					printf("Tamper type: %s \n",optarg);
    				} else {
			
					DEBUG("Error \nArgument tamper type is very large  \n");
					exit(1);
				}
				break;

   			case '?':
    				if(optopt == 'p' || optopt == 'o' || optopt == 't') 
    				{
     					init_banner_mask();
     					puts(RED);
     					DEBUG("Option -%c requires an argument.\n", optopt); 
     					puts(LAST);
     					exit(1);
    				}
				break;
  		}

	if(pack[1]==NULL)
	{
		DEBUG("need use argument output file");
		exit(1);
 	}


	if(pack[0]==NULL)
	{
		DEBUG("need use argument payload");
		exit(1);
 	}




	if(pack[2]==NULL)
	{
		DEBUG("need use argument tamper");
		exit(1);

	}

	convert_payload(pack[0],pack[1],pack[2]);	
	
	fprintf(stdout,"%s Look file %s%s\n%s",RED,GREEN,pack[1],LAST);
	
 	exit(0);
}

