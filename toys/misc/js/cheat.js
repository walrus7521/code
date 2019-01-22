#!/usr/bin/env node

'use strict'

const program = require('commander');
var readline = require('readline');
const fs = require('fs');
const Buffer = require('buffer').Buffer;
var printf = require('printf');
const csv = require('csv');
var colors = require('colors');

console.log("Hello, world!");

let listFunction = (directory,options) => {
  //some code here
    console.log("dude");
}

program
  .version('0.0.1')
  .command('list [directory]')
  .description('List files and folders')
  .option('-a, --all','List all files and folders')
  .option('-l, --long','')
  .action(listFunction);
program.parse(process.argv);


var rl = readline.createInterface({
  //input: process.stdin,
  input: fs.createReadStream('dude.txt'),
  output: process.stdout,
  terminal: false
});

rl.on('line', function(line){
    //console.log(line);
    parse_pkt(line);
})

var regex2 = new RegExp('\\w+');

function parse_pkt(pkt) {
    var res = regex2.test(pkt);
    var str = printf("pkt: %s", pkt);
    console.log(str);
    console.log(colors.green(str));
    console.log(colors.yellow(str));
    console.log(colors.red(str));
    console.log(colors.blue(str));
}

csv
// Generate 20 records
.generate({
  delimiter: '|',
  length: 20
})
// Parse the records
.pipe(csv.parse({
  delimiter: '|'
}))
// Transform each value into uppercase
.pipe(csv.transform(function(record){
   return record.map(function(value){
     return value.toUpperCase()
   });
}))
// Convert the object into a stream
.pipe(csv.stringify({
  quoted: true
}))
// Print the CSV stream to stdout
.pipe(process.stdout)


