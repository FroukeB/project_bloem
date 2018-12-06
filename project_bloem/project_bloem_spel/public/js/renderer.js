// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const osc = require('osc');

const udpPort = new osc.UDPPort({   remoteAddress: "localhost",   remotePort: 12345 });

udpPort.on("ready", () => {   // vanaf nu kunnen we messages versturen }); udpPort.open()
}); 
udpPort.open();