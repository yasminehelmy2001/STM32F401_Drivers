#include <stdio.h>
#include <stdarg.h>
#include "time.h"

#define NO	0
#define YES	1

#define INFO	0
#define WARNING 1
#define ERROR 	2

/**
 * Choose YES/NO to print output to Console
 */
#define PRINT_TO_CONSOLE	YES

/**
 * Choose YES/NO to print output to File
 */
#define  PRINT_TO_FILE		YES

/**
 * Choose Severity Level
 * 1) INFO: Displays info, warnings and errors
 * 2) WARNING: Displays warnings and errors 
 * 3) ERROR: Displays errors only
 */
#define  SEVERITY_LEVEL 	WARNING

void printTimeFile(FILE *logFile) {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
	if (logFile == NULL) {
        perror("Error opening file");
    }
	else 
	{
        fprintf(logFile, "\n[%s] ", timestamp);
	}	
}

void printTimeConsole() {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
	printf("\n[%s] ", timestamp);
}


void CheckValues(FILE*logFile,int count, ...) {
    static int sum = 0;
    va_list args;
    va_start(args, count);
    
    // Sum up the values
    for (int i = 0; i < count; i++) {
        int val = va_arg(args, int);
		    
	if (PRINT_TO_FILE == YES) {
            if (SEVERITY_LEVEL == INFO)
			{
				if (val >= 0 && val <= 100) {
					printTimeFile(logFile);
					fprintf(logFile, "INFO: Price %d is acceptable\n", i + 1);
				}
			}
            
            if (SEVERITY_LEVEL == INFO || SEVERITY_LEVEL == WARNING)
			{
				if (val > 100) {
					printTimeFile(logFile);
					fprintf(logFile, "WARNING: Price %d exceeds maximum price\n", i + 1);
				}
			}
            if (SEVERITY_LEVEL == INFO || SEVERITY_LEVEL == WARNING || SEVERITY_LEVEL == ERROR)
			{
				if (val < 0) {
					printTimeFile(logFile);
					fprintf(logFile, "ERROR: Price %d is a negative value\n", i + 1);
				}
            }
    }
        
    if (PRINT_TO_CONSOLE == YES) {
            if (SEVERITY_LEVEL == INFO){
				if (val >= 0 && val <= 100) {
					printTimeConsole();
					printf("INFO: Price %d is acceptable\n", i + 1);
				}
			}
			if (SEVERITY_LEVEL == INFO || SEVERITY_LEVEL == WARNING)
			{
				if (val > 100) {
					printTimeConsole();
					printf("WARNING: Price %d exceeds maximum price\n", i + 1);
				}
			}
			if (SEVERITY_LEVEL == INFO || SEVERITY_LEVEL == WARNING || SEVERITY_LEVEL == ERROR)
			{            
				if (val < 0) {
				printTimeConsole();
                printf("ERROR: Price %d is a negative value\n", i + 1);
				}
			}
    }
	
}
    va_end(args);

}

int main() {

    FILE *logFile = fopen("time_log.txt", "a");
	int count=3;
    CheckValues(logFile,count,-5,200,30);
	fprintf(logFile,"\n");
    fclose(logFile);
	printf("\n");

    return 0;
}