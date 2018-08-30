import Control.Applicative
import Control.Monad
import System.IO


main :: IO ()
main = do
    n_temp <- getLine
    let n = read n_temp :: Int
    ar_temp <- getLine
    let ar = map read $ words ar_temp :: [Int]
    return 'a'
    
--getMultipleLines :: Int -> IO [String]
--getMultipleLines n
--   | n <= 0 = return []
--   | otherwise = do          
--       x <- getLine         
--       xs <- getMultipleLines (n-1)    
--       let ret = (x:xs)    
--       return ret          

