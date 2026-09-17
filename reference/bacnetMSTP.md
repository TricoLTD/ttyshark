# As ashrae seems to keep the open standard paywalled this is the best approx at this moment.

BACnet over serial primarily uses the BACnet MS/TP (Master-Slave/Token-Passing) protocol, which defines how packets (called Protocol Data Units, or PDUs) are framed and transmitted across an RS-485 serial network. 
At the serial layer, BACnet wraps the network data in a specific frame structure to ensure it reaches the correct device without errors. 
🛠️ The MS/TP Frame Structure 
Every BACnet MS/TP packet transmitted over serial follows a strict sequence of bytes. 

| Byte Position | Field Name | Size | Purpose  |
| --- | --- | --- | --- |
| 1 | Preamble 1 | 1 byte | Fixed hex value  (identifies start of frame)  |
| 2 | Preamble 2 | 1 byte | Fixed hex value  (identifies start of frame)  |
| 3 | Frame Type | 1 byte | Indicates the function (e.g., Token, Data, Reply)  |
| 4 | Destination Address | 1 byte | MAC address of the receiver (0-127 for masters, 255 for broadcast)  |
| 5 | Source Address | 1 byte | MAC address of the sender (0-127)  |
| 6–7 | Length | 2 bytes | The size of the data field (0 to 501 bytes)  |
| 8 | Header CRC | 1 byte | Cyclic Redundancy Check to validate the header  |
| 9–N | Data (Payload) | Variable | The actual BACnet NPDU/APDU (Optional)  |
| N+1–N+2 | Data CRC | 2 bytes | Checksum for the data payload (Only present if Length &gt; 0)  |

🔍 Detailed Field Breakdown 

• Preambles (, ): These two bytes always start the packet. They alert the serial hardware to prepare for an incoming message. 
• Frame Type: This byte tells the device what kind of packet this is. Common types include: 

	• : Token (used to pass network control) 
	• : BACnet Data Expecting Reply (standard request) 
	• : BACnet Data Not Expecting Reply (broadcast or unconfirmed request) 

• Addresses: MS/TP uses 8-bit MAC addresses. A destination of  () means it is a broadcast message to all devices on the serial link. 
• Header CRC: An 8-bit checksum calculated using the  polynomial. If this check fails, the receiver drops the entire packet immediately. 
• Data (The Payload): This contains the actual BACnet Network Layer (NPDU) and Application Layer (APDU) data, such as a "Read Property" request. 
• Data CRC: A 16-bit checksum (CRC-16) used to ensure the data payload wasn't corrupted during serial transmission. 

⚡ Physical Layer Requirements 
For these packets to be read correctly, the serial connection must be configured exactly the same way across all devices on the network: 

• Physical Medium: RS-485 (shielded twisted-pair wire). 
• Baud Rate: Typically 9600, 19200, 38400, or 76800 bps. 
• Data Bits: 8 
• Parity: None 
• Stop Bits: 1 


AI responses may include mistakes.

