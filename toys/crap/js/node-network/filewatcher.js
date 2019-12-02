#!/usr/bin/env node

//filewatcher.js "/var/log/system.log"

const net = require('net'),
   fs = require('fs'),
   Tail = require('tail').Tail,
   filename = process.argv[2],
   tail = new Tail(filename),
      
server = net.createServer((connection)=>{
 console.log('Subscriber connected');
 connection.write(`watching ${filename} for changes`);
  
tail.on("line", function(data) {
  //console.log(data);
  connection.write(data);
});


//let watcher = fs.watch(filename,(err,data)=>{
//  connection.write(`${filename} has changed`);
// });
  
//connection.on('close',()=>{
//  console.log('Subscriber disconnected');
//  watcher.close();
// });
  
});
server.listen(3000,()=>console.log('listening for subscribers'));
