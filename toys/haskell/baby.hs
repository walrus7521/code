-- :l baby
doubleMe x = x + x
doubleUs x y = x*2 + y*2
doubleSmallNumber x = if x > 100
    then x
    else x*2
boomBangs xs = [if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]
-- bangBooms [7..13] [7..13]
boomBangs2 xs ys = [[if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x],
                    [if y < 10 then "WUDUP!" else "HOMI!" | y <- ys, odd y]]

