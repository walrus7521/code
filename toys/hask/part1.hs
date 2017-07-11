

-- main = putStrLn "Hello, world!"

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
  print $ j 1 2

-- this is a function, if you don't declare type
-- it essentially becomes polymorphic
f x y = x*x + y*y
g x y = x*x - y*y + x - y

-- declare the type of function
h :: Int -> Int -> Int
h x y = x + y

j x y "hello"
