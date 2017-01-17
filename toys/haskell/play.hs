import System.Environment
import System.IO
import Control.Monad
import System.IO.Unsafe 

-- myNum :: Int                 -- int myNum() {
--myNum = 12+13                --   return 12+13; }

-- square :: Int -> Int         -- int square(int n) {
-- square n = n*n               --   return = n*n;  }

-- double :: Int -> Int         -- int double(int n) {
-- double n = 2*n               --   return 2*n;  }

-- dubSqr :: Int -> Int         -- int dubSqr(int n) { 
-- dubSqr n = square (double n) --   return square(double(n)); }

-- main = putStrLn "hello world"
-- main = putStrLn myNum

 
-- | 'main' runs the main program
--main :: IO ()
--main = getArgs >>= print . haqify . head
 
--haqify s = "Haq! " ++ s

--module Main where

-- import BinaryTree

-- foo :: Integer -> Integer
-- foo 0 = 0
-- foo n = n + foo (n-1)
-- main = print $ foo 1

-- main = do  
--         let list = []
--         handle <- openFile "test.txt" ReadMode
--         contents <- hGetContents handle
--         let singlewords = words contents
--             list = f singlewords
--             --list = singlewords
--         print list
--         hClose handle   
-- 
-- f :: [String] -> [Int]
-- f = map read

main = do
   args <- getArgs
   content <- readFile (args !! 0)
   let linesOfFiles = lines content
   print linesOfFiles



