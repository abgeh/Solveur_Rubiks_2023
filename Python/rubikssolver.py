# -*- coding: utf-8 -*-
"""
Created on Mon Apr 24 13:17:00 2023

@author: ahmed
"""
import collections.abc
#hyper needs the four following aliases to be done manually.
collections.Iterable = collections.abc.Iterable
collections.Mapping = collections.abc.Mapping
collections.MutableSet = collections.abc.MutableSet
collections.MutableMapping = collections.abc.MutableMapping

from rubik_solver import utils
from pathlib import Path




def solution(file_name):       
    path = Path(file_name)
    while(1):
        if(path.is_file() == True):
            with open(file_name) as file:
                cube = file.readlines()
            cube = " ".join(cube)
            sol = utils.solve(cube, 'Kociemba')
            sol = ' '.join([str(elem) for elem in sol])
            f = open('solution.txt', "w")
            f.write(sol + '\n')
            
            #ecriture des couleurs de faces dans l'environnement du site (en changeant le code couleur)
            cube_site = cube.replace('w', 'D')
            cube_site = cube_site.replace('r', 'F')
            cube_site = cube_site.replace('g', 'R')
            cube_site = cube_site.replace('o', 'B')
            cube_site = cube_site.replace('b', 'L')
            cube_site = cube_site.replace('y', 'U')
            f.write(cube_site)
            f.close()
            break;