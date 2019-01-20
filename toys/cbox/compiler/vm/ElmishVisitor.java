import java.util.HashMap;
import java.util.Map;

public class ElmishVisitor extends ElmBaseVisitor<Integer> {
    Map<String, Integer> memory = new HashMap<String, Integer>();

    @Override
    public Integer visitAssign(ElmParser.AssignContext ctx) {
        String id = ctx.ID().getText();
        int value = visit(ctx.expr());
        memory.put(id, value);
        return value;
    }

    @Override
    public Integer visitPrintExpr(ElmParser.PrintExprContext ctx) {
        Integer value = visit(ctx.expr());
        System.out.println(value);
        return 0;
    }

    @Override
    public Integer visitInt(ElmParser.IntContext ctx) {
        return Integer.valueOf(ctx.INT().getText());
    }

    @Override
    public Integer visitId(ElmParser.IdContext ctx) {
        String id = ctx.ID().getText();
        if (memory.containsKey(id)) return memory.get(id);
        return 0;
    }

    @Override
    public Integer visitMulDiv(ElmParser.MulDivContext ctx) {
        int left = visit(ctx.expr(0));
        int right = visit(ctx.expr(1));
        if (ctx.op.getType() == ElmParser.MUL) {
            return left * right;
        } else {
            return left / right;
        }
    }

    @Override
    public Integer visitAddSub(ElmParser.AddSubContext ctx) {
        int left = visit(ctx.expr(0));
        int right = visit(ctx.expr(1));
        if (ctx.op.getType() == ElmParser.ADD) {
            return left + right;
        } else {
            return left - right;
        }
    }

    @Override
    public Integer visitParens(ElmParser.ParensContext ctx) {
        return visit(ctx.expr());
    }

    @Override
    public Integer visitClear(ElmParser.ClearContext ctx) {
        memory.clear();
        System.out.println("clear");
        return 0;
    }

}

