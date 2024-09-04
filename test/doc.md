
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

**ping implementation from inetutils-2.0**

https://manpages.debian.org/stretch/inetutils-ping/ping.1.en.html

Ping uses the ICMP protocol's mandatory ECHO_REQUEST datagram to elicit an ICMP ECHO_RESPONSE from a host or gateway. ECHO_REQUEST datagrams (``pings'') have an IP and ICMP header, followed by a “struct timeval” and then an arbitrary number of ``pad'' bytes used to fill out the packet.

socket() crée un point de communication, et renvoie un descripteur.

http://manpagesfr.free.fr/man/man7/packet.7.html


  difference between iputils's ping and inetutils's ping
https://unix.stackexchange.com/questions/400351/what-are-the-differences-between-iputils-ping-and-inetutils-ping
/what-are-the-differences-between-iputils-ping-and-inetutils-ping

(iputils's ping has more features but work only under linux unlike nuetutils's ping which works just as well under windows)

iputils’s ping supports quite a few more features than inetutils’ ping, e.g. IPv6 (which inetutils implements in a separate binary, ping6), broadcast pings, quality of service bits... The linked manpages provide details.

iputils’ ping supports all the options available on inetutils’ ping, so scripts written for the latter will work fine with the former. The reverse is not true: scripts using iputils-specific options won’t work with inetutils.

As far as why both exist, inetutils is the GNU networking utilities, targeting a variety of operating systems and providing lots of different networking tools; iputils is Linux-specific and includes fewer utilities. So typically you’d combine both to obtain complete coverage and support for Linux-specific features, on Linux, and only use inetutils on non-Linux systems.



  broadcast ip 
L'adresse de broadcast est une adresse IP qui termine en . 255 dans des réseaux de classe A, B ou C, cette adresse est celle qui permet de faire de la diffusion à toutes les machines du réseau. Ainsi, quand on veut envoyer une information à toutes les machines, on utilise cette adresse.

  damn ca a l'air long mais interessant

https://gursimarsm.medium.com/customizing-icmp-payload-in-ping-command-7c4486f4a1be

The output of ping from windows machine which by default sends 4 packets and stop.
The output of ping from Linux machine which by default continue pinging until ctrl+c is pressed to cancel.

on peut pas target de ports

comprendre ce que sonr exactement bits frame packets datagram

"Clarify PADDING vs PING frames"
https://www.baeldung.com/cs/networking-packet-fragment-frame-datagram-segment



https://github.com/quicwg/base-drafts/issues/838


When a client searches for a hostname—typically through a web browser—their network’s DNS provider executes a multi-step resolution process via the following four servers in order to find and return the appropriate IP address:



sscanf() pour le parsing trooop bien!!


https://github.com/dgibson/iputils/blob/master/ping_common.c


  bitwise operators

a = 0011 1100
b = 0000 1101

* & (bitwise and)	-> if the bit is present in both, is 1, else is 0
  * a&b = 0000 1100
* | (bitwise or)	-> every bits present in both numbers
  * a|b = 0011 1101
* ^ (bitwise XOR)	-> if bit is present in one of the 'numbers' not in both
  * a^b = 0011 0001
* ⁓ (bitwise compliment) -> invert bits
  * ~a  = 1100 0011

https://youtu.be/jxZ9qXtOt7o?si=-jHDpPYc_HNu0fsb


regex:
https://info2html.sourceforge.net/cgi-bin/info2html-demo/info2html?(libc)Regular%2520Expressions


https://www.youtube.com/watch?v=F83ZvOKj2BU


a regarder: https://www.youtube.com/watch?v=RnpSaDSSjR4

utile:
https://ram-0000.developpez.com/tutoriels/reseau/ICMP/

 ** -> An efficient checksum implementation is critical to good performance.**
  a fraction of a microsecond per TCP data byte can add up to a significant CPU time savings
  overall. 
      -> trouver comment opti le machin

calculate ICMP checksum:
https://forum.microchip.com/s/topic/a5C3l000000LxmDEAS/t221513
http://www.faqs.org/rfcs/rfc1071.html

compute IP checksum:
https://www.thegeekstuff.com/2012/05/ip-header-checksum/

jeannneeeee 1 octet 1 byte 8 bits

struct ip https://sites.uclouvain.be/SystInfo/usr/include/netinet/ip.h.html
struct icmp https://sites.uclouvain.be/SystInfo/usr/include/netinet/ip_icmp.h.html

time to live
Everytime an IP packet passes through a router, the time to live field is decremented by 1. Once it hits 0 the router will drop the packet and sends an ICMP time exceeded message to the sender

ip header length
The minimum length of an IP header is 20 bytes so with 32 bit increments, you would see value of 5 here. The maximum value we can create with 4 bits is 15 so with 32 bit increments, that would be a header length of 60 bytes. This field is also called the Internet Header Length (IHL).

ip id field:
The Identification field (16 bits) is populated with an ID number unique for the combination of source & destination addresses and Protocol field value of the original packet, allowing the destination to distinguish between the fragments of different packets (from the same source). This does not mean the same ID should be used when fragmenting packets where the source, destination and protocol are the same but that the same ID could be used when they are not.

ip offset: Like the original packet, the first, reserved bit of the Flags field (3 bits) will be 0 (unset) and the second bit, Don’t Fragment (DF), will also be unset. Unlike the original packet, all but the last fragment will have the third bit of the field, More Fragments (MF), set to 1. The last packet will have all bits in this field set to 0 just like the original packet (unless it was a fragment itself). If the Don’t Fragment flag was set in the original packet, this prevents fragmentation and results in packets that require it being discarded. An ICMP error of type 3: ‘Destination Unreachable’, code 4: ‘Fragmentation required, and DF set’ should be sent to the sender. See the following PMTUD section for more on this. le champ Fragment Offset : indique la position du premier octet de données du paquet reçu dans la partie donnée du paquet d’origine. Le premier fragment à donc toujours la valeur 0 (position du premier octet), de même que tous paquets non fragmentés. The Fragment Offset field (13 bits) is used to indicate the starting position of the data in the fragment in relation to the start of the data in the original packet. This information is used to reassemble the data from all the fragments (whether they arrive in order or not). In the first fragment the offset is 0 as the data in this packet starts in the same place as the data in the original packet (at the beginning). In subsequent fragments, the value is the offset of the data the fragment contains from the beginning of the data in the first fragment (offset 0), in 8 byte ‘blocks’ (aka octawords). If a packet containing 800 bytes of data is split into two equal fragments carrying 400 bytes of data, the fragment offset of the first fragment is 0, of the second fragment 50 (400/8). The offset value must be the number of 8 byte blocks of data, which means the data in the prior fragment must be a multiple of 8 bytes. The last fragment can carry data that isn’t a multiple of 8 bytes as there won’t be a further fragment with an offset that must meet the 8 byte ‘rule’. https://packetpushers.net/blog/ip-fragmentation-in-detail/#:~:text=The%20Fragment%20Offset%20field%20(13,arrive%20in%20order%20or%20not).

le champ Flag (3 bits) : il permet de gérer la fragmentation :
bit 0: réservé – toujours positionné à 0
bit 1 : dit bit DF (Don’t Fragment) – S’il est positionné à 0, la fragmentation est autorisée – S’il est positionné à 1 la fragmentation est interdite. Dans ce dernier cas, si le paquet est trop volumineux pour être encapsulé dans une trame, dont le MTU est inférieur à la taille du paquet, la passerelle qui devrait réaliser la fragmentation retournera à l’émetteur du paquet un ICMP « Paquet non fragmentable ».
bit 2 : dit bit MF (More Fragment) – S’il est positionné à 0 il indique que le paquet reçu est le dernier du paquet d’origine. S’il est positionné à 1, il indique que le paquet reçu est un fragment du paquet d’origine mais pas le dernier fragment. Un paquet qui n’a pas été fragmenté aura donc toujours ce bit à 0.
le champ Fragment Offset : indique la position du premier octet de données du paquet reçu dans la partie donnée du paquet d’origine. Le premier fragment à donc toujours la valeur 0 (position du premier octet), de même que tous paquets non fragment


ip_src et ip_dest sont de type
          struct in_addr {
              uint32_t       s_addr;     /* address in network byte order */
          };
    alors que getaddrinfo nous return
                struct sockaddr {
                    sa_family_t     sa_family;      /* Address family */
                    char            sa_data[];      /* Socket address */
                };
                
sockaddr is a generic struct, which is shared by different types of sockets. For TCP/IP sockets this struct becomes sockaddr_in (IPv4) or sockaddr_in6 (IPv6). For unix sockets it becomes sockaddr_un.

Ideally you would use sockaddr_in instead of sockaddr.

But given sockaddr, you could do this to extract IP address from it:

sockaddr foo;
in_addr ip_address = ((sockaddr_in)foo).sin_addr;
or
in_addr_t ip_address = ((sockaddr_in)foo).sin_addr.s_addr;

If you look inside sockaddr_in you will see that the first 2 bytes of sa_data are the port number. And the next 4 bytes are the IP address.

PS: Please note that the IP address is stored in network byte order, so you will probably need to use ntohl (network-to-host) and htonl (host-to-network) to convert to/from host byte order.



Network byte order 
  The network byte order is defined to always be big-endian, which may differ from the host byte order on a particular machine. Using network byte ordering for data exchanged between hosts allows hosts using different architectures to exchange address information without confusion because of byte ordering. The following C functions allow the application program to switch numbers easily back and forth between the host byte order and network byte order without having to first know what method is used for the host byte order:

      htonl() translates an unsigned long integer into network byte order.
      htons() translates an unsigned short integer into network byte order.
      ntohl() translates an unsigned long integer into host byte order.
      ntohs() translates an unsigned short integer into host byte order.

tropcool:
inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary form (in network byte order) and stores it in the structure that inp points to. 

timestamp explained:
https://stackoverflow.com/questions/70175164/icmp-timestamps-added-to-ping-echo-requests-in-linux-how-are-they-represented-t
Background
Including the UNIX timestamp of the time of transmission in the first data bytes of the ICMP Echo message is a trick/optimization the original ping by Mike Muuss used to avoid keeping track of it locally. It exploits the following guarantee made by RFC 792's Echo or Echo Reply Message description:

The data received in the echo message must be returned in the echo reply message.

Many (if not all) BSD ping implementations are based on Mike Muuss' original implementation and therefore kept this behavior. On Linux systems, ping is typically provided by iputils, GNU inetutils, or Busybox. All exhibit the same behavior. fping is a notable exception, which stores a mapping from target host and sequence number to timestamp locally.

Implementations typically store the timestamp in the sender's native precision and byte order as opposed to a well-defined precision in conventional network byte order (big endian), that is normally used for data transmitted over the network, as it intended to be only be interpreted by the original sender and others should just treat it as opaque stream of bytes.

Because this is so common however, the Wireshark ICMP dissector (as of v3.6.2) tries to be clever and heuristically decode it nonetheless, if the first 8 data bytes look like a struct timeval timestamp in 32-bit precision for seconds and microseconds in either byte order. Please note that if the sender was actually using big endian 64-bit precision, this will fail and if it was using little endian 64-bit precision, it will truncate the microseconds before the Epochalypse and fail after that.

Obtaining and serializing epoch time
To answer your actual question:

How do you convert the UNIX Epoch time to the TOD timestamp form which linux ping adds at the end of the ICMP header/begining of data field?

Most implementations use the obsolescent gettimeofday(2) instead of the newer clock_gettime(2). The following snippet is taken from iputils:

struct icmphdr *icp /* = pointer to ICMP packet */;
struct timeval tmp_tv;
gettimeofday(&tmp_tv, NULL);
memcpy(icp + 1, &tmp_tv, sizeof(tmp_tv));
memcpy from a temporary variable instead of directly passing the icp + 1 as target to gettimeofday is used to avoid potential improper alignment, effective type and strict aliasing violation issues.


https://fr.wikipedia.org/wiki/IPv4


pas de magic number = faire des define pour la clarté du code
  https://en.wikipedia.org/wiki/Magic_number_(programming)

epoll pour le flood et -i

ECHO_REPLY

https://www.firewall.cx/networking/network-protocols/icmp-protocol/icmp-echo-ping.html

https://networklessons.com/cisco/ccna-routing-switching-icnd1-100-105/icmp-internet-control-message-protocol


lire tt les commentaires et le code:
https://github.com/dspinellis/unix-history-repo/blob/BSD-4_3/usr/src/etc/ping.c#L233



get the ip adress of my machine
https://www.sanfoundry.com/c-program-get-ip-address/
using ioctl, 
SIOCGIFADDR
For compatibility, SIOCGIFADDR returns only AF_INET addresses
Get, set, or delete the address of the device using
              ifr_addr, or ifr6_addr with ifr6_prefixlen.  Setting or
              deleting the interface address is a privileged operation.

inside ifreq
Constant: size_t IFNAMSIZ
    This constant defines the maximum buffer size needed to hold an interface name, including its terminating zero byte.



we need to be root to create raw socket, we can set give the rights to an executable using setcap (set capabilities)
    in the makefile: `sudo setcap cap_net_raw ./ft_ping`

we now need to make it work with valgrind :')
cmd to see a binary capabilities: `grepcap /path/to/the/binary` (ex: /usr/bin/ping)
        set capabilities : `setcap the_capability ./the_binary` (ex: setcap cap_net_raw=ep ./ft_ping)
        remove capabilities: `setcap -r </path/to/binary>`
    setcap needs root or sudo

The capabilities are attached to the process by the Linux kernel
from the file in the filesystem when the kernel performs the
syscall execve(filename,,).  Neither valgrind nor its tools
perform execve(target_filename,,).

If a capability is inheritable, then attaching it to the filename
of some valgrind execve() in the dynamic chain of execve()s (see
"strace -e trace=execve valgrind ...") should work.
Otherwise, investigate prctl(PR_CAP_AMBIENT_RAISE,) etc.
Logically you want valgrind to prctl(PR_CAP_SET_ATTACH,)
but that apparently does not exist.



Linux capabilities:
https://book.hacktricks.xyz/linux-hardening/privilege-escalation/linux-capabilities