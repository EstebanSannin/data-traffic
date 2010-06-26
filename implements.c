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
#include <stdlib.h>
#include "include/implements.h"
#define NETWORK "/proc/net/dev"


long long int get_byte_received(char *interface){
        FILE *fp;
        char line[1024];
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true;
        int token2; 
        long long int number_byte;
        char *final_down;
        
        int one_token = 0;
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0; 
                   if (one_token == 0){     
                        while(tok != NULL){
                                if(token2){
                                        token2 = 0;
                                        number_byte = atoll(tok);
                                }
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);           //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if (equal_string == 0){
                                        token2 = 1;
                                        }else{
                                        char byte_down_temp[strlen(final_down)];      //array for temporary byte download
                                        strcpy(byte_down_temp, final_down);           //copy the string in to array byte_down
                                        i=1;                                          //for control
                                        j = 0;                                        //for control
                                        int dim = strlen(final_down);                 //computing the dimension for the array
                                        char byte_download[dim];
                                        for(j = 0; j<(dim-1); j++){                   //get byte clean
                                                one_token = 1;
                                                byte_download[j] = byte_down_temp[i];
                                                i++;
                                        }
                                        number_byte = atoll(byte_download);
                                        }
                                        }else{
                                                if(control_token !=1 ){
                                                number_byte = -1;
                                                }
                                        }
                tok = strtok(NULL, " ");
                }
                   }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
        return number_byte;
}     


long long int get_byte_trasmitted(char *interface){
        int loop = 9;
        FILE *fp;
        char line[1024];
        int iRet = 0;
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true; 
        long long int number_byte;
        char *final_down;
        int token2 = 0;
        
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0;      
                        while(tok != NULL){
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);             //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if(equal_string == 0){
                                                token2 = 1;
                                        }
                                }
                                if (token2 == 1){
                                        loop++;
                                        token2 = 0;
                                }
                                if (count_string_token == loop && control_token == 1){
                                        control_token = 0;
                                        number_byte = atoll(tok);
                                }
                tok = strtok(NULL, " ");
                }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
      return number_byte; 
}

int command(char *command){
	FILE *fp;
	char line[1024];
	int status = 0;
	fp = popen(command, "r");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		pclose(fp);
		status = 0;
	} else {
		status = -1;
	}
	return status;
}
void blink_led(){
	int i;
	for (i = 0; i<15; i++){
	command("ledctrl Ethernet On");
	command("ledctrl Ethernet Off");
	}
	
}

int data_byte_rate(char *interface, char *mode){
#define CLOCK 10

        int i,j;
        double array_rate[CLOCK];
        double total = 0;
        double rate_average;
                        printf("Download mode on interface: %s\n\n",interface);
                        for(;;){
                                long long int first = get_byte_received(interface);
                                long long int first_up = get_byte_trasmitted(interface);
				
				long long int first2 = get_byte_received("eth0");
				long long int first_up2 = get_byte_trasmitted("eth0");

				sleep(2);
                                
				long long int second2 = get_byte_received("eth0");
				long long int second_up2 = get_byte_trasmitted("eth0");
				
				long long int second = get_byte_received(interface);
				long long int second_up = get_byte_trasmitted(interface);
				
				long long int difference = second - first;
				long long int difference2 = second2 - first2;
				
				long long int difference_up = second_up - first_up;
				long long int difference_up2 = second_up2 - first_up2;
			
					
				printf("difference: %lld  difference2: %lld \n",difference,difference2);
				printf("difference up: %lld difference up2: %lld \n",difference_up, difference_up2);

				if (difference != 0 || difference2 != 0){
					command("ledctrl Ethernet FastBlinkContinues");

				}
				else{
					command("ledctrl Ethernet Off");
				}
					if (difference_up != 0 || difference_up2 !=0){
		      				command("ledctrl Ethernet FastBlinkContinues");				
					}
						else{
							command("ledctrl Ethernet Off");
						}
	}
}
