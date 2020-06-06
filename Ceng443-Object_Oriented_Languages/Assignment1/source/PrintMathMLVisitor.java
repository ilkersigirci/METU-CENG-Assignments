package hw1;

public class PrintMathMLVisitor implements MathVisitor<String> {
	@Override
	public String visit(Op op) {

		String result;
		String operand = op.getOperand();
		MathExpression first = op.getFirst();
		MathExpression second = op.getSecond();

		switch(operand) {
			case "*":
				operand = "&times;"; break;
			case "|-":
				operand = "&vdash;"; break;
		}

		if (operand.equals("/")) {
			result = "<mrow><mfrac>" + first.accept(this) + " " + second.accept(this) + "</mfrac></mrow>";

		} else {
			result = "<mrow><mo>(</mo>" + first.accept(this) + "<mo>" + operand + "</mo>" + second.accept(this) + "<mo>)</mo></mrow>";
		}

		return result;
	}

	@Override
	public String visit(Num num) {

		return "<mrow><mn>" + num.getValue() + "</mn></mrow>";
	}

	@Override
	public String visit(Sym sym) {

		return "<mrow><mi>" + sym.getValue() + "</mi></mrow>";
	}

	@Override
	public String visit(Var var) {

		String result;
		if (var.getPreviousMatch() == null) {
			result = "<mrow><msub><mi>V</mi><mn>" + var.getId() + "</mn></msub></mrow>";
		} else  {
			result = "<mrow><msub><mi>V</mi><mn>" + var.getId() + "</mn></msub><mo>[</mo>" + var.getPreviousMatch().accept(new PrintMathMLVisitor()) + "<mo>]</mo></mrow>";
		}
		return result;
	}
}
