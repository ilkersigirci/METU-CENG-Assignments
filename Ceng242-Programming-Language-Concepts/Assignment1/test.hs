import Data.List
import System.IO

initials :: String -> String -> String
initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
    where (f:_) = firstname
        (l:_) = lastname
        
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

x1 = [ x*y | x <- [2,5,10], y <- [8,10,11]]
--[16,20,22,40,50,55,80,100,110]   

x2 = [ (b,c) | c <- [1,2], b <- [3,4] ]
--[(3,1),(4,1),(3,2),(4,2)]

x3 = [ (b,c) | b <- [3,4],c <- [1,2]  ]
--[(3,1),(3,2),(4,1),(4,2)]