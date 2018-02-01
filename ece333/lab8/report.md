# Lab 8

## Meta

Gregory N. Schmit

ECE 333 Computer Networks I

## Lab

1. The Ethernet address of my computer is ac:bc:32:c4:bd:ad
2. The destination address is 00:a0:c9:19:02:01, which is the MAC of my gateway router.
3. The hex value for the Frame type field is 0x0800, which is IPv4.
4. The 'G' appears 52 bytes from the start of the frame. 14 bytes of frame follow, and after that are 20 bytes (IP header). Then, 20 bytes for the TCP header.
5. The CRC field was not included in the packet. It may have been stripped from the hardware NIC.

6. The source address 00:a0:c9:19:02:01 (gateway).
7. The destination address is my computer ac:bc:32:c4:bd:ad.
8. 0x0800
9. The 'O' appears 52 bytes from the start. 14 bytes for Ethernet frame, 20 bytes of IP header, 20 bytes of TCP header before HTTP data.
10. I don't see the CRC field.
11. Host (IP Address) at MAC on Interface [protocol]

```
wireless-886.gw.uic.edu (10.63.208.1) at 0:a0:c9:19:2:1 on en0 ifscope [ethernet]
? (172.20.10.204) at 0:1d:e0:b7:ef:4d on tap0 ifscope [ethernet]
? (172.20.10.213) at 20:ab:37:7:da:78 on tap0 ifscope [ethernet]
? (172.20.10.234) at b0:70:2d:d4:48:71 on tap0 ifscope [ethernet]
? (172.20.10.237) at d8:fc:93:75:9d:6f on tap0 ifscope [ethernet]
? (224.0.0.251) at 1:0:5e:0:0:fb on en0 ifscope permanent [ethernet]
? (239.255.255.250) at 1:0:5e:7f:ff:fa on en0 ifscope permanent [ethernet]
```

12. Source is ac:bc:32:c4:bd:ad. Destination is ff:ff:ff:ff:ff:ff (broadcast).
13. 0x0806
14. ARP Questions
    1. The ARP opcode is 20 bytes from the start of the Ethernet frame.
    2. 0x0001
    3. Yes, 10.63.215.252
    4. The target MAC is 00:00:00:00:00:00.
15. Now find the ARP reply that was sent in response to the ARP request.
    1. ARP opcode is 20 bytes from the start of the Ethernet frame.
    2. 0x0002
    3. 00:a0:c9:19:02:01
16. Source is 00:a0:c9:19:02:01 and for the destination is ac:bc:32:c4:bd:ad.
17. There was no reply.
