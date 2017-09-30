var WebSocketServer = require("ws").Server
var http = require("http")
var express = require("express")
var app = express()
var basicAuth = require('basic-auth')

var auth = function (req, res, next) {
  
  function unauthorized(res) {
    res.set('WWW-Authenticate', 'Basic realm=Authorization Required');
    return res.send(401);
  };

  var user = basicAuth(req);

  if (!user || !user.name || !user.pass) {
    return unauthorized(res);
  };

  if (user.name === '*not published on github*' && user.pass === '*not published on github*') {
    return next();
  } else {
    return unauthorized(res);
  };
};


var port = process.env.PORT || 5000

app.get('/', auth, function (req, res) {
  app.use(express.static(__dirname + "/public"))
  res.redirect('index.html')
});

var server = http.createServer(app)
server.listen(port)

console.log("http server listening on %d", port)
var wss = new WebSocketServer({server: server})
console.log("websocket server created")


wss.broadcast = function broadcast(data) {
  wss.clients.forEach(function each(client) {
    client.send(data);
  });
};


var userID 		= 0
var clients 	= {}
var webSockets 	= {} // deviceID: webSocket
wss.on("connection", function(ws) {

	var deviceID = ws.upgradeReq.url.substr(1)
  	
  	webSockets[deviceID] = ws
 	console.log('connected: ' + deviceID)

 	if (deviceID !== 'milow') {
 		//userID = (Object.keys(clients).length + 1);
 		// if (Object.keys(clients).length !== 0) {
 		// 	ws.send('Could not connect, milow is busy with other connection');
 		// 	ws.terminate();
 		// }else{
 		// 	clients[deviceID] = ws;
 		// }

 		clients[deviceID] = ws;
 		console.log('client: ' + deviceID)
 	};
 	

 	ws.send('connected to websocket');
   	// var id = setInterval(function() {
   	//   ws.send(JSON.stringify(new Date()), function() {  })
   	// }, 1000)
	//console.log(wss.clients)


	ws.on('message', function incoming(message) {
		var messageArray = [];
		console.log('received from ' + deviceID + ': ' + message)
		
		if (deviceID == 'milow') {
			messageArray = ['usr',message]
		}else{
			messageArray = ['milow',message]
		}
    

	    var toUserWebSocket = webSockets[messageArray[0]]
	    
	    if (toUserWebSocket) {
	      //console.log('sent to ' + messageArray[0] + ': ' + JSON.stringify(messageArray))
	      messageArray[0] = deviceID
	      toUserWebSocket.send(messageArray[1])
	    }


    //console.log('received: %s', message);
	
	//wss.broadcast(message)
	});


  ws.on("close", function() {
    console.log("websocket connection close")
    //clearInterval(id)
    console.log((new Date()) + ' Peer ' + userID + ' disconnected.');
    delete clients[deviceID]
    console.log(Object.keys(clients).length)
  })
})
