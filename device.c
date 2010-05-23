#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NETWORK "/proc/net/dev"

//se tutto va a buon fine ritorna 0 altrimenti -1
int device(char *input_interface, int list){
        FILE *fp;
        char line[1024];
        char *network_interface;
        char *token_string;
        int i = 0,tot,x;
        char array_interface[20][40];
        char *temp;
        int true_interface = 0;
        int status_interface = -1;
        
        //ottengo tutte le interfacce di rete disponibili
        fp = fopen(FILE_NETWORK, "r");
        if(fp != NULL){
                while (fgets(line, sizeof(line), fp)){
                        token_string = strtok(line," ");
                        while (token_string != NULL){
                                network_interface = strstr(token_string,":");
                                if(network_interface!=NULL){
                                        temp = strtok(token_string,":");
                                        strcpy(array_interface[i],temp);  //array_interface content all interface
                                        tot = i++;
                                }
                                token_string = strtok(NULL, " ");
                        }
                }
        } 

        //controllo se e' stato richiamato l'help - per richiamarlo passare 1      
        if(list == 1){
                int j;
                for(j=0; j<=tot; j++){
                        printf("%s\n",array_interface[j]);
                }
                status_interface = 0;
        }else{
                //controllo se l'interfaccia di rete passata in input e' corretta
                for(x=0; x<=tot; x++){
                        true_interface = strcmp(array_interface[x],input_interface);
                        //printf("true_interface: %d\n",true_interface);
                        if(true_interface == 0)
                        status_interface = 0;
                }
                //printf("trovata: %d\n",control_interface);
        }
               return status_interface;   
}

/*
int main(int argc, char *argv[]){
                int pippo = device(argv[1],1);
            printf("status: %d\n",pippo);
              return 0;
}*/

