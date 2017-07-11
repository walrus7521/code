-- haskell-fast-hard-part-3

import Data.List -- for foldl'

-- Version 1
-- evenSum :: [Integer] -> Integer
evenSum :: Integral a => [a] -> a
evenSum l = accumSum 0 l

accumSum n l = if l == []
                  then n
                  else let x = head l
                           xs = tail l
                       in if even x
                              then accumSum (n+x) xs
                              else accumSum n xs

-- Version 2
evenSum2 :: Integral a => [a] -> a
evenSum2 l = accumSum2 0 l
  where accumSum2 n l =
          if l == []
             then n
             else let x = head l
                      xs = tail l
                  in if even x
                        then accumSum2 (n+x) xs
                        else accumSum2 n xs

-- Version 3 pattern matching
-- evenSum3 :: Integral a => [a] -> a
evenSum3 l = accumSum3 0 l 
  where
    accumSum3 n [] = n
    accumSum3 n (x:xs) =
      if even x
         then accumSum3 (n+x) xs
         else accumSum3 n xs

-- Version 3b
evenSum3b l = accumSum3b 0 l
  where
    accumSum3b n [] = n
    accumSum3b n (x:xs) =
      if even x
         then accumSum3b (n+x) xs
         else accumSum3b n xs

-- Version 4
evenSum4 :: Integral a => [a] -> a
evenSum4 = accumSum4 0
  where
    accumSum4 n [] = n
    accumSum4 n (x:xs) =
      if even x
         then accumSum4 (n+x) xs
         else accumSum4 n xs

-- higher order functions
-- Version 5
evenSum5 l = mysum5 0 (filter even l)
  where
    mysum5 n [] = n
    mysum5 n (x:xs) = mysum5 (n+x) xs

-- Version 6
-- foldl' isn't accessible by default
-- we need to import it from the module Data.List
evenSum6 l = foldl' mysum6 0 (filter even l)
  where mysum6 acc value = acc + value

-- Version 7
-- use lambda for mysum6
evenSum7 l = foldl' (\x y -> x+y) 0 (filter even l)

-- Version 8
evenSum8 :: Integral a => [a] -> a
evenSum8 l = foldl' (+) 0 (filter even l)

-- using foldl'
-- show prod [3,4,5] will return 3*4*5=60
prod :: [Integer] -> Integer
prod [] = 1
prod (x:xs) = x*prod xs

-- no rewrite using foldl'
prod2 = foldl' (*) 1 -- 1 is becuse multiply, if add then 0
add2 = foldl' (+) 0 -- 0 is becuse add

-- now checkout the (.) operator
-- Version 9
evenSum9 :: Integral a => [a] -> a
evenSum9 = (foldl' (+) 0) . (filter even)

oddSum :: Integral a => [a] -> a
oddSum = (foldl' (+) 0) . (filter odd)

-- Version 10
sum' :: (Num a) => [a] -> a
sum' = foldl' (+) 0
evenSum10 :: Integral a => [a] -> a
evenSum10 = sum' . (filter even)

squareEvenSum = sum' . (filter even) . (map (^2))
squareEvenSum' = evenSum10 . (map (^2))

main = do
  print $ add2 [3,4,5]
  print $ prod2 [3,4,5]
  print $ prod [3,4,5]
  print $ oddSum [1 .. 10]
  print $ squareEvenSum [1 .. 10]
  print $ evenSum10 [1 .. 10]
  print $ evenSum7 [1 .. 10]
  -- print $ evenSum6 [1 .. 10]
  --print $ evenSum4 [1 .. 10]
  --print $ evenSum3b [1 .. 10]
  --print $ evenSum3 [1 .. 10]
  --print $ evenSum2 [1 .. 10]
  --print $ evenSum [1 .. 10]
  print $ filter even [1..10]
  print $ filter odd [1..10]
  print $ is_even 3
  print $ is_odd 3
  print $ my_tail [1,2,3]
  print $ my_head [42,8,9]
  print $ my_tail [2,43]


is_even :: Integral a => a -> Bool
is_even n = if n `mod` 2 == 0
           then True
           else False

is_odd :: Integral a => a -> Bool
is_odd n = if n `mod` 2 /= 0
           then True
           else False
                
-- even n = if mod n 2 == 0 then True else False

my_head :: [a] -> a
my_head l = head l
                    
my_tail :: [a] -> [a]
my_tail l = tail l

