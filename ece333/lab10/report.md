# Lab 10

## Meta

Gregory N. Schmit

ECE 333 Computer Networks I

## Lab

1. Frame    Source    SSL Records   SSL Type
   2590     Client	  1	            Client Hello
   2591	    Server	  1	            Server Hello
   2592	    Server	  2	            Certificate
                                    Server Hello Done
   2593	    Client	  3	            Client Key Exchange
                                    Change Cipher Spec
                                    Encrypted Handshake Message
   2594	    Server	  2	            Change Cipher Spec
                                    Encrypted Handshake Message
   2595	    Client	  1	            Application Data
   2596	    Server	  1	            Application Data
   2597	    Server	  1	            Application Data

2. Content Type: 1 byte; Version: 2 bytes; Length: 2 bytes
3. 22
4. Random = `93:b8:57:69:6f:61:12:dc:db:36:d7:64:c8:3d:f1:e4:c1:28:ee:e1:2e:f8:73:41:ff:cc:e7:dc:d8:25:19:1b`
5. The first uses elliptic-curve Diffie-Hellman exchange and AES128 for the cipher, with SHA256 as the hash function.
6. The server chose ECDHE, AES 256, and SHA384.
7. Yes, 32-byte Random field (28 is nonce data and 4 is a timestamp). This prevents a replay attack.
8. Yes, a 32-byte session ID is sent to resume session later.
9. There is no cert; that comes in another record. It fits in a single Frame.
10. Yes, it does contain a premaster secret which is 128 bytes long and used to make a master secret.
11. The Change Cipher Spec is used to show that the contents of the following SSL records will be encrypted. They are 6 bytes (5 for header and 1 for message).
12. MAC of the concatenation of all the previous handshake messages sent from this client is generated and sent to the server.
13. Yes the server will also send a Change Cipher Spec record and encrypted handshake to the client. The server’s encrypted handshake record is different from that sent by the client because it contains the concatenation of all the handshake messages sent from the server rather than from the client. Otherwise the records would end up being the same.
14. Application data is encrypted using symmetric encryption chosen during the handshake. The client key encrypts data from client to server and the server key is used in the other direction.
15. I used TLS 1.2 so there were some slight differences.
