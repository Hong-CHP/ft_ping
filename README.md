# FT_PING

## Description
This is a project about reproduct ping implementation from inetutils-2.0 in programming language C.

## Principales
* ICMP protocole
* Raw Socket
* Checksum
* TTL

### ICMP Protocole
![icmp type and code](https://www.infosecinstitute.com/globalassets/wpcontentmedia/1-3193.webp)

#### a. Two kinds of ICMP message:
##### 1. Error message: 
* Destination Unreachable (type: 3);  
* Time Exceeded (type: 11);  
* Rediect (type: 5);  
* Parameter Problem (type 12)

*- When error message already sent, do not send again;*  
*- Fragmentation missing, error message sent, do not send again;*  
*- multi-destinations do not send error message;* 
*- For adress as: 127.0.0.1/0.0.0.0/ANY*

##### 2. Query message:
* Echo Request
* Echo Reply

#### b. ICMP message format:
* 1 bytes(0-8): type
* 1 bytes(8-16): code
* 2 bytes(16-32): checksum
* 2 bytes(32-48): id
* 2 bytes(48-64): sequence
* 56 bytes(default): payload

### Raw Socket
### Checksum
### TTL
An initial value from destination return in Echo Replay, -1 by passing a routage

## Structure
### 1. parsing
* parsing arguments
* getaddrinfo() get ip from DNS
### 2. init
* socket init
* signal handler
* ttl
### 3. build echo request
* build ICMP header (8 bytes)
* build ICMP payload (56 bytes)
* checksum
### 4. send
* sendto
### 5. recv and parse
* recvfrom
* jump to ICMP part
* reply type : 0  or Error
* check id/sequence
### 6. print
* print reply
* print error
### 7. statistics (SIGINT)
* print statistics
* send/recv, rtt min/max/avg/mdev
### 8. main loop
* build->send->recv->print / second
* until SIGINT

