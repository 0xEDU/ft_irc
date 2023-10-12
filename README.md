<div align="center">
<h1>
	ft_irc
</h1>

<p align="center">
	<img src="https://github.com/guiribei/guiribei/blob/main/42_badges/ft_ircn.png" />
</p>

<h1>WIP</h1>
</div>

## Summary
> <i>Internet Relay Chat (IRC) is a protocol that facilitates text communication in the form of messages. This project offers a C++98 IRC server implementation. Users can connect, join channels, send direct messages, and participate in group chats, among other typical IRC functionalities.</i>

## TCP protocol
The Transmission Control Protocol (TCP) is one of the main protocols in the Internet protocol suite. It's a connection-oriented protocol, meaning it establishes a connection between two hosts, ensuring that data packets arrive in the same order they were sent.

In simpler terms, when an application wants to communicate with another over the internet, it sends a message broken down into smaller packets via TCP. TCP guarantees the packets are sent and received in order and ensures they are reassembled correctly at the other end. It also checks for errors and if any packet is found missing or corrupted, it will be retransmitted. This reliability makes TCP an excellent choice for applications like web browsing, email, and of course, IRC, where data integrity is essential.
