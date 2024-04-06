#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;

void displayTimer(int t);
void updatePasswordInFile(string username, string newPassword);

// Define structures for tasks and code tasks
struct Task
{
    string name;
    string deadline;
    bool isCompleted;

    Task(const string& taskName, const string& taskDeadline, bool isComp)
        : name(taskName), deadline(taskDeadline), isCompleted(isComp) {}
};

struct CodeTask
{
    string code;

    CodeTask(const string& taskCode) : code(taskCode) {}
};

// Data structures
map<string, string> userCredentials;
map<string, string> securityQuestions;
map<string, vector<Task>> userPersonalTasks;
map<string, vector<Task>> userCollegeTasks;
map<string, vector<CodeTask>> userCodeTasks;
map<string, queue<string>> userNotifications;
map<string, stack<string>> userReminders;

class CodeStorage
{
public:
    CodeStorage() : root(nullptr) {}

    void insert(const string& code)
    {
        root = insertCode(root, code);
    }

    void display()
    {
        displayCode(root);
    }

private:
    struct TreeNode
    {
        string code;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const string& code) : code(code), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* insertCode(TreeNode* node, const string& code)
    {
        if (node == nullptr)
        {
            return new TreeNode(code);
        }

        if (code < node->code)
        {
            node->left = insertCode(node->left, code);
        }
        else
        {
            node->right = insertCode(node->right, code);
        }

        return node;
    }

    void displayCode(TreeNode* node)
    {
        if (node != nullptr)
        {
            displayCode(node->left);
            cout << node->code << "\n";
            displayCode(node->right);
        }
    }
};

// Function to save user data
void saveUserData()
{
    ofstream credentialsFile("credentials.txt");
    for (const auto& entry : userCredentials)
    {
        credentialsFile << entry.first << " " << entry.second << "\n";
    }
    credentialsFile.close();

    ofstream securityQuestionsFile("security_questions.txt");
    for (const auto& entry : securityQuestions)
    {
        securityQuestionsFile << entry.first << " " << entry.second << "\n";
    }
    securityQuestionsFile.close();

    ofstream personalTasksFile("personal_tasks.txt");
    for (const auto& entry : userPersonalTasks)
    {
        for (const Task& task : entry.second)
        {
            personalTasksFile << entry.first << " " << task.name << " " << task.deadline << " " << task.isCompleted << "\n";
        }
    }
    personalTasksFile.close();

    ofstream collegeTasksFile("college_tasks.txt");
    for (const auto& entry : userCollegeTasks)
    {
        for (const Task& task : entry.second)
        {
            collegeTasksFile << entry.first << " " << task.name << " " << task.deadline << " " << task.isCompleted << "\n";
        }
    }
    collegeTasksFile.close();

    ofstream codeTasksFile("code_tasks.txt");
    for (const auto& entry : userCodeTasks)
    {
        for (const CodeTask& codeTask : entry.second)
        {
            codeTasksFile << entry.first << " " << codeTask.code << "\n";
        }
    }
    codeTasksFile.close();

    ofstream notificationsFile("notifications.txt");
    for (auto& entry : userNotifications)
    {
        while (!entry.second.empty())
        {
            notificationsFile << entry.first << " " << entry.second.front() << "\n";
            entry.second.pop();
        }
    }
    notificationsFile.close();

    ofstream remindersFile("reminders.txt");
    for (auto& entry : userReminders)
    {
        while (!entry.second.empty())
        {
            remindersFile << entry.first << " " << entry.second.top() << "\n";
            entry.second.pop();
        }
    }
    remindersFile.close();
}

// Function to load user data
void loadUserData()
{
    ifstream credentialsFile("credentials.txt");
    string username, password;
    while (credentialsFile >> username >> password)
    {
        userCredentials[username] = password;
    }
    credentialsFile.close();

    ifstream securityQuestionsFile("security_questions.txt");
    while (securityQuestionsFile >> username >> password)
    {
        securityQuestions[username] = password;
    }
    securityQuestionsFile.close();

    ifstream personalTasksFile("personal_tasks.txt");
    string taskUsername, taskName, taskDeadline;
    bool isCompleted;
    while (personalTasksFile >> taskUsername >> taskName >> taskDeadline >> isCompleted)
    {
        userPersonalTasks[taskUsername].emplace_back(taskName, taskDeadline, isCompleted);
    }
    personalTasksFile.close();

    ifstream collegeTasksFile("college_tasks.txt");
    while (collegeTasksFile >> taskUsername >> taskName >> taskDeadline >> isCompleted)
    {
        userCollegeTasks[taskUsername].emplace_back(taskName, taskDeadline, isCompleted);
    }
    collegeTasksFile.close();

    ifstream codeTasksFile("code_tasks.txt");
    string codeTaskUsername, code;
    while (codeTasksFile >> codeTaskUsername >> code)
    {
        userCodeTasks[codeTaskUsername].emplace_back(code);
    }
    codeTasksFile.close();

    ifstream notificationsFile("notifications.txt");
    string notificationUsername, notification;
    while (notificationsFile >> notificationUsername >> notification)
    {
        userNotifications[notificationUsername].push(notification);
    }
    notificationsFile.close();

    ifstream remindersFile("reminders.txt");
    string reminderUsername, reminder;
    while (remindersFile >> reminderUsername >> reminder)
    {
        userReminders[reminderUsername].push(reminder);
    }
    remindersFile.close();
}

int main()
{
    loadUserData();

    int choice;
    string username, password;
    string newPassword;
    string answer;

    while (true)
    {
        cout << "Welcome to the Task Manager!" << endl;
        cout << "1. Log in" << endl;
        cout << "2. Register" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (userCredentials.find(username) != userCredentials.end() && userCredentials[username] == password)
            {
                cout << "Registeration successful!" << endl;
                break;
            }
            else
            {
                cout << "Invalid credentials. Please try again." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "Enter a new username: ";
            cin >> username;
            cout << "Enter a new password: ";
            cin >> password;

            userCredentials[username] = password;

            // Set a security question for password recovery
            cout << "Set a security question: ";
            cin.ignore();  // Clear the newline character from the buffer
            getline(cin, answer);
            securityQuestions[username] = answer;

            cout << "Sign up successful!" << endl;
            break;
        }
        else if (choice == 3)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    while (true)
    {
        cout << "Main Menu" << endl;
        cout << "1. Personal Tasks" << endl;
        cout << "2. College Tasks" << endl;
        cout << "3. Code Tasks" << endl;
        cout << "4. Notifications" << endl;
        cout << "5. Reminders" << endl;
        cout << "6. Change Password" << endl;
        cout << "7. Log Out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            while (true)
            {
                cout << "Personal Tasks Menu" << endl;
                cout << "1. Add Task" << endl;
                cout << "2. View Tasks" << endl;
                cout << "3. Mark Task as Completed" << endl;
                cout << "4. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    string taskName, taskDeadline;
                    cout << "Enter task name: ";
                    cin.ignore();
                    getline(cin, taskName);
                    cout << "Enter task deadline: ";
                    getline(cin, taskDeadline);
                    userPersonalTasks[username].emplace_back(taskName, taskDeadline, false);
                    saveUserData();
                    cout << "Task added successfully!" << endl;
                }
                else if (choice == 2)
                {
                    cout << "Personal Tasks:" << endl;
                    for (const Task& task : userPersonalTasks[username])
                    {
                        cout << "Task: " << task.name << " | Deadline: " << task.deadline << " | Completed: " << (task.isCompleted ? "Yes" : "No") << endl;
                    }
                }
                else if (choice == 3)
                {
                    cout << "Personal Tasks:" << endl;
                    for (int i = 0; i < userPersonalTasks[username].size(); i++)
                    {
                        cout << i + 1 << ". Task: " << userPersonalTasks[username][i].name << " | Deadline: " << userPersonalTasks[username][i].deadline << " | Completed: " << (userPersonalTasks[username][i].isCompleted ? "Yes" : "No") << endl;
                    }
                    cout << "Enter the task number to mark as completed: ";
                    int taskNumber;
                    cin >> taskNumber;
                    if (taskNumber >= 1 && taskNumber <= userPersonalTasks[username].size())
                    {
                        userPersonalTasks[username][taskNumber - 1].isCompleted = true;
                        saveUserData();
                        cout << "Task marked as completed!" << endl;
                    }
                    else
                    {
                        cout << "Invalid task number." << endl;
                    }
                }
                else if (choice == 4)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else if (choice == 2)
        {
            // College Tasks Menu
            while (true)
            {
                cout << "College Tasks Menu" << endl;
                cout << "1. Add Task" << endl;
                cout << "2. View Tasks" << endl;
                cout << "3. Mark Task as Completed" << endl;
                cout << "4. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    string taskName, taskDeadline;
                    cout << "Enter task name: ";
                    cin.ignore();
                    getline(cin, taskName);
                    cout << "Enter task deadline: ";
                    getline(cin, taskDeadline);
                    userCollegeTasks[username].emplace_back(taskName, taskDeadline, false);
                    saveUserData();
                    cout << "Task added successfully!" << endl;
                }
                else if (choice == 2)
                {
                    cout << "College Tasks:" << endl;
                    for (const Task& task : userCollegeTasks[username])
                    {
                        cout << "Task: " << task.name << " | Deadline: " << task.deadline << " | Completed: " << (task.isCompleted ? "Yes" : "No") << endl;
                    }
                }
                else if (choice == 3)
                {
                    cout << "College Tasks:" << endl;
                    for (int i = 0; i < userCollegeTasks[username].size(); i++)
                    {
                        cout << i + 1 << ". Task: " << userCollegeTasks[username][i].name << " | Deadline: " << userCollegeTasks[username][i].deadline << " | Completed: " << (userCollegeTasks[username][i].isCompleted ? "Yes" : "No") << endl;
                    }
                    cout << "Enter the task number to mark as completed: ";
                    int taskNumber;
                    cin >> taskNumber;
                    if (taskNumber >= 1 && taskNumber <= userCollegeTasks[username].size())
                    {
                        userCollegeTasks[username][taskNumber - 1].isCompleted = true;
                        saveUserData();
                        cout << "Task marked as completed!" << endl;
                    }
                    else
                    {
                        cout << "Invalid task number." << endl;
                    }
                }
                else if (choice == 4)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else if (choice == 3)
        {
            // Code Tasks Menu
            while (true)
            {
                cout << "Code Tasks Menu" << endl;
                cout << "1. Add Task" << endl;
                cout << "2. View Tasks" << endl;
                cout << "3. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    string code;
                    cout << "Enter the code task: ";
                    cin.ignore();
                    getline(cin, code);
                    userCodeTasks[username].emplace_back(code);
                    saveUserData();
                    cout << "Code task added successfully!" << endl;
                }
                else if (choice == 2)
                {
                    cout << "Code Tasks:" << endl;
                    //for (const string& code : userCodeTasks[username])
                    {
                       // cout << code << endl;
                    }
                }
                else if (choice == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else if (choice == 4)
        {
            // Notifications Menu
            while (true)
            {
                cout << "Notifications Menu" << endl;
                cout << "1. View Notifications" << endl;
                cout << "2. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    cout << "Notifications:" << endl;
                    while (!userNotifications[username].empty())
                    {
                        cout << userNotifications[username].front() << endl;
                        userNotifications[username].pop();
                    }
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else if (choice == 5)
        {
            // Reminders Menu
            while (true)
            {
                cout << "Reminders Menu" << endl;
                cout << "1. View Reminders" << endl;
                cout << "2. Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    cout << "Reminders:" << endl;
                    while (!userReminders[username].empty())
                    {
                      //  cout << userReminders[username].front() << endl;
                        userReminders[username].pop();
                    }
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else if (choice == 6)
        {
            // Change Password
            cout << "Enter your current password: ";
            cin >> password;

            if (userCredentials[username] == password)
            {
                cout << "Enter your new password: ";
                cin >> newPassword;
                userCredentials[username] = newPassword;
                saveUserData();
                cout << "Password changed successfully!" << endl;
            }
            else
            {
                cout << "Invalid password. Password change failed." << endl;
            }
        }
        else if (choice == 7)
        {
            cout << "Logging out..." << endl;
            saveUserData();
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
