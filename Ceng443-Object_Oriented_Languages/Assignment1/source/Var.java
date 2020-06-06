package hw1;

public class Var implements MathExpression {

	private int id;
	private MathExpression previousMatch;

	public Var(int id) {
		this.id = id;
	}

	@Override
	public <T> T accept(MathVisitor<T> visitor) {
		return visitor.visit(this);
	}

	@Override
	public boolean match(MathExpression me) {

		if (previousMatch == null) {
			previousMatch = me;
			return true;
		} else {
			return (previousMatch.match(me));
		}
	}

	public int getId() {
		return id;
	}

	public MathExpression getPreviousMatch() {
		return previousMatch;
	}

	public void setPreviousMatch(MathExpression me) {
		previousMatch = me;
	}
}
