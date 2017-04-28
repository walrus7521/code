using System;
using System.Collections;
using System.Collections.Generic;

public abstract class Item
{
    private string description;
    private int cost;

    public Item(string description, int cost)
    {
        this.description = description;
        this.cost = cost;
    }

    public virtual string Description
    {
        get
        {
            return description;
        }
    }

    public virtual int Cost
    {
        get
        {
            return cost;
        }
    }

    public abstract void AddItem(Item item);
    public abstract void RemoveItem(Item item);
    public abstract Item[] Items { get; }

    public override string ToString()
    {
        return description + " (cost " + Cost + ")";
    }

}

public class Part : Item
{
    public Part(string description, int cost)
        : base(description, cost)
    {
    }

    // Empty implementations for unit parts
    public override void AddItem(Item item)
    {
    }

    public override void RemoveItem(Item item)
    {
    }

    public override Item[] Items
    {
        get
        {
            return new Item[0];
        }
    }
}

public class Assembly : Item
{
    private List<Item> items;

    public Assembly(string description)
        : base(description, 0)
    {
        items = new List<Item>();
    }

    public override void AddItem(Item item)
    {
        items.Add(item);
    }

    public override void RemoveItem(Item item)
    {
        items.Remove(item);
    }

    public override Item[] Items
    {
        get
        {
            return items.ToArray();
        }
    }

    // Also have to override getCost() to accumulate cost of all items in list
    public override int Cost
    {
        get
        {
            int total = 0;
            foreach (Item item in items)
            {
                total += item.Cost;
            }
            return total;
        }
    }
}

class Client
{
    public static void Main()
    {
        Item nut = new Part("Nut", 5);
        Item bolt = new Part("Bolt", 9);
        Item panel = new Part("Panel", 35);

        Item gizmo = new Assembly("Gizmo");
        gizmo.AddItem(panel);
        gizmo.AddItem(nut);
        gizmo.AddItem(bolt);

        Item widget = new Assembly("Widget");
        widget.AddItem(gizmo);
        widget.AddItem(nut);

        Console.WriteLine(nut);
        Console.WriteLine(bolt);
        Console.WriteLine(panel);
        Console.WriteLine(gizmo);
        Console.WriteLine(widget);

    }

}
