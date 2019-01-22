#!/usr/bin/env node

/*
 * https://medium.freecodecamp.org/writing-command-line-applications-in-nodejs-2cf8327eee2
 */

'use strict'

const program = require('commander');
var readline = require('readline');
const fs = require('fs');
const Buffer = require('buffer').Buffer;
var printf = require('printf');

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
}


