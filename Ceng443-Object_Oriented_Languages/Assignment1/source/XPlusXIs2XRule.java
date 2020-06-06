package hw1;

public class XPlusXIs2XRule implements Rule {

	Var x;
	MathExpression premise, entails;

	public XPlusXIs2XRule(Var x) {

		this.x = x;
		premise = new Op("+",x,x);
		entails = new Op("*",new Num(2),x);
	}

	public Var getX() {
		return x;
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
