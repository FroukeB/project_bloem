// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const osc = require('osc');

//  const udpPort = new osc.UDPPort({   remoteAddress: "localhost",   remotePort: 12345 }); // zenden van boodschap
const udpPort = new osc.UDPPort({
    localAddress: "localhost",
    localPort: 12345
}); // ontvangen van boodschap

/* udpPort.on("ready", () => {
    udpPort.send({
        address: "/test",
        args: [{           
            type: "i",
             value: 100
            },{
                type: "f",
                value: 3.5
            },{
                type: "s",
                value: "hello"
            },{
                type: "f",
                 value: performance.now()
            }
        ]
    }); 
}); */ // zenden boodschap
udpPort.open();
// ontvangen boodschap
udpPort.on("message", (oscMsg) => {   console.log("An OSC message just arrived!", oscMsg); });