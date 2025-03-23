import { SerialPort } from "serialport";
import { ReadlineParser } from "@serialport/parser-readline";
import express from "express";
import http from "http";
import { WebSocketServer } from "ws";

// Create an Express application
const app = express();
const port = 80;

// Serve static files from the current directory
app.use(express.static('.'));

// Replace with your Arduino port name (e.g., "COM12" for Windows or "/dev/ttyACM0" for Linux)
const portName = "COM12";
const serialPort = new SerialPort({
    path: portName,
    baudRate: 9600,
    autoOpen: false,
});

// Open the serial port and handle errors
serialPort.open((err) => {
    if (err) {
        console.error(`Failed to open ${portName}:`, err.message);
        process.exit(1);
    } else {
        console.log(`Serial port ${portName} opened successfully`);
    }
});

serialPort.on("error", (err) => {
    console.error("Serial port error:", err.message);
});

serialPort.on("close", () => {
    console.error(`Serial port ${portName} was closed.`);
});

// Attach a readline parser to the serial port (using newline as delimiter)
const parser = serialPort.pipe(new ReadlineParser({ delimiter: "\n" }));

// Message queue to store commands if no WebSocket connection is available yet
let messageQueue = [];

// Process incoming serial data (from Arduino)
// For example, if Arduino sends "RED" or "GREEN", this code sends it over WebSocket.
let primaryWs = null;
parser.on("data", (data) => {
    const command = data.trim().toUpperCase();
    console.log(`Received from MEGA: ${command}`);
    if (command === "RED" || command === "GREEN") {
        const lowerCmd = command.toLowerCase();
        if (primaryWs && primaryWs.readyState === primaryWs.OPEN) {
            // Flush queued messages if any
            if (messageQueue.length > 0) {
                messageQueue.forEach((msg) => primaryWs.send(msg));
                messageQueue = [];
            }
            primaryWs.send(lowerCmd);
        } else {
            console.warn("WebSocket not open; queuing command.");
            messageQueue.push(lowerCmd);
        }
    }
});

// Create HTTP server using Express
const server = http.createServer(app);

// Create a WebSocket server attached to the HTTP server
const wss = new WebSocketServer({ server });

// Handle WebSocket connections
wss.on("connection", (ws) => {
    console.log("WebSocket client connected");

    // Listen for messages coming from the client and forward them to the Arduino's serial port.
    ws.on("message", (message) => {
        console.log(`Message from client: ${message}`);
        // Write the command to the serial port with a newline terminator.
        serialPort.write(message + "\n", (err) => {
            if (err) {
                console.error("Error writing to serial port:", err.message);
            } else {
                console.log("Sent to Arduino:", message);
            }
        });
    });

    // Send an initial greeting message to the client.
    ws.send("Connected to SIM Mateo WebSocket server");

    // Assign the active WebSocket to primaryWs so that incoming serial commands can be forwarded.
    primaryWs = ws;

    // Delay flushing any queued serial commands to ensure the client's onmessage handler is set up.
    setTimeout(() => {
        if (messageQueue.length > 0) {
            messageQueue.forEach((msg) => {
                if (ws.readyState === ws.OPEN) {
                    ws.send(msg);
                }
            });
            messageQueue = [];
        }
    }, 1000);
});

// Gracefully close the serial port on process termination (SIGINT)
process.on("SIGINT", () => {
    console.log("Closing serial port...");
    serialPort.close(() => {
        console.log("Serial port closed. Exiting.");
        process.exit(0);
    });
});

// Start the HTTP server
server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});