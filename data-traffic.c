/*
 * Author: Stefano Viola
 * Licenze GLPv3
 *
 */
#include <stdio.h>
#include "data-traffic.h"

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
