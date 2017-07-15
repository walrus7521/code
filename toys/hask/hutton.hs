

double x = x + x

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

main = do
    print $ double 4
    print $ qsort [3,5,1,4,2]
    print $ qsort ['n','x','e','b','w']
    print $ qsort ["yes","no","maybe"]
    print $ [7,8,9] ++ [42,43,44]
    print $ seqn [qsort [1,3,2], qsort [7,2,4]]


    
    




