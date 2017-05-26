import java.sql.*;

//
// java -classpath ".:sqlite-jdbc-3.8.7.jar" SQLiteJDBC
//  copied jar file into same directory has .class files
// http://www.tutorialspoint.com/sqlite/sqlite_java.htm
//

public class SQLiteJDBC
{
    public static Connection connectDB(String driver, String dbname) {
        Connection c = null;
        try {
            Class.forName(driver);
            c = DriverManager.getConnection(dbname);
        } catch ( Exception e ) {
            System.err.println( e.getClass().getName() + ": " + e.getMessage() );
            System.exit(0);
        }
        System.out.println("Opened database successfully");
        return c;
    }

    public static void createTable(Connection c, String sql) {
        Statement stmt = null;
        try {
            stmt = c.createStatement();
            stmt.executeUpdate(sql);
            stmt.close();
        } catch (Exception e) {
            System.err.println( e.getClass().getName() + ": " + e.getMessage() );
            System.exit(0);
        }
        System.out.println("Table created successfully");
    }

    public static void insertRecord() {
    }

    public static void fetchRecord() {
    }

    public static void updateRecord() {
    }

    public static void deleteRecord() {
    }

    public static void main( String args[] ) {
        Connection c = connectDB("org.sqlite.JDBC", "jdbc:sqlite:test.db");
        String sql = "CREATE TABLE COMPANY " +
                     "(ID INT PRIMARY KEY     NOT NULL," +
                     " NAME           TEXT    NOT NULL, " + 
                     " AGE            INT     NOT NULL, " + 
                     " ADDRESS        CHAR(50), " + 
                     " SALARY         REAL)"; 

        createTable(c, sql);

        try {

            c.close();
        } catch (Exception e) {
            System.err.println( e.getClass().getName() + ": " + e.getMessage() );
            System.exit(0);
        }
        
    }
}

