# Lab 5

## Meta

Gregory N. Schmit

ECE 333 Computer Networks I

## Lab

1. 4 UDP Headers:
	1. Source Port
	2. Dest. Port
	3. Length
	4. Checksum
2. Each field is 2 bytes
3. Length is the size (in bytes) of UDP header + payload.
4. 65,527 bytes (65,535 - 8 header bytes)
5. 65535
6. 17 (0x11)
7. Checksum is calculated from header, payload, source address, destination address, protocol (padded with a zero byte) and UDP length.
8. The destination port and source port are reversed between the incoming and outgoing packets.