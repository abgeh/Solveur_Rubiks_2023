

RUBIKS CUBE SOLVER 2022/2023

-Le dossier Arduino contient le sketch à televerser sur la STM32.

-Le dossier python contient converttobitmap, rubiksmapping, rubikssolver, main (qui appelle les trois premières). Il contient également scriptserial qui effectue la capture d'une image et enregistre un fichier txt (il faut directement appuyer sur le bouton utilisateur après l'execution du script).

-Nous avons ajouté trois fichiers txt comme exemples (trois images du cube), il faut executer le main et les images seront créées, ainsi que le fichier couleurs et le fichier solution. 

-GUIDE DE CAPTURE

	Il faut organiser le cube de telle sorte que les six faces centrales soient: 
		Jaune : Haut/UP 
		Bleu : Gauche/LEFT
		Rouge : Devant/FRONT
		Vert Droite/RIGHT
		Orange Derrière/BACK
		Blanc Bas/DOWN  

	Cette configuration doit être celle qui est toujours utilisée pour la capture. On commence avec Jaune (Haut) et Rouge (Devant) pour la première capture, ensuite on fait une rotation afin d'avoir Vert(Haut) et Blanc(Devant) pour la deuxième, et enfin Orange(Haut) et Bleu(Devant) pour la dernière capture.


	Cette configuration doit être celle qui est toujours utilisée pour la capture. On commence avec Jaune (Haut) et Rouge (Devant) pour la première capture, ensuite on fait une rotation afin d'avoir Vert(Haut) et Blanc(Devant) pour la deuxième, et enfin Orange(Haut) et Bleu(Devant) pour la dernière capture.


