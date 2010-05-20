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
#include "include/parameters.h"

//if the parser terminat correctly return 1
int parse_line_parameters(int argc, char *argv[]){
        int status;
        //printf("argc: %d\n", argc);
        if (argc == 2){
                if(!strcmp(argv[1],"-h")){
                        usage();
                        status = 1;
                }else{
                        printf("\n  [ERROR]: Missing Parameter! \n\n");
                        usage();
                        status = 0;
                }
        }else{

        if (argc == 5){
                if(!strcmp(argv[1],"-i") && !strcmp(argv[3],"-m")){
                        status = 1;
                        //print("5\n");
                }else{
                        usage();
                        status = 0;
                        printf("\n  [ERROR]: Missing Parameter! \n\n");
                }
        
        }else{
                printf("\n  [ERROR]: Missing Parameter! \n\n");
                usage();
                status = 0;
        }
        }
        return status;

}
void usage(){
        fprintf(stderr,"  [USAGE]:  dtraffic -i [interface] -m [mode]\n"
                        "\t    -i  <interface> indicate the interface to calculate the traffic rate\n"
                        "\t    -m  <mode> indicate the mode for scanning interface: [ down | up ]\n"
                       "  [EXAMPLE]: dtraffic -i wlan0 -m down\n\n");
}

void version(){
        fprintf(stderr,"\n Data-Traffic v0.1 BETA\n"
                        " Date Build: may 2010\n"
                        " (C) 2010 - Stefano Viola\n\n");

}
