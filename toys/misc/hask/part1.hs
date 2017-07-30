

-- main = putStrLn "Hello, world!"

x1 :: Int
x1 = 3
y1 :: Int --Float
y1 = 4

main = do
  putStrLn "What is your name?"
  name <- getLine
  putStrLn $ name ++ "! This is a very nice name."
  putStrLn "Where do you live?"
  city <- getLine
  putStrLn $ "Hey, I love " ++ city ++ "!"
  print $ f 2 2
  print $ g 3 2
  print $ h 3 2
  print (f 2.3 4.2)
  print $ j 1
  print $ k 1 2
  print $ m 1

  print (f2 x1 y1)

-- this is a function, if you don't declare type
-- it essentially becomes polymorphic
f x y = x*x + y*y
g x y = x*x - y*y + x - y

-- declare the type of function
h :: Int -> Int -> Int
h x y = x + y

-- From Int to Float
j :: Int -> Float
j x = 3.14

k :: Num a => a -> a -> a
k x y = x+y
m :: Num a => a -> a
-- m = k 3
m = \y -> 3 + y
-- m y <=> 3*3 + y*y

f2 :: Num a => a -> a -> a
f2 x y = x*x + y*y

