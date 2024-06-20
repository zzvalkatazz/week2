#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<cmath>

struct IntegratedCircuit
{
	std::string name; // ����� �� �������
	std::vector<std::string> inputs; //������ � ������� �� �������� ����������
	std::string expression; //��������� ����� �� �������
};
struct InputValue
{
	std::string name; //����� �� �������� ����������
	int value; //���������� �� ����� (0 ��� 1)
};
//�������� ���� �������� � ����� ��� �����
bool isAlphaOrNumber(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
bool parseDefineCommand(const std::string& command, IntegratedCircuit& ic)
{
	std::string definePrefix = "DEFINE";
	//�������� ���� ��������� ������� � DEFINE
	if (command.substr(0, definePrefix.size()) != definePrefix)
	{
	return false;
	}
	//��������� ����  ���� �� ���������
	std::string commandPart = command.substr(definePrefix.size());
	//������� ����� �� ������� � ���������
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
	// ���������� ������ ���� ������ � ���������� ��������� �� ��������� �� �� �� ������� �������� ���������

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
	//���������� ������ � ��������� �� ������� �� �������
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
	//��������� ���������� �����
	//������ ��������� ��":" �� �� �� ������������ �������� �� ���������� ����� � ��� �������� � ��������
	size_t exprStart = commandPart.find(':', inputsEnd);
	if (exprStart == std::string::npos)
	{
		return false;
	}
	ic.expression = commandPart.substr(exprStart + 2);
	
	//�������� ���� ������ ������� �� ����������
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
//�������, ����� ����� ���������� �� ��������� ��������
int priority(char op)
{
	if (op == '!') return 3;
	if (op == '&') return 2;
	if (op == '|') return 1;
	return 0;
}
// �������, ����� ������� ������� ��������� �������� ��� ��� ������ �������
bool applyOp�ration(char op, bool a, bool b)
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
	std::stack<bool> values; // ����� ��������� �������� ���������
	std::stack<char> operators; // ����� ��������� �����������
	std::string token; // �������� ��������� ����� �� �������
	size_t pos = 0; // ���������� �� ��������� �� ���� 'expression'

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
				values.push(applyOp�ration(op, val1, val2));
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
				values.push(applyOp�ration(op, val1, val2));
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
			values.push(applyOp�ration(op, val1, val2));
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
	//����������� ���������� �� ��������� �� �����, ���������� �� DEFINE
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
	//������� ���� � ������ ��������� ����� ���������� � ����������� ����� � �� ������� � 'inputsStr'
	std::string inputsStr = commandPart.substr(nameEnd + 1, inputsEnd - nameEnd - 1);
	//��������� ������ 'inputValues' �� ���������� �� �������� ��������� � �������� ����� �� ��������� �� 'inputStr' �� ������� � ������� ����� �������� ���� ���� �����,����� ������ ��� ������� 'inputValues'
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
	//T���� ������������ ���� � ��� 'circuitName' ��� ������� 'circuits' � ������� �� std::find_if
	// ��������� ���� ����� �� �������� ��������� ����������� �� ���� �� ���������,���������� �� ��������� ���������� ����
	//��� ����� �� �������,������� ������ � ������ �� ���������
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
	//��������� ������ 'inputMap' �� ���������� �� ������������� ����� ����� � ��������� �� ���������
	//�������� ����� �� ��������� �� 'inputMap' � ������ �� ��� 'InputValue', ������ ����� ��� �� ���� �� ��������� � �������� ��������
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
	//����������� ���������
	std::string allPrefix = "ALL";
	if (command.substr(0, allPrefix.size()) != allPrefix)
	{
		std::cout << "Error: Invalid ALL command.\n";
		return;
	}
	std::string circuitName = command.substr(allPrefix.size());
	//����� ������������ ���� ��� ������� 'circuits' � ������� �� std::find_if
	auto it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic)
		{
			return ic.name == circuitName;
		});
	if (it == circuits.end())
	{
		std::cout << "Error:Circuit" << circuitName << "is not defined.\n";
		return;
	}
	//��������� ������������'inputCount', ����� ��������� ���� �� ������� �� �������� ���������� ���� � ��������� ����� ���� �������� ���������� �� ������ ��������� � �� ��������� � 'combinations'
	size_t inputCount = it->inputs.size();
	size_t combinations = std::pow(2, inputCount);
	//��������� ����� ��������� ����� ���������� �� ������ ��������� �� �������� �������� �� ������� ����� � ��������� ����� "InputValue"�� ����� ����, ������ �� ��� � ��������, � �� ������ ��� ������� 'InputMap'
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
		//������� ��������� 'evaluateExpression' � ������ �� ������������ ����, ������������� �� ��������� � 'result'
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
