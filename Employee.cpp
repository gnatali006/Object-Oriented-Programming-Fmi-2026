#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"
#include <cstring>
#include <print>
#include <format>

//unsigned id;
//char name[128];
//char position[128];
//double salary;
unsigned Employee::id_count = 0;
Employee::Employee() : salary(0)
{
	strcpy(name, "unknown");
	strcpy(position, "unknown");
	id = ++id_count;
}

Employee::Employee(const char* n, const char* p, double s)
{
	if (!n || strlen(n) >= 128)
		strcpy(name, "unknown");
	else
		strcpy(name, n);
	if (!p || strlen(p) >= 128)
		strcpy(position, "unknown");
	else
		strcpy(position, p);
	id = ++id_count;
	if (s < 0) salary = 0;
	else salary = s;
}

double Employee::getSalary() const
{
	return salary;
}

unsigned Employee::getId() const
{
	return id;
}

ErrorCode Employee::updateSalary(double amount)
{
	if (amount < 0)
		return ErrorCode::InvalidInput;

	if (amount == salary)
		return ErrorCode::Duplicate;

	salary = amount;
	return ErrorCode::OK;
}

unsigned Employee::getLastId()
{
	return id_count;
}

void Employee::print() const
{
	std::println("Name: {}, position: {}, salary: {}", name, position, salary);
}

Department::Department(): countOfEmployees(0)
{
}

Department::Department(const char* name, Employee* employees, unsigned countOfEmployees)
{
	setName(name);

	if (countOfEmployees > MAX_SIZE)
		this->countOfEmployees = MAX_SIZE;
	else
		this->countOfEmployees = countOfEmployees;

	for (int i = 0; i < this->countOfEmployees; i++) {
		this->employees[i] = employees[i];
	}
}

void Department::setName(const char* name)
{
	if (!name) return;

	if (strlen(name) >= MAX_NAME)
		return;

	if (this->name)
		delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

const char* Department::getName() const
{
	return name;
}

ErrorCode Department::addEmployee(const Employee& employee)
{
	if (countOfEmployees >= MAX_SIZE)
		return ErrorCode::InvalidInput;

	for (int i = 0; i < countOfEmployees; i++) {
		if (employees[i].getId() == employee.getId())
			return ErrorCode::Duplicate;
	}

	employees[countOfEmployees++] = employee;
	return ErrorCode::OK;
}

ErrorCode Department::removeEmployee(unsigned id)
{
	for (int i = 0; i < countOfEmployees; i++) {
		if (employees[i].getId() == id) {
			for (int j = i; j < countOfEmployees - 1; j++) {
				employees[j] = employees[j + 1];
			}
			countOfEmployees--;
			return ErrorCode::OK;
		}
	}
	return ErrorCode::NotFound;
}

unsigned Department::getMaxEmployees()
{
	return MAX_SIZE;
}

void Department::print() const
{
	
	std::println("Name: {}", name);
	for (int i = 0; i < countOfEmployees; i++) {
		employees[i].print();
	}
}

Department::~Department()
{
	if (name)
		delete[] name;
}

Company::Company() : countOfDepartments(0) {}


int Company::findDepartmentIndex(const char* name)
{
	if (!name) return -1;

	for (int i = 0; i < countOfDepartments; i++) {
		if (strcmp(departments[i].getName(), name) == 0)
			return i;
	}

	return -1;
}

Company& Company::getInstance()
{
	static Company instance;
	return instance;
}

void Company::print() const
{
	for (int i = 0; i < countOfDepartments; i++) {
		departments[i].print();
	}
}

ErrorCode Company::addDepartment(const char* name)
{
	if (countOfDepartments >= MAX_SIZE)
		return ErrorCode::InvalidInput;

	if (findDepartmentIndex(name) != -1)
		return ErrorCode::Duplicate;

	departments[countOfDepartments].setName(name);
	countOfDepartments++;

	return ErrorCode::OK;
}

ErrorCode Company::removeDepartment(const char* name)
{
	int index = findDepartmentIndex(name);
	if(index==-1) return ErrorCode::NotFound;
	for (int i = index; i < countOfDepartments - 1; i++) {
		departments[i] = departments[i + 1];
	}
	countOfDepartments--;
	return ErrorCode::OK;
}

ErrorCode Company::addEmployeeToDepartment(const char* departmentName, const Employee& employee)
{
	int index = findDepartmentIndex(departmentName);
	if (index == -1) return ErrorCode::NotFound;
	return departments[index].addEmployee(employee);
}

ErrorCode Company::removeEmployeeFromDepartment(const char* departmentName, unsigned id)
{
	int index = findDepartmentIndex(departmentName);
	if (index == -1) return ErrorCode::NotFound;
	return departments[index].removeEmployee(id);
}

