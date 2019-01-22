#!/usr/bin/env node

// connect in browser at: http://localhost:3000/
//server.js
const http = require('http'),
      server = http.createServer();

server.on('request',(request,response)=>{
   response.writeHead(200,{'Content-Type':'text/plain'});
   response.write('wusup dawg, yo hooda');
   response.end();
});

server.listen(3000,()=>{
  console.log('Node server created at port 3000');
});

