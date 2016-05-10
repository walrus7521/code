public abstract class VehicleFactory
{
    public enum DrivingStyle
    {
        Economical, Midrange, Powerful
    }
    public enum Category
    {
        Car, Van
    }
    public virtual IVehicle Build(DrivingStyle style,
                                  VehicleColour colour)
    {
        IVehicle v = SelectVehicle(style);
        v.Paint(colour);
        return v;
    }
    // This is the "factory methoc"
    protected internal abstract IVehicle SelectVehicle(
                                   DrivingStyle style);


    public static IVehicle Make(Category cat,
                                DrivingStyle style,
                                VehicleColour colour)
    {
        VehicleFactory factory;
        if (cat == Category.Car)
        {
            factory = new CarFactory();
        }
        else
        {
            factory = new VanFactory();
        }
        return factory.Build(style, colour);
    }
}

public class CarFactory : VehicleFactory
{
    protected internal override IVehicle SelectVehicle(
                                   DrivingStyle style)
    {
        if (style == DrivingStyle.Economical)
        {
            return new Saloon(new StandardEngine(1300));
        } else
        if (style == DrivingStyle.Midrange)
        {
            return new Coupe(new StandardEngine(1600));
        } else
        {
            return new Sport(new TurboEngine(2000));
        }
    }
}

public class VanFactory : VehicleFactory
{
    protected internal override IVehicle SelectVehicle(
                                   DrivingStyle style)
    {
        if ((style == DrivingStyle.Economical) ||
            (style == DrivingStyle.Midrange))
        {
            return new Pickup(new StandardEngine(2200));
        } else
        {
            return new BoxVan(new TurboEngine(2500));
        }
    }
}


