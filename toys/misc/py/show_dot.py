#!/usr/bin/python

# http://patriottech.weebly.com/uploads/3/7/9/7/37976741/teach_your_kids_to_code_a_parent-friendly_guide_to_python_programming__2015_.pdf

import pygame

pygame.init()
screen = pygame.display.set_mode([800,600])

keep_going = True
GREEN = (0,255,0) # RGB color triplet for GREEN
radius = 50

while keep_going:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            keep_going = False
    pygame.draw.circle(screen, GREEN, (100,100), radius)
    pygame.display.update()

pygame.quit()
