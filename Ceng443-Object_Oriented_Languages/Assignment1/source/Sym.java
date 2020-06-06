package hw1;

public class Sym implements MathExpression {

	private String value;

	public Sym(String value) {
		this.value = value;
	}

	@Override
	public <T> T accept(MathVisitor<T> visitor) {
		return visitor.visit(this);
	}

	@Override
	public boolean match(MathExpression me) {
		return me instanceof Sym && value.equals(((Sym) me).getValue());
	}

	public String getValue() {
		return value;
	}
}
