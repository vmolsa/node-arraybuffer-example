var sample = require('./build/Release/sample.node');

function PrintJS(arrayBuffer) {
  var buffer = new Buffer(new Uint8Array(arrayBuffer));
  
  if (Buffer.byteLength(buffer, 'utf8')) {  
    console.log('JS:', "'" + buffer.toString('utf8') + "'", Buffer.byteLength(buffer, 'utf8'));
  }
}

function Print(arrayBuffer) {
  sample.PrintArrayBuffer(arrayBuffer);
  PrintJS(arrayBuffer);
}

var buf = new Buffer(5);
buf.write('HELLO', 0);

var arrayBuffer = new Uint8Array(buf).buffer;

Print(arrayBuffer);
Print('New ArrayBuffer From String!');
Print(sample.CreateArrayBuffer());

sample.DisposeMemory();