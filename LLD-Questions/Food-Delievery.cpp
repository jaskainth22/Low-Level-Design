/*
5. Design a restaurant food ordering system like Zomato, Swiggy, DoorDash

Write code for low level design of a restaurant food ordering and rating system, similar to food delivery apps like Zomato, Swiggy, Door Dash, Uber Eats etc.

There will be food items like 'Veg Burger', 'Veg Spring Roll', 'Ice Cream' etc.
And there will be restaurants from where you can order these food items.

Same food item can be ordered from multiple restaurants. e.g. you can order 'food-1' 'veg burger' from burger king as well as from McDonald's.

Users can order food, rate orders, fetch restaurants with most rating and fetch restaurants with most rating for a particular food item e.g. restaurants which have the most rating for 'veg burger'.

You can practice this question in both Java and Python
Your solution should implement below methods:

Method : init(Helper05 helper)
- Use this method to initialize your instance variables
- use helper's methods for printing logs else logs will not be visible.

Method : orderFood(String orderId, String restaurantId, String foodItemId)
- Orders food item from a restaurant.
- for now lets assume for that only a single food item is purchased in one order.
- orderId, restaurantId, foodItemId will all be valid and available.
- PARAMETER : restaurantId is restaurant from where food is being ordered.
- PARAMETER : foodItemId is food item which is being ordered

Method : rateOrder(String orderId, int rating)
- Customers can rate their order.
- when you are giving rating an order e.g giving 4 stars to an order, then it means you are assigning 4 stars to both the food item in that restaurant as well as 4 stars to the overall restaurant ranting.
- PARAMETER : orderId is order which will be rated by customer, orderId will always be valid i.e. order will always be created for an orderId before rateOrder() is called.
- PARAMETER : rating ranges from 1 to 5 stars in increasing order, 1 being the worst and 5 being the best rating.

Method : List[String] getTopRestaurantsByFood(String foodItemId)
- Fetches a list of top 20 restaurants based on strategy
- unrated restaurants will be at the bottom of list.
- restaurants will be sorted on the basis of strategy
- restaurants are sorted in descending order on average ratings of the food item and then based on restaurant id lexicographically.
- e.g. veg burger is rated 4.3 in restaurant-4 and 4.6 in restaurant-6 then
we will return ['restaurant-6', 'restaurant-4']
- PARAMETER : foodItemId is food item for which restaurants need to be fetched.

Method : List[String] getTopRatedRestaurants()
- returns top 20 most rated restaurants ids sorted in descending order of their ratings.
- if two restaurants have the same rating then they will be ordered lexicographically by their restaurantId.
- Here we are talking about restaurant's overall rating and NOT food item's rating.
- e.g. restaurant-2 is rated 4.6 while restaurant-3 is rated 4.2 and restaurant-5 is rated 4.4 and restaurant-6 is rated 4.6,
we will return ['restaurant-2','restaurant-6', 'restaurant-5', 'restaurant-3']
- even though restaurant-2 and restaurant-6 have same rating , restaurant-6 came later because it is lexicographically greater than restaurant-2

Note :
- There will be at max 50 food items, at max 10,000 restaurants,
    and each restaurant can sell at max 25 food items
- Average ratings are rounded down to 1 decimal point,
    i.e. 4.05, 4.08, 4.11, 4.12, 4.14 all become 4.1
    and 4.15, 4.19, 4.22, 4.24 all become 4.2
- For Python, use round(rating, 1) function to round rating to 1 decimal point.
- For Java, use the formula (double)((int)((rating+0.05)*10))/10.0 to round rating

Example : Read the below method calls to get a better understanding of how this works.

init(helper)
orderFood(orderId = 'order-0', foodItemId = 'food-1', restaurantId = 'restaurant-0')

rateOrder(orderId = 'order-0', rating = 3)

orderFood(orderId = 'order-1', foodItemId = 'food-0', restaurantId = 'restaurant-2')

rateOrder(orderId = 'order-1', rating = 1)

orderFood(orderId = 'order-2', foodItemId = 'food-0', restaurantId = 'restaurant-1')

rateOrder(orderId = 'order-2', rating = 3)

orderFood(orderId = 'order-3', foodItemId = 'food-0', restaurantId = 'restaurant-2')

rateOrder(orderId = 'order-3', rating = 5)

orderFood(orderId = 'order-4', foodItemId = 'food-0', restaurantId = 'restaurant-0')

rateOrder(orderId = 'order-4', rating = 3)

orderFood(orderId = 'order-5', foodItemId = 'food-0', restaurantId = 'restaurant-1')

rateOrder(orderId = 'order-5', rating = 4)

orderFood(orderId = 'order-6', foodItemId = 'food-1', restaurantId = 'restaurant-0')

rateOrder(orderId = 'order-6', rating = 2)

orderFood(orderId = 'order-7', foodItemId = 'food-1', restaurantId = 'restaurant-0')

rateOrder(orderId = 'order-7', rating = 2)

orderFood(orderId = 'order-8', foodItemId = 'food-0', restaurantId = 'restaurant-1')

rateOrder(orderId = 'order-8', rating = 2)

orderFood(orderId = 'order-9', foodItemId = 'food-0', restaurantId = 'restaurant-1')

rateOrder(orderId = 'order-9', rating = 4)

getTopRestaurantsByFood('food-0')
returns [restaurant-1, restaurant-0, restaurant-2]
(For reference only) list of restaurants with rating for food food-0 : [('restaurant-1' : 3.3), ('restaurant-0' : 3.0), ('restaurant-2' : 3.0)]

getTopRestaurantsByFood('food-1')
returns [restaurant-0, restaurant-2]
(For reference only) list of restaurants with rating for food food-1 : [('restaurant-0' : 2.3), ('restaurant-2' : 0.0)]


getTopRatedRestaurants() returns
[restaurant-1, restaurant-2, restaurant-0]
(For reference only) list of top restaurants with rating : [('restaurant-1' : 3.3), ('restaurant-2' : 3.0), ('restaurant-0' : 2.5)]
*/


#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class IObserver {
    public:
    virtual void setRating(double rating) = 0;
    virtual void increaseTotalRatingCount () = 0;
};

// Subscriber
class FoodItem : public IObserver {
    string name;
    double rating;
    int totalRatings = 0;
    public:
    FoodItem(string name, double rating) : name(name), rating(rating) {

    }

    void increaseTotalRatingCount() {
        this->totalRatings++;
    }

    int getTotalRatings() {
        return this->totalRatings;
    }

    void setRating(double rating) {
        increaseTotalRatingCount();
        this->rating = (this->rating + rating)/ (1.0 * totalRatings);
        cout<<"FoodItem: "<<this->name<<", Rating: "<<this->rating<<endl;
    }

    void setName(string name) {
        this->name = name;
    }

    double getRating() {
        return this->rating;
    }

    string getName() {
        return this->name;
    }
};

// Subscriber
class Restaurant : public IObserver {
    string name;
    double rating;
    int totalRatings = 0;
    unordered_map<FoodItem*, pair<double, int>> foodMenu;
    public:
    Restaurant(string name, double rating) : name(name), rating(rating) {

    }

    void increaseTotalRatingCount() {
        this->totalRatings++;
    }

    int getTotalRatings() {
        return this->totalRatings;
    }
    void setRating(double rating) {
        increaseTotalRatingCount();
        this->rating = (this->rating + rating)/ (1.0 * totalRatings);
        cout<<"Restaurant: "<<this->name<<", Rating: "<<this->rating<<endl;
    }

    void setName(string name) {
        this->name = name;
    }

    int getRating() {
        return this->rating;
    }

    string getName() {
        return this->name;
    }

    double getFoodRating(FoodItem* food) {
        if (foodMenu.find(food) != foodMenu.end())
            return this->foodMenu[food].first;
    }

    unordered_map<FoodItem*, pair<double, int>> GetMenu() {
        return this->foodMenu;
    }

    bool checkFoodItemAvailabilty(FoodItem* item) {
        if (foodMenu.find(item) != foodMenu.end())
            return true;
        return false;
    }

    void addMenu(FoodItem* food) {
        foodMenu[food] = {0.0, 1};
    }

    void increaseFoodRating(FoodItem* food, double rating) {
        foodMenu[food].second++;
        foodMenu[food].first = (foodMenu[food].second + rating)/(1.0 * foodMenu[food].second);
    }

    void orderFood(FoodItem* food, string orderdId) {
        if (foodMenu.find(food) == foodMenu.end()) {
            this->addMenu(food);
        } else {

        }
        cout<<"OrderdId: "<<orderdId<< ", Restaurant: "<<this->name<<"--"<<", FoodItem: "<<food->getName()<<endl;
    }
};

// Observer design pattern
// Publisher
class RateOrder {
    unordered_map<IObserver*, bool> observersList;

    public:
    void AddSubscriber(IObserver* ob) {
        observersList[ob] = true;
    }

    void removeSubscriber(IObserver* ob) {
        observersList.erase(ob);
    }

    void notify(int rating) {
        for (auto itr = observersList.begin();itr != observersList.end(); itr++) {
            itr->first->setRating(rating);
        }
    }

    void newRating(int rating) {
        this->notify(rating);
    }
};


// Strategy design pattern
class IGetTopRestaurants {
    public:
    virtual vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList) = 0;

    virtual vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList, FoodItem* food) = 0;
};

class GetTopRestaurantsByFood : public IGetTopRestaurants {
    public:

    vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList) {
        vector<Restaurant*> res;
        return res;
    }

    static bool myFunc(pair<Restaurant*, double>p1, pair<Restaurant*, double>p2) {
        return p1.second > p2.second;
    }    

    vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList, FoodItem* food) {
        vector<Restaurant*> res;
        vector<pair<Restaurant*, double>>temp;
        for (auto itr=restaurantList.begin();itr != restaurantList.end(); itr++) {
            if (itr->second->checkFoodItemAvailabilty(food)) {
                temp.push_back({itr->second, itr->second->getFoodRating(food)});
            }
        }
        sort(temp.begin(), temp.end(), myFunc);
        cout<<"Get Restuarants By food rating, "<<food->getName()<<endl;
        for (int i=0;i<temp.size();i++) {
            cout<<temp[i].first->getName()<<" "<<temp[i].second<<endl;
            res.push_back(temp[i].first);
        }
        cout<<endl;
        return res;
    }
};  

class GetTopRatedRestaurants : public IGetTopRestaurants {
    public:

    static bool myFunc(Restaurant* r1, Restaurant* r2) {
        return r1->getRating() > r2->getRating();
    }

    vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList, FoodItem* food) {
        vector<Restaurant*>res;
        return res;
    }

    vector<Restaurant*> GetRestaurants(unordered_map<string, Restaurant*> &restaurantList) {
        vector<Restaurant*> res;
        for (auto itr=restaurantList.begin(); itr != restaurantList.end(); itr++) {
            res.push_back(itr->second);
        }
        sort(res.begin(), res.end(), myFunc);
        return res;
    }
};

class FoodDelieverySystem {
    public:
    unordered_map<string, FoodItem*> foodItemMap;
    unordered_map<string, Restaurant*> restaurantMap;
    unordered_map<string, vector<IObserver*>> orderMap;
    void init() {
        FoodItem* food0 = new FoodItem("food-0", 0.0);
        FoodItem* food1 = new FoodItem("food-1", 0.0);
        // FoodItem Pastry("Pastry", 0.0);
        // FoodItem Pasta("Pasta", 0.0);

        Restaurant* restaurant0 = new Restaurant("restaurant-0", 0.0);
        Restaurant* restaurant1 = new Restaurant("restaurant-1", 0.0);
        Restaurant* restaurant2 = new Restaurant("restaurant-2", 0.0);

        foodItemMap["food-0"] = food0;
        foodItemMap["food-1"] = food1;
        // foodItemMap["Pastry"] = &Pastry;
        // foodItemMap["Pasta"] = &Pasta;

        restaurantMap["restaurant-0"] = restaurant0;
        restaurantMap["restaurant-1"] = restaurant1;
        restaurantMap["restaurant-2"] = restaurant2;
    }

    void destroy() {
        for (auto itr=foodItemMap.begin();itr !=foodItemMap.end(); itr++) {
            delete itr->second;
        }
        for (auto itr=restaurantMap.begin();itr !=restaurantMap.end(); itr++) {
            delete itr->second;
        }
        foodItemMap.clear();
        restaurantMap.clear();
    }

    void orderFood(string orderId, string foodItemId, string restaurantId) {
        // Restaurant* r = restaurantMap[restaurantId];
        // FoodItem* f = foodItemMap[foodItemId];
        restaurantMap[restaurantId]->orderFood(foodItemMap[foodItemId], orderId);
        orderMap[orderId].push_back(restaurantMap[restaurantId]);
        orderMap[orderId].push_back(foodItemMap[foodItemId]);
    }

    // While giving rating to an order, we will give the same rating to both fooditem and restaurat
    // Here foodItem and restaurant can be subscibers and Giverating here can be a publisher
    void rateOrder(string orderId, double rating) {
        vector<IObserver*> list = orderMap[orderId];
        RateOrder ro;
        for (int i=0;i<list.size();i++) {
            ro.AddSubscriber(list[i]);
        }
        ro.newRating(rating);
        // RateOrder* ro = new RateOrder();
        // for (int i=0;i<list.size();i++) {
        //     ro->AddSubscriber(list[i]);
        // }
        // ro->newRating(rating);
        // delete ro;
    }


    // There are 2 ways to get top restaurants
    // either by food or by overall rating
    // we can use strategy design pattern here
    vector<string> getTopRestaurantsByFood(string foodItemId) {
        IGetTopRestaurants* gtf = new GetTopRestaurantsByFood();
        // GetTopRestaurantsByFood gtf;
        vector<Restaurant*> res = gtf->GetRestaurants(restaurantMap, foodItemMap[foodItemId]);
        vector<string>ans;
        for (int i=0;i<res.size();i++) {
            ans.push_back(res[i]->getName());
        }
        return ans;
    }

    vector<string> getTopRatedRestaurants() {
        IGetTopRestaurants* gtrr = new GetTopRatedRestaurants();
        // GetTopRatedRestaurants gtrr;
        vector<Restaurant*> res = gtrr->GetRestaurants(restaurantMap);
        vector<string>ans;
        for (int i=0;i<res.size();i++) {
            ans.push_back(res[i]->getName());
        }
        return ans;
    }

};

int main() {
    FoodDelieverySystem swiggy;
    swiggy.init();
    swiggy.orderFood("order-0", "food-1", "restaurant-0");
    swiggy.rateOrder("order-0",  3.0);

    swiggy.orderFood("order-1", "food-0",  "restaurant-2");
    swiggy.rateOrder("order-1",  1.0);

    swiggy.orderFood("order-2", "food-0",  "restaurant-1");
    swiggy.rateOrder("order-2", 3.0);

    swiggy.orderFood("order-3", "food-0",  "restaurant-2");
    swiggy.rateOrder("order-3", 5.0);

    swiggy.orderFood("order-4", "food-0",  "restaurant-0");
    swiggy.rateOrder("order-4", 3.0);

    swiggy.orderFood("order-5", "food-0",  "restaurant-1");
    swiggy.rateOrder("order-5", 4.0);

    swiggy.orderFood("order-6", "food-1",  "restaurant-0");
    swiggy.rateOrder("order-6", 2.0);

    swiggy.orderFood("order-7", "food-1",  "restaurant-0");
    swiggy.rateOrder("order-7", 2.0);

    swiggy.orderFood("order-8", "food-0",  "restaurant-1");
    swiggy.rateOrder("order-8", 2.0);

    swiggy.orderFood("order-9", "food-0",  "restaurant-1");
    swiggy.rateOrder("order-9", 4.0);

    vector<string> res = swiggy.getTopRatedRestaurants();
    cout<<"Top Rated Restaurants: ";
    for (int i=0;i<res.size();i++) {
        cout<<res[i]<<", ";
    }
    cout<<endl;
    // res = swiggy.getTopRestaurantsByFood("food-0");
    // cout<<"Top Rated Restaurants by food: ";
    // for (int i=0;i<res.size();i++) {
    //     cout<<res[i]<<", ";
    // }
    // cout<<endl;
    swiggy.destroy();
}