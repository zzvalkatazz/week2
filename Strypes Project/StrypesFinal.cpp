#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<cmath>

struct IntegratedCircuit
{
	std::string name; // името на схемата
	std::vector<std::string> inputs; //Списък с имената на входните променливи
	std::string expression; //логически израз на схемата
};
struct InputValue
{
	std::string name; //името на входната променлива
	int value; //стойността на входа (0 или 1)
};
//проверка дали символът е буква или цифра
bool isAlphaOrNumber(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
bool parseDefineCommand(const std::string& command, IntegratedCircuit& ic)
{
	std::string definePrefix = "DEFINE";
	//проверка дали командата започва с DEFINE
	if (command.substr(0, definePrefix.size()) != definePrefix)
	{
	return false;
	}
	//извличаме като  част от командата
	std::string commandPart = command.substr(definePrefix.size());
	//извлича името на схемата и входовете
	size_t nameEnd = commandPart.find('(');
	if (nameEnd == std::string::npos)
	{
		return false;
	}
	ic.name = commandPart.substr(0, nameEnd);
	size_t inputsEnd = commandPart.find(')');
	if (inputsEnd == std::string::npos)
	{
		return false;
	}
	std::string inputsStr = commandPart.substr(nameEnd + 1, inputsEnd - nameEnd - 1);
	// следващата стъпка маха водещи и завършващи интервали от входовете за да се осигури правилно парсиране

	size_t startPos = 0;
	size_t endPos = inputsStr.length() - 1;

	while (startPos <= endPos && std::isspace(inputsStr[startPos]))
	{
		startPos++;
	}

	while (endPos >= startPos && std::isspace(inputsStr[endPos]))
	{
		endPos--;
	}
	inputsStr = inputsStr.substr(startPos, endPos - startPos + 1);
	//следващата стъпка е разделяне на входове по запетая
	size_t pos = 0;
	while ((pos = inputsStr.find(',')) != std::string::npos)
	{
		ic.inputs.push_back(inputsStr.substr(0, pos));
		inputsStr.erase(0, pos + 1);
		while (!inputsStr.empty() && std::isspace(inputsStr[0]))
		{
			inputsStr.erase(0, 1);
		}
	}

	ic.inputs.push_back(inputsStr);
	//Извличаме логическия израз
	//намира позицията на":" за да се идентифицира началото на логическия израз и ако форматът е правилен
	size_t exprStart = commandPart.find(':', inputsEnd);
	if (exprStart == std::string::npos)
	{
		return false;
	}
	ic.expression = commandPart.substr(exprStart + 2);
	
	//Проверка дали всички входове са дефинирани
	size_t posInput = 0;
	std::string inputName;

	while (posInput < ic.expression.length())
	{
		if (isAlphaOrNumber(ic.expression[posInput]))
		{
			inputName.clear();
			while (posInput < ic.expression.length() && isAlphaOrNumber(ic.expression[posInput]))
			{
				inputName += ic.expression[posInput];
				posInput++;
			}
			if (std::find(ic.inputs.begin(), ic.inputs.end(), inputName) == ic.inputs.end())
			{
				std::cout << "Error: Input " <<" "<< inputName << " "<< "is not defined.\n";
				return false;
			}
		}
		else
		{
			posInput++;
		}
	}
	return true;
}
//фунцкия, която връща приоритета на логически оператор
int priority(char op)
{
	if (op == '!') return 3;
	if (op == '&') return 2;
	if (op == '|') return 1;
	return 0;
}
// функция, която прилага двоичен логически оператор към две булеви функции
bool applyOpеration(char op, bool a, bool b)
{
	switch (op)
	{
	case '&': return a && b;
	case '|': return a || b;
	default: return false;
	}
}
bool evaluateExpression(const std::string& expression, const std::vector<InputValue>& inputValues, bool& result)
{
	std::stack<bool> values; // стека съхранява булевите стойности
	std::stack<char> operators; // стека съхранява операторите
	std::string token; // временно съхранява имена на входове
	size_t pos = 0; // променлива за обхождане на низа 'expression'

	while (pos < expression.size())
	{
		if (isspace(expression[pos]))
		{
			pos++;
			continue;
		}
		if (expression[pos] == '(')
		{
			operators.push(expression[pos]);
		}
		else if (expression[pos] == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				char op = operators.top();
				operators.pop();
				bool val2 = values.top();
				values.pop();
				bool val1 = values.top();
				values.pop();
				values.push(applyOpеration(op, val1, val2));
			}
			operators.pop();
		}
		else if (expression[pos] == '&' || expression[pos] == '|')
		{
			while (!operators.empty() && priority(operators.top()) >= priority(expression[pos]))
			{
				char op = operators.top(); operators.pop();
				bool val2 = values.top();
				values.pop();
				bool val1 = values.top();
				values.pop();
				values.push(applyOpеration(op, val1, val2));
			}
			operators.push(expression[pos]);
		}
		else if (expression[pos] == '!')
		{
			operators.push(expression[pos]);
		}
		else if (isAlphaOrNumber(expression[pos]))
		{
			token.clear();
			while (pos < expression.size() && isAlphaOrNumber(expression[pos]))
			{
				token += expression[pos++];
			}
			pos--;
			auto it = std::find_if(inputValues.begin(), inputValues.end(), [&token](const InputValue& inputValue)
				{
					return inputValue.name == token;
				});
			if (it == inputValues.end())
			{
				std::cout << "Error: Undefined input " << token << " in expression.\n";
				return false;
			}
			values.push(it->value);
		}
		pos++;
	}

	while (!operators.empty())
	{
		char op = operators.top(); operators.pop();
		if (op == '!')
		{
			bool val = values.top(); values.pop();
			values.push(!val);
		}
		else
		{
			bool val2 = values.top(); values.pop();
			bool val1 = values.top(); values.pop();
			values.push(applyOpеration(op, val1, val2));
		}
	}

	if (values.size() != 1)
	{
		std::cout << "Error: Invalid expression evaluation.\n";
		return false;
	}

	result = values.top();
	return true;
}

void runCommand(const std::string& command, const std::vector<IntegratedCircuit>& circuits)
{
	//проверяваме валидноста на командата по начин, аналогичен на DEFINE
	std::string runPrefix = "RUN";
	if (command.substr(0, runPrefix.size()) != runPrefix)
	{
		std::cout << "Errot:Invalid RUN command.\n";
		return;
	}
	std::string commandPart = command.substr(runPrefix.size());
	size_t nameEnd= commandPart.find('(');
	if (nameEnd == std::string::npos)
	{
		std::cout << "Error: Invalid circuit name or inputs.'\n";
		return;
	}
	std::string circuitName = commandPart.substr(0, nameEnd);
	size_t inputsEnd = commandPart.find(')');
	if (inputsEnd == std::string::npos)
	{
		std::cout << "Error:Invalid circuit name or inputs.\n";
		return;
	}
	//извлича низа с входни стойности между отварящата и затварящата скоба и го записва в 'inputsStr'
	std::string inputsStr = commandPart.substr(nameEnd + 1, inputsEnd - nameEnd - 1);
	//декларира вектор 'inputValues' за съхранение на входните стойности и използва цикъл за разделяне на 'inputStr' по запетаи и извлича всяка стойност като цяло число,което добавя във вектора 'inputValues'
	std::vector<int> inputValues;
	size_t pos = 0;
	while (pos < inputsStr.length())
	{
		size_t commaPos = inputsStr.find(',', pos);
		if (commaPos == std::string::npos)
		{
			commaPos = inputsStr.length();
		}
		std::string inputValueStr = inputsStr.substr(pos, commaPos - pos);
		inputValues.push_back(std::stoi(inputValueStr));
		pos = commaPos + 1;
	}
	//Tърси интегрирания блок с име 'circuitName' във вектора 'circuits' с помощта на std::find_if
	// Проверява дали броят на входните стойности съответства на броя на входовете,дефинирани за намерения интегриран блок
	//ако броят не съвпада,извежда грешка и излиза от фунцкията
	auto it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic)
		{
			return ic.name == circuitName;
		});
	if (it == circuits.end())
	{
		std::cout << "Error:Circuit" << circuitName << "is not defined.\n";
		return;
	}
	if (inputValues.size() != it->inputs.size())
	{
		std::cout << "Error:Incorrect number of input values for circuit" << circuitName << ".\n";
		return;
	}
	//декларира вектор 'inputMap' за съхранение на съответсвията между имена и стойности на входовете
	//използва цикъл за попълване на 'inputMap' с обекти от тип 'InputValue', където всяко име на вход се съпоставя с неговата стойност
	std::vector<InputValue> inputMap;
	for (size_t i = 0; i < it->inputs.size(); i++)
	{
		InputValue iv;
		iv.name = it->inputs[i];
		iv.value = inputValues[i];
		inputMap.push_back(iv);
	}

	bool result;
	if (evaluateExpression(it->expression, inputMap, result))
	{
		std::cout<<"Result:"<<result <<"\n";
	}
	else
	{
		std::cout << "Error: Failed to evaluate the expression.\n";
	}
}
void allComand(const std::string& command, const std::vector<IntegratedCircuit>& circuits)
{
	//декларираме командата
	std::string allPrefix = "ALL";
	if (command.substr(0, allPrefix.size()) != allPrefix)
	{
		std::cout << "Error: Invalid ALL command.\n";
		return;
	}
	std::string circuitName = command.substr(allPrefix.size());
	//Търси интегрирания блок във вектора 'circuits' с помощта на std::find_if
	auto it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic)
		{
			return ic.name == circuitName;
		});
	if (it == circuits.end())
	{
		std::cout << "Error:Circuit" << circuitName << "is not defined.\n";
		return;
	}
	//Декларира променливата'inputCount', която съхранява бори на входове на намерния интегриран блок и изчислява общия брой възможни комбинации от входни стойности и го съхранява в 'combinations'
	size_t inputCount = it->inputs.size();
	size_t combinations = std::pow(2, inputCount);
	//вътрешния цикъл генерирра всяка комбинация от входни стойности за текущата итерация на външния цикъл и декларира обект "InputValue"за всеки вход, задава му име и стойност, и го добавя към вектора 'InputMap'
	for (size_t i = 0; i < combinations; i++)
	{
		std::vector<InputValue> inputMap;
		for (size_t j = 0; j < inputCount; j++)
		{
			InputValue iv;
			iv.name = it->inputs[j];
			iv.value = (i >> j) & 1;
			inputMap.push_back(iv);
		}
		bool result;
		//извиква функцията 'evaluateExpression' с израза на интегрирания блок, съотвествията на входовете и 'result'
		if (evaluateExpression(it->expression, inputMap, result))
		{
			std::cout << "Inputs:";
			for (size_t j = 0; j < inputCount; j++)
			{
				std::cout<< ((i >> j) & 1) << " ";
			}
			std::cout << "Result:" << result << "\n";
		}
		else {
			std::cout << "Error:Failed to evaluate the expression.\n";
		}
	}
}


int main() {
	std::vector<IntegratedCircuit> circuits;
	std::string command;

	while (true) {
		std::cout << "Enter command: ";
		std::getline(std::cin, command);

		if (command.find("DEFINE") == 0) {
			IntegratedCircuit ic;
			if (parseDefineCommand(command, ic)) {
				circuits.push_back(ic);
			}
			else {
				std::cout << "Error: Invalid DEFINE command.\n";
			}
		}
		else if (command.find("RUN") == 0) {
			runCommand(command, circuits);
		}
		else if (command.find("ALL") == 0) {
			allComand(command, circuits);
		}
		else {
			std::cout << "Error: Invalid command.\n";
		}
	}

	return 0;
}
