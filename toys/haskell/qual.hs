module Main where
 
import qualified Data.Map as M
 
errorsPerLine = M.fromList
    [ ("Chris", 72), ("Don", 60), ("Simon", 25), ("Bart", 42) ]
 
main = do putStrLn "Who are you?"
          name <- getLine
          case M.lookup name errorsPerLine of
              Nothing -> putStrLn "I don't know you"
              Just n  -> do putStr "Hello: "
                            print name
                            print n

