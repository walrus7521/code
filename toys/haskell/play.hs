import System.Environment

myNum :: Int                 -- int myNum() {
myNum = 12+13                --   return 12+13; }

-- square :: Int -> Int         -- int square(int n) {
-- square n = n*n               --   return = n*n;  }

-- double :: Int -> Int         -- int double(int n) {
-- double n = 2*n               --   return 2*n;  }

-- dubSqr :: Int -> Int         -- int dubSqr(int n) { 
-- dubSqr n = square (double n) --   return square(double(n)); }

-- main = putStrLn "hello world"
-- main = putStrLn myNum

 
-- | 'main' runs the main program
main :: IO ()
main = getArgs >>= print . haqify . head
 
haqify s = "Haq! " ++ s


