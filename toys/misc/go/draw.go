package main

import (
        "github.com/llgcode/draw2d/draw2dimg"

        "image"
        "image/color"
)

func main() {
        i := image.NewRGBA(image.Rect(0, 0, 200, 200))
        gc := draw2dimg.NewGraphicContext(i)
        gc.Save()
        gc.SetStrokeColor(color.Black)
        gc.SetFillColor(color.Black)
        draw2d.Rect(gc, 10, 10, 100, 100)
        gc.FillStroke()
        gc.Restore()

        draw2dimg.SaveToPngFile("yay-rectangle.png", i)
}
