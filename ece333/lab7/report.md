# Lab 7

## Meta

Gregory N. Schmit

ECE 333 Computer Networks I

## Lab

1. My host is 10.9.208.112, a private IP. The destination is 137.132.21.27.
2. ICMP is a layer 4 protocol that does not use ports, so there is no TCP or UDP header to have a port number.
3. `Type` is `8` (Echo request), `Code` is 0. Other fields include `Code`, `Checksum`, `Identifier`, `Sequence Number`, and `Timestamp`. `Checksum`, `Sequence Number`, and `Identifier` are all 2 bytes long.
4. Type is `8` (Echo request), `Code` is 0. Other fields include `Code`, `Checksum`, `Identifier`, `Sequence Number`, and `Timestamp`. `Checksum`, `Sequence Number`, and `Identifier` are all 2 bytes long.
5. My Host: `10.9.208.112` -- Destination: `128.93.162.84`
6. No, it would be 17 for UDP.
7. Yes, the TTL is set really low (1 for first packet, 2 for second, etc).
8. There is an embedded ipv4 header and ICMP header in the ICMP segment.
9. They are normal responses.
10.  The jump in lag from `7  et-0-0-2.4079.rtsw.wash.net.internet2.edu (162.252.70.63)  19.902 ms  20.097 ms  20.855 ms` to `8  internet2-gw.mx1.lon.uk.geant.net (62.40.124.44)  96.433 ms  95.603 ms  95.708 ms` seemed to indicate the link between them being saturated or slow.
