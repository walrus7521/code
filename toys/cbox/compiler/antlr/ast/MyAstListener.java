import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

// https://www.antlr.org/api/JavaTool/org/antlr/v4/runtime/tree/ParseTree.html
//
public class MyAstListener extends AstrecBaseListener {

    AstrecParser parser;

    public MyAstListener(AstrecParser parser)
    {
        //System.out.println("construct - enter");
        this.parser = parser;
        String[] rules = parser.getRuleNames();
        for (String rule : rules) {
            //System.out.println(rule);
        }
        //System.out.println("construct - exit");
    }

    @Override
    public void enterStart(AstrecParser.StartContext ctx)
    {
        //System.out.println("enter - start");
        //List<AstrecParser.DeclsContext> decls = ctx.decls();
        //for (AstrecParser.DeclsContext temp : decls) {
        //    System.out.println(temp.getRuleIndex());
        //    int index = temp.getRuleIndex();
        //    switch (index) {
        //        case 1:
        //        case 2:
        //        case 3:
        //    }
        //}
    }

    @Override 
    public void exitStart(AstrecParser.StartContext ctx)
    {
       // System.out.println("exit - start");
    }

    @Override 
    public void enterDecls(AstrecParser.DeclsContext ctx)
    {
        System.out.println("DECLS - enter");
    }

    @Override 
    public void exitDecls(AstrecParser.DeclsContext ctx)
    {

        int n_c = ctx.getChildCount();
        System.out.printf("DECLS - %d\n", n_c);
        for (int i = 0; i < n_c; i++) {
            ParseTree tree = ctx.getChild(i);
            int n_t = tree.getChildCount();
            System.out.printf("=> %s (%d) : ", tree.getText(), n_t);
            for (int j = 0; j < n_t; j++) {
                ParseTree t2 = tree.getChild(j);
                System.out.printf(" . %s\n", t2.getText());
            }
        }

        List<AstrecParser.TypeDeclContext> decls = ctx.typeDecl();
        for (AstrecParser.TypeDeclContext temp : decls) {
            System.out.println("decl");
        }
        System.out.println("DECLS - exit");
    }

}

