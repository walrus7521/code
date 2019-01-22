#!/usr/bin/env node

/*
 * https://medium.freecodecamp.org/writing-command-line-applications-in-nodejs-2cf8327eee2
 */

'use strict'

const program = require('commander');

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


