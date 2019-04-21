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

#include "sysvars.h"
#include "flowctl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

/* [*1 DPs for additional stuff, i.e. using argv[] to provide host and port, in case you wanna control > 1 server, or just don't want the IP:PORT to be hard-coded]
char **host;
char **port;
*/

int **KB_MODE;
char **KB_STRING;

int do_connect(void);

int main(int argc, char *argv[])
{
	if (argc == 3) {
		if (strncmp(argv[1], "0", sizeof(argv[1])) != 0 && strncmp(argv[1], "1", sizeof(argv[1])) != 0) {
            printf("\033[1;38;5;202m[!!] \033[0;38;5;208mUsing default mode: '0 - KB_STRING'\n");
            KB_MODE = 0;
        } else {KB_MODE = atoi(argv[1]);}
		KB_STRING = argv[2];
        printf("\033[1;38;5;198m[MODE]: \033[0;38;5;198m%d\n\033[1;38;5;200m[KB_STR]: \033[0;38;5;200m'%s'\033[0m\n", KB_MODE, KB_STRING);
    } else if (argc == 2) {
        if (strncmp(argv[1], "--help", strlen("--help")) == 0) {
            printf("\033[1;38;5;9mUsage: \033[0;38;5;9m'%s MODE KB_STRING'\n", argv[0]);
            printf("\n\033[38;5;208m[\033[0;32mMODES\033[38;5;208m]:\n");
            printf(" \033[38;5;198m0 \033[38;5;208m- \033[38;5;1mKB_STRING - \033[38;5;34mString Mode\033[38;5;208m  (Write given string)\n");
            printf(" \033[38;5;198m1 \033[38;5;208m- \033[38;5;21mKB_COM    \033[38;5;208m- \033[38;5;91mCommand Mode\033[38;5;208m (Execute keyboard shortcut/command)\n");
            printf("\n\033[38;5;208m[\033[0;32mDEFAULT COMMANDS\033[38;5;208m]:\n");
            printf("\n \033[38;5;208m'\033[38;5;197mCTRLW\033[38;5;208m'  - CTRL+W (Close Tab)\n \033[38;5;208m'\033[38;5;197mSPACE\033[38;5;208m'  - Spacebar\n \033[38;5;208m'\033[38;5;197mALTTAB\033[38;5;208m' - ALT+TAB\n '\033[0;31mYT\033[38;5;208m'     - Open YouTube TV\n \033[38;5;208m'\033[38;5;197mF11\033[38;5;208m'    - F11 (Fullscreen)\n \033[38;5;208m'\033[38;5;197mTAB\033[38;5;208m'    - TAB\n \033[38;5;208m'\033[38;5;197mRLD\033[38;5;208m'    - Refresh/Reload [F5]\n");
            printf("\n\033[38;5;208m[\033[0;32mRETURN CODES\033[38;5;208m]:\n [\033[38;5;51mkb_event_ok\033[38;5;208m]      - Success\n [\033[38;5;51mkb_null_req\033[38;5;208m]      - KB_STRING is NULL\n [\033[38;5;51mkb_type_error\033[38;5;208m]    - Corrupted/Invalid KB_STRING\n [\033[38;5;51mkb_unknown_event\033[38;5;208m] - Unknown Keyboard Event [MODE 1]\n");
            printf("\n\033[38;5;214mhttps://github.com/Volvo2v1\033[0m\n");
            printf("\033[0;31mhttps://youtube.com/Volvo2v1\033[0m\n");
            return 0;
        }
        if (strlen(argv[1]) >= 1) {
            KB_MODE = 0;
            printf("\033[1;38;5;202m[!!] \033[0;38;5;208mUsing default mode: '0 - KB_STRING'\n");
            KB_STRING = argv[1];
            printf("\033[1;38;5;198m[MODE]: \033[0;38;5;198m%d\n\033[1;38;5;200m[KB_STR]: \033[0;38;5;200m'%s'\033[0m\n", KB_MODE, KB_STRING);
        }
    } else {
        printf("\033[1;38;5;9mUsage: \033[0;38;5;9m'%s MODE KB_STRING'\n", argv[0]);
        printf("\033[1;38;5;203m'%s --help' \033[0;38;5;203mto display help\n", argv[0]);
		return 1;
	}
    if (do_connect() != 0); {
            cleanup();
            return 1;
        }
    cleanup();
	return 0;
}


int do_connect(void) {
    CURL *curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    curl = curl_easy_init();
    if(curl) {
        /*
        Authentication example:
            char *__token = "THIS IS A TOKEN TO USE WITH FLASK-HTTPAUTH TOKEN AUTHORIZATION";

            For more 1337, do some simple encoding, e.g. Client -> XOR the token with a key and convert the XOR'd output to octal
                                                         Server -> Decode octal input and XOR it with THE key.

                            .. I'm sure you can figure something out o_O

        
            EXAMPLE:
        */
        /*"Authorization: Token EXAMPLE_INSECURE_TOKEN"
        char *__token = "Authorization: Token EXAMPLE_INSECURE_TOKEN";    // 'EXAMPLE_INSECURE_TOKEN' is the actual token (password), keep in mind that you have to keep the 'Authorization: Token' part in the cURL header
        some_encrypt_func(__token, "PASSWORD");                           // Imitating some encoding mechanism
        str_to_octal(__token);                                            // Converting the encoded token to octal, so you don't have to deal with tokens like: '�Ÿ§�È-��×í�†’��ÀpŠ��'
        headers = curl_slist_append(headers, __token);                    // Append the token to the cURL headers
        */
        char __kbBuff[4096]; /* This will hold the cURL headers i.e. Authorization Token */

        snprintf(__kbBuff, (sizeof(__kbBuff)-8), "kb_str=%s&kb_mod=%d", KB_STRING, KB_MODE);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, __kbBuff);

        
        struct string s;
        init_string(&s);
        curl_easy_setopt(curl, CURLOPT_URL, "https://192.168.0.1:1337/kb_handler");  /* [*1] THIS IS THE HOST IP AND PORT .. i.e. server.py dest */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // cURL Insecure Mode ¯\_(ツ)_/¯     *Default 1L* - secure
        /*curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); - you may need this, if you're planning on using self-signed certs */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);         // Timeout
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);
        if (strncmp(s.ptr,"kb_event_ok",strlen("kb_event_ok")+1) == 0) { /* SUCCESS */
            free(s.ptr);
            curl_easy_cleanup(curl);
            printf("\033[1;38;5;208m[\033[1;32mOK\033[1;38;5;208m]: \033[0;38;5;208mSUCCESS\n");
            return 0;
        } else if (strncmp(s.ptr, "kb_unknown_event", strlen("kb_unknown_event")+1) == 0) { /* FAIL: UNKNOWN COMMAND */
            free(s.ptr);
            curl_easy_cleanup(curl);
            printf("\033[1;31m[ERR]: \033[0;31mUnknown Command!\n");
            write_err("[ERR]: Server received unknown keyboard event!");
            return 1;
        } else if (CURLE_OPERATION_TIMEDOUT == res) { /* FAIL: TIMEOUT */
            free(s.ptr);
            curl_easy_cleanup(curl);
            printf("\033[1;31m[ERR]: \033[0;31mTimeout!");
            return 2;
        } if (res != CURLE_OK) { /* FAIL: EXCEPTION WILL BE WRITTEN TO THE LOG FILE */
            write_err("[ERR]: EXCEPTION: [%s]", curl_easy_strerror(res));
            printf("\033[1;31m[ERR]: \033[0;31mInfo written to log file!\n");
            return 1;
        } else { /* FAIL: EXCEPTION WILL BE WRITTEN TO THE LOG FILE */
            write_err("[ERR]: [%s]", s.ptr);
            printf("\033[1;31m[ERR]: \033[0;31mInfo written to log file!\n");
            free(s.ptr);
            curl_easy_cleanup(curl);
            return 1;
        }
    }
}