module Hw2 where

data ASTResult = ASTError String | ASTJust (String, String, Int) deriving (Show, Read)
data ASTDatum = ASTSimpleDatum String | ASTLetDatum String deriving (Show, Read)
data AST = EmptyAST | ASTNode ASTDatum AST AST deriving (Show, Read)

isNumber :: String -> Bool
eagerEvaluation :: AST -> ASTResult
normalEvaluation :: AST -> ASTResult
-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT isNumber, eagerEvaluation and normalEvaluation FUNCTIONS ACCORDING TO GIVEN SIGNATURES -- 
addThird :: ASTResult -> Int -> ASTResult
addThird ( ASTJust (x,y,a) ) b = ASTJust (x,y,a+b)

changeAST:: (String,String,Int) -> AST -> String
astToString :: AST -> String
evaluate :: AST -> Int -> ASTResult -- 0 ->Eager / 1 -> Normal

isNumber "" = False
isNumber (n:num)
    | result == [] = True
    | otherwise = False
    where result = [x | x<-(n:num),n /= '-' && not (x `elem` "0123456789") ]

--eagerEvaluation EmptyAST =  ASTJust ("","",0)
--changeAST ("","",0) EmptyAST = EmptyAST 

takeFirst (ASTJust (a,b,c)) = a --FIXME: errorlari da aliyor galiba
takeSecond (ASTJust (a,b,c)) = b
takeThird (ASTJust (a,b,c)) = c

astToString EmptyAST = "EmptyAST"
astToString (ASTNode (ASTSimpleDatum op) left right) = "(ASTNode (ASTSimpleDatum \""++op++"\") "++ astToString left ++" "++ astToString right++")"   
astToString (ASTNode (ASTLetDatum str) left right) = "(ASTNode (ASTLetDatum \""++str++"\") "++ astToString left ++" "++ astToString right++")"

--normalEvaluation EmptyAST =  ASTError "var"
normalEvaluation (ASTNode (ASTLetDatum str) left right) = evaluate result 1
    where 
        result =  let
                x = astToString left
                in read (changeAST (str,x,0) right)::AST

normalEvaluation ast = evaluate ast 1

--eagerEvaluation (ASTError str) = ASTError str
eagerEvaluation (ASTNode (ASTLetDatum str) left right) = addThird (evaluate result 0) count
    where 
        result =  let
                x = takeFirst (evaluate left 0)
                in read (changeAST (str,x,0) right)::AST
        count = takeThird (evaluate left 0)

eagerEvaluation ast = evaluate ast 0

changeAST (var,value,_) EmptyAST = "EmptyAST"
changeAST (var,value,collide) (ASTNode (ASTSimpleDatum op) left right) 
    | var == op && collide == 0 && length (value) < 20 = "(ASTNode (ASTSimpleDatum \""++value++"\") "++ changeAST (var,value,0) left ++" "++ changeAST (var,value,0) right++")" --asil olay EAGER EVALUATION
    | var == op && collide == 0 && length (value)>= 20 = value --asil olay NORMAL EVALUATION
    | otherwise = "(ASTNode (ASTSimpleDatum \""++op++"\") "++ changeAST (var,value,collide) left ++" "++ changeAST (var,value,collide) right++")"   
changeAST (var,value,collide) (ASTNode (ASTLetDatum str) left right) 
    | var /= str = "(ASTNode (ASTLetDatum \""++str++"\") "++ changeAST (var,value,collide) left ++" "++ changeAST (var,value,collide) right++")"
    | var == str = "(ASTNode (ASTLetDatum \""++str++"\") "++ changeAST (var,value,1) left ++" "++ changeAST (var,value,1) right++")"



--evaluate (ASTError str) = ASTError str --TODO: throw error without exception
evaluate (ASTNode (ASTLetDatum str) left right) eval
    | eval == 0 = eagerEvaluation  (ASTNode (ASTLetDatum str) left right) --Eager
    | otherwise = normalEvaluation (ASTNode (ASTLetDatum str) left right) --Normal
evaluate(ASTNode (ASTSimpleDatum str) EmptyAST EmptyAST) eval
    | isNumber str = ASTJust(str,"num",0)
    | otherwise  = ASTJust(str,"str",0)

evaluate (ASTNode (ASTSimpleDatum op) left right) x
    | sol     &&    op == "num"    = ASTJust(( takeFirst (evaluate left x) ),"num",countLeft-1)
    | op == "str"    = ASTJust(( takeFirst (evaluate left x) ),"str",countLeft-1)
    | not sol &&    op == "num"    = ASTError ("the value '" ++( takeFirst (evaluate left x) )++ "' is not a number!")
    | sol     &&    op == "len"    = ASTError (op++" operation is not defined on num!")
    | not sol &&    op == "negate" = ASTError (op++" operation is not defined on str!")
    | not sol &&    op == "len"    = ASTJust(result5,"num",countLeft)
    | sol &&        op == "negate" = ASTJust(result3,"num",countLeft)
    | sol && sag && op == "plus"   = ASTJust(result1,"num",count)
    | sol && sag && op == "times"  = ASTJust(result2,"num",count)    
    | not(sol||sag) && op == "cat" = ASTJust(result4,"str",count)    
    | not sol && sag && (op =="plus" || op =="times" || op =="cat")      = ASTError (op++" operation is not defined between str and num!")
    | sol     && not sag  && (op =="plus" || op =="times" || op =="cat") = ASTError (op++" operation is not defined between num and str!")
    | not(sol||sag) && (op =="plus" || op =="times")  = ASTError (op++" operation is not defined between str and str!")
    | sol    && sag && op =="cat"  = ASTError (op++" operation is not defined between num and num!")
    | otherwise                    = ASTError "NO ERROR"
    where
        sol = "num" == takeSecond (evaluate left x)
        sag = "num" == takeSecond (evaluate right x)
        result1 = show ( read (takeFirst (evaluate left x)) + read (takeFirst (evaluate right x)) )
        result2 = show ( read (takeFirst (evaluate left x)) * read (takeFirst (evaluate right x)) )
        result3 = show ( (-1) * ( read (takeFirst (evaluate left x) ) ) )
        result4 = (takeFirst (evaluate left x) ) ++ (takeFirst (evaluate right x) )
        result5 = show ( length (takeFirst (evaluate left x) ) )
        count = takeThird (evaluate left x) + takeThird (evaluate right x) + 1
        countLeft = takeThird (evaluate left x) + 1
