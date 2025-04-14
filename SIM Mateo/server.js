import { SerialPort } from "serialport";
import { ReadlineParser } from "@serialport/parser-readline";
import express from "express";
import http from "http";
import { WebSocketServer, WebSocket } from "ws";

const app = express();
const port = 80;

// Serve static files from the current directory
app.use(express.static('.'));

// Replace with your Arduino port name (e.g., "COM11")
const portName = "COM9";
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

// Message queue for commands if WebSocket is not open
let messageQueue = [];

// Process incoming serial data and forward commands if exactly "RED" or "GREEN"
let primaryWs = null;
parser.on("data", (data) => {
    // Read the line, trim whitespace, and convert to uppercase for uniformity.
    const command = data.trim().toUpperCase();
    console.log(`Received from MEGA: ${command}`);

    // Define a regular expression for the expected board command pattern.
    // This regex will match commands like A1_GREEN, A1_RED, C1_GREEN, etc.
    const regex = /^(A1|A2|C1|C2|D1|D2|D3|E1|E2|F1)_(RED|GREEN)$/i;

    // Test if the command matches the expected pattern.
    if (regex.test(command)) {
        // Convert it to lower case for sending to the client.
        const lowerCmd = command.toLowerCase();
        if (primaryWs && primaryWs.readyState === WebSocket.OPEN) {
            // Flush any queued messages and then send the current command.
            if (messageQueue.length > 0) {
                messageQueue.forEach((msg) => primaryWs.send(msg));
                messageQueue = [];
            }
            primaryWs.send(lowerCmd);
        } else {
            console.warn("WebSocket not open; queuing command.");
            messageQueue.push(lowerCmd);
        }
    } else {
        console.warn("Ignoring non-command message:", command);
    }
});

const server = http.createServer(app);
const wss = new WebSocketServer({ server });

wss.on("connection", (ws) => {
    console.log("WebSocket client connected");
    ws.on("message", (msg) => {
        // Convert the message to a string if it isn't already.
        let message = (typeof msg === "string") ? msg : msg.toString('utf8');
        console.log(`Message from client: ${message}`);

        // Ensure it ends with a newline. If not, append one.
        if (!message.endsWith("\n")) {
            message += "\n";
        }

        serialPort.write(message, (err) => {
            if (err) {
                console.error("Error writing to serial port:", err.message);
            } else {
                console.log("Sent to Arduino:", message);
            }
        });
    });

    ws.send("Connected to SIM Mateo WebSocket server");
    primaryWs = ws;
    // Delay flushing queued commands to ensure the client's onmessage handler is ready
    setTimeout(() => {
        if (messageQueue.length > 0) {
            messageQueue.forEach((msg) => {
                if (ws.readyState === WebSocket.OPEN) {
                    ws.send(msg);
                }
            });
            messageQueue = [];
        }
    }, 1000);
});

// Gracefully close the serial port on process termination
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