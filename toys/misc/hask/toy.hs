import Control.Applicative
import Control.Monad
import System.IO
import System.IO (isEOF)
import Data.Char

-- checkout https://wiki.haskell.org/Introduction_to_Haskell_IO/Actions
    --
-- main :: IO ()
-- main =  do c <- getChar
--            putChar c

-- ready :: IO Bool
-- ready =  do c <- getChar
--             return (c == 'y')

myGetLine :: IO String
myGetLine =  do c <- getChar
                if c == '\n'
                   then return ""
                   else do l <- getLine
                           return (c:l)


-- main :: IO ()
-- main = do
--  input <- getLine
--  print input
--  inputs <- replicateM (read input) getLine
--  print $ length inputs

main :: IO ()
main = myLoop
myLoop = do done <- isEOF
            if done
              then putStrLn "Bye!"
              else do inp <- myGetLine
                      -- putStrLn (map toUpper inp)
                      putStrLn inp
                      myLoop

--main :: IO ()
--main = do n_temp <- getLine
--          let n = read n_temp :: Int
--          ar_temp <- getLine
--          let ar = map read $ words ar_temp :: [Int]
--          putChar 'a'

getMultipleLines :: Int -> IO [String]
getMultipleLines n
   | n <= 0 = return []
   | otherwise = do          
       x <- getLine         
       xs <- getMultipleLines (n-1)    
       let ret = (x:xs)    
       print ret
       return ret          

getLines :: IO [String]
getLines = do
  x <- getLine
  if x == ""
    then return []
    else do
      xs <- getLines
      return (x:xs)

