take second
(ASTNode 
    (ASTSimpleDatum "negate") 
    (ASTNode 
        (ASTSimpleDatum "num") 
        (ASTNode (ASTSimpleDatum "123x") EmptyAST EmptyAST) 
        EmptyAST) 
    EmptyAST)


ASTError "the value '123x' is not a number!"
--------------------------------------------------------------------------------------------------
take second 
(ASTNode 
    (ASTLetDatum "x") 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST)) 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST)))

(ASTNode 
    (ASTSimpleDatum "plus") 
    (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "abc") EmptyAST EmptyAST) EmptyAST) 
    (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "123") EmptyAST EmptyAST) EmptyAST))

ASTError "the value 'abc' is not a number!"
------------------------------------------------------------------------------
normal-hata
normalEvaluation (ASTNode (ASTLetDatum "x") (ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST) (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST)) (ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST)))

(ASTNode 
    (ASTLetDatum "x") 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST)) 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST)))
------------------------------------------------------------------------------
normal-hata yok
normalEvaluation (ASTNode (ASTLetDatum "x") (ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "2") EmptyAST EmptyAST) EmptyAST) (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST)) (ASTNode (ASTLetDatum "x") (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST) (ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST))))

(ASTNode 
    (ASTLetDatum "x") 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "2") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST)) 
    (ASTNode 
        (ASTLetDatum "x") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode 
            (ASTSimpleDatum "plus") 
            (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) 
            (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST))))










--------------------------------------------------------------------------------------------------

(ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST) (ASTNode (ASTSimpleDatum "num")(ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST)) 

( ASTNode 
    (ASTLetDatum "x") 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode 
            (ASTSimpleDatum "num") 
            (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) 
            EmptyAST) 
        (ASTNode 
            (ASTSimpleDatum "num")
            (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) 
            EmptyAST)) 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) 
        (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST)) )

ASTJust ("14","num",2)   -> eager
ASTJust ("14","num",3)   -> normal          
--------------------------------------------------------------------------------------------------
( ASTNode 
    (ASTLetDatum "x") 
    (ASTNode 
        (ASTSimpleDatum "plus") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "2") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "3") EmptyAST EmptyAST) EmptyAST)) 
    (ASTNode 
        (ASTLetDatum "x") 
        (ASTNode (ASTSimpleDatum "num") (ASTNode (ASTSimpleDatum "4") EmptyAST EmptyAST) EmptyAST) 
        (ASTNode (ASTSimpleDatum "plus") (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST) (ASTNode (ASTSimpleDatum "x") EmptyAST EmptyAST))))

ASTJust ("8","num",2)   -> eager
ASTJust ("8","num",1)   -> normal  

