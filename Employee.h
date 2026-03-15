#pragma once
enum class ErrorCode {
    OK,
    NotFound,
    Duplicate,
    InvalidInput
};
class Employee {
    unsigned id;
    static unsigned id_count;
    char name[128];
    char position[128];
    double salary;
public:
    Employee();
    Employee(const char*, const char*, double);
    
    double getSalary() const;
    unsigned getId() const;
    ErrorCode updateSalary(double amount);
    static unsigned getLastId();
    void print() const;
};

class Department {
    static constexpr int MAX_NAME = 128;
    static constexpr int MAX_SIZE = 15;
    char* name = nullptr;
    Employee employees[MAX_SIZE];
    unsigned countOfEmployees;
public:
    Department();
    Department(const char* name, Employee* employees, unsigned countOfEmployees);
    
    void setName(const char* name);
    const char* getName() const;
    
    ErrorCode addEmployee(const Employee& employee);
    ErrorCode removeEmployee(unsigned id);
    static unsigned getMaxEmployees();
    void print() const;

    ~Department();
};

class Company {
    static constexpr int MAX_SIZE = 10;
    Department departments[MAX_SIZE];
    unsigned countOfDepartments;
    
    Company();
    
    Company(const Company&) = delete;
    Company& operator=(const Company&) = delete;

    int findDepartmentIndex(const char* name);
public:
    static Company& getInstance();

    void print() const;

    ErrorCode addDepartment(const char* name);
    ErrorCode removeDepartment(const char* name);
    ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee);
    ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id);
};
