package hw1;
import hw1.Num;
import hw1.Op;
import hw1.Sym;
import hw1.Var;

public interface MathVisitor<T> {
	T visit(Op op);
	T visit(Num num);
	T visit(Sym sym);
	T visit(Var var);
}
