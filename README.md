# RemoteCTL
Just a simple example of combining Python Flask server and C client to achieve multi-arch remote keyboard

### A lil background story/expl:
This was created for my lazy !@# to control Chrome browser on my PC from my phone's terminal when I'm watching stuff from bed..
     ..Don't ask me anything..

### important_disclaimer.exe
###### ! This code is dysfunctional without proper configuration that fits your environment !

###### ! This code is not focused on security in any way, therefore should be NEVER used in production/public projects !

###### I'm not responsible for any data breaches or pwnage in case you use it w/o any security addition/tunning

  _.. it's a sittin-in-a-couch-with-a-bowl-of-popcorn code gdmt.._
  
  
```
Usage: './client MODE KB_STRING'

[MODES]:
 0 - KB_STRING - String Mode  (Write given string)
 1 - KB_COM    - Command Mode (Execute keyboard shortcut/command)

[DEFAULT COMMANDS]:

 'CTRLW'  - CTRL+W (Close Tab)
 'SPACE'  - Spacebar
 'ALTTAB' - ALT+TAB
 'YT'     - Open YouTube TV
 'F11'    - F11 (Fullscreen)
 'TAB'    - TAB
 'RLD'    - F5 (Refresh/Reload)
 'AUP'    - Arrow Up
 'VUP'    - (Arrow Up)*10 (Fire the volume all the way up)
 'LMB'    - Left Mouse Button Click

[RETURN CODES]:
 [kb_event_ok]      - Success
 [kb_null_req]      - KB_STRING is NULL
 [kb_type_error]    - Corrupted/Invalid KB_STRING
 [kb_unknown_event] - Unknown Keyboard Event [MODE 1]
 
[EXAMPLE USAGE]:
  {Toggle Fullscreen /F11/}: $ ./client 1 F11
  {Write 'hello'}:           $ ./client 0 hello
 ```
 
 ## How-to-compile-this-s@!t
###### Just a friendly reminder :) ..:
###### !!! YOU HAVE TO MAKE THE GODDAMN CHANGES TO THE CODE FIRST !!!
  ```
  $ git clone https://https://github.com/Volvo2v1/RemoteCTL
  
  $ cd RemoteCTL
  
  $ make
  ```
 ## How-to-run-this-s@!t
```  
Example IDGAF_ABOUT_SECURITY.exe Startup:
  Unix:
    $:    FLASK_APP=server.py flask run --host=192.168.0.1 --port=1337
  Windows:
    cmd:> set FLASK_APP=server.py
    cmd:> flask run --host=192.168.0.1 --port=1337

Example {ehm, ehm} "Secure" Startup:
  Unix:
    $:    FLASK_APP=server.py flask run --host=192.168.0.1 --port=1337 --cert cert.pem --key key.pem
  Windows:
    cmd:> set FLASK_APP=server.py
    cmd:> flask run --host=192.168.0.1 --port=1337 --cert cert.pem --key key.pem
 ```
 
 All the important stuff is documented/commented in each file. Focus on 'client.c' and 'server.py'
 
 
 Hey! Did I mention that you have to make THE GODDAMN CHANGES TO THE CODE???!?!!?!
