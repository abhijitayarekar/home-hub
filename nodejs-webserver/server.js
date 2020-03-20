'use strict';

var express = require('express');
var port = process.env.port || 1337;

var app = express();

app.listen(port, function() {
	console.log('Web Server listening on : ' + port);
});
