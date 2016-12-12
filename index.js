let tf = module.exports = require('./src/js');

var SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler("crash.log"); // With no argument, SegfaultHandler will generate a generic log file name
