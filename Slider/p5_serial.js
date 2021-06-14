let serial;

function setup() {
  serial = new p5.SerialPort();
  let portlist = serial.list();
  serial.open("COM5"); //Serial Port

  // Register some callbacks
  serial.on("connected", serverConnected);
  serial.on("list", gotList);
  // serial.on("data", gotData);
  // serial.on("error", gotError);
  // serial.on("open", gotOpen);
}

function draw() {
  if (serial.available() > 0) {
    let data = serial.readStringUntil("\n");
    let hasNum = /^\d*$/.test(data);
    if (!hasNum) {
      console.log(data);
    }
  }
}


// Methods available
// serial.read() returns a single byte of data (first in the buffer)
// serial.readChar() returns a single char 'A', 'a'
// serial.readBytes() returns all of the data available as an array of bytes
// serial.readBytesUntil('\n') returns all of the data available until a '\n' (line break) is encountered
// serial.readString() retunrs all of the data available as a string
// serial.readStringUntil('\n') returns all of the data available as a tring until a (line break) is encountered
// serial.last() returns the last byte of data from the buffer
// serial.lastChar() returns the last byte of data from the buffer as a char
// serial.clear() clears the underlying serial buffer
// serial.available() returns the number of bytes available in the buffer
