package hw1;

public class ClearVarsVisitor implements MathVisitor<Void>{
	@Override
	public Void visit(Op op) { //TODO: Void e bak

		MathExpression first = op.getFirst();
		MathExpression second = op.getSecond();
		first.accept(this);
		second.accept(this);
		return null;
	}

	@Override
	public Void visit(Num num) {
		return null;
	}

	@Override
	public Void visit(Sym sym) {
		return null;
	}

	@Override
	public Void visit(Var var) {
		var.setPreviousMatch(null);
		return null;
	}
}
