'''
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

''''''
 Example IDGAF_ABOUT_SECURITY.exe Startup:
  Unix:
	$:    FLASK_APP=server.py flask run --host=192.168.0.1 --port=1337
  Windows:
  	cmd:> set FLASK_APP=server.py
  	cmd:> flask run --host=192.168.0.1 --port=1337

 Example Secure Startup:
  Unix:
 	$:    FLASK_APP=server.py flask run --host=192.168.0.1 --port=1337 --cert cert.pem --key key.pem
  Windows:
	cmd:> set FLASK_APP=server.py
	cmd:> flask run --host=192.168.0.1 --port=1337 --cert cert.pem --key key.pem


 
'''

from flask import Flask, request
from flask_httpauth import HTTPTokenAuth
import keyboard
app = Flask(__name__)

'''
This is the Token Authorization part.
Let's continue with the example from 'client.c'

1. Convert Octal to Text
2. XOR the Token back to the original 'text' form
3. Auth Auth Auth

auth = HTTPTokenAuth(scheme='Token')

sec_token = "EXAMPLE_INSECURE_TOKEN"
@auth.verify_token
def verify_token(token):
    octal_to_text(token)
    decrypt_token(token)
    if token == sec_token:
        return True
    return False

'''
@app.route("/kb_handler", methods=['GET','POST']) #@switch -l and -h
#@auth.login_required # Uncomment this to block Unauthorized Access to /kb_handler
def kb_handler():
	KB_STRING = request.form.get('kb_str')
	KB_MODE	= request.form.get('kb_mod')
	print("[INFO] Received: '%s', MODE: '%s'" %(KB_STRING, KB_MODE))
	if KB_STRING == None:
		return "kb_null_req" # bad creds

	try:
		type(KB_STRING[0])
	except TypeError as e:
		return "kb_type_error"

	if KB_MODE == '0':
		keyboard.write(KB_STRING)
	elif KB_MODE == '1':
	'''
		Define your command / keyboard shortcuts here.
		Check out the documentation: https://github.com/boppreh/keyboard#api
	'''
		if KB_STRING == "CTRLW":
			keyboard.press_and_release("ctrl+w")
		elif KB_STRING == "SPACE":
			keyboard.press_and_release("space")
		elif KB_STRING == "ALTTAB":
			keyboard.press_and_release("alt+tab")
		elif KB_STRING == "YT":
			keyboard.press_and_release("f11")
			keyboard.press_and_release("ctrl+t")
			keyboard.write("youtube.com/tv")
			keyboard.press_and_release("enter")
			keyboard.press_and_release("f11")
		elif KB_STRING == "F11":
			keyboard.press_and_release("f11")
		elif KB_STRING == "TAB":
			keyboard.press_and_release("tab")
		elif KB_STRING == "RLD":
			keyboard.press_and_release("f5")
		elif KB_STRING == "AUP":
			keyboard.press_and_release("up")
		elif KB_STRING == "VUP":
			for i in range(10):
				keyboard.press_and_release("up")
		elif KB_STRING == "LMB":
			mouse.click(button='left')
		else:
			return "kb_unknown_event"
	#elif KB_MODE == '2':     # {disabled by default} - MODE 2 - If enabled/used, server doesn't verify given keyboard shortcuts, instead it executes them immediately. [Must be enabled in client.c too] 
	#	keyboard.press_and_release(KB_STRING)
	return "kb_event_ok"

if __name__ == "__main__":
    app.run(ssl_context=('cert.pem', 'key.pem')) # Let's base this on a self-signed certificate.. Generate one with: 'openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365'
