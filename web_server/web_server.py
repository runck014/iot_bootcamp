import string
from time import gmtime, strftime
import pymongo
from pymongo import MongoClient
from flask import Flask, request
app = Flask(__name__)

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

# route adds data to mongodb
@app.route('/post_data', methods=['POST'])
def post_data():
  print("**********************")
  print("**** POSTING DATA ****")
  print("**********************")
  # establish database connection
  client = pymongo.MongoClient("mongodb+srv://db3:1q2w3e4r5t@cluster0-moupm.gcp.mongodb.net/test?retryWrites=true")
  db = client.bootcamp # database is called bootcamp
  '''
  Each group has a collection in the bootcamp database.
  They are named after the gruop number:
  - group1
  - gruop2
  - group3
  - group4
  - group5
  - and so on
  '''
  collection = db.group1 #group 1 collection
  doc_count = collection.count_documents({}) + 1 # see [1]
  current_time = strftime("%Y-%m-%d %H:%M:%S", gmtime())
  payload = ({"doc_count":doc_count, 
              "data":request.data, 
              "web_server_time":current_time}) #add time stamp
  collection.insert_one(payload)
  
  print("Payload Inserted:", payload)
  print("***********************")
  print("***********************") 
  print(" ")

  return "Accepted 202 - post received; post to DB"
  

if __name__ == "__main__":
    app.run(
      #debug=True, #shows errors 
      host='0.0.0.0', #tells app to run exposed to outside world
      port=5000) #specifies port to listen to
''' 
[1] MongoDB collections are unstructured.
    This means we need some other way to keep track
    of order and uniqueness. doc_count serves this purpose.
'''
