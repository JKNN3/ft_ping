
https://www.cloudflare.com/learning/ddos/glossary/internet-control-message-protocol-icmp/

The ICMP protocol also does not allow for targeting a specific port on a device.

An ICMP packet is a packet that uses the ICMP protocol. ICMP packets include an ICMP header after a normal IP header. When a router or server needs to send an error message, the ICMP packet body or data section always contains a copy of the IP header of the packet that caused the error.

A ping flood or ICMP flood is when the attacker attempts to overwhelm a targeted device with ICMP echo-request packets. The target has to process and respond to each packet, consuming its computing resources until legitimate users cannot receive service.


Ping of death attack

A ping of death attack is when the attacker sends a ping larger than the maximum allowable size for a packet to a targeted machine, causing the machine to freeze or crash. The packet gets fragmented on the way to its target, but when the target reassembles the packet into its original maximum-exceeding size, the size of the packet causes a buffer overflow.

The ping of death attack is largely historical at this point. However, older networking equipment could still be susceptible to it.

Smurf attack

In a Smurf attack, the attacker sends an ICMP packet with a spoofed source IP address. Networking equipment replies to the packet, sending the replies to the spoofed IP and flooding the victim with unwanted ICMP packets. Like the 'ping of death,' today the Smurf attack is only possible with legacy equipment.

#include <icmp.h>
https://sites.uclouvain.be/SystInfo/usr/include/linux/icmp.h.html

ping implementation from inetutils-2.0

https://manpages.debian.org/stretch/inetutils-ping/ping.1.en.html

Ping uses the ICMP protocol's mandatory ECHO_REQUEST datagram to elicit an ICMP ECHO_RESPONSE from a host or gateway. ECHO_REQUEST datagrams (``pings'') have an IP and ICMP header, followed by a “struct timeval” and then an arbitrary number of ``pad'' bytes used to fill out the packet.

socket() crée un point de communication, et renvoie un descripteur.

http://manpagesfr.free.fr/man/man7/packet.7.html


  difference between iputils's ping and inetutils's ping
https://unix.stackexchange.com/questions/400351/what-are-the-differences-between-iputils-ping-and-inetutils-ping

(iputils's ping has more features but work only under linux unlike nuetutils's ping which works just as well under windows)

iputils’s ping supports quite a few more features than inetutils’ ping, e.g. IPv6 (which inetutils implements in a separate binary, ping6), broadcast pings, quality of service bits... The linked manpages provide details.

iputils’ ping supports all the options available on inetutils’ ping, so scripts written for the latter will work fine with the former. The reverse is not true: scripts using iputils-specific options won’t work with inetutils.

As far as why both exist, inetutils is the GNU networking utilities, targeting a variety of operating systems and providing lots of different networking tools; iputils is Linux-specific and includes fewer utilities. So typically you’d combine both to obtain complete coverage and support for Linux-specific features, on Linux, and only use inetutils on non-Linux systems.


