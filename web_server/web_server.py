import string
from time import gmtime, strftime
import pymongo
from pymongo import MongoClient
from flask import Flask, request

app = Flask(__name__)

# establish database connection
client = pymongo.MongoClient("mongodb+srv://db3:1q2w3e4r5t@cluster0-moupm.gcp.mongodb.net/test?retryWrites=true"
)
db = client.bootcamp # specific database is bootcamp
collection = db.group1 #group 1 collection
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


@app.route('/')
def last_100(): # returns last 100 readings to html output
  doc_count = collection.count_documents({})
  grtr_filter = doc_count - 100
  cursor = collection.find({"doc_count": {"$gt":grtr_filter}})
 
  response = []
  for data in cursor: # iterate through cursor
    response.append(data) # append to response
  return str(response) #convert to string so it can be viewed as HTML




@app.route('/post_data', methods=['POST'])
def post_data():
  print("**********************")
  print("**** POSTING DATA ****")
  print("**********************")
  # establish database connection

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
