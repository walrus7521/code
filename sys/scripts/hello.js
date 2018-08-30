#!/usr/local/bin/node

// http://javascript.cs.lmu.edu/notes/commandlinejs/

console.log('Hello, world');

for (var x = 1, i = 0; i <= 32; i += 1) {
    console.log(x);
    x += x;
}

var deck = [];
"♠♡♢♣".split("").forEach(function (suit) {
    "A 2 3 4 5 6 7 8 9 10 J Q K".split(" ").forEach(function (rank) {
        deck.push(rank + suit);
    });
});

// Create a hand by successively removing a random card from the deck 
// and adding it to the hand. 
var hand = [];
for (var i = 0; i < 5; i += 1) {
    hand.push(deck.splice(Math.floor(Math.random() * deck.length), 1));
}

// Display the hand.
console.log(hand.join(" "));


