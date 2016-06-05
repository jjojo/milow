robotApp.controller('HomeCtrl', function ($scope,$routeParams,$document) {
	// This file has no code yet.
	//var host = location.origin.replace(/^http/, 'ws')
    var host 	= "ws://http://46.101.22.6:5000/usr"
    var ws 		= new WebSocket(host);
	var fired 	= false;
	var sendMsg = function (msg) { ws.send(msg) };

	$scope.events = [];
	$scope.status = "connecting..."

    ws.onmessage = function (event) {
    	$scope.status = event.data
    	
    	$scope.events.push(event.data)
    	$scope.$apply()
    };

	$scope.submit = function (msg) {
		// body...
		sendMsg(msg);
	}

	
	$document.bind("keydown", function(event) {
		console.log(event)
		if (!fired) {
			fired = true;
			switch(event.keyCode) {
			    case 38:
			        $scope.keyUpColor = "green"
	        		$scope.$apply()
	        		setTimeout(ws.send('F1'), 5)
			        break;
			     case 39:
			        $scope.keyRightColor = "green"
	        		$scope.$apply()
	        		setTimeout(ws.send('r1'), 5)
			        break;
			     case 40:
			        $scope.keyDownColor = "green"
	        		$scope.$apply()
	        		setTimeout(ws.send('R1'), 5)
			        break;
			     case 37:
			        $scope.keyLeftColor = "green"
	        		$scope.$apply()
	        		setTimeout(ws.send('l1'), 5)
			        break;
			    default: 
			       	$scope.keyColor = "none";
			}
		};
     });


    $document.bind("keyup", function(event) {
    	console.log(event)
    	fired = false;
        switch(event.keyCode) {
		    case 38:
		        $scope.keyUpColor = "none"
        		$scope.$apply()
        		setTimeout(ws.send('F0'), 5)
		        break;
		     case 39:
		        $scope.keyRightColor = "none"
        		$scope.$apply()
        		setTimeout(ws.send('r0'), 5)
		        break;
		     case 40:
		        $scope.keyDownColor = "none"
        		$scope.$apply()
        		setTimeout(ws.send('R0'), 5)
		        break;
		     case 37:
		        $scope.keyLeftColor = "none"
        		$scope.$apply()
        		setTimeout(ws.send('l0'), 5)
		        break;
		    default: 
		       	$scope.keyColor = "none";
		}
    });


    $scope.test = function (argument) {
    	// body...
    	console.log("works")
    	$scope.keyColor = "none"
    }
});
