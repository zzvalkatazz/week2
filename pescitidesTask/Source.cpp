#include<stack>
#include<iostream>
//obrashtane na stek
template<typename T>
void reverse(Stack<T>& stack)
{
	Stack<T> reversed;
	while(!stack.empty())
	{
		reversed.push(stack.top());
		stack.pop();
	}
	stack = reversed;
}
//simulacia na edin den v ramkite na zadachata
//връща истина ако разстението е умряло,иначе лъжа

bool kill_plants(Stack<int>& pesticides)
{
	Stack<int> for_next_day;
	bool plant_has_been_killed = false;

	while (!pesticides.empty())
	{
		int plant_pesticide = pesticides.top();
		pesticides.pop();
		if (!pesticides.empty() && plant_pesticide > pesticides.top())
		{
			plant_has_been_killed = true;
		}
		else {
			for_next_day.push(plant_pesticide);
		}
	}
	reverse(for_next_day);
	pesticides = for_next_day;
	return plant_has_been_killed;
}
int main()
{
	int number_of_plants;
	Stack<int> pesticides;

	std::cin >> number_of_plants;
	for (int i = 0; i < number_of_plants; i++)
	{
		int plant_pesticide;
		std::cin >> plant_pesticide;
		pesticides.push(plant_pesticides);
	}
	int day = 0;
	while (kill_plants(pesticides))
	{
		day++;
	}
	std::cout << day << std::endl;
	return 0;

}