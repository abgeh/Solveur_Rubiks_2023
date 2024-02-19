
#%%# import cv2

# # Load the input image
# image = cv2.imread('img3.bmp')

# # Define the centers of the squares in the Rubik's Cube
# centers = [(59, 88), (94,85), (135,65), (57,139), (92,139), (135,139), (55,182), (90,186), (132,188),
#            (188,63), (232,83), (268,87), (185,138), (230,138), (269,138), (185,200), (230,190), (269,184)]

# # Define the colors of the Rubik's Cube
# colors = []

# # Loop over each center
# for center in centers:
#     # Crop the region around the center
#     x, y = center
#     square = image[y-2:y+2, x-2:x+2]

#     # Compute the average color of the region
    
#     average_color = cv2.mean(square)[:3]
#     r = average_color[2]
#     g = average_color[1]
#     b = average_color[0]
    
#     if (r > 140 and g < 120 and b < 120):
#        color_name = 'r';
#     elif (r > 170 and g < 115 and b < 115):
#        color_name = 'o';
#     elif (r < 100 and g > 90 and b < 100):
#        color_name = 'g';
#     elif (r < 120 and g < 110 and b > 110):
#        color_name = 'b';
#     elif (r > 150 and g > 150 and b > 170):
#        color_name = 'w';
#     elif (r > 100 and g > 100 and b < 170):
#        color_name = 'y';
#     else:
#        color_name = 'u'  # unknown color


#     # Add the color name to the list of colors
#     colors.append(color_name)

# # Write the colors to a file
# with open('rubiks_cube_colors.txt', 'w') as f:
#     f.write(''.join(colors))



#%%
import cv2
import numpy as np

def replace_colors(string):
    string = string.replace('b', 'L')
    string = string.replace('r', 'F')
    string = string.replace('w', 'D')
    string = string.replace('g', 'R')
    string = string.replace('o', 'B')
    string = string.replace('y', 'U')
    return string

def rubiksmapping(img_name):
    # Load the input image
    image = cv2.imread(img_name)
    
    # Define the centers of the squares in the Rubik's Cube
    centers = [(59, 88), (94,85), (135,65), (57,139), (92,139), (135,139), (55,185), (90,186), (132,188),
               (188,63), (232,83), (268,87), (185,138), (230,138), (269,138), (185,200), (230,190), (269,184)]
    
    # Define the color ranges for each color
    color_ranges = {
        'r': ((0, 0, 100), (50, 50, 255)),
        'g': ((0, 100, 0), (50, 255, 50)),
        'b': ((100, 0, 0), (255, 50, 50)),
        'y': ((0, 100, 100), (50, 255, 255)),
        'o': ((0, 70, 120), (50, 150, 255)),
        'w': ((200, 200, 200), (255, 255, 255))
    }
    
    # Define the colors of the Rubik's Cube
    colors = []
    
    # Loop over each center
    for center in centers:
        # Crop the region around the center
        x, y = center
        square = image[y-2:y+2, x-2:x+2]
    
        # Check that the cropped region is not empty
        if square is None or square.size == 0:
            print(f"Error: Cropped region at center {center} is empty")
            continue  # skip to the next center if the region is empty
    
        # Compute the histogram of the region in the HSV color space
        hsv = cv2.cvtColor(square, cv2.COLOR_BGR2HSV)
        hist = cv2.calcHist([hsv], [0], None, [180], [0, 180])
    
        # Find the dominant hue in the histogram
        dom_hue_bin = np.argmax(hist)
        dom_hue_deg = int(round((dom_hue_bin / 180) * 360))
        print (dom_hue_deg)
        average_color = cv2.mean(square)[:3]
        r = average_color[2]
        g = average_color[1]
        b = average_color[0]
    
        # Determine the color name based on the dominant hue
        if 0 <= dom_hue_deg < 15 or 330 <= dom_hue_deg <= 360:
            color_name = 'r'
        elif 30 <= dom_hue_deg < 90:
            color_name = 'y'
        elif 90 <= dom_hue_deg < 160:
            color_name = 'g'
        # elif 150 <= dom_hue_deg < 210:
        #     color_name = 'w'
        elif 213 <= dom_hue_deg < 270:
            color_name = 'b'  # orange
        elif 15 <= dom_hue_deg < 30:
            color_name = 'o'
            
        # elif (r < 100 and g > 90 and b < 100):
        #     color_name = 'g';
        elif (r > 150 and g > 150 and b > 170):
            color_name = 'w';
        else:
            color_name = 'u'  # unknown color
    
        # Add the color name to the list of colors
        colors.append(color_name)
    
    
    # Write the colors to a file
    with open('rubiks_cube_colors.txt', 'a') as f:
        print(''.join(colors))
        f.write(''.join(colors))

# my_string = 'ggwwbyyrborboowyorgbgywbbbwwryorboyrrgboyywggogywgworr'
# new_string = replace_colors(my_string)
# print(new_string)

