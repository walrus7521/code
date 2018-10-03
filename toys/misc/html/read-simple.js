'use strict'

const fs = require('fs');
fs.readFile('test.bin', (err, data) => {
    if (err) {
        throw err;
    }
    console.log(Number(data.slice(1,4)));
    var digit = parseInt(data.slice(0,3), 2);
    console.log(digit);
    console.log(bin2dec(data.slice(0,3)));

    console.log(bin2hex(data.slice(0,1)));
    console.log(bin2hex(data.slice(4,5)));
    console.log(bin2hex(data.slice(8,9)));
    console.log(bin2hex(data.slice(12,13)));
    console.log(data.slice(0,3).toString("hex"));
    console.log(data.slice(4,7).toString());
    console.log(data.slice(8,11).toString());
    console.log(data.slice(12,15).toString());
});

function dec2bin(dec) {
    return (dec >>> 0).toString(2);
}

function bin2dec(num) {
    return num.split('').reverse().reduce(function(x, y, i){
      return (y === '1') ? x + Math.pow(2, i) : x;
    }, 0);
}

function bin2hex(bin) {
    return new Buffer(bin).toString("hex");
}

