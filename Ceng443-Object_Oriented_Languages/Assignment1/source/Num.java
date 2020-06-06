package hw1;

public class Num implements MathExpression {

	private int value;

	public Num(int value) {
		this.value = value;
	}

	@Override
	public <T> T accept(MathVisitor<T> visitor) {
		return visitor.visit(this);
	}

	@Override
	public boolean match(MathExpression me) {
		return me instanceof Num && value == ((Num)me).getValue();
	}

	public int getValue() {
		return value;
	}
}
