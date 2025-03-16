import { SerialPort } from "serialport";
import { ReadlineParser } from "@serialport/parser-readline";
import express from "express";
import http from "http";
import { WebSocketServer, WebSocket } from "ws";

const app = express();
const port = 80;

// Serve static files from the current directory
app.use(express.static('.'));

// Update with your Arduino port name (e.g., "COM11" for Windows)
const portName = "COM11";
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

// Attach a readline parser
const parser = serialPort.pipe(new ReadlineParser({ delimiter: "\n" }));

// WebSocket setup: forward Arduino data to the client
let primaryWs = null;
parser.on("data", (data) => {
  console.log(`Received from Arduino: ${data}`);
  if (primaryWs && primaryWs.readyState === WebSocket.OPEN) {
    primaryWs.send(data);
  } else {
    console.warn("WebSocket not open; data not sent.");
  }
});

const server = http.createServer(app);
const wss = new WebSocketServer({ server });

wss.on("connection", (ws) => {
  console.log("WebSocket client connected");
  ws.on("message", (message) => {
    console.log(`Message from client: ${message}`);
  });
  ws.send("Connected to SIM Mateo WebSocket server");
  primaryWs = ws;
});

// Gracefully close serial port on process termination
process.on("SIGINT", () => {
  console.log("Closing serial port...");
  serialPort.close(() => {
    console.log("Serial port closed. Exiting.");
    process.exit(0);
  });
});

// Start the server
server.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
