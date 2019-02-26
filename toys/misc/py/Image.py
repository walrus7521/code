#!/usr/bin/env python3

import os
import pickle

class ImageError(Exception): pass
class CoordinateError(ImageError): pass
class LoadError(ImageError): pass
class SaveError(ImageError): pass
class ExportError(ImageError): pass
class NoFilenameError(ImageError): pass

class Image:
    def __init__(self, width, height, filename="",
            background="#FFFFFF"):
        self.filename = filename
        self.__background = background
        self.__data = {}
        self.__width = width
        self.__height = height
        self.__colors = {self.__background}

    @property
    def background(self):
        return self.__background

    @property
    def width(self):
        return self.__width

    @property
    def height(self):
        return self.__height

    @property
    def colors(self):
        return self.__colors

    def __getitem__(self, coordinate):
        assert len(coordinate) == 2, "coordinate should be a 2-tuple"
        if (not (0 <= coordinate[0] < self.width) or
            not (0 <= coordinate[1] < self.height)):
            raise CoordinateError(str(coordinate))
        return self.__data.get(tuple(coordinate), self.__background)

    def __setitem(self, coordinate, color):
        assert len(coordinate) == 2, "coordinate should be a 2-tuple"
        if (not (0 <= coordinate[0] < self.width) or
            not (0 <= coordinate[1] < self.height)):
            raise CoordinateError(str(coordinate))
        if color == self.__background:
            self.__data.pop(tuple(coordinate), None)
        else:
            self.__data[tuple(coordinate)] = color
            self.__colors.add(color)

    def __delitem(self, coordinate):
        assert len(coordinate) == 2, "coordinate should be a 2-tuple"
        if (not (0 <= coordinate[0] < self.width) or
            not (0 <= coordinate[1] < self.height)):
            raise CoordinateError(str(coordinate))
        self.__data.pop(tuple(coordinate), None)







def main():
    print("dude")
    border_color = "#FF0000"  # red
    square_color = "#0000FF"  # blue
    width, height = 240, 60
    midx, midy = width // 2, height //2

    image = Image(width, height, "square_eye.img")
"""
    for x in range(width):
        for y in range(height):
            if x < 5 or x >= width-5 or y < 5 or y >= height-5:
                image[x,y] = border_color
            elif midx-20 < x < midx+20 and midy-20 < y < midy+20:
                image[x,y] = square_color

    image.save()
    image.export("square_eye.xpm")
"""

if __name__ == "__main__":
    main()

