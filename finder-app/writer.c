#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<syslog.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Error: Two arguments required\nUsage: %s <writefile> <writestr>\n", argv[0]);
        return 1;
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

    // Setup syslog logging for utility using the LOG_USER facility.
    openlog(NULL, 0, LOG_USER);
    
    // Use the syslog capability to write a message “Writing <string> to <file>” 
    // where <string> is the text string written to file (second argument) 
    // and <file> is the file created by the script.
    // This should be written with LOG_DEBUG level.
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Open file for writing.
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        syslog(LOG_ERR, "Error opening file %s", writefile);
        closelog();

        return 1;
    }

    // Write string to file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if(bytes_written == -1){
        syslog(LOG_ERR, "Error writing to file %s", writefile);
        close(fd);

        closelog();
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}