package hw1;
import hw1.MathExpression;
import hw1.ClearVarsVisitor;

public interface Rule {

	default void clear() {

		MathExpression premise = getPremise();
		MathExpression entails = getEntails();

		premise.accept(new ClearVarsVisitor());
		entails.accept(new ClearVarsVisitor());
	}

	default boolean apply(MathExpression me) {

		clear();
		boolean isMatch = getPremise().match(me);
		if (!isMatch) clear();
		return isMatch;
	}

	MathExpression getPremise();
	MathExpression getEntails();

	default MathExpression entails(MathExpression me) {

		apply(me);
		return getEntails();
	}
}
