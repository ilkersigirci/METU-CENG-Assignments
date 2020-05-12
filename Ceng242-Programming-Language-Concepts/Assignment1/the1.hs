module Hw1 where

type Mapping = [(String, String, String)]
data AST = EmptyAST | ASTNode String AST AST deriving (Show, Read)

writeExpression :: (AST, Mapping) -> String
evaluateAST :: (AST, Mapping) -> (AST, String)
-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT writeExpression and evaluateAST FUNCTION ACCORDING TO GIVEN SIGNATURES --

helper :: AST -> String -> String 
helper (ASTNode var EmptyAST EmptyAST) flag = 
    if flag == "num" then var
    else if flag == "str" then "\"" ++ var ++ "\""
    else if flag == "evalStr" then var
    else "no possible match"

helper2 :: Mapping -> String
helper2 ([(x,"num",var)]) = x ++ "=" ++ var
helper2 ((x,"num",var):xs) = x ++ "=" ++ var ++ ";" ++ helper2 xs 
helper2 ([(x,"str",var)]) =   x ++ "=" ++ "\"" ++ var ++ "\""
helper2 ((x,"str",var):xs) = x ++ "=" ++ "\"" ++ var ++ "\"" ++ ";" ++ helper2 xs 

writeExpression( (ASTNode "plus" left right), [] ) = "(" ++ writeExpression(left,[]) ++ "+" ++ writeExpression(right,[]) ++ ")"
writeExpression( (ASTNode "times" left right), [] ) = "(" ++ writeExpression(left,[]) ++ "*" ++ writeExpression(right,[]) ++ ")"
writeExpression( (ASTNode "cat" left right), [] ) = "(" ++ writeExpression(left,[]) ++ "++" ++ writeExpression(right,[]) ++ ")"
writeExpression( (ASTNode "len" left EmptyAST), [] ) = "(" ++ "length " ++ writeExpression(left,[]) ++ ")"
writeExpression( (ASTNode "negate" left EmptyAST), [] ) = "(-" ++ writeExpression (left,[]) ++ ")"

writeExpression( (ASTNode "num" variable EmptyAST), [] ) =  helper variable "num"                        
writeExpression( (ASTNode "str" variable EmptyAST), [] ) =  helper variable "str"
writeExpression( (ASTNode var EmptyAST EmptyAST), [] ) =  var

writeExpression( ast, mapping ) = "let "++ helper2 mapping ++ " in " ++ writeExpression(ast,[])

evaluateAST(ast, mapping) = (read (helper4(ast,mapping))::AST, evaluateAST'(ast,mapping))

helper3 :: String -> Mapping -> (String,String)
helper3 var [] = ("_",var)
helper3 var ([(x,typ,value)]) 
    | typ == "num" && var == x = ("num",value)
    | typ == "str" && var == x = ("str",value)
helper3 var ((x,"num",value):xs) = if var == x then ("num",value) else helper3 var xs
helper3 var ((x,"str",value):xs) = if var == x then ("str",value) else helper3 var xs

evaluateAST' :: (AST, Mapping) -> String
evaluateAST'( (ASTNode "plus" left right), mapping ) = show ( read(evaluateAST'(left,mapping)) + read(evaluateAST'(right,mapping)) )
evaluateAST'( (ASTNode "times" left right), mapping ) = show ( read(evaluateAST'(left,mapping)) * read(evaluateAST'(right,mapping)) )
evaluateAST'( (ASTNode "cat" left right), mapping ) = evaluateAST'(left,mapping) ++ evaluateAST'(right,mapping) 
evaluateAST'( (ASTNode "len" left EmptyAST), mapping ) = show ( length (evaluateAST'(left,mapping) ) )
evaluateAST'( (ASTNode "negate" left EmptyAST), mapping ) = show ( (-1) * read(evaluateAST'(left,mapping)) )

evaluateAST'( (ASTNode "num" variable EmptyAST), mapping ) =  helper variable "num"
evaluateAST'( (ASTNode "str" variable EmptyAST), mapping ) =  helper variable "evalStr"
evaluateAST'( (ASTNode var EmptyAST EmptyAST), mapping ) =  ( (\(x,y) -> y) (helper3 var mapping) )

helper4 :: (AST, Mapping) -> String
helper4( (ASTNode "plus" left right), mapping ) = "(ASTNode \"plus\" "++helper4(left,mapping)++" "++helper4(right,mapping)++")"
helper4( (ASTNode "times" left right), mapping ) = "(ASTNode \"times\" "++helper4(left,mapping)++" "++helper4(right,mapping)++")"
helper4( (ASTNode "cat" left right), mapping ) = "(ASTNode \"cat\" "++helper4(left,mapping)++" "++helper4(right,mapping)++")"
helper4( (ASTNode "len" left EmptyAST), mapping ) = "(ASTNode \"len\" "++helper4(left,mapping)++" EmptyAST)"
helper4( (ASTNode "negate" left EmptyAST), mapping ) = "(ASTNode \"negate\" "++helper4(left,mapping)++" EmptyAST)"
helper4( (ASTNode "num" variable EmptyAST), mapping ) = "(ASTNode \"num\" "++helper4(variable,mapping)++" EmptyAST)"
helper4( (ASTNode "str" variable EmptyAST), mapping ) =  "(ASTNode \"str\" "++helper4(variable,mapping)++" EmptyAST)"
helper4( (ASTNode var EmptyAST EmptyAST), mapping ) 
    | var /= ( (\(x,y) -> y) (helper3 var mapping) )  = "(ASTNode \""++ ( (\(x,y) -> x) (helper3 var mapping) ) ++"\" (ASTNode \""++ ( (\(x,y) -> y) (helper3 var mapping) ) ++"\" EmptyAST EmptyAST) EmptyAST)"
    | otherwise  = "(ASTNode \""++var++"\" EmptyAST EmptyAST)"
