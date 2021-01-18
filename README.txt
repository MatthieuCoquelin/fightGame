###############################################################
#                       Paramétrage du jeu                    #
############################################################### 
Avant de jouer il faut au préalable compléter les fichiers de 
paramétrage. (Il seront fournis remplis mais peuvent 
être modifiés si on veut changer des armes ou des personnage)
Chaque personnage a son fichier de configuration et une arme 
avec son fichier de configuration.
Pour modifier un fichier de config il faut suivre la procédure
suivante:
    - pour les personnages(forme teamICharacterJ où I est le 
numéro de l'équipe du personnage et J le personnage conserné):
1) ouvrir le fichier characters.jdc
2) choisir un personnage en copiant collant ses 
caractéristrique (entre Character et EndCharacter) dans le 
fichier de configuration du personnage souhaité.
Dans le cas présent il reste 2 colonnes d'information(la 
colonne de gauche, le nom des attribut et la colonne de 
droite, les attribut des personnages).
3) Supprimer UNIQUEMENT le nom de chaquue attibut (soit la 
colonne de gauche dans fichier du personnage)
4) NE toucher PLUS a RIEN dans le fichier précédement modifié  

    - pour les armes(forme weaponTeamICharacterJ où I est le 
numéro de l'équipe du personnage et J le personnage conserné):
1) ouvrir le fichier weapons.jdc
2) choisir une arme en copiant collant ses 
caractéristrique (entre Weapon et EndWeapon) dans le 
fichier de configuration de l'arme souhaitée.
Dans le cas présent il reste 2 colonnes d'information(la 
colonne de gauche, le nom des attribut et la colonne de 
droite, les attribut des armes).
3) Supprimer UNIQUEMENT le nom de chaquue attibut (soit la 
colonne de gauche dans fichier de l'arme)
4) NE toucher PLUS a RIEN dans le fichier précédement modifié  

!!!EN AUCUN CAS les nom des fichier de configuration (fichier 
".txt" sauf README) ne doivent être modifiés !!!

Tant que ces règles sont appliqués vous pouvez modifier les 
fichier de configuration comme bon vous semble.

###############################################################
#                   Initialisation du jeu                     #
############################################################### 
Sauf exeption, A TOUT MOMENT DU JEU, Team1 et Team2 font 
référence aux différent joueur(chaque joueur a une équipe),
Character1, Character2 et Character3 font référence au 
personnages du jeu et seront utilisé dans l'ordre ou il sont 
nommé dans les fichier de configuration. Il en va de même pour 
les armes.
Suivant donc l'ordre présenté on demandera alors pour chaque 
personnage si il doit être équipé d'une arme.
Si une arme attribué dans les fichier txt est incorrecte elle
sera retiré du personnage et ce dernier se battera a mains 
nues tout au lon du combat (on pourra alors remmarquer un 
"0" en face de l'onglet arme dans l'affichage tour par tour 
du personnage concerné).
En fonction de l'arme détenue les stats des personnages sont 
modifiées. 
La premièrer description de tous les personnage s'affiche: le
jeu peu commencer.

###############################################################
#                   Déroulement d'un tour                     #
############################################################### 
1) On détermine qui jouera en premier .
2) On regarde si le pernnage est empoisonné.
3) Le personnage choisi son action et la cible si nécessaire.
4) On met a jour les états du personnage.
5) On reset la vitesse du personnage.
6) On regarde si les personnages sur le terrain sont en vie.
7) On présente les personnages sur le terrain.
8) On vérifi si il y a au moins un perssonnage dans chaque 
équipe. Sinon c'est la fin du jeu.
