var sample = require('./build/Release/sample.node');

function PrintJS(arrayBuffer) {
  var buffer = new Buffer(new Uint8Array(arrayBuffer));
  
  try {
    if (Buffer.byteLength(buffer, 'utf8')) {  
      console.log('JS:', "'" + buffer.toString('utf8') + "'", Buffer.byteLength(buffer, 'utf8'));
    }
  } catch(ignored) {
    console.log('JS:', buffer.toString('utf8'));
  }
}

function Print(arrayBuffer) {
  sample.PrintArrayBuffer(arrayBuffer);
  PrintJS(arrayBuffer);
}

var buf = new Buffer(5);
buf.write('HELLO', 0);

var arrayBuffer = new Uint8Array(buf).buffer;

for (var index = 0; index < 100; index++) {
  Print(arrayBuffer);
  Print('New ArrayBuffer From String!');
  Print(sample.CreateArrayBuffer());
  sample.DisposeMemory();
}