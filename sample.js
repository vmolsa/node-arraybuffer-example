var sample = require('./build/Release/sample.node');

function PrintJS(arrayBuffer) {
  var buffer = new Buffer(new Uint8Array(arrayBuffer));
  
  if (Buffer.byteLength(buffer, 'utf8')) {  
    console.log('JS:', "'" + buffer.toString('utf8') + "'", Buffer.byteLength(buffer, 'utf8'));
  }
}

function Print(arrayBuffer) {
  if (!arrayBuffer) {
    var buf = new Buffer(5);
    buf.write('HELLO', 0);

    var arrayBuffer = new Uint8Array(buf).buffer;    
  }
 
  sample.PrintArrayBuffer(arrayBuffer);
  PrintJS(arrayBuffer);
}

function Create() {
  var arrayBuffer = sample.CreateArrayBuffer();
  Print(arrayBuffer);
  sample.PrintWrapped(arrayBuffer);
}

function String() {
  var arrayBuffer = sample.StringArrayBuffer();
  Print(arrayBuffer);
}

for (var index = 0; index < 100; index++) {
  Print('New ArrayBuffer From String!');
  Create();
  String();
}

sample.DisposeMemory();