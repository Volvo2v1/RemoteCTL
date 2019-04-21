/*
MIT License

Copyright (c) 2019 Volvo2v1

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <curl/curl.h>

int log_update = -1;

void cleanup() { /* Display a message when the log file is updated. */
    if (log_update == 1) {
        printf("\033[38;5;202m[\033[0;32m!!\033[38;5;202m] Log file has been updated!\n");
    }
}

void write_err(const char* message, ...) {
    va_list args;
    char* newline = "\n";
    
    va_start(args, message);  
    FILE *errfp = fopen("rkb_client.log", "ab");  /* Name of the log file */
    
    time_t now;
    time(&now);

    char tt_time[256];

    sprintf(tt_time, ctime(&now));
        int time_len = strlen(tt_time);
        if (tt_time[time_len-1] == '\n') {
                tt_time[time_len-3] = 0;
    }
    
    fprintf(errfp, "[%s]: ", tt_time);
    vfprintf(errfp,message,args);
    fprintf(errfp,newline);
    
    va_end(args);
    fclose(errfp);

    log_update = 1;

}