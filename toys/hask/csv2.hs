{-# LANGUAGE BangPatterns, ScopedTypeVariables #-}

-- uses: cabal install cassava
--

-- sample CSV content:
-- sumSalaries rs = sum [salary | Right (_ :: String, salary :: Int) <- rs]
-- John Doe,50000
-- Jane Doe,60000

-- import Control.Monad
-- import qualified Data.ByteString as BL
-- import Data.Csv.Incremental
-- import System.Exit
-- import System.IO

-- main :: IO ()
-- main = withFile "test.csv" ReadMode $ \ csvFile -> do
--     let loop !_ (Fail _ errMsg) = putStrLn errMsg >> exitFailure
--         loop acc (Many rs k)    = loop (acc + sumPullDowns rs) =<< feed k
--         loop acc (Done rs)      = putStrLn $ "Total pulldowns: " ++
--                                   show (sumPullDowns rs + acc)
-- 
--         feed k = do
--             isEof <- hIsEOF csvFile
--             if isEof
--                 then return $ k B.empty
--                 else k `fmap` B.hGetSome csvFile 4096
--     loop 0 (decode NoHeader)
--   where
--     sumPullDowns rs = sum [pulldown | Right (frame :: Int, bogus1 :: Int, pulldown :: Int, bogus2 :: Int) <- rs]
-- 

-- #2
-- import qualified Data.ByteString.Lazy as BL
-- import qualified Data.Vector as V
-- import Data.Csv
-- import Data.Foldable


-- main = do
--    csv <- BL.readFile "test.csv"
--    let Right res = decode HasHeader csv :: Either String (V.Vector(V.Vector(BL.ByteString)))
--    print $ res V.! 0


{-# LANGUAGE OverloadedStrings #-}

import Control.Applicative
import qualified Data.ByteString.Lazy as BL
import Data.Csv
import qualified Data.Vector as V

data Person = Person
    { name   :: !Int
    , salary :: !Int
    , num1   :: !Int
    , num2   :: !Int
    }

instance FromNamedRecord Person where
    parseNamedRecord r = Person <*> r .: "name" <*> r .: "salary" <*> r .: "num1" <*> y r .: "num2"

main :: IO ()
main = do
    csvData <- BL.readFile "test.csv"
    case decodeByName csvData of
        Left err -> putStrLn err
        Right (_, v) -> V.forM_ v $ \ p ->
            putStrLn $ name p ++ " earns " ++ show (salary p) ++ " dollars"