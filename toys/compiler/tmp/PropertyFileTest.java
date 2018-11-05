
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;


public class PropertyFileTest {
    public static void main(String[] args) {
        String inputFile = null; 
        if ( args.length>0 ) inputFile = args[0];
        InputStream is = System.in;
        if ( inputFile!=null ) is = new FileInputStream(inputFile);
        ANTLRInputStream input = new ANTLRInputStream(is); 
        PropertyFileLexer lexer = new PropertyFileLexer(input); 
        CommonTokenStream tokens = new CommonTokenStream(lexer); 
        PropertyFileParser parser = new PropertyFileParser(tokens); 
        ParseTree tree = parser.prog(); // parse; start at prog <label id="code.tour.main.6"/>
        System.out.println(tree.toStringTree(parser)); // print tree as text <label id="code.tour.main.7"/>
    }
}
