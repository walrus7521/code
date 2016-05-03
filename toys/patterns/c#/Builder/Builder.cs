using System;

// mcs Builder.cs Vehicle.cs Engine.cs

namespace Chapter03
{

    // Note how this class defines all possible 'build' methods for 
    // both cars and vans, and provides empty implementations for 
    // each as a default. The abstract Vehicle property getter is 
    // for returning the finished vehicle.

    public abstract class VehicleBuilder {     
        public virtual void BuildBody() {}     
        public virtual void BuildBoot() {}     
        public virtual void BuildChassis() {}     
        public virtual void BuildPassengerArea() {}     
        public virtual void BuildReinforcedStorageArea() {}     
        public virtual void BuildWindows() {}
        public abstract IVehicle Vehicle {get;} 
    }

    // The CarBuilder class inherits from VehicleBuilder and overrides 
    // the appropriate methods: 

    // Note that the BuildReinforcedStorageArea() method was not overridden 
    // since it is not applicable to cars. The

    public class CarBuilder : VehicleBuilder {     
        private AbstractCar carInProgress;     
        public CarBuilder(AbstractCar car)     
        {
            carInProgress = car;
        }
        public override void BuildBody()     
        {         
            Console.WriteLine("building car body");
        }
        public override void BuildBoot()
        {
            Console.WriteLine("building car boot");     
        }
        public override void BuildChassis()
        {         
            Console.WriteLine("building car chassis");     
        }
        public override void BuildPassengerArea()
        {         
            Console.WriteLine("building car passenger area");     
        }
        public override void BuildWindows()
        {         
            Console.WriteLine("building car windows");     
        }     
        public override IVehicle Vehicle     
        {         
            get         
            {             
                return carInProgress;         
            }     
        } 
    }    


    // The VanBuilder class overrides the appropriate methods to build a van: 

    // Note that the BuildBoot() and BuildPassengerArea() methods were not 
    // overridden since they are not applicable to vans.

    public class VanBuilder : VehicleBuilder 
    {     private AbstractVan vanInProgress;


        public VanBuilder(AbstractVan van)     
        {         
            vanInProgress = van;     
        }     
        public override void BuildBody()     
        {         
            Console.WriteLine("building van body");     
        }     
        public override void BuildChassis()     
        {         
            Console.WriteLine("building van chassis");     
        }     
        public override void BuildReinforcedStorageArea()     
        {         
            Console.WriteLine("building van storage area");     
        }

        public override void BuildWindows()     
        {         
            Console.WriteLine("building van windows");     
        }     
        public override IVehicle Vehicle     
        {         
            get         
            {             
                return vanInProgress;         
            }     
        } 
    }

    // The VehicleDirector abstract class requires a VehicleBuilder object 
    // passed to its Build() method for implementation by subclasses:
    public abstract class VehicleDirector 
    {     
        public abstract IVehicle Build(VehicleBuilder builder); 
    }


    // The CarDirector class inherits from VehicleDirector and provides 
    // the step-by-step process for building a car:
    public class CarDirector : VehicleDirector 
    {     
        public override IVehicle Build(VehicleBuilder builder)     
        {         
            builder.BuildChassis();         
            builder.BuildBody();         
            builder.BuildPassengerArea();         
            builder.BuildBoot();         
            builder.BuildWindows();         
            return builder.Vehicle;     
        } 
    }

    // The VanDirector class provides the step-by-step process for building a van: 
    public class VanDirector : VehicleDirector 
    {     
        public override IVehicle Build(VehicleBuilder builder)     
        {         
            builder.BuildChassis();         
            builder.BuildBody();         
            builder.BuildReinforcedStorageArea();         
            builder.BuildWindows();         
            return builder.Vehicle;     
        } 
    }

    public class Client
    {
        static void Main()
        {

            AbstractCar car = new Saloon(new StandardEngine(1300));
            VehicleBuilder builder = new CarBuilder(car);

            VehicleDirector director = new CarDirector(); 
            IVehicle v = director.Build(builder); 
            Console.WriteLine(v); 
            Console.Read(); 
            // You can see the required Builder object is constructed 
            // and passed to the required Director object, after which 
            // we invoke the method to build the product and then retrieve 
            // the finished article. 
            // The output should show: 
            //        Building car chassis 
            //        Building car body 
            //        Building car passenger area 
            //        Building car boot 
            //        Building car windows 
            //        Saloon (StandardEngine (1300), Unpainted)

        }
    }
    
}
