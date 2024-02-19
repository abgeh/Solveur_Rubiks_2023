# -*- coding: utf-8 -*-
"""
Created on Mon Apr 24 13:50:21 2023

@author: ahmed
"""
import struct
import os
import cv2
import numpy as np

#import scriptserial
from converttobitmap import convertToBitmap
from rubiksmapping import rubiksmapping
from rubikssolver import solution





#%%conversion de fichiers bruts txt en fichiers bmp et mapping du cube
if os.path.exists('rubiks_cube_colors.txt'):
    os.remove('rubiks_cube_colors.txt')
for i in range (1, 4):
    for j in range(1, 100):
        file_name = f'file{j}.txt'
        img_name= f'img{j}.bmp'
        if not os.path.exists(file_name):
            break
        if not os.path.exists(img_name):
            break

    convertToBitmap(file_name,img_name)
    rubiksmapping(img_name)

#%%solution


with open("rubiks_cube_colors.txt", "r") as file:
    # Read the contents of the file into a string variable
    original_str = file.read()


# Ordre désiré : On change le "sens de lecture" des cubes dans les faces: 741852963 pour la face 1, 369258147 pour les faces 2 et 3, et on change rien sur les dernières. 
#On fait ça car la position du cube lors de la capture n'est pas celle que l'algorithme de solution prend en paramètre
new_order = [6, 3, 0, 7, 4, 1, 8, 5, 2, 11, 14, 17, 10, 13, 16, 9, 12, 15, 20, 23, 26, 19, 22, 25, 18, 21, 24]
new_str_start = "".join([original_str[i] for i in new_order])
new_str_end = original_str[-27:]
new_str = new_str_start + new_str_end
print (new_str.lower())

#On change à présent l'ordre des six faces pour que l'algorithme de solution puisse le prendre en paramètre:
#l'ordre souhaité est : 4-3-5-6-2-1
original_str = new_str
sets_of_nine = [original_str[i:i+9] for i in range(0, len(original_str), 9)]
new_order = [3, 2, 4, 5, 1, 0]
reordered_sets = [sets_of_nine[i] for i in new_order]
new_str = "".join(reordered_sets)
print(new_str)

#on écrit le string final sur le fichier couleur (on écrase l'ancien)...
f = open('rubiks_cube_colors.txt', "w")
f.write(new_str + '\n')
f.close()

#et on donne la solution
file_mapping='rubiks_cube_colors.txt'
solution(file_mapping)


