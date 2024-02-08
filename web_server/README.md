# Web Server Overview
The web server uses Flask. The underlying database is MongoDB, hosted on Google Cloud via Mongo Atlas.

# To get started
To start, run the web_server_setup.sh on your VM (see [Wiki](https://github.com/runck014/iot_bootcamp/wiki/Setting-Up-VM-on-Google-Cloud) for more help):

```bash
$ bash web_server_setup.sh
```

The hello_web_server.py provides basic website functionality and posting. The website is simply "hello, world". The posting prints whatever is sent to console. There is also an exercise in the file to create a new route with your own basic functionality.

# Testing the API
You can use a web browser for the GET methods. For the POST methods, see the provided script.

# Full functionality
The web_server.py file has the full functionality including posting to a MongoDB database called bootcamp in a collection that corresponds to your group name. You can also get data out of the database using the "/last_100" method.
