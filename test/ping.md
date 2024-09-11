**checksum:** petite quantité de données calculée à partir d'une plus grosse quantité de données. Permett la verification de l'intégrité des données (très bonne fidélité). Souvent utilisé apres une transmission, une copie, un stockage.

getaddrinfo()
https://gist.github.com/jirihnidek/bf7a2363e480491da72301b228b35d5d

getnameinfo()

https://www.developpez.net/forums/d4485/c-cpp/c/reseau/raw-socket-forger-propre-packet-icmp-pinge/


traceroute implementation in python

https://www.geeksforgeeks.org/traceroute-implementation-on-python/

options:

      invalid option:
                  root@k-VirtualBox:/home/k/Documents/ping# ping -z abc 1.1.1.1
                  ping: invalid option -- 'z'
                  Try 'ping --help' or 'ping --usage' for more information.


-c --count=nb forcément un int, on peut metre un long long        // stop after sending NUMBER packets
-i --interval=nb int ou float                                     // wait, FLOAT * 1, second between sending each packet
      erreur:
            ping: invalid argument: '18446744073709551610': Numerical result out of range
              
--ttl nb       nb entre 0 et 255                                     // specify nb as time-to-live
      erreur:
            ping -t nb 1.1.1.1
                  ping: option value too big: nb
                        (-> 0 <= value <= 255)
            
            root@k-VirtualBox:/home/k/Documents/ping# ping --ttl a 1.1.1.1
                  ping: invalid value (`a' near `a')
            root@k-VirtualBox:/home/k/Documents/ping# ping --ttl a1 1.1.1.1
                  ping: invalid value (`a1' near `a1')
            root@k-VirtualBox:/home/k/Documents/ping# ping --ttl abc 1.1.1.1
                  ping: invalid value (`abc' near `abc')

  -v, --verbose              verbose output

  -w, --timeout=N            stop after N seconds
      erreurs:
            ping -w 1844674407370955161 1.1.1.1
                  -> ping: invalid argument: '1844674407370955161': out of range: 0 <= value <= 2147483647

      -d, --debug                set the SO_DEBUG option


  -f, --flood                flood ping (root only)
  -q, --quiet                quiet output

  -?, --help                 give this help list
      --usage                give a short usage message

      -- print                print le paquet en hexa
      -q


            ** BONUS: **

-- print                print le paquet en hexa
format :

adresse memoire |                   hexa                    | traduction ascii

00000000  30 31 32 33 34 35 36 37  38 39 41 42 43 44 45 46  |0123456789ABCDEF|
00000010  0a 2f 2a 20 2a 2a 2a 2a  2a 2a 2a 2a 2a 2a 2a 2a  |./* ************|
00000020  2a 2a 2a 2a 2a 2a 2a 2a  2a 2a 2a 2a 2a 2a 2a 2a  |****************|
*
00000040  2a 2a 20 2a 2f 0a 09 54  61 62 6c 65 20 77 69 74  |** */..Table wit|
00000050  68 20 54 41 42 73 20 28  30 39 29 0a 09 31 09 09  |h TABs (09)..1..|
00000060  32 09 09 33 0a 09 33 2e  31 34 09 36 2e 32 38 09  |2..3..3.14.6.28.|
00000070  39 2e 34 32 0a                                    |9.42.|
00000075


Pratiques et interessants:
        -m marque
              Utilise une marque pour tagguer les paquets en sortie.  Ceci est
              parfois utile au noyau pour diverses raisons.

        -c nombre
              S'arrêter après l'envoi de nombre paquets ECHO_REQUEST.  Combiné
              à l'option  -w deadline,  ping  doit recevoir ses nombre paquets
              ECHO_REPLY avant que la temporisation n'expire.

        -p motif
              Vous pouvez spécifier jusqu'à 16 octets de bourrage pour remplir
              complètement  le paquet  à  envoyer.  Ceci  est  utile  dans  le
              diagnostic  des problèmes  dépendant des données dans un réseau.
              Par exemple,  -p ff forcera le remplissage du paquet envoyé avec
              des 1.

        -t ttl
              Spécifie le champ IP « Time to Live ».

        -W timeout
              Temps d'attente d'une réponse (en secondes) (NdT : ?)
        -b     
              Permet de « pinger » une adresse de diffusion (broadcast).

        -d                 use SO_DEBUG socket option

        -f
              Mode inondation (dit « Flood »).Pour chaque ECHO_REQUEST envoyé,
              un  point  est  affiché,  et  pour  chaque ECHO_REPLY  reçu,  un
              effacement  arrière  (backspace)  est  affiché.  Ceci  donne  un
              affichage rapide du nombre de paquets qui ont été jetés. 
              Si aucun intervalle n'est fourni,  ping fixe l'intervalle à zéro
              et émet  des paquets  dès qu'en  reviennent  d'autres,  avec  un
              minimum de 100 fois/s.  Seul le super-utilisateur  peut utiliser
              cette option avec un intervalle à zéro.
        -i intervalle
              Attendre intervalle secondes  entre chaque  envoi de paquet.  Le
              délai par défaut est normalement d'une seconde  (ou nul  en mode
              inondation). Seul le super-utilisateur peut fixer l'intervalle à
              des valeurs inférieures à 0.2 secondes.

Simples à faire:
       -D
              Affiche un horodatage avant chaque ligne.  Le timestamp respecte
              le format  utilisé par  la  fonction gettimeofday  (temps unix +
              microsecondes). Cette option n'est pas toujours disponible.
        -q
              Sortie silencieuse. Rien n'est affiché sauf les lignes de résumé
              au démarrage et à la fin de l'exécution.
        -a
              ping audible. 


              Payload Options

--data <hex string> (Append custom binary data to sent packets)

This option lets you include binary data as payload in sent packets. <hex string> may be specified in any of the following formats: 0xAABBCCDDEEFF<...>, AABBCCDDEEFF<...> or \xAA\xBB\xCC\xDD\xEE\xFF<...>. Examples of use are --data 0xdeadbeef and --data \xCA\xFE\x09. Note that if you specify a number like 0x00ff no byte-order conversion is performed. Make sure you specify the information in the byte order expected by the receiver.

--data-string <string> (Append custom string to sent packets)

This option lets you include a regular string as payload in sent packets. <string> can contain any string. However, note that some characters may depend on your system's locale and the receiver may not see the same information. Also, make sure you enclose the string in double quotes and escape any special characters from the shell. Example: --data-string "Jimmy Jazz...".

--data-length <len> (Append random data to sent packets)

This option lets you include <len> random bytes of data as payload in sent packets. <len> must be an integer in the range [0–65400]. However, values higher than 1400 are not recommended because it may not be possible to transmit packets due to network MTU limitations.