module Main where

import qualified Data.Map as M

main = do
    let emptyMap = M.empty
        mapWithKeys = M.insert 1 "One" emptyMap
        mapWithKeys' = M.insert 5 "Five" mapWithKeys
    putStrLn $ mapWithKeys' M.! 5
