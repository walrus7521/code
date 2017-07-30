
fn a = a `div` length xs
    where
        a = 10
        xs = [1,2,3,4,5]

last2 xs = head (drop (length xs - 1) xs)

init2 xs = take (length xs - 1) xs

double x = x + x
quadruple x = double (double x)
factorial n = product [1..n]
average ns = sum ns `div` length ns

qsort :: Ord a => [a] -> [a]
qsort []     = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
    where
        smaller = [a | a <- xs, a <= x]
        larger  = [b | b <- xs, b > x]

seqn :: Monad m => [m a] -> m [a]
seqn []         = return []
seqn (act:acts) = do x <- act
                     xs <- seqn acts
                     return (x:xs)

bools :: [Bool]
bools = [True, False]

nums :: [[Int]]
nums = [[3,2],[2]]

add :: Int -> Int -> Int -> Int
add a b c = a+b+c

copy :: a -> (a,a)
copy a = (a,a)

apply :: (a -> b) -> a -> b
apply a b = a b

main = do
    print $ double 4
    print $ qsort [3,5,1,4,2]
    print $ qsort ['n','x','e','b','w']
    print $ qsort ["yes","no","maybe"]
    print $ [7,8,9] ++ [42,43,44]
    print $ seqn [qsort [1,3,2], qsort [7,2,4]]
    print $ 2+3*4
    print $ sqrt(3^2 + 4^2)
    print $ [1,2,3,4] !! 2
    print $ take 3 [1,2,3,4,5]
    print $ drop 3 [1,2,3,4,5]
    print $ last [1,2,3,4,5]
    print $ init [1,2,3,4,5]
    print $ length [1,2,3]
    print $ sum [1,2,3]
    print $ product [1,2,3]
    print $ reverse [1,2,3]
    

    
    
