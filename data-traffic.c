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
#include "include/data-traffic.h"

//typedef long long int llint;

int main(int argc, char *argv[]){
        int status;

        printf("\n\tdtraffic v.0.1\n\n");
        status =  data_byte_rate(argv[1],argv[2]);
        if (status)
                printf("error input!\n");
        else
                printf("\nTest Completed!\n\n");
        return 0;
}
