# -*- coding: utf-8 -*-
"""
Created on Sun Apr 23 21:21:07 2023

@author: ahmed
"""
import struct
import os

def convertToBitmap(infile,outfile):
    # Open the input file
    with open(infile, 'r') as f:
        lines = f.readlines()

    # Reverse the order of the lines
    lines = reversed(lines)

    # Create a new bitmap file
    with open(outfile, 'wb') as f:
        # Bitmap file header
        file_header = bytearray([0x42, 0x4D, 0x38, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00])
        # Bitmap information header
        info_header = bytearray([0x28, 0x00,
0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x84, 0x03, 0x00, 0x47, 0x30, 0x00, 0x00, 0x47, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        # Compute image width and height
        
        width = 320
        height = 240
        pixel_data_size = width * height * 3
        row_size = width * 3
        pixel_array_size = pixel_data_size 
        file_size = 54 + pixel_array_size

        # Write bitmap file header to output file
        f.write(file_header)
        # Write bitmap information header to output file
        f.write(info_header)
        # Write pixel data to output file
        for line in lines:
            for value in reversed(line.split()):
                f.write(bytes([int(value)]))

    return True



#infile = file_name
#outfile= img_name

#infile = 'file1.txt'
#outfile = 'img1.bmp'

