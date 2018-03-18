#!/usr/bin/env node
var b = require('bonescript');

var led = "P9_15";

b.pinMode(led, b.OUTPUT); 

var state = b.LOW; 

b.digitalWrite(led, state); 

setInterval(toggle, 0);

 function toggle() {
    if(state == b.LOW) state = b.HIGH;
    else state = b.LOW;
    b.digitalWrite(led, state);
}
