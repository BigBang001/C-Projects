<h3 align="center">Task Master: Personal Task Management System</h3>

<p align="center">
  <em>Empower yourself with Task Master, a comprehensive personal task management system designed to streamline your daily activities and enhance productivity. Seamlessly organize your tasks, set deadlines, and receive timely reminders, all within a user-friendly interface.</em>
</p>


### Purpose

Task Master is developed with the following objectives in mind:

1. **Efficient Task Management:** Enable users to efficiently manage their personal tasks by providing features for task creation, organization, and tracking.

2. **Deadline Management:** Facilitate effective deadline management by allowing users to set deadlines for their tasks and receive reminders to ensure timely completion.

3. **Enhanced Productivity:** Enhance user productivity by providing a centralized platform for task management, reducing the likelihood of missed deadlines and overlooked tasks.


### Key Features

- **User Authentication and Registration:** Users can log in with existing credentials or register with a new username and password. Security questions can be set during registration for password recovery.

- **Task Management:** Users can manage personal tasks and college tasks separately. Features include adding tasks, viewing tasks, and marking tasks as completed. Tasks are stored with their names, deadlines, and completion status.

- **Code Task Management:** Users can manage code-related tasks separately. Features include adding code tasks and viewing code tasks.

- **Password Change:** Users can change their passwords after successful authentication.

- **Data Persistence:** User data, including credentials, tasks, notifications, and reminders, are stored in text files. Data is loaded upon program startup and saved upon user interaction to maintain persistence across sessions.

- **Menu-Based User Interface:** Users interact with the system through a menu-based command-line interface. Menus guide users through various features and options available in the system.


### Technical Details

- **Programming Language:** C++
- **Libraries Used:** STL (Standard Template Library)
- **Data Structures:** Maps, Queues, Stacks, Structs
- **File Handling:** Read/write user data to/from text files

### Registration and Login

- Task Master does not provide a default username and password. Users need to register or log in with their own chosen credentials.


### How to Use

1. **Clone the Repository:**

   git clone https://github.com/BigBang001/task-genius.git
   
3. **Navigate to the Task Master Directory:**

   cd task-master
   
4. **Compile and Run the Application:**

   g++ task_master.cpp -o task_genius./task_genius
   

### Contributing
If you'd like to contribute to the Task Master project, please follow these steps:

1. Fork the repository.
2. Create a new branch: git checkout -b feature/new-feature.
3. Make your changes and commit them: git commit -m "Add new feature".
4. Push to the branch: git push origin feature/new-feature.
5. Create a pull request.
