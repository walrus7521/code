module Main where

import Graphics.Gloss

width, height, offset :: Int
width = 300
height = 300
offset = 100

window :: Display
window = InWindow "Pong" (width, height) (offset,offset)

background :: Color
background = black

drawing :: Picture
drawing = pictures [ball, walls,
                    mkPaddle rose 120 (-20),
                    mkPaddle orange (-120) 40]

  [ translate (-20) (-100) $ color ballColor $ circleSolid 30
  , translate (30) (50) $ color paddleColor $ rectangleSolid 10 50
  ]
  where
    ballColor = dark red 
    paddleColor = light (light blue)


main :: IO ()
main = display window background drawing

--main = putStrLn "Hello, Haskell!"
