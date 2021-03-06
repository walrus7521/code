import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.misc.Interval;
import java.util.*;

public class ElmishListener extends ElmBaseListener {
    ElmParser parser;
    int num;

    Queue<String> instructionsQueue = new ArrayDeque<>();
    Map<String, Integer> variables = new HashMap<>();

    public Queue<String> getInstructionsQueue() {
        return instructionsQueue;
    }

    public ElmishListener(ElmParser parser) { 
        this.parser = parser;
        num = 0;
    }

    @Override
    public void enterProg(ElmParser.ProgContext ctx) {
        TokenStream tokens = parser.getTokenStream();
        //System.out.printf("prog: %s\n", tokens.getText());
    }

    @Override
    public void exitProg(ElmParser.ProgContext ctx) {
    }

    @Override
    public void enterStat(ElmParser.StatContext ctx) {
        TokenStream tokens = parser.getTokenStream();
        //if (ctx.expr() == null) return;
        //String args = tokens.getText(ctx.expr());
        //System.out.printf("stat: %s\n", tokens.getText());
        //System.out.printf("stat[%d]: %s\n", num, args);
        //num++;

        //int n_c = ctx.getChildCount();
        //System.out.printf("stats: %d\n", n_c);
        //for (int i = 0; i < n_c; i++) {
        //    ParseTree tree = ctx.getChild(i);
        //    int n_t = tree.getChildCount();
        //    System.out.printf(" => %s (%d) : ", tree.getText(), n_t);
        //    for (int j = 0; j < n_t; j++) {
        //        ParseTree t2 = tree.getChild(j);
        //        System.out.printf(" . %s\n", t2.getText());
        //    }
        //}
    }

    @Override
    public void exitStat(ElmParser.StatContext ctx) {


    }

    @Override
    public void enterExpr(ElmParser.ExprContext ctx) {
        TokenStream tokens = parser.getTokenStream();
        //if (ctx.expr() == null) return;
        //String args = tokens.getText(ctx.expr());
        //System.out.printf("stat: %s\n", tokens.getText());
        //System.out.printf("expr[%d]: %s\n", num, args);
        //num++;

        //int n_c = ctx.getChildCount();
        //System.out.printf("exprs: %d\n", n_c);
        //for (int i = 0; i < n_c; i++) {
        //    ParseTree tree = ctx.getChild(i);
        //    int n_t = tree.getChildCount();
        //    System.out.printf(" => %s (%d) : ", tree.getText(), n_t);
        //    for (int j = 0; j < n_t; j++) {
        //        ParseTree t2 = tree.getChild(j);
        //        System.out.printf(" . %s\n", t2.getText());
        //    }
        //}

        return;


        //String ID = "";
        //String INT = "";

        //if (ctx.ID() != null) {
        //    System.out.printf("id: %s\n", ctx.ID().toString());
        //}
        //if (ctx.INT() != null) {
        //    System.out.printf("int: %s\n", ctx.INT().toString());
        //}
        //if (ctx.expr() != null) {
        //    System.out.printf("exp: %s\n", ctx.expr().toString());
        //}
        //String args = tokens.getText();
        //System.out.printf("expr[%d]: %s\n", num, args);
        //System.out.printf("expr[%d]: %s\n", num, tokens.getText());
        //num++;
    }

    @Override
    public void exitExpr(ElmParser.ExprContext ctx) {

        final TerminalNode varName = ctx.ID();
        final int varType = ctx.getStart().getType();
        final int varIndex = ctx.expr().size();
        final String varTextValue = ctx.getText();

        //Variable var = new Variable(varIndex, varType, varTextValue);
        //variables.put(varName.getText(), var);
        //instructionsQueue.add(new VariableDeclaration(var));
        //logVariableDeclarationStatementFound(varName, varValue);
        String strVar = ElmParser.VOCABULARY.getSymbolicName(varType);
        //System.out.printf("nm: %s, type: %d, index: %d, val: %s\n", varName, varType, varIndex, varTextValue);
        System.out.printf("nm: %s, type: %s, index: %d, val: %s\n", varName, strVar, varIndex, varTextValue);

    }
    
}

