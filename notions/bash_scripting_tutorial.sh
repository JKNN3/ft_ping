
# https://www.youtube.com/watch?v=p0KKBmfiVl0


# https://www.youtube.com/watch?v=2733cRPudvI&list=PLT98CRl2KxKGj-VKtApD8-zCqSaN2mD4w&index=1


shebang ou hashbang est un header qu'on met en haut du script pour indiquer 
avec quell shell on va executer le script. 
    ex: #!/bin/bash
même si on execute le script avec zsh il utilisera bash
    on peut ajouter -x pour afficher le détail de l'exécution

pour la compréhension il vaut mieux ne créer que des variable avec des noms 
en bas de casse car les majscules sont les variables d'environnement système .

pour faire un calcul: expr devant
expr 1 + 2 - 14 \* 5
    faut escape les *, ca prend pas les float

to assign the result of a shell cmd to a variable, i have to put () arount it
like this: timestamp=$(date) and timestamp have the value of the date return

si le if statement a des brackets [ ], la cmd test est utilisée même sans être
explicitement écrite.
man test utilisation: test EXPRESSION
                      test
                      [ EXPRESSION ]
                      [ ]

    #!/bin/bash

    mynum=200

    if [ $mynum -eq 200 ]   # pas oublier les espaces apres le premier bracket et avant le second!!
    then
            echo "caca"
    else
            echo "pipi"
    fi
    
! = negation comme ailleurs makis tj avec des espaces
        if [ ! $mynum -eq 200 ]

-eq check if statement is equal
-ne check if statement is not equal
-gt check if statement is greater than
-lt check if statement is lower than            -> options of the test cmd (man test)


check in my home directory if a file named file exists

    if [ -f ~/file ]
    then
            echo "the file exist"
    else
            echo "pipi"
    fi

-f search for a file
-d search for a directorys

command1 && command2
    -> command 2 will be executed only if command1 succeed


if command -v $command

    -> command est une commande qui check si une commande existe/est utilisable


    EXIT CODES:

which cherche un executable et return son/leurs chemin/s

parfois, des fichiers sont importants et un simple script while file exist qui 
par exemple envoie un error msg si n'existe pas peut être très pratique (penser a 
mettre des petits sleep quand on fait des trucs comme ça)

while [ statement ]
do
    something
done

to read smth
IFS -> internal field separator

IFS='\n'

colors:

We need to add the -e option to echo for enable their interpretation.
ex:

#colors:
green="\e[32m"
yellow="\e[33m"
endcolor="\e[0m"

echo -e "test $yellow $line $green PASSED $endcolor"
