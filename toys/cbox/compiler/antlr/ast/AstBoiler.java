import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;

public class AstBoiler {

    public static void main(String[] args) throws Exception {

        String inputFile = null;
        if (args.length > 0) inputFile = args[0];
        InputStream is = System.in;
        if (inputFile != null) is = new FileInputStream(inputFile);

        ANTLRInputStream input = new ANTLRInputStream(is);
        AstrecLexer lexer = new AstrecLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        AstrecParser parser = new AstrecParser(tokens);
        ParseTree tree = parser.start(); // parse; start at start

        ParseTreeWalker walker = new ParseTreeWalker();
        walker.walk(new MyAstListener(parser), tree);

        //AstrecVisitor eval = new AstrecVisitor();
        //eval.visit(tree);

        //System.out.println(tree.toStringTree(parser));

    }

}
