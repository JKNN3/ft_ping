**checksum:** petite quantité de données calculée à partir d'une plus grosse quantité de données. Permett la verification de l'intégrité des données (très bonne fidélité). Souvent utilisé apres une transmission, une copie, un stockage.

getaddrinfo()
https://gist.github.com/jirihnidek/bf7a2363e480491da72301b228b35d5d

getnameinfo()

https://www.developpez.net/forums/d4485/c-cpp/c/reseau/raw-socket-forger-propre-packet-icmp-pinge/


traceroute implementation in python

https://www.geeksforgeeks.org/traceroute-implementation-on-python/



bonus:

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