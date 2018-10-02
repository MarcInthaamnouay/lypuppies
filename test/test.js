const lib = require('../build/Release/lypuppies');

const text = 'hello';
const t = lib.SayHello(text);
console.warn(t);