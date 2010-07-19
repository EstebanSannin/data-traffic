/*
 *
 * AUTHOR:   Stefano Viola (aka) Esteban Sannin
 * CONTACT:  stefanoviola[at]sannioglug[dot]org
 * HOME:     http://esteban.homelinux.org   
 *
 *      Licenze GLPv3
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      3 of the License, or (at your option) any later version.
 *
 */

#include <stdio.h>
#include <string.h>
#include "include/data-traffic.h"

int main(int argc, char *argv[]){
        int status=1;
        version();   //print the information of software

        int parse = parse_line_parameters(argc, argv);
        
	if(parse == 2){         
		//if (!strcmp(argv[5],"-n"))
		//	printf("CLOCK: %d\n",argv[6]);
		status = data_byte_rate(argv[2],argv[4]);
		if (status == 1){
       			printf("\n  [ERROR]: Mode Wrong! \n\n");
       			usage();
		}
	}else{            
  		return 1;
	}
	return 0;
}

