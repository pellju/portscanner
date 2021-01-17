#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
* TODO:
* - Enhance the user experience (i.e. ask the ports/IP from the user...)
* - Write the list of open ports to a text-file
* - Fix bugs
* - Suggestions? 
*/

int main() {
    char *ip = "127.0.0.1"; //The IP wanted to scan. Change that it'll be asked from the user!
    int s = socket(AF_INET, SOCK_STREAM, 0); //Creating the socket.
    
    if (s < 0){ //Testing if creating the socket has failed.
        printf("There was some kind of a problem when creating socket!\n");
        return -1;
    }

    struct sockaddr_in target_srv; //Creating the transport item. 
    target_srv.sin_family = AF_INET;

    int addr_test = inet_pton(AF_INET,ip,&target_srv.sin_addr); //Testing if the given IP-address is valid
    if (addr_test < 1) {
        printf("There was a problem with the given IP-address.\n");
        return -1;
    }

    for (int a=79; a<81; a++) { //For-loop for scanning the ports
        target_srv.sin_port = htons(a); //htons(a)!!

        int info = connect (s, (struct sockaddr *)&target_srv, sizeof(target_srv)); //Trying to establish the connection to the server.
        if (info == 0) { //If success, print that port is open.
            printf("Port %d is open!\n",a);
        }
   }
    printf("Ready!");
    return 0;
}