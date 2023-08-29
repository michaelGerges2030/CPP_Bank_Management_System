#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <Windows.h>

using namespace std;
typedef long long ll;

class Validation
{
public:
    static bool validateName(string name)
    {
        //The valid name should be between a:z or A:Z
        string pattern = " 0123456789~!@#$%^&*()_+=?.,<>;:";
        for (int i = 0; i < name.size(); i++)
        {
            if (pattern.find(name[i]) >= 0 && pattern.find(name[i]) <= pattern.size() || name.size() < 5 || name.size() > 20)
            {
                return false;
            }
        }
        return true;
    }

    static bool validatePassword(string password)
    {
        for (int i = 0; i < password.size(); i++)
        {
            if (password[i] == ' ' || password.size() < 8 || password.size() > 20)
            {
                return false;
            }
        }
        return true;
    }
    static bool validateBalance(double balance)
    {
        if (balance < 1500)
        {
            return false;
        }
        return true;
    }

    static bool validateSalary(double salary)
    {
        if (salary < 5000)
        {
            return false;
        }
        return true;
    }

    static string enterName() {
        string name;
        system("cls");
        cout << "Enter name: ";
        cin >> name;
        while (!validateName(name)) {
            system("cls");
            cout << "Invalid name!\n";
            cout << "Name must be 5 to 20 alphabetic characters.\n";
            cout << "Enter name: ";
            cin >> name;
        }
        return name;
    }
    static string enterPassword() {
        string password;
        system("cls");
        cout << "Enter password: ";
        cin >> password;
        while (!validatePassword(password)) {
            system("cls");
            cout << "Invalid password!\n";
            cout << "Password must be 8 to 20 characters.\n" << endl;
            cout << "Enter password: ";
            cin >> password;
        }
        return password;
    }
    static double enterBalance() {
        double balance;
        cout << "Enter balance: ";
        cin >> balance;
        while (!validateBalance(balance)) {
            system("cls");
            cout << "Invalid balance!\n";
            cout << "Balance must be at least 1500.\n" << endl;
            cout << "Enter balance: ";
            cin >> balance;
        }
        return balance;
    }
    static double enterSalary() {
        double salary;
        cout << "Enter salary: ";
        cin >> salary;
        while (!validateSalary(salary)) {
            system("cls");
            cout << "Invalid salary!\n";
            cout << "Salary must be at least 5000.\n" << endl;
            cout << "Enter salary: ";
            cin >> salary;
        }
        return salary;
    }
};

class Person
{
private:
    string name, password;
    int id;

public:
    //Constructors
    Person()
    {
        this->id = 0;
    }

    Person(int id, string name, string password)
    {
        setid(id);
        setname(name);
        setpassword(password);
    }
    //Setters
    void setname(string name)
    {
        if (Validation::validateName(name))
        {
            this->name = name;
        }
    }

    void setpassword(string password)
    {
        if (Validation::validatePassword(password))
        {
            this->password = password;
        }
    }

    void setid(int id)
    {
        this->id = id;
    }

    //Getters
    string getname()
    {
        return this->name;
    }

    string getpassword()
    {
        return this->password;
    }

    int getid()
    {
        return this->id;
    }

    //Method
    void display() {
        cout << "Name: " << getname() << "\n";
        cout << "Id: " << getid() << "\n";
        cout << "Password: " << getpassword() << "\n";
    }
};

class Client : public Person
{
private:
    double balance;

public:
    //Constructors
    Client() :Person()
    {
        this->balance = 0;
    }

    Client(int id, string name, string password, double balance) : Person(id, name, password)
    {
        setbalance(balance);
    }
    //Setters
    void setbalance(double balance)
    {
        if (Validation::validateBalance(balance))
        {
            this->balance = balance;
        }
    }

    //Getters
    double getbalance()
    {
        return this->balance;
    }

    //Methods
    void deposit(double amount)
    {
        if (amount > 0) {
            this->balance += amount;
            cout << "\nSuccessful Transaction.\n";
        }
    }

    void withdraw(double amount)
    {
        if (this->balance >= amount)
        {
            this->balance -= amount;
            cout << "\nSuccessful Transaction.\n";
        }
        else {
            cout << "\nYour Balance Isn't Enough!\n";
        }
    }

    void transferTo(double amount, Client& recipient)
    {
        if (this->balance >= amount)
        {
            this->balance -= amount;
            recipient.balance += amount;
            cout << "\nSuccessful Transaction.\n";
        }
        else
        {
            cout << "\nThe Balance Isn't Enough.\n";
        }
    }

    void checkBalance()
    {
        cout << "The Balance is: " << this->balance << "\n";
    }

    void display()
    {
        Person::display();
        cout << "Balance: " << this->balance << "\n";
    }
};
//Global Vectors to store data of allClients.
static vector <Client> allClients;
static vector <Client>::iterator clIt;

class Employee : public Person
{
private:
    double salary;

public:
    //Constructors
    Employee() :Person()
    {
        this->salary = 0;
    }

    Employee(int id, string name, string password, double salary) : Person(id, name, password)
    {
        setSalary(salary);
    }

    //Setters
    void setSalary(double salary)
    {
        if (Validation::validateSalary(salary))
        {
            this->salary = salary;
        }
    }

    //Getters
    double getSalary()
    {
        return this->salary;
    }

    //Methods
    void display()
    {
        Person::display();
        cout << "Salary: " << this->salary << "\n";
    }
    void addClient(Client& client) {
        allClients.push_back(client);
    }

    Client* searchClient(int id) {
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            if (clIt->getid() == id) {
                return clIt._Ptr;
            }
        }
        return NULL;
    }

    void listClient() {
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            clIt->display();
            cout << "------------------------------------------\n";
        }
    }

    void editClient(int id, string name, string password, double balance) {
        searchClient(id)->setname(name);
        searchClient(id)->setpassword(password);
        searchClient(id)->setbalance(balance);
    }
};
//Global Vector to store data of all Employees.
static vector <Employee> allEmployees;
static vector <Employee>::iterator emIt;

class Admin : public Employee
{
public:
    Admin() :Employee()
    {

    }

    Admin(int id, string name, string password, double balance) :Employee(id, name, password, balance)
    {

    }
    void addClient(Client& client) {
        allClients.push_back(client);
    }

    Client* searchClient(int id) {
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            if (clIt->getid() == id) {
                return clIt._Ptr;
            }
        }
        return NULL;
    }

    void listClient() {
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            clIt->display();
            cout << "---------------------------\n";
        }
    }

    void editClient(int id, string name, string password, double balance) {
        searchClient(id)->setname(name);
        searchClient(id)->setpassword(password);
        searchClient(id)->setbalance(balance);
    }

    void addEmployee(Employee& employee) {
        allEmployees.push_back(employee);
    }

    Employee* searchEmployee(int id) {
        for (emIt = allEmployees.begin(); emIt != allEmployees.end(); emIt++) {
            if (emIt->getid() == id) {
                return emIt._Ptr;
            }
        }
        return NULL;
    }

    void editEmployee(int id, string name, string password, double salary) {
        searchEmployee(id)->setname(name);
        searchEmployee(id)->setpassword(password);
        searchEmployee(id)->setSalary(salary);
    }

    void listEmployee() {
        for (emIt = allEmployees.begin(); emIt != allEmployees.end(); emIt++) {
            emIt->display();
            cout << "---------------------\n";
        }
    }
};
//Global Vector to store data of allAdmins.
static vector <Admin> allAdmins;
static vector <Admin>::iterator adIt;

class Parser {
private:
    static vector<string> split(string line) {
        stringstream stream(line);
        string part;
        vector <string> parts;
        while (getline(stream, part, '|')) {
            parts.push_back(part);
        }
        return parts;
    }

public:
    //id|name|password|balance or salary
    static Client parseToClient(string line) {
        vector <string> parts = split(line);
        Client client;
        client.setid(stoi(parts[0]));
        client.setname(parts[1]);
        client.setpassword(parts[2]);
        client.setbalance(stod(parts[3]));
        return client;
    }
    static Employee parseToEmployee(string line) {
        vector <string> parts = split(line);
        Employee employee;
        employee.setid(stoi(parts[0]));
        employee.setname(parts[1]);
        employee.setpassword(parts[2]);
        employee.setSalary(stod(parts[3]));
        return employee;
    }
    static Admin parseToAdmin(string line) {
        vector <string> parts = split(line);
        Admin admin;
        admin.setid(stoi(parts[0]));
        admin.setname(parts[1]);
        admin.setpassword(parts[2]);
        admin.setSalary(stod(parts[3]));
        return admin;
    }
};

class FilesHelper {
private:
    static void saveLast(string fileName, int id) {
        ofstream file;
        file.open(fileName);
        file << id;
        file.close();
    }
public:
    static int getLast(string fileName) {
        ifstream file;
        file.open(fileName);
        int id;
        file >> id;
        file.close();
        return id;
    }

    static void saveClient(Client c) {
        int id = getLast("LastClientID.txt");
        fstream file;
        file.open("Clients.txt", ios::app);
        file << id + 1 << '|' << c.getname() << '|' << c.getpassword() << '|' << c.getbalance() << "\n";
        file.close();
        saveLast("LastClientID.txt", id + 1);
    }

    static void saveEmployee(string fileName, string lastIdFile, Employee e) {
        int id = getLast(lastIdFile);
        fstream file;
        file.open(fileName, ios::app);
        file << id + 1 << '|' << e.getname() << '|' << e.getpassword() << '|' << e.getSalary() << "\n";
        file.close();
        saveLast(lastIdFile, id + 1);
    }

    static void getClients() {
        string line;
        ifstream file;
        file.open("Clients.txt");
        while (getline(file, line)) {
            Client c = Parser::parseToClient(line);
            allClients.push_back(c);
        }
        file.close();
    }

    static void getEmployees() {
        string line;
        ifstream file;
        file.open("Employees.txt");
        while (getline(file, line)) {
            Employee e = Parser::parseToEmployee(line);
            allEmployees.push_back(e);
        }
        file.close();
    }

    static void getAdmins() {
        string line;
        ifstream file;
        file.open("Admins.txt");
        while (getline(file, line)) {
            Admin a = Parser::parseToAdmin(line);
            allAdmins.push_back(a);
        }
        file.close();
    }

    static void clearFile(string fileName, string lastIdFile) {
        fstream file1, file2;
        file1.open(fileName, ios::out);
        file1.close();
        file2.open(lastIdFile, ios::out);
        file2 << 0;
        file2.close();
    }
};

class  DataSourceInterface {
public:
    //Pure virtual methods
    virtual void addClient(Client) = 0;
    virtual void addEmployee(Employee) = 0;
    virtual void addAdmin(Admin) = 0;
    virtual void getAllClients() = 0;
    virtual void getAllEmployees() = 0;
    virtual void getAllAdmins() = 0;
    virtual void removeAllClients() = 0;
    virtual void removeAllEmployees() = 0;
    virtual void removeAllAdmins() = 0;
};

class FileManager : public DataSourceInterface {
private:
    static void addClient(Client client) {
        FilesHelper::saveClient(client);
    }

    static void addEmployee(Employee employee) {
        FilesHelper::saveEmployee("Employees.txt", "LastEmployeeID.txt", employee);
    }

    static void addAdmin(Admin admin) {
        FilesHelper::saveEmployee("Admins.txt", "LastAdminID.txt", admin);
    }

    static void getAllClients() {
        FilesHelper::getClients();
    }

    static void getAllEmployees() {
        FilesHelper::getEmployees();
    }

    static void getAllAdmins() {
        FilesHelper::getAdmins();
    }

    static void removeAllClients() {
        FilesHelper::clearFile("Clients.txt", "LastClientID.txt");
    }

    static void removeAllEmployees() {
        FilesHelper::clearFile("Employees.txt", "LastEmployeeID.txt");
    }

    static void removeAllAdmins() {
        FilesHelper::clearFile("Admins.txt", "LastAdminID.txt");
    }

public:
    static void getAllData() {
        getAllClients();
        getAllEmployees();
        getAllAdmins();
    }

    static void updateClients() {
        removeAllClients();
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            addClient(*clIt);
        }
    }

    static void updateEmployees() {
        removeAllEmployees();
        for (emIt = allEmployees.begin(); emIt != allEmployees.end(); emIt++) {
            addEmployee(*emIt);
        }
    }

    static void updatAdmins() {
        removeAllAdmins();
        for (adIt = allAdmins.begin(); adIt != allAdmins.end(); adIt++) {
            addAdmin(*adIt);
        }
    }
};

class ClientManger {
private:
    static void printClientMenue() {
        system("cls");
        cout << "1. Display My Info" << "\n";
        cout << "2. Check Balance" << "\n";
        cout << "3. Update Password" << "\n";
        cout << "4. Withdraw Money" << "\n";
        cout << "5. Deposite Money" << "\n";
        cout << "6. Transfer Money" << "\n";
        cout << "7. Logout" << "\n";
    }
    // A Method to go back one step
    static void back(Client* client) {
        cout << "\n";
        system("pause");
        clientOptions(client);
    }

public:
    static void updatePassword(Person* person) {
        cout << "Enter Password: ";
        string password;
        cin >> password;
        if (Validation::validatePassword(password)) {
            person->setpassword(password);
            cout << "Password Updated Successfully.\n";
        }
        else {
            updatePassword(person);
        }
    }
    static Client* login(int id, string password) {
        for (clIt = allClients.begin(); clIt != allClients.end(); clIt++) {
            if (clIt->getid() == id && clIt->getpassword() == password) {
                return clIt._Ptr;
            }
        }
        return NULL;
    }
    static bool clientOptions(Client* client) {
        printClientMenue();
        cout << "Enter Your Choice\n";
        Employee e;
        double amount;
        int choice, id;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            client->display();
            break;
        case 2:
            system("cls");
            client->checkBalance();
            break;
        case 3:
            updatePassword(client);
            FileManager::updateClients();
            break;
        case 4:
            system("cls");
            cout << "Enter Amount To Withdraw: ";
            cin >> amount;
            client->withdraw(amount);
            FileManager::updateClients();
            break;
        case 5:
            system("cls");
            cout << "Enter Amount To Deposite: ";
            cin >> amount;
            client->deposit(amount);
            FileManager::updateClients();
            break;
        case 6:
            system("cls");
            cout << "Enter ID Of The Recipient: ";
            cin >> id;
            while (e.searchClient(id) == NULL) {
                system("cls");
                cout << "Invalid ID.\n\n";
                cout << "Enter ID of The Recipient: ";
                cin >> id;
            }
            cout << "\nEnter Amount Of Money To Transfer: ";
            cin >> amount;
            client->transferTo(amount, *e.searchClient(id));
            FileManager::updateClients();
            break;
        case 7:
            return false;
            break;
        default:
            system("cls");
            clientOptions(client);
            return true;
        }
        back(client);
        return true;
    }
};

class EmployeeManager {
private:
    static void printEmployeeMenu() {
        system("cls");
        cout << "(1) Display my info" << endl;
        cout << "(2) Update Password" << endl;
        cout << "(3) Add new client" << endl;
        cout << "(4) Search for client" << endl;
        cout << "(5) List all clients" << endl;
        cout << "(6) Edit client info" << endl;
        cout << "(7) Logout\n" << endl;
    }
    static void back(Employee* employee) {
        cout << "\n";
        system("pause");
        employeeOptions(employee);
    }

public:
    static void newClient(Employee* employee) {
        Client client;
        client.setid(FilesHelper::getLast("LastClientID.txt") + 1);
        string password;
        client.setname(Validation::enterName());
        client.setpassword(Validation::enterPassword());
        employee->addClient(client);
        FileManager::updateClients();
        cout << "\nClient added successfully.\n";
    }
    static void listAllClients(Employee* employee) {
        system("cls");
        cout << "All clients: \n" << endl;
        employee->listClient();
    }
    static void searchForClient(Employee* employee) {
        system("cls");
        cout << "Enter The Client ID: ";
        int id;
        cin >> id;
        if (employee->searchClient(id) == NULL) {
            cout << "\nClient Not Found.\n";
        }
        else {
            employee->searchClient(id)->display();
        }
    }
    static void editClientInfo(Employee* employee) {
        system("cls");
        cout << "Enter Client ID: ";
        int id;
        cin >> id;
        if (employee->searchClient(id) == NULL) {
            cout << "\nClient Not Found.\n";
        }
        else {
            string name = Validation::enterName();
            string password = Validation::enterPassword();
            double balance = Validation::enterBalance();
            employee->editClient(id, name, password, balance);
            FileManager::updateClients();
            cout << "\nClient Info Updated Successfully.\n";
        }
    }
    static Employee* login(int id, string password) {
        for (emIt = allEmployees.begin(); emIt != allEmployees.end(); emIt++) {
            if (emIt->getid() == id && emIt->getpassword() == password)
                return emIt._Ptr;
        }
        return NULL;
    }
    static bool employeeOptions(Employee* employee) {
        printEmployeeMenu();
        cout << "Enter Your Choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            employee->display();
            break;
        case 2:
            ClientManger::updatePassword(employee);
            FileManager::updateEmployees();
            break;
        case 3:
            newClient(employee);
            break;
        case 4:
            searchForClient(employee);
            break;
        case 5:
            listAllClients(employee);
            break;
        case 6:
            editClientInfo(employee);
            break;
        case 7:
            return false;
            break;
        default:
            system("cls");
            employeeOptions(employee);
            return true;
        }
        back(employee);
        return true;
    }
};

class AdminManager {
private:
    static void printAdminMenu() {
        system("cls");
        cout << "(1) Display my info" << endl;
        cout << "(2) Update Password" << endl;
        cout << "(3) Add new client" << endl;
        cout << "(4) Search for client" << endl;
        cout << "(5) List all clients" << endl;
        cout << "(6) Edit client info" << endl;
        cout << "(7) Add new Employee" << endl;
        cout << "(8) Search for Employee" << endl;
        cout << "(9) List all Employees" << endl;
        cout << "(10) Edit Employee info" << endl;
        cout << "(11) Logout\n" << endl;
    }
    static void back(Admin* admin) {
        cout << endl;
        system("pause");
        adminOptions(admin);
    }
public:
    static Admin* login(int id, string password) {
        for (adIt = allAdmins.begin(); adIt != allAdmins.end(); adIt++) {
            if (adIt->getid() == id && adIt->getpassword() == password)
                return adIt._Ptr;
        }
        return NULL;
    }
    static bool adminOptions(Admin* admin) {
        printAdminMenu();
        cout << "Enter Your Choice: ";
        Employee e;
        int choice, id;
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            admin->display();
            break;
        case 2:
            ClientManger::updatePassword(admin);
            FileManager::updatAdmins();
            break;
        case 3:
            EmployeeManager::newClient(admin);
            break;
        case 4:
            EmployeeManager::searchForClient(admin);
            break;
        case 5:
            EmployeeManager::listAllClients(admin);
            break;
        case 6:
            EmployeeManager::editClientInfo(admin);
            break;
        case 7:
            e.setname(Validation::enterName());
            e.setpassword(Validation::enterPassword());
            e.setSalary(Validation::enterSalary());
            e.setid(FilesHelper::getLast("LastEmployeeID.txt") + 1);
            admin->addEmployee(e);
            FileManager::updateEmployees();
            cout << "\nEmployee Added Successfully.\n";
            break;
        case 8:
            system("cls");
            cout << "Enter Employee ID: ";
            cin >> id;
            if (admin->searchEmployee(id) == NULL) {
                cout << "\nEmployee Not Found.\n";
            }
            else {
                admin->searchEmployee(id)->display();
            }
            break;
        case 9:
            system("cls");
            cout << "All Employees Are: \n";
            admin->listEmployee();
            break;
        case 10:
            system("cls");
            cout << "Enter Employee ID: ";
            cin >> id;
            if (admin->searchEmployee(id) == NULL) {
                cout << "\nEmployee Not Found.\n";
            }
            else {
                string name = Validation::enterName();
                string password = Validation::enterPassword();
                double salary = Validation::enterSalary();
                admin->editEmployee(id, name, password, salary);
                FileManager::updateEmployees();
                cout << "\nEmployee Info Updated Successfully.\n";
            }
            break;
        case 11:
            return false;
            break;
        default:
            system("cls");
            adminOptions(admin);
            return true;
        }
        back(admin);
        return true;
    }
};

class Screens {
private:
    static void bankName() {
        cout << "\t\t@@       @@   @@@@@@@      #######   ########  ####     ##  ##   ##\n";
        cout << "\t\t@@   @   @@   @@           ##    ##  ##    ##  ## ##    ##  ##  ##\n";
        cout << "\t\t@@  @@@  @@   @@@@@@@      #######   ########  ##  ##   ##  ## #\n";
        cout << "\t\t@@ @@ @@ @@   @@           ##    ##  ##    ##  ##   ##  ##  ##  ##\n";
        cout << "\t\t@@@     @@@   @@@@@@@      #######   ##    ##  ##    ####   ##   ##\n";
    }
    static void welcome() {
        system("Color 3f");
        cout << "\n\n\n\n\n\n\t    ##       ##   #######   ##      #######  ########    ####    ####   #######\n";
        cout << "\t    ##   #   ##   ##        ##      ##       ##    ##    ##  #  #  ##   ##\n";
        cout << "\t    ##  ###  ##   ######    ##      ##       ##    ##    ##   ##   ##   #######\n";
        cout << "\t    ## ## ## ##   ##        ##      ##       ##    ##    ##        ##   ##\n";
        cout << "\t    ###     ###   #######   ######  #######  ########    ##        ##   #######\n\n\n";
        bankName();
        Sleep(3000);
        system("cls");
        system("Color 0f");
    }
    static void loginOptions() {
        cout << "(1) Admin\n";
        cout << "(2) Employee\n";
        cout << "(3) Client\n";
        cout << "Login As: ";
    }
    static int loginAs() {
        loginOptions();
        int choice;
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3) {
            system("cls");
            return choice;
        }
        else {
            system("cls");
            return loginAs();
        }
    }
    static void invalid(int c) {
        system("cls");
        cout << "Incorrect ID or Password.\n";
        loginScreen(c);
    }
    static void logout() {
        system("cls");
        loginScreen(loginAs());
    }
    static void loginScreen(int c) {
        int choice = c, id;
        string password;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> password;
        switch (choice) {
        case 1:
            if (AdminManager::login(id, password) != NULL) {
                while (AdminManager::adminOptions(AdminManager::login(id, password)) != false);
                logout();
            }
            else invalid(1);
            break;
        case 2:
            if (EmployeeManager::login(id, password) != NULL) {
                while (AdminManager::adminOptions(AdminManager::login(id, password)) != false);
                logout();
            }
            else invalid(2);
            break;
        case 3:
            if (ClientManger::login(id, password) != NULL) {
                while (ClientManger::clientOptions(ClientManger::login(id, password)) != false);
                logout();
            }
            else invalid(3);
            break;
        default:
            system("cls");
            loginOptions();
        }
    }
public:
    static void runApp() {
        FileManager::getAllData();
        welcome();
        loginScreen(loginAs());
    }
};

int main()
{
    Screens().runApp();

    return 0;
}
