package hw1;

public class XDotZeroIsZeroRule implements Rule {

	Var x;
	MathExpression premise, entails;

	public XDotZeroIsZeroRule(Var x) {

		this.x = x;
		premise = new Op("*", x, new Num(0));
		entails = new Num(0);
	}

	@Override
	public MathExpression getPremise() {
		return premise;
	}

	@Override
	public MathExpression getEntails() {
		return entails;
	}
}
