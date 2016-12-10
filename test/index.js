const Mocha = require('mocha');
const fs = require('fs');
const path = require('path');

const mocha = new Mocha();
const test_dir = path.resolve(path.join(__dirname, 'js'));

fs.readdirSync(test_dir)
  .filter(function(file) { return path.extname(file) == '.js'; })
  .forEach(function(file) { mocha.addFile(path.join(test_dir, file)); });

mocha.run(function(failures){ process.on('exit', function () { process.exit(failures); }); });
