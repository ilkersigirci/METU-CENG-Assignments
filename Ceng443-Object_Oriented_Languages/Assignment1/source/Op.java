package hw1;

public class Op implements MathExpression {

	private String operand;
	private MathExpression first;
	private MathExpression second;

	public Op(String operand,MathExpression first,MathExpression second) {
		this.operand = operand;
		this.first = first;
		this.second = second;
	}

	@Override
	public <T> T accept(MathVisitor<T> visitor) {
		return visitor.visit(this);
	}

	@Override
	public boolean match(MathExpression me) {
		return me instanceof Op &&
			operand.equals(((Op) me).getOperand()) &&
			first.match(((Op) me).getFirst()) &&
			second.match(((Op) me).getSecond());
	}

	public String getOperand() {
		return operand;
	}

	public MathExpression getFirst() {
		return first;
	}

	public MathExpression getSecond() {
		return second;
	}
}
