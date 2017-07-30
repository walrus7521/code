import Data.Complex

-- haskell-fast-hard-part-4

square x = x*x

-- type construction
type Name = String
type Color = String


main = do
  print $ square 2
  print $ square 2.1
  print $ square (2 :+ 1)
  
