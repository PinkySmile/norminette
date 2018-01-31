# norminette
Norminette en C à la norme de la promo 2022

## USAGE :
	./norminette [-vfunahd] [-I<chemin>] [dossiers/fichiers]

## DESCRIPTION :
	-a :		Active les options v, u et n (equivaut à -vun)

	-d :		Flag de debug à éviter

	-f :		Change la langue en français

	-h :		Affiche cette page d'aide

	-n :		Affiche le nom des fichiers scannés

	-u :		Cherche les fichiers inutiles dans le repo et
			les noms invalides

	-v :		Affiche la ligne contenant l'erreur et met en
			valeur l'erreur

	-I<chemin> : 	Utiliser le flag I permet d'activer la détection des
			fonctions dans les dossiers et fichiers .c. Utiliser
			ce flag transforme tous les charactères suivants en
			en un chemin d'accès vers un dossier ou fichier. La
			norminette va sauvegarder toutes les fonctions déclarées
			dans les fichier .c et .h et les interprèter comme fonctions
			autorisées. Toute fonction n'étant pas déclaré ici seront
			donc considéré comme des fonction interdites. Les fonctions
			systèmes autorisées doivent avoir une définition dans un
			fichier .h ou .c. La définition des fonctions n'as pas a être
			complète ! Vous pouvez toutes les déclarer comme ceci
					void fonction();
			À noter aussi que plusieurs -I peuvent être utiliser en même
			temps si vous avez plusieurs dossiers d'include comme avec
			la CSMFL par exemple. Les includes de la CSML sont stocké dans le
			dossier /usr/local/include/SFML.
			Utiliser donc -I/usr/local/include/SFML pour vos projets graphiques.

## EXEMPLES :
	./norminette :
		Lance un scan basique dans le dossier courant

	./norminette src test.c :
		Lance un scan basique dans le dossier 'src' et sur le fichier 'test.c'

	./norminette -vfIinclude -I/usr -I../sys.h
		Lance un scan en mode verbeux en français avec la détections des fonctions interdites
		avec les fonctions autorisées dans les dossiers 'include' et '/usr' et dans le fichier '../sys.h'

## VALEURS DE RETOUR :
	Si aucune erreur n'est trouvée, le programme sort avec le code 0.
	Si une ou plusieurs erreurs ont été détectées, le programme sort avec le code 1.

## RAPPORTER UN BUG :
	Si vous  trouvez un bug, mettez  à jour  le  programme
	(Utilisez le script 'update.sh' dans le repo ou encore
	<votre alias>-update  si vous  avez utilisé  le script
	d'installation). Si le bug persiste, lancez 'debug.sh'
	(<votre alias>-debug) avec, comme argument, le fichier
	ayant causé  le bug. Envoyez moi  ensuite  le  fichier
	scan.log (vous pouvez aussi  joindre le fichier posant
	problème)   à   l'addresse  "andgel.halley@epitech.eu"
	en expliquant  le bug rencontrez  et je le  corrigerai
	le plus vite possible !

	Note : Inutile de le lancer en mode debug si  ce n'est
	qu'un problème d'affichage (faute de frappe, ...)
	Les   scripts   fournis   (update.sh,   debug.sh)   ne
	fonctionneront que  si la  norminette se  trouve de le
	dossier ~/norminette.  Vous pouvez sinon  les modifier
	pour les faire  fonctionner avec votre chemain d'accès
	N'hésitez pas à m'envoyer des suggestions par mail !
