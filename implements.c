/*
 *
 * AUTHOR:   Stefano Viola (aka) Esteban Sannin
 * CONTACT:  stefanoviola@sannioglug.org
 * HOME:     http://esteban.homelinux.org
 * LICENSE:  GPLv3
 *
 *
 */

#include <stdio.h>
#include <string.h>


int get_byte_received(char *interface){

#define NETWORK "/proc/net/dev"

        FILE *fp;
        char line[1024];
        int iRet = 0;
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true; 
        long long int number_byte;
        //char *interface = "wlan0";
        char *final_down;
       

        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        //char *s = "wlan";
                        tok = strtok(line," ");
                        count_string_token = 0;      
                        
                        while(tok != NULL){
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);             //search the interface in the string
                                        final_down = strchr(tok,':');                   //cut the byte download oh the interface
                                        char byte_down_temp[strlen(final_down)];        //array for temporary byte download
                                        strcpy(byte_down_temp, final_down);             //copy the string in to array byte_down
                                        
                                        i=1;                                            //for control
                                        j = 0;                                          //for control
                                        int dim = strlen(final_down);                   //computing the dimension for the array
                                        char byte_download[dim];
                                        
                                        for(j = 0; j<(dim-1); j++){                     //get byte clean
                                                byte_download[j] = byte_down_temp[i];
                                                i++;
                                        }
                                        number_byte = atoll(byte_download);
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


int get_byte_trasmitted(char *interface){

#define NETWORK "/proc/net/dev"

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
                                        }
                                if (count_string_token == 9 && control_token == 1){
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

data_byte_rate(char *interface, char *mode){
#define CLOCK 10

        int i,j;
        double array_rate[CLOCK];
        double total, rate_average;
if(strcmp(mode,"down")==0){
        printf("Download mode on interface: %s\n\n",interface);
        for(i = 0; i<CLOCK ; i++){
        long long int first = get_byte_received(interface);
        sleep(1);
        long long int second = get_byte_received(interface);
        long long int difference = second - first;
        double rate_down = difference/1024.00;
        array_rate[i] = rate_down;
        printf("Reception Rate: %f    kB/sec\n", rate_down);
        }
        
        for(i = 0; i<CLOCK; i++){
        total +=array_rate[i];
        }
        rate_average = total/CLOCK;
        printf("\nAverange Reception-rate:  %f kB/sec\n",rate_average);
}else if (strcmp(mode,"up")==0){
        printf("Upload mode on interface: %s\n\n",interface);
        for(i = 0; i<CLOCK ; i++){
                long long int first_up = get_byte_trasmitted(interface);
                sleep(1);
                long long int second_up = get_byte_trasmitted(interface);
                long long int difference_up = second_up - first_up;
                double rate_down = difference_up/1024.00;
                array_rate[i] = rate_down;
                printf("Trasmission Rate: %f    kB/sec\n", rate_down);
        }
        for(i = 0; i<CLOCK; i++){
                total +=array_rate[i];
        }
        rate_average = total/CLOCK;
        printf("\nAverange up-rate:  %f kB/sec\n",rate_average);
}else{
        //input mode error        
        return 1;
        }
return 0;
}

