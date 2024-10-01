/*
 * Requirements
The coffee vending machine should support different types of coffee, such as espresso, cappuccino, and latte.
Each type of coffee should have a specific price and recipe (ingredients and their quantities).
The machine should have a menu to display the available coffee options and their prices.
Users should be able to select a coffee type and make a payment.
The machine should dispense the selected coffee and provide change if necessary.
The machine should track the inventory of ingredients and notify when they are running low.
The machine should handle multiple user requests concurrently and ensure thread safety.
 * */



public class Inventory
{
    private int coffeeBeansQuantity;
    private int milkQuantity;
    public Inventory(int coffeeBeansQuantity, int milkQuantity)
    {
        this.coffeeBeansQuantity = coffeeBeansQuantity;
        this.milkQuantity = milkQuantity;
    }
    public void addCoffeeBeans(int quantity)
    {
        this.coffeeBeansQuantity += quantity;
    }
    public int getCoffeeBeansQuantity()
    {
        return this.coffeeBeansQuantity;
    }
    public void removeCoffeeBeans(int quantity)
    {
        this.coffeeBeansQuantity -= quantity;
        if (this.coffeeBeansQuantity <= 0)
        { 
            this.coffeeBeansQuantity = 0;
            Console.WriteLine("Low on CoffeeBeans");
        }
        
    }
    public void addMilk(int quantity)
    {
        this.milkQuantity += quantity;
    }
    public int getMilk()
    {
        return this.milkQuantity;
    }
    public void removeMilk(int quantity)
    {
        this.milkQuantity -= quantity;
        if (this.milkQuantity <= 0)
        {
            this.milkQuantity = 0;
            Console.WriteLine("Low on Milk");
        }
        
    }
}

public class Recipe
{
    public int coffeeBeans;
    public int milk;
    public Recipe(int coffeeBeans, int milk)
    {
        this.milk = milk;
        this.coffeeBeans = coffeeBeans;
    }
}

public class Coffee
{
    public string name;
    public int price;
    public Recipe recipe;
    public Coffee(string name, int price, Recipe recipe)
    {
        this.name = name;
        this.price = price;
        this.recipe = recipe;
    }
}

public class Machine
{
    public List<Coffee> coffeeList;
    private Inventory inventory;
    public Machine(List<Coffee> coffeeList, Inventory inventory)
    {
        this.coffeeList = coffeeList;
        this.inventory = inventory;
    }
    public void displayMenu()
    {
        foreach (Coffee coffee in coffeeList)
        {
            Console.WriteLine($"{coffee.name} - {coffee.price}");
        }
    }
    public void GetCoffee(string name)
    {
        foreach(Coffee coffee in coffeeList)
        {
            if (coffee.name == name)
            {
                if (inventory.getCoffeeBeansQuantity() < coffee.recipe.coffeeBeans)
                {
                    Console.WriteLine("Running low on coffee beans");
                    return;
                }
                if (inventory.getMilk() < coffee.recipe.milk)
                {
                    Console.WriteLine("Running low on milk");
                    return;
                }
                // decrease the ingredients
                inventory.removeCoffeeBeans(coffee.recipe.coffeeBeans);
                inventory.removeMilk(coffee.recipe.milk);
                Console.WriteLine($"{coffee.name} - Enjoy your coffee");
                return;
            }
        }
        Console.WriteLine("Sorry, Not Available!");
    }
}

public class Program
{
    public static void Main()
    {
        Inventory inventory = new Inventory(30, 30);
        Recipe recipe1 = new Recipe(5, 10);
        Recipe recipe2 = new Recipe(10, 10);
        Recipe recipe3 = new Recipe(20, 15);
        Coffee espresso = new Coffee("Espresso", 100, recipe1);
        Coffee cappuccino = new Coffee("Cappuccino", 150, recipe2);
        Coffee latte = new Coffee("latte", 200, recipe3);
        List<Coffee> coffees = new List<Coffee>();
        coffees.Add(espresso);
        coffees.Add(cappuccino);
        coffees.Add(latte);
        Machine machine = new Machine(coffees, inventory);
        machine.displayMenu();
        machine.GetCoffee("Espresso");
        machine.GetCoffee("Cappuccino");
        machine.GetCoffee("latte");
    }
}
