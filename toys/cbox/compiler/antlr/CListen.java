import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;

public class CListen extends CBaseListener {
    @Override
    public void enterDeclaration(CParser.DeclarationContext ctx) {
        System.out.println("enter decl");
    }

    @Override
    public void exitDeclaration(CParser.DeclarationContext ctx) {
        System.out.println("enter decl");
    }

}
