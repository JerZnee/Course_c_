#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    [[nodiscard]] const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return user.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person){
        user[person][TaskStatus::NEW]++;
    }

    // Функция для удаления нулей из словаря
    static void RemoveZeros(TasksInfo& tasks_info) {
        // Соберём те статусы, которые нужно убрать из словаря
        vector<TaskStatus> statuses_to_remove;
        for (const auto& task_item : tasks_info) {
            if (task_item.second == 0) {
                statuses_to_remove.push_back(task_item.first);
            }
        }
        for (const TaskStatus status : statuses_to_remove) {
            tasks_info.erase(status);
        }
    }

    // Обновить статусы по данному количеству задач конкретного разработчика
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){
            TasksInfo updated_tasks, untouched_tasks;
        // В std::map оператор [] в случае отсутствия ключа инициализирует значение по умолчанию
            TasksInfo& tasks = user[person];


            for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
                // Считаем обновлённые
                updated_tasks[Next(status)] = min(task_count, tasks[status]);
                // Считаем, сколько осталось обновить
                task_count -= updated_tasks[Next(status)];
            }

            // Обновляем статус текущих задач в соответствии с информацией об обновлённых
            for (TaskStatus status = TaskStatus::NEW;
                 status != TaskStatus::DONE;
                 status = Next(status)) {
                untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
                tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
            }
            // По условию DONE задачи не нужно возвращать в не обновлённых задачах
            tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

            // По условию в словарях не должно быть нулей
            RemoveZeros(updated_tasks);
            RemoveZeros(untouched_tasks);
            return {updated_tasks, untouched_tasks};
    }

private:
    map <string, TasksInfo> user;
};




// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
