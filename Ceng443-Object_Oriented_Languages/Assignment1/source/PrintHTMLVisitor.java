package hw1;

public class PrintHTMLVisitor implements TextVisitor<String> {
	@Override
	public String visit(Document document) {

		StringBuilder result = new StringBuilder("<html><head><title>" + document.getTitle() + "</title></head><body>");

		for(DocElement doc : document.getElements()) {
			result.append(doc.accept(new PrintHTMLVisitor()));
		}
		result.append("</body></html>");
		return result.toString();
	}

	@Override
	public String visit(EquationText equationText) {

		MathExpression innerMath = equationText.getInnerMath() ;
		return "<math>" + innerMath.accept(new PrintMathMLVisitor()) + "</math>";
	}

	@Override
	public String visit(Paragraph paragraph) {

		return "<p>" + paragraph.getText() + "</p>";
	}
}
