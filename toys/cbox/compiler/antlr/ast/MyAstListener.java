import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

public class MyAstListener extends AstrecBaseListener {

    AstrecParser parser;

    public MyAstListener(AstrecParser parser)
    {
        System.out.println("construct - enter");
        this.parser = parser;
        String[] rules = parser.getRuleNames();
        for (String rule : rules) {
            System.out.println(rule);
        }
        System.out.println("construct - exit");
    }

    @Override
    public void enterStart(AstrecParser.StartContext ctx)
    {
        System.out.println("enter - start");
        List<AstrecParser.DeclsContext> decls = ctx.decls();
        for (AstrecParser.DeclsContext temp : decls) {
            System.out.println(temp.getRuleIndex());
            int index = temp.getRuleIndex();
            switch (index) {
                case 1:
                case 2:
                case 3:
            }
        }
    }

    @Override 
    public void exitStart(AstrecParser.StartContext ctx)
    {
        System.out.println("exit - start");
    }

    @Override 
    public void enterDecls(AstrecParser.DeclsContext ctx)
    {
        System.out.println("enter - decls");
    }

    @Override 
    public void exitDecls(AstrecParser.DeclsContext ctx)
    {
        System.out.println("exit - decls");
        List<AstrecParser.TypeDeclContext> decls = ctx.typeDecl();
        for (AstrecParser.TypeDeclContext temp : decls) {
            System.out.println("decl");
        }

    }

}

