package hw1;

public class XDotYDivXIsYRule implements Rule {

	Var x, y;
	MathExpression premise, entails;

	public XDotYDivXIsYRule(Var x, Var y) {

		this.x = x;
		this.y = y;
		premise = new Op("/", new Op("*", x, y), x);
		entails = y;
	}

	@Override
	public MathExpression getPremise() {
		return premise;
	}

	@Override
	public MathExpression getEntails() {
		return entails;
	}

	public Var getX() {
		return x;
	}

	public Var getY() {
		return y;
	}
}
