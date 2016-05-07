
// bogus implementation to make this work
// this would normally be provided by a 3rd party.
public class SuperGreenEngine
{
    public SuperGreenEngine(int engineSize)
    {
        EngineSize = engineSize;
    }
    public int EngineSize;
    public string ToStringerize()
    {
        return this.GetType().Name + " GREENAGE (" + EngineSize + ")";
    }
}

// 3 steps to adapt a class
//   1. Extend the class we are adapting to
//   2. Specify the class we are adapting from in the ctor and store
//      a reference to it in an instance variable.
//   3. For each method in the class you are extending, override it
//      to delegate to the corresponding method of the class you are
//      adapting from.

// we are adapting FROM SuperGreenEngine
// we are adapting TO AbstractEngine
// note that SuperGreenEngine has adapted the ToString() method
// from the AbstractEngine rather than that of SuperGreenEngine.
public class SuperGreenEngineAdapter : AbstractEngine
{
    private SuperGreenEngine greenEngine; // class adapting from

    public SuperGreenEngineAdapter(SuperGreenEngine greenEngine)
        : base(greenEngine.EngineSize, false) // pass to superclass ctor
    {
        this.greenEngine = greenEngine;
    }

    // overridden method from TO class
    // as a delegate for the FROM class
    public override string ToString() //method in TO class (AbstractEngine)
    {
        return greenEngine.ToStringerize(); // method in FROM class
    }
}


