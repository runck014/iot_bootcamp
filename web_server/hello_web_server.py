import string
from flask import Flask, request

app = Flask(__name__) # setup initial flask app; gets called throughout in routes

'''
Python decorateors point to a function
Here, it specifies the app route '/'.
It sends basic text from the hello() function
back as a response. This is what you
see in your web browser when you type in
x.x.x.x:5000/

Note: the / in the above path references the '/'
in the @app.route('/') designation.

For more on decorators, Google "decorators in python".
'''
@app.route('/') #python decorator 
def hello_world(): #function that app.route decorator references
  response = hello()
  return response

def hello():
  return "hello, world"

'''
MAKE YOUR OWN ROUTE:

If you added a decorator @app.route('/test')
and defined a function def test():
you can see how this works. Note: you
will need to restart the web server if you do this.

See github wiki pages for more details:
https://github.com/runck014/gems_iot_bootcamp/wiki/4.-Web-Server
'''

# route only prints data to console
@app.route('/print_data', methods=['POST'])
def print_data():
  
  print("*********************")
  print("*********************")
  print(request.method) # finds method -> here it should be "POST"
  print(request.data) # generic - get all data; covers case where you don't know what's coming
  print(request.json) # parses json data
  print("*********************")
  print("*********************")
  return "Accepted 202 - post received; printed to console"

if __name__ == "__main__":
    app.run(
      #debug=True, #shows errors 
      host='0.0.0.0', #tells app to run exposed to outside world
      port=5000)
