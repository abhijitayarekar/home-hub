'use strict';

var express = require('express');
var app = express();
var port = process.env.port || 1337;
var os = require('os');
var Ssdp = require('node-ssdp').Server;
var ssdpServer = new Ssdp({ location: { port: port, path: '' } });

ssdpServer.addUSN('upnp:rootdevice');
ssdpServer.addUSN('urn:schemas-upnp-org:service:HomeHubService:1');
ssdpServer.start();

app.use("*", function(req, res) {
	res.json({
			name: 'Home Hub Webserver',
			hostname: os.hostname(),
			user: os.userInfo().username
		});
});

const webServer = app.listen(port, function() {
	console.log('Web Server listening on : ' + port);
});

function cleanup() {
	console.log('Closing http server.');
	webServer.close(() => {
		console.log('Http server closed.');
		ssdpServer.stop();
		console.log('Ssdp server stopped.');
		process.exit(0);
	});
}

process.on('SIGINT', () => {
	console.info('SIGINT signal received.');
	cleanup();
});

process.on('SIGTERM', () => {
	console.info('SIGTERM signal received.');
	cleanup();
});
