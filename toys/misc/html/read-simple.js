'use strict'

const fs = require('fs');
fs.readFile('helicopter.jpg', (err, data) => {
    if (err) {
        throw err;
    }
    console.log(data.slice(0,48).toString());
    console.log(data.slice(48,128).toString());
    console.log(data.slice(128,164).toString());
});


