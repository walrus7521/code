import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;

public class ElmMain {
    public static void main(String[] args) throws Exception {
        String inputFile = null;
        if (args.length > 0) inputFile = args[0];
        InputStream is = System.in;
        if (inputFile != null) is = new FileInputStream(inputFile);

        ANTLRInputStream input = new ANTLRInputStream(is);
        ElmLexer lexer = new ElmLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        ElmParser parser = new ElmParser(tokens);
        ParseTree tree = parser.prog();
        
        // visitor
        //ElmishVisitor eval = new ElmishVisitor();
        //eval.visit(tree);

        // listener
        ParseTreeWalker walker = new ParseTreeWalker();
        ElmishListener extractor = new ElmishListener(parser);
        walker.walk(extractor, tree);

        //System.out.println(tree.toStringTree(parser));
    }
}

