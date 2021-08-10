# Gossip Protocol
This is an implementation of Gossip Protocol in c++ language.

## What is gossip protocol?
A gossip protocol is a procedure or process of computer peer-to-peer communication that is based on the way epidemics spread.Some distributed systems use peer-to-peer gossip to ensure that data is disseminated to all members of a group. Some ad-hoc networks have no central registry and the only way to spread common data is to rely on each member to pass it along to their neighbours. 

The term <b>epidemic protocol</b> is sometimes used as a synonym for a gossip protocol, as gossip spreads information in a manner similar to the spread of a virus in a biological community. 

The Gossip protocol is used to repair the problems caused by multicasting; it is a type of communication where a piece of information or gossip in this scenario, is sent from one or more nodes to a set of other nodes in a network. This is useful when a group of clients in the network require the same data at the same time. But there are many problems that occur during multicasting, if there are many nodes present at the recipient end, latency increases; the average time for a receiver to receive a multicast.

To get this multicast message or gossip across the desired targets in the group, the gossip protocol sends out the gossip periodically to random nodes in the network, once a random node receives the gossip, it is said to be infected due to the gossip. Now the random node that receives the gossip does the same thing as the sender, it sends multiple copies of the gossip to random targets. This process continues until the target nodes get the multicast. This process turns the infected nodes to uninfected nodes after sending the gossip out to random nodes.

![image](https://user-images.githubusercontent.com/50926437/128827898-f6fbc38e-aa17-4e87-80a2-3275fd40536a.png)

## Project
The main functionalities of the project :
* Introduction : Each new peer contacts a well-known peer (the introducer) to join the group.
* Membership : A membership protocol satisfies completeness all the time (for joins and failures), and accuracy when there are no message delays or losses (high accuracy when there are losses or delays).

## Detail
Data Structure of Message :
```cpp
typedef struct MessageHdr {
	enum MsgTypes msgType; 
	vector< MemberListEntry> member_vector; // membership list of source
	Address* addr; // the source of this message
}MessageHdr;
```
![image](https://user-images.githubusercontent.com/50926437/128828262-d20d9f93-eee0-49e3-9010-3ca9a6b1d290.png)

